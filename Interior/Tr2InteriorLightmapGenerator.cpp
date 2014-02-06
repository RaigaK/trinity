////////////////////////////////////////////////////////////
//
//    Created:   August 2011
//    Copyright: CCP 2011
//

#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "Tr2InteriorLightmapGenerator.h"
#include "Tr2Mesh.h"
#include "Tr2ShaderMaterial.h"
#include "Tr2VariableStore.h"
#include "Tr2Renderer.h"
#include "TriRenderBatch.h"
#include "include/ITr2Interior.h"
#include "Tr2DxtCompressor.h"
#include "Tr2InteriorStatic.h"
#include "Tr2HostBitmap.h"
#include "Tr2PushPopDS.h"

using namespace Tr2RenderContextEnum;

// --------------------------------------------------------------------------------------
// Description:
//   Tr2InteriorBoxLight default constructor
// --------------------------------------------------------------------------------------
Tr2InteriorLightmapGenerator::Tr2InteriorLightmapGenerator( IRoot* lockobj )
:	m_outputFormat( ARGB16F ),
	m_visualization( NONE ),
	m_renormalizationConstant( 1.f ),
	m_generateMipMaps( true )
{
}

// --------------------------------------------------------------------------------------
// Description:
//   Adds a light source to a list of light that are used for lightmap baking.  
// Arguments:
//   light - A light source to add
// --------------------------------------------------------------------------------------
void Tr2InteriorLightmapGenerator::AddLightSource( ITr2InteriorLight* light )
{
	m_lights.push_back( light );
}

