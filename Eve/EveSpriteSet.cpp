#include "StdAfx.h"
#include "EveSpriteSet.h"
#include "Tr2Effect.h"
#include "TriRenderBatch.h"

CCP_STATS_DECLARED_ELSEWHERE( primitiveCount );

using namespace Tr2RenderContextEnum;

struct SpriteVertex
{
	Vector3 m_position;
	uint32_t m_color;
	float m_blinkPhase;
	float m_blinkRate;
	float m_minScale;
	float m_maxScale;
	float m_falloff;
	uint8_t m_index;
	uint8_t m_boneIndex;

	uint8_t m_padding[2];
};

EveSpriteSet::EveSpriteSet( IRoot* lockobj ) :
	PARENTLOCK( m_sprites ),
	m_bytesPerVertex( 0 ),
	m_vertexCount( 0 ),
	m_display( true ),
	m_vertexDeclHandle( Tr2EffectStateManager::UNINITIALIZED_DECLARATION )
{
}

EveSpriteSet::~EveSpriteSet()
{
}

bool EveSpriteSet::Initialize()
{
	PrepareResources();
	return true;
}

void EveSpriteSet::ReleaseResources( TriStorage s )
{
	m_vertexDeclHandle = Tr2EffectStateManager::UNINITIALIZED_DECLARATION;
	m_vertexBuffer.Destroy();
}

bool EveSpriteSet::OnPrepareResources()
{
	if( m_vertexBuffer.IsValid() )
	{
		return true;
	}

	if( m_sprites.empty() )
	{
		return true;
	}

	// register vertex declaration
	static Tr2VertexDefinition s_spriteVertexDecl;
	if( s_spriteVertexDecl.empty() )
	{
		Tr2VertexDefinition& vd = s_spriteVertexDecl;
		vd.Add( vd.FLOAT32_3, vd.POSITION );
		vd.Add( vd.UBYTE_4_NORM , vd.COLOR );
		vd.Add( vd.FLOAT32_1, vd.TEXCOORD, 0 );
		vd.Add( vd.FLOAT32_1, vd.TEXCOORD, 1 );
		vd.Add( vd.FLOAT32_1, vd.TEXCOORD, 2 );
		vd.Add( vd.FLOAT32_1, vd.TEXCOORD, 3 );
		vd.Add( vd.FLOAT32_1, vd.TEXCOORD, 4 );
		vd.Add( vd.UBYTE_4  , vd.TEXCOORD, 5 );
	}

	m_vertexDeclHandle = Tr2EffectStateManager::GetVertexDeclarationHandle( s_spriteVertexDecl );
	if( m_vertexDeclHandle == Tr2EffectStateManager::UNINITIALIZED_DECLARATION )
	{
		return false;
	}

	m_vertexCount = (unsigned int)m_sprites.GetSize() * 6;
	m_bytesPerVertex = sizeof( SpriteVertex );

	std::vector<SpriteVertex> pVerts( m_vertexCount );

	int n = (unsigned int)m_sprites.GetSize();
	for( int i = 0; i < n; ++i )
	{
		for( int j = 0; j < 6; ++j )
		{
			SpriteVertex& vertex = pVerts[i*6 + j];
			vertex.m_position = m_sprites[i]->m_position;
			uint32_t color = m_sprites[i]->m_color;
			vertex.m_color = 
				( ( color & 0xff0000 ) >> 16 ) |
				( color & 0xff00ff00 ) |
				( ( color & 0xff ) << 16 );
			vertex.m_blinkPhase = m_sprites[i]->m_blinkPhase;
			vertex.m_blinkRate = m_sprites[i]->m_blinkRate;
			vertex.m_minScale = m_sprites[i]->m_minScale;
			vertex.m_maxScale = m_sprites[i]->m_maxScale;
			vertex.m_falloff = m_sprites[i]->m_falloff;
			vertex.m_boneIndex = m_sprites[i]->m_boneIndex;
		}

		pVerts[i*6 + 0].m_index = 0;
		pVerts[i*6 + 1].m_index = 2;
		pVerts[i*6 + 2].m_index = 1;

		pVerts[i*6 + 3].m_index = 0;
		pVerts[i*6 + 4].m_index = 3;
		pVerts[i*6 + 5].m_index = 2;
	}

	USE_MAIN_THREAD_RENDER_CONTEXT();
	CR_RETURN_VAL( 
			m_vertexBuffer.Create(	m_vertexCount * m_bytesPerVertex, 
									USAGE_IMMUTABLE, 
									&pVerts[0], 
									renderContext )
			, false );

	return true;
}

void EveSpriteSet::Clear()
{
	m_vertexDeclHandle = Tr2EffectStateManager::UNINITIALIZED_DECLARATION;
	m_vertexBuffer.Destroy();
	m_sprites.Remove(-1);
}

void EveSpriteSet::Add( const Vector3& pos, float blinkRate, float blinkPhase, float minScale, float maxScale, float falloff, Color color )
{
	CCP_ASSERT( minScale < 10000.0f );
	CCP_ASSERT( maxScale < 10000.0f );

	EveSpriteSetItemPtr item;
	item.CreateInstance();

	item->m_position = pos;
	item->m_blinkRate = blinkRate;
	item->m_blinkPhase = blinkPhase;
	item->m_minScale = minScale;
	item->m_maxScale = maxScale;
	item->m_falloff = falloff;
	item->m_color = color;
	item->m_boneIndex = 0;

	Add( item );
}

void EveSpriteSet::Add( const Vector3& pos, float scale, Color color )
{
	Add( pos, 0.0f, 0.0f, scale, scale, 0.0f, color );
}

void EveSpriteSet::Add( EveSpriteSetItemPtr newItem )
{
	m_sprites.Append( newItem );
}

void EveSpriteSet::SubmitGeometry( Tr2RenderContext& renderContext )
{
	renderContext.m_esm.ApplyVertexDeclaration( m_vertexDeclHandle );
	renderContext.m_esm.ApplyStreamSource( 0, m_vertexBuffer, 0, m_bytesPerVertex );
	
	renderContext.SetTopology( TOP_TRIANGLES );
	renderContext.DrawPrimitive( 0, m_vertexCount / 3 );
}

void EveSpriteSet::GetBatches( ITriRenderBatchAccumulator* accumulator, const Tr2PerObjectData* perObjectData )
{
	if( !m_vertexBuffer.IsValid() || !m_effect )
	{
		return;
	}

	if( m_vertexDeclHandle == Tr2EffectStateManager::UNINITIALIZED_DECLARATION )
	{
		return;
	}

	if( !m_display )
	{
		return;
	}

	TriForwardingBatch* batch = accumulator->Allocate<TriForwardingBatch>();
	if( batch )
	{
		batch->SetPerObjectData( perObjectData );
		batch->SetShaderMaterial( m_effect );
		batch->SetGeometryProvider( this );

		accumulator->Commit( batch );
	}
}

EveSpriteSetItemVector* EveSpriteSet::GetSprites()
{
	return &m_sprites;
}

const char* EveSpriteSet::GetName()
{
	return m_name.c_str();
}

Tr2EffectPtr EveSpriteSet::GetEffect()
{
	return m_effect;
}

void EveSpriteSet::SetEffect( Tr2EffectPtr effect )
{
	m_effect = effect;
}

void EveSpriteSet::SetName( const char* name )
{
	m_name = name;
}

// --------------------------------------------------------------------------------
// Description:
//   Rebuild resources after adding/removing/changing individual sprites
// --------------------------------------------------------------------------------
void EveSpriteSet::Rebuild()
{
	ReleaseResources( 0 );
	PrepareResources();
}