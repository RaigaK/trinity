#include "StdAfx.h"
#include "TriTexture2DParameter.h"
#include "Resources/TriTextureRes.h"

BLUE_DEFINE( TriTexture2DParameter );

extern Be::VarChooser SamplerStateChooser_AddressMode[];
extern Be::VarChooser SamplerStateChooser_FilterMode[];
extern Be::VarChooser SamplerStateChooser_MipFilterMode[];

const Be::ClassInfo* TriTexture2DParameter::ExposeToBlue()
{
	EXPOSURE_BEGIN( TriTexture2DParameter, "" )
		MAP_INTERFACE( ITriEffectParameter )
		MAP_INTERFACE( ITriEffectResourceParameter )
		MAP_INTERFACE( IInitialize )
		MAP_INTERFACE( INotify )
		MAP_INTERFACE( ICopierCustomAssignment )

		////////////////////////////////////////////////////////////////////////////
		//	name
		MAP_ATTRIBUTE
		( 
			"name",    
			m_name,    
			"na", 
			Be::READWRITE | Be::NOTIFY | Be::PERSIST
		)
		////////////////////////////////////////////////////////////////////////////
		//	resource path (texture / buffer)
		// TODO: Add valid chooser
		MAP_ATTRIBUTE_WITH_CHOOSER( 
			"resourcePath",	
			m_resourcePath,				
			"Resource path to .x file", 
			Be::READWRITE | Be::NOTIFY | Be::PERSIST,
			NULL
		)
		////////////////////////////////////////////////////////////////////////////
		MAP_ATTRIBUTE
		(    
			"resource",
			m_resource,
			"na",
			Be::READ
		)
		////////////////////////////////////////////////////////////////////////////
		MAP_ATTRIBUTE("usedByCurrentTechnique", m_isUsedByEffect, "na", Be::READ)
		MAP_ATTRIBUTE("usedByCurrentEffect", m_isUsedByEffect, "na", Be::READ)

		MAP_METHOD_AND_WRAP( "SetResource", SetResource, "Takes a TriTextureRes and sets it directly, without using a resourcePath.")
		MAP_METHOD_AND_WRAP( "GetResourcePath", GetResourcePath, "Returns the respath to the currently used texture. Might be LOD dependent." )

	EXPOSURE_END( )
}