// --------------------------------------------------------------------------------------
// Description:
//   Bakes lighting into a new lightmap.  
// Arguments:
//   contents - A list of meshes and their areas. The lightmap is generated for all of 
//		these given areas
//   transform - Model to world space transform for the given contents
//   width - Width of the resulting lightmap
//   height - Height of the resulting lightmap
//   lightmapResult - Lightmap result. The texture is created by this function and will
//		not survive lost device
//   renderContext - Current render context
// Return Value:
//   true If lightmap is succesfully created
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2InteriorLightmapGenerator::BakeLighting( std::vector<BakeContents>& contents, 
												 const Matrix& transform, 
												 unsigned width, 
												 unsigned height, 
												 Tr2HostBitmapPtr& lightmapResult,
												 Tr2RenderContext& renderContext )
{
	if( contents.empty() )
	{
		return false;
	}

	lightmapResult = nullptr;

	Tr2RenderTargetAL lightmap;
	Tr2RenderTargetAL positions;
	Tr2RenderTargetAL normals;

	{
		USE_MAIN_THREAD_RENDER_CONTEXT();

		CR_RETURN_VAL( 
			positions.Create(	width, 
								height, 
								1, 
								PIXEL_FORMAT_R16G16B16A16_FLOAT, 
								1, 
								0, 
								renderContext )
			, false );

		CR_RETURN_VAL( 
			normals.Create(		width, 
								height, 
								1, 
								PIXEL_FORMAT_R16G16B16A16_FLOAT, 
								1, 
								0, 
								renderContext )
			, false );

		CR_RETURN_VAL( 
			lightmap.Create(	width, 
								height, 
								m_generateMipMaps ? 0 : 1, 
								PIXEL_FORMAT_R16G16B16A16_FLOAT, 
								1, 
								0, 
								renderContext )
			, false );
	}

	GlobalStore().RegisterVariable( "BakeLightingTransform", transform );

	renderContext.m_esm.BeginManagedRendering();
	ON_BLOCK_EXIT( [&]{ renderContext.m_esm.EndManagedRendering(); } );
	
	Tr2PushPopDS pushPopDS( nullDS, renderContext );

	if( !GenerateGBuffer( contents, positions, normals, renderContext ) )
	{
		return false;
	}

	GlobalStore().RegisterVariable( "BakeLightingPositions", &positions.GetTexture() );
	GlobalStore().RegisterVariable( "BakeLightingNormals", &normals.GetTexture() );

	if( !GenerateEmissiveLightmap( contents, transform, lightmap, renderContext ) )
	{
		return false;
	}

	if( !GenerateLightmap( lightmap, renderContext ) )
	{
		return false;
	}

	GlobalStore().RegisterPlaceholderTextureVariable( "BakeLightingPositions" );
	GlobalStore().RegisterPlaceholderTextureVariable( "BakeLightingNormals" );

	if( m_generateMipMaps && m_visualization == NONE )
	{
		CR_RETURN_VAL( lightmap.GenerateMipMaps( renderContext ), false );
	}

	// copy into a lockable texture
	Tr2RenderTargetAL* finalLightmap;
	switch( m_visualization )
	{
	case POSITIONS:
		finalLightmap = &positions;
		break;
	case NORMALS:
		finalLightmap = &normals;
		break;
	default:
		finalLightmap = &lightmap;
	}

	renderContext.m_esm.ApplyStandardStates( Tr2EffectStateManager::RM_FULLSCREEN );

	Tr2HostBitmapPtr lockableLightmap;
	lockableLightmap.CreateInstance();
	CR_RETURN_VAL( lockableLightmap->Create( width, height, m_generateMipMaps ? 0 : 1, PIXEL_FORMAT_R16G16B16A16_FLOAT ), false );
	if( !lockableLightmap->CopyFromRenderTarget( *finalLightmap, renderContext ) )
	{
		return false;
	}

	if( m_outputFormat == ARGB16F || m_visualization != NONE )
	{
		lightmapResult = lockableLightmap;
	}
	else
	{
		// convert to LRB
		Tr2HostBitmapPtr lightmap8bpp;
		lightmap8bpp.CreateInstance();
		CR_RETURN_VAL( lightmap8bpp->Create( width, height, m_generateMipMaps ? 0 : 1, PIXEL_FORMAT_B8G8R8A8_UNORM ), false );
		m_renormalizationConstant = 1.0f;
		if( !ConvertToLRB( lockableLightmap, lightmap8bpp ) )
		{
			return false;
		}
		if( m_outputFormat == LRB8 )
		{
			lightmapResult = lightmap8bpp;
		}
		else
		{
			// Compress to DXT5
			Tr2HostBitmapPtr compressedLightmap;
			compressedLightmap.CreateInstance();
			CR_RETURN_VAL( compressedLightmap->Create( width, height, m_generateMipMaps ? 0 : 1, PIXEL_FORMAT_BC5_UNORM ), false );
			for( unsigned i = 0; i < lightmap8bpp->GetTrueMipCount(); ++i )
			{
				unsigned width = lightmap8bpp->GetMipWidth( i );
				unsigned height = lightmap8bpp->GetMipHeight( i );

				ptrdiff_t count = 0;
				bool cancel = false;
				Tr2DxtCompressSurface( 
					TR2DXT_COMPRESS_SQUISH_DXT5, 
					reinterpret_cast<unsigned char*>( lightmap8bpp->GetMipRawData( i ) ),
					width,
					height,
					reinterpret_cast<unsigned char*>( compressedLightmap->GetMipRawData( i ) ), 
					width * 16, 
					cancel, 
					TR2DXT_COMPRESS_SQ_UNIFORM );
			}
			lightmapResult = compressedLightmap;
		}

	}

	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Converts given texture into LRB format. Function sets m_renormalizationConstant
//   varible to the renormalization factor for the largets mip map of the source texture.
// Arguments:
//   source - A texture to convert into LRB format. The texture is assumed to have
//		ARGB16F format
//   destination - Result of LRB conversion. The texture is assumed to have
//		ARGB8 format
// Return Value:
//   true If texture is succesfully converted
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2InteriorLightmapGenerator::ConvertToLRB( Tr2HostBitmap* source, 
												 Tr2HostBitmap* destination )
{
	m_renormalizationConstant = 0;
	for( unsigned level = 0; level < source->GetTrueMipCount(); ++level )
	{
		unsigned width = source->GetMipWidth( level );
		unsigned height = source->GetMipHeight( level );

		void* inputData = source->GetMipRawData( level );
		unsigned inputPitch = source->GetMipPitch( level );
		void* outputData = destination->GetMipRawData( level );
		unsigned outputPitch = destination->GetMipPitch( level );

		if( level == 0 )
		{
			// find maximum intensity (renormalization constant) for the texture
			char *row = reinterpret_cast<char*>( inputData );
			for( unsigned j = 0; j < height; ++j )
			{
				D3DXVECTOR4_16F* data = reinterpret_cast<D3DXVECTOR4_16F*>( row );
				for( unsigned i = 0; i < width; ++i )
				{
					m_renormalizationConstant = std::max( m_renormalizationConstant, 
						float( data[i].x ) + float( data[i].y ) + float( data[i].z ) );
				}
				row += inputPitch;
			}
			if( m_renormalizationConstant == 0 )
			{
				m_renormalizationConstant = 1;
			}
		}
		// pack into LRB format
		char *row = reinterpret_cast<char*>( inputData );
		char *outputRow = reinterpret_cast<char*>( outputData );
		for( unsigned j = 0; j < height; ++j )
		{
			D3DXVECTOR4_16F* data = reinterpret_cast<D3DXVECTOR4_16F*>( row );
			unsigned* outputData = reinterpret_cast<unsigned*>( outputRow );
			for( unsigned i = 0; i < width; ++i )
			{
				float r = std::max( float( data[i].x ), 0.f ) / m_renormalizationConstant;
				float g = std::max( float( data[i].y ), 0.f ) / m_renormalizationConstant;
				float b = std::max( float( data[i].z ), 0.f ) / m_renormalizationConstant;

				float intensity = ( r + g + b );
				int outr, outb;
				if( intensity == 0 )
				{
					outr = outb = 85;
				}
				else
				{
					outr = int( r / intensity * 255 );
					outb = int( b / intensity * 255 );
				}
				unsigned intIntensity = unsigned( intensity * 65535 );
				int outa = intIntensity & 0xff;
				int outg = intIntensity >> 8;
				outputData[i] = outa << 24 | outr << 16 | outg << 8 | outb;
			}
			row += inputPitch;
			outputRow += outputPitch;
		}
	}
	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Generates GBuffer (position and normal texture) from the given set of meshes and mesh
//   areas.  
// Arguments:
//   contents - A list of object, meshes and their areas. The GBuffer is generated for
//		all of these given areas
//   positions - Render target to write positions to
//   normals - Render target to write normals to
//   renderContext - Current render context
// Return Value:
//   true If GBuffer is succesfully generated
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2InteriorLightmapGenerator::GenerateGBuffer( std::vector<BakeContents>& contents, 
												    Tr2RenderTargetAL& positions, 
													Tr2RenderTargetAL& normals,
													Tr2RenderContext& renderContext )
{
	renderContext.m_esm.ApplyStandardStates( Tr2EffectStateManager::RM_FULLSCREEN );

	Tr2Renderer::PushRenderTarget( positions, 0, renderContext );
	ON_BLOCK_EXIT( [&]{ Tr2Renderer::PopRenderTarget( 0, renderContext ); } );
	Tr2Renderer::PushRenderTarget( normals, 1, renderContext );
	ON_BLOCK_EXIT( [&]{ Tr2Renderer::PopRenderTarget( 1, renderContext ); } );

	const char* situationName = "GeneratePositionNormals";

	std::string name = " ";
	name += situationName;

	for( std::vector<BakeContents>::iterator mesh = contents.begin(); mesh != contents.end(); ++mesh )
	{
		for( std::vector<Tr2MeshArea*>::iterator it = mesh->areas.begin(); it != mesh->areas.end(); ++it )
		{
			Tr2ShaderMaterial* material = dynamic_cast<Tr2ShaderMaterial*>( ( *it )->GetMaterialInterface() );
			
			std::string situation = material->GetDefaultSituationString();
			material->SetDefaultSituationString( ( situation + name ).c_str() );
		}
	}
	std::vector<unsigned int> localFlags;
	for( std::vector<BakeContents>::iterator mesh = contents.begin(); mesh != contents.end(); ++mesh )
	{
		mesh->mesh->BindLowLevelShaders( localFlags );
	}

	// Render the object.
	TriPoolAllocator* allocator = Tr2Renderer::GetPoolAllocator();
	ITriRenderBatchAccumulator* batches = CCP_NEW( "Tr2InteriorLightingBake/batches" ) TriRenderBatchAccumulator<>( allocator );

	for( std::vector<BakeContents>::iterator mesh = contents.begin(); mesh != contents.end(); ++mesh )
	{
		for( std::vector<Tr2MeshArea*>::iterator it = mesh->areas.begin(); it != mesh->areas.end(); ++it )
		{
			Tr2MeshArea* area = *it;
			ITr2ShaderMaterial* shadMat = area->GetMaterialInterface();

			if( area->IsHidden())
			{
				continue;
			}

			if( !shadMat )
			{
				continue;
			}

			TriGeometryBatch* batch = batches->Allocate<TriGeometryBatch>();
			// Note that this can fail if the accumulator can't add more batches!
			if( batch )
			{
				batch->SetShaderMaterial( shadMat );
				batch->SetPerObjectData( NULL );
				batch->SetGeometryResource( mesh->mesh->GetGeometryResource() );
				batch->SetMeshParameters( mesh->mesh->GetMeshIndex(), area->GetIndex(), area->GetCount(), area->GetReversed() );

				batches->Commit( batch );
			}
		}
	}

	renderContext.m_esm.RenderBatches( batches );

	batches->Clear();
	CCP_DELETE batches;

	// Restore original material situations.
	size_t len = name.length();
	for( std::vector<BakeContents>::iterator mesh = contents.begin(); mesh != contents.end(); ++mesh )
	{
		for( std::vector<Tr2MeshArea*>::iterator it = mesh->areas.begin(); it != mesh->areas.end(); ++it )
		{
			Tr2ShaderMaterial* material = dynamic_cast<Tr2ShaderMaterial*>( ( *it )->GetMaterialInterface() );
			
			std::string situation = material->GetDefaultSituationString();
				material->SetDefaultSituationString( situation.substr( 0, situation.length() - len ).c_str() );
		}
	}

	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Puts emissive and secondary lighting into lightmap.  
// Arguments:
//   contents - A list of object, meshes and their areas. The GBuffer is generated for
//		all of these given areas
//   transform - Model to world space transform for the given contents
//   lightmap - Lightmap render target
//   renderContext - Current render context
// Return Value:
//   true If lightmap is succesfully generated
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2InteriorLightmapGenerator::GenerateEmissiveLightmap( std::vector<BakeContents>& contents, 
															 const Matrix& transform,
															 Tr2RenderTargetAL& lightmap,
															 Tr2RenderContext& renderContext )
{
	Tr2Renderer::PushRenderTarget( lightmap, renderContext );
	ON_BLOCK_EXIT( [&]{ Tr2Renderer::PopRenderTarget( renderContext ); } );

	renderContext.m_esm.ApplyStandardStates( Tr2EffectStateManager::RM_LIGHT );

	CR_RETURN_VAL( renderContext.Clear( CLEARFLAGS_TARGET, 0, 0, 0 ), false );

	const char* situationName = "GenerateEmissiveLightmap";

	std::string name = " ";
	name += situationName;

	for( std::vector<BakeContents>::iterator mesh = contents.begin(); mesh != contents.end(); ++mesh )
	{
		for( std::vector<Tr2MeshArea*>::iterator it = mesh->emissiveAreas.begin(); it != mesh->emissiveAreas.end(); ++it )
		{
			Tr2ShaderMaterial* material = dynamic_cast<Tr2ShaderMaterial*>( ( *it )->GetMaterialInterface() );
			
			std::string situation = material->GetDefaultSituationString();
			material->SetDefaultSituationString( ( situation + name ).c_str() );
		}
	}
	std::vector<unsigned int> localFlags;
	for( std::vector<BakeContents>::iterator mesh = contents.begin(); mesh != contents.end(); ++mesh )
	{
		if( Tr2InteriorStatic* staticObject = dynamic_cast<Tr2InteriorStatic*>( mesh->object ) )
		{
			staticObject->BindLowLevelShaders();
		}
		else
		{
			mesh->mesh->BindLowLevelShaders( localFlags );
		}
	}

	// Render the object.
	TriPoolAllocator* allocator = Tr2Renderer::GetPoolAllocator();
	ITriRenderBatchAccumulator* batches = CCP_NEW( "Tr2InteriorLightingBake/batches" ) TriRenderBatchAccumulator<>( allocator );

	for( std::vector<BakeContents>::iterator mesh = contents.begin(); mesh != contents.end(); ++mesh )
	{
		Tr2PerObjectData* perObjectData = NULL;
		if( mesh->object )
		{
			perObjectData = mesh->object->GetPerObjectDataWithPerInstanceLighting( batches, NULL, transform, transform );
		}
		for( std::vector<Tr2MeshArea*>::iterator it = mesh->emissiveAreas.begin(); it != mesh->emissiveAreas.end(); ++it )
		{
			Tr2MeshArea* area = *it;
			ITr2ShaderMaterial* shadMat = area->GetMaterialInterface();

			if( area->IsHidden())
			{
				continue;
			}

			if( !shadMat )
			{
				continue;
			}

			TriGeometryBatch* batch = batches->Allocate<TriGeometryBatch>();
			// Note that this can fail if the accumulator can't add more batches!
			if( batch )
			{
				batch->SetShaderMaterial( shadMat );
				batch->SetPerObjectData( perObjectData );
				batch->SetGeometryResource( mesh->mesh->GetGeometryResource() );
				batch->SetMeshParameters( mesh->mesh->GetMeshIndex(), area->GetIndex(), area->GetCount(), area->GetReversed() );

				batches->Commit( batch );
			}
		}
	}

	renderContext.m_esm.RenderBatches( batches );

	batches->Clear();
	CCP_DELETE batches;

	// Restore original material situations.
	size_t len = name.length();
	for( std::vector<BakeContents>::iterator mesh = contents.begin(); mesh != contents.end(); ++mesh )
	{
		for( std::vector<Tr2MeshArea*>::iterator it = mesh->emissiveAreas.begin(); it != mesh->emissiveAreas.end(); ++it )
		{
			Tr2ShaderMaterial* material = dynamic_cast<Tr2ShaderMaterial*>( ( *it )->GetMaterialInterface() );
			
			std::string situation = material->GetDefaultSituationString();
				material->SetDefaultSituationString( situation.substr( 0, situation.length() - len ).c_str() );
		}
	}

	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Puts primary lighting into ligthmap.  
// Arguments:
//   lightmap - Lightmap texture
//   renderContext - Current render context
// Return Value:
//   true If lightmap is succesfully generated
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2InteriorLightmapGenerator::GenerateLightmap( Tr2RenderTargetAL& lightmap, 
													 Tr2RenderContext& renderContext )
{
	Tr2Renderer::PushRenderTarget( lightmap, renderContext );
	ON_BLOCK_EXIT( [&]{ Tr2Renderer::PopRenderTarget( renderContext ); } );

	renderContext.m_esm.ApplyStandardStates( Tr2EffectStateManager::RM_LIGHT );

	TriPoolAllocator* allocator = Tr2Renderer::GetPoolAllocator();
	ITriRenderBatchAccumulator* batches = CCP_NEW( "Tr2InteriorLightingBake/batches" ) TriRenderBatchAccumulator<>( allocator );

	for( std::vector<ITr2InteriorLightPtr>::iterator it = m_lights.begin(); it != m_lights.end(); ++it )
	{
		( *it )->GetLightMapBatches( batches );
	}

	renderContext.m_esm.RenderBatches( batches );

	batches->Clear();
	CCP_DELETE batches;

	return true;
}

#endif
