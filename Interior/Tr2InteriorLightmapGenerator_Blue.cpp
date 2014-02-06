#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "Tr2InteriorLightmapGenerator.h"
#include "include/ITr2Interior.h"
#include "Resources/TriTextureRes.h"
#include "Tr2Mesh.h"
#include "Tr2HostBitmap.h"

BLUE_DEFINE( Tr2InteriorLightmapGenerator );

static Be::VarChooser LightmapVisualizerChooser[] =
{
	{
		"NONE",     
		BeCast( Tr2InteriorLightmapGenerator::NONE ),     
		"No visualizer - output lightmap"
	},
	{
		"POSITIONS",     
		BeCast( Tr2InteriorLightmapGenerator::POSITIONS ),     
		"Output world position in lightmap"
	},
	{
		"NORMALS",     
		BeCast( Tr2InteriorLightmapGenerator::NORMALS ),     
		"Output world normal in lightmap"
	},
	{ 0 }
};

// Register the enum as trinity.Tr2InteriorLightmapVisualization
BLUE_REGISTER_ENUM_EX( "Tr2InteriorLightmapVisualization", 
					  Tr2InteriorLightmapGenerator::DebugVisualization, 
					  LightmapVisualizerChooser, 
					  ENUM_REG_ENUM_OBJECT_ON_MODULE );

static Be::VarChooser LightmapOutputFormatChooser[] =
{
	{
		"ARGB16F",     
		BeCast( Tr2InteriorLightmapGenerator::ARGB16F ),     
		"Unpacked 16 bit per channel lightmap (alpha channel unused)"
	},
	{
		"LRB8",     
		BeCast( Tr2InteriorLightmapGenerator::LRB8 ),     
		"Packed luminance-red-green format (in 8 bits per channel texture)"
	},
	{
		"DXT5",     
		BeCast( Tr2InteriorLightmapGenerator::DXT5 ),     
		"Packed luminance-red-green format (in a DXT5 compressed texture)"
	},
	{ 0 }
};

// Register the enum as trinity.Tr2InteriorLightmapOutputFormat
BLUE_REGISTER_ENUM_EX( "Tr2InteriorLightmapOutputFormat", 
					  Tr2InteriorLightmapGenerator::OutputFormat, 
					  LightmapOutputFormatChooser, 
					  ENUM_REG_ENUM_OBJECT_ON_MODULE );

#if BLUE_WITH_PYTHON
static PyObject* PyBakeLighting( PyObject* self, PyObject* args )
{
	Tr2InteriorLightmapGenerator* pThis = BluePythonCast<Tr2InteriorLightmapGenerator*>( self );

	PyObject* contentsArg = NULL;
	PyObject* transformArg = NULL;
	unsigned width = 0;
	unsigned height = 0;
	if( !PyArg_ParseTuple( args, "OOii", &contentsArg, &transformArg, &width, &height ) )
	{
		return NULL;
	}
	if( !PyList_Check( contentsArg ) )
	{
		return NULL;
	}
	Matrix transform;
	if( !BlueExtractMatrix( transformArg, transform, 16 ) )
	{
		return NULL;
	}
	std::vector<Tr2InteriorLightmapGenerator::BakeContents> contents;
	Py_ssize_t pos = 0;
	for( int j = 0; j < PyList_GET_SIZE( contentsArg ); ++j )
	{
		PyObject* tuple = PyList_GetItem( contentsArg, j );
		PyObject* object, *mesh, *areas, *emissiveAreas;
		if( !PyTuple_Check( tuple ) )
		{
			return NULL;
		}
		Tr2InteriorLightmapGenerator::BakeContents bakeItem;
		if( !PyArg_ParseTuple( tuple, "OOOO", &object, &mesh, &areas, &emissiveAreas ) )
		{
			return NULL;
		}
		bakeItem.object = BluePythonCast<ITr2Interior*>( object );
		bakeItem.mesh = BluePythonCast<Tr2Mesh*>( mesh );
		if( bakeItem.mesh == NULL )
		{
			return NULL;
		}
		if( !PyList_Check( areas ) )
		{
			return NULL;
		}
		unsigned count = (unsigned int)PyList_GET_SIZE( areas );
		for( unsigned i = 0; i < count; ++i )
		{
			PyObject* item = PyList_GetItem( areas, i );
			Tr2MeshArea* area = BluePythonCast<Tr2MeshArea*>( item );
			if( area == NULL )
			{
				return NULL;
			}
			bakeItem.areas.push_back( area );
		}
		if( !PyList_Check( emissiveAreas ) )
		{
			return NULL;
		}
		count = (unsigned int)PyList_GET_SIZE( emissiveAreas );
		for( unsigned i = 0; i < count; ++i )
		{
			PyObject* item = PyList_GetItem( emissiveAreas, i );
			Tr2MeshArea* area = BluePythonCast<Tr2MeshArea*>( item );
			if( area == NULL )
			{
				return NULL;
			}
			bakeItem.emissiveAreas.push_back( area );
		}
		contents.push_back( bakeItem );
	}

	USE_MAIN_THREAD_RENDER_CONTEXT();

	Tr2HostBitmapPtr texture;
	if( !pThis->BakeLighting( contents, transform, width, height, texture, renderContext ) )
	{
		return NULL;
	}

	return PyOS->WrapBlueObject( texture->GetRawRoot() );
}
#endif


const Be::ClassInfo* Tr2InteriorLightmapGenerator::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2InteriorLightmapGenerator, "" )
        MAP_INTERFACE( Tr2InteriorLightmapGenerator )

		MAP_ATTRIBUTE_WITH_CHOOSER( 
			"visualization", 
			m_visualization, 
			"Changes lightmap rendering to a visualizing method instead of normal rendering", 
			Be::READWRITE | Be::ENUM, 
			LightmapVisualizerChooser )

		MAP_ATTRIBUTE_WITH_CHOOSER( 
			"outputFormat", 
			m_outputFormat, 
			"Changes lightmap output format", 
			Be::READWRITE | Be::ENUM, 
			LightmapOutputFormatChooser )

		MAP_ATTRIBUTE( 
			"generateMipMaps", 
			m_generateMipMaps, 
			"Generate mipmaps for the lightmap", 
			Be::READWRITE )

		MAP_ATTRIBUTE( 
			"renormalizationConstant", 
			m_renormalizationConstant, 
			"Renormalization constant for packed lightmap (readonly)", 
			Be::READ )

		MAP_METHOD( 
			"BakeLighting", 
			PyBakeLighting, 
			"Creates a lightmap for specified geometry"
			"\n"
			"\nArguments:"
			"\ncontents - A list of (object, mesh, depthNormalAreas, emissiveAreas) tuples "
			"where object is an ITr2Interior object, mesh - its Tr2Mesh, depthNormalAreas - "
			"a list of meshes depth normal areas and emissiveAreas is a list of opaque areas"
			" (if baking of secondary/emissive lighting is needed)"
			"\ntransform - A world transform for input meshes"
			"\nwidth - Width of the resulting lightmap"
			"\nheight - Height of the resulting lightmap" )

		MAP_METHOD_AND_WRAP( 
			"AddLightSource", 
			AddLightSource, 
			"Adds a light source to be baked into the lightmap"
			"\n"
			"\nArguments:"
			"\nlight - The ITri2InteriorLight to add" )
	EXPOSURE_END()
}

#endif
