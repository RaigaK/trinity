////////////////////////////////////////////////////////////
//
//    Created:   August 2011
//    Copyright: CCP 2011
//

#pragma once
#ifndef Tr2InteriorLightmapGenerator_H
#define Tr2InteriorLightmapGenerator_H

BLUE_DECLARE( Tr2Mesh );
BLUE_DECLARE_VECTOR( Tr2Mesh );
BLUE_DECLARE( Tr2MeshArea );
BLUE_DECLARE_VECTOR( Tr2MeshArea );
BLUE_DECLARE_INTERFACE( ITr2InteriorLight );
BLUE_DECLARE_INTERFACE( ITr2Interior );
BLUE_DECLARE_IVECTOR( ITr2InteriorLight );
BLUE_DECLARE( Tr2HostBitmap );

// --------------------------------------------------------------------------------------
// Description:
//   Tr2InteriorLightmapGenerator provides methods for baking light maps. Given a set of
//   mesh areas and lights the class generates a lightmap texture for this set of areas.
// --------------------------------------------------------------------------------------
class Tr2InteriorLightmapGenerator : public IRoot
{
public:
	Tr2InteriorLightmapGenerator( IRoot* lockobj = 0 );

	EXPOSE_TO_BLUE();

	// ----------------------------------------------------------------------------------
	// Description:
	//   A mesh and a vector of its areas. A vector of BakeContents is used as an input to
	//   BakeLighting method.
	// ----------------------------------------------------------------------------------
	struct BakeContents
	{
		ITr2Interior* object;
		Tr2Mesh* mesh;
		std::vector<Tr2MeshArea*> areas;
		std::vector<Tr2MeshArea*> emissiveAreas;
	};

	// ----------------------------------------------------------------------------------
	// Description:
	//   Options to output debug information into a lightmap.
	// ----------------------------------------------------------------------------------
	enum DebugVisualization
	{
		// None: output lightmap
		NONE,
		// Output world space positions (always as a ARGB16F texture)
		POSITIONS,
		// Output world space normals (always as a ARGB16F texture)
		NORMALS,
	};

	// ----------------------------------------------------------------------------------
	// Description:
	//   Light map output format.
	// ----------------------------------------------------------------------------------
	enum OutputFormat
	{
		// Unpacked floating point format
		ARGB16F,
		// Packed luminance-red-blue (in ARGB8 texture)
		LRB8,
		// Packed luminance-red-blue (in DXT5 texture)
		DXT5,
	};

	void AddLightSource( ITr2InteriorLight* light );
	void SetOutputFormat( OutputFormat outputFormat );
	void SetDebugVisualization( DebugVisualization visualization );
	bool BakeLighting( std::vector<BakeContents>& contents, 
					   const Matrix& transform, 
					   unsigned width, 
					   unsigned height, 
					   Tr2HostBitmapPtr& lightmap,
					   Tr2RenderContext& renderContext );
private:
	bool GenerateGBuffer( std::vector<BakeContents>& contents, 
						  Tr2RenderTargetAL& positions, 
						  Tr2RenderTargetAL& normals,
						  Tr2RenderContext& renderContext );
	bool GenerateEmissiveLightmap( std::vector<BakeContents>& contents, 
								  const Matrix& transform,
								  Tr2RenderTargetAL& lightmap,
								  Tr2RenderContext& renderContext );
	bool GenerateLightmap( Tr2RenderTargetAL& lightmap, Tr2RenderContext& renderContext );
	bool ConvertToLRB( Tr2HostBitmap* source, Tr2HostBitmap* destination );

	// Vector of light sources to use for baking
	std::vector<ITr2InteriorLightPtr> m_lights;
	// Lightmap format
	OutputFormat m_outputFormat;
	// Visualization option
	DebugVisualization m_visualization;
	// Renormalization factor for LRB output formats
	float m_renormalizationConstant;
	// Generate light map mip maps 
	bool m_generateMipMaps;
};

TYPEDEF_BLUECLASS( Tr2InteriorLightmapGenerator );
BLUE_DECLARE_VECTOR( Tr2InteriorLightmapGenerator );

#endif Tr2InteriorLightmapGenerator_H
