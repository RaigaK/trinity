////////////////////////////////////////////////////////////
//
//    Created:   June 2010
//    Copyright: CCP 2010
//

#include "StdAfx.h"
#include "Tr2ShaderParameterDescription.h"
#include "include/ITriEffectParameter.h"

BLUE_DEFINE( Tr2ShaderParameterDescription );
BLUE_DEFINE( Tr2ShaderFloat4Desc );
BLUE_DEFINE( Tr2ShaderFloat3Desc );
BLUE_DEFINE( Tr2ShaderFloat2Desc );
BLUE_DEFINE( Tr2ShaderFloatDesc );
BLUE_DEFINE( Tr2ShaderTexDesc );

const Be::ClassInfo* Tr2ShaderParameterDescription::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ShaderParameterDescription, "" )
		
	MAP_INTERFACE(Tr2ShaderParameterDescription)
	MAP_INTERFACE(IInitialize)

		MAP_ATTRIBUTE
		( 
			"parameterName",      
			m_parameterName,
			"artist friendly name of this setting", 
			Be::READ | Be::PERSIST
		)

		MAP_ATTRIBUTE
		( 
			"name",      
			m_artistName,
			"artist friendly name of this setting", 
			Be::READ | Be::PERSIST
		)

		MAP_ATTRIBUTE
		( 
			"helpText",      
			m_helpText,
			"special instructions for this shader perhaps even a URL to a help pages", 
			Be::READ | Be::PERSIST
		)

		MAP_ATTRIBUTE
		( 
			"section",      
			m_sectionName,
			"grouping/section name for this parameter.", 
			Be::READ | Be::PERSIST
		)

	EXPOSURE_END()
}

const Be::ClassInfo* Tr2ShaderFloat4Desc::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ShaderFloat4Desc, "" )
		
	MAP_INTERFACE(Tr2ShaderParameterDescription)
	MAP_INTERFACE(Tr2ShaderFloat4Desc)
	MAP_INTERFACE(IInitialize)

	MAP_ATTRIBUTE
	(
		"defaultValue",
		m_defaultValue,
		"Default value",
		Be::READWRITE | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"minimumValue",
		m_minimumValue,
		"Minimum value",
		Be::READWRITE | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"maximumValue",
		m_maximumValue,
		"Maximum value",
		Be::READWRITE | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"isColor",
		m_isColor,
		"Use the color editor, instead of the vector editor",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"normalize",
		m_normalize,
		"After values are entered, normalize the result",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"thumbnailResPath",
		m_thumbnailResPath,
		"Res-path for surface-style thumbnails",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"valueToNameMethod",
		m_valueToNameMethod,
		"Python method for mapping from a float4 value to a surface-style name",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"nameToValueMethod",
		m_nameToValueMethod,
		"Python method for mapping from a surface-style name to a float4 value",
		Be::READ | Be::PERSIST
	)

	MAP_METHOD_AND_WRAP( "CreateDefaultParameter", CreateDefaultParameter, "CreateDefaultParameter( )" );

	EXPOSURE_CHAINTO(Tr2ShaderParameterDescription)
}

const Be::ClassInfo* Tr2ShaderFloat3Desc::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ShaderFloat3Desc, "" )
		
	MAP_INTERFACE(Tr2ShaderParameterDescription)
	MAP_INTERFACE(Tr2ShaderFloat3Desc)
	MAP_INTERFACE(IInitialize)

	MAP_ATTRIBUTE
	(
		"defaultValue",
		m_defaultValue,
		"Default value",
		Be::READWRITE | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"minimumValue",
		m_minimumValue,
		"Minimum value",
		Be::READWRITE | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"maximumValue",
		m_maximumValue,
		"Maximum value",
		Be::READWRITE | Be::PERSIST
	)
	
	MAP_ATTRIBUTE	
	(
		"isColor",
		m_isColor,
		"use the color editor, instead of the vector editor",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"normalize",
		m_normalize,
		"after values are entered, normalize the result",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"thumbnailResPath",
		m_thumbnailResPath,
		"Res-path for surface-style thumbnails",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"valueToNameMethod",
		m_valueToNameMethod,
		"Python method for mapping from a float3 value to a surface-style name",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"nameToValueMethod",
		m_nameToValueMethod,
		"Python method for mapping from a surface-style name to a float3 value",
		Be::READ | Be::PERSIST
	)

	MAP_METHOD_AND_WRAP( "CreateDefaultParameter", CreateDefaultParameter, "CreateDefaultParameter( )" );

	EXPOSURE_CHAINTO(Tr2ShaderParameterDescription)
}

const Be::ClassInfo* Tr2ShaderFloat2Desc::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ShaderFloat2Desc, "" )
		
	MAP_INTERFACE(Tr2ShaderParameterDescription)
	MAP_INTERFACE(Tr2ShaderFloat2Desc)
	MAP_INTERFACE(IInitialize)

	MAP_ATTRIBUTE
	(
		"defaultValue",
		m_defaultValue,
		"Default value",
		Be::READWRITE | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"minimumValue",
		m_minimumValue,
		"Minimum value",
		Be::READWRITE | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"maximumValue",
		m_maximumValue,
		"Maximum value",
		Be::READWRITE | Be::PERSIST
	)
	
	MAP_ATTRIBUTE
	(
		"normalize",
		m_normalize,
		"after values are entered, normalize the result",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"thumbnailResPath",
		m_thumbnailResPath,
		"Res-path for surface-style thumbnails",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"valueToNameMethod",
		m_valueToNameMethod,
		"Python method for mapping from a float2 value to a surface-style name",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"nameToValueMethod",
		m_nameToValueMethod,
		"Python method for mapping from a surface-style name to a float2 value",
		Be::READ | Be::PERSIST
	)

	MAP_METHOD_AND_WRAP( "CreateDefaultParameter", CreateDefaultParameter, "CreateDefaultParameter( )" );

	EXPOSURE_CHAINTO(Tr2ShaderParameterDescription)
}

const Be::ClassInfo* Tr2ShaderFloatDesc::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ShaderFloatDesc, "" )
		
	MAP_INTERFACE(Tr2ShaderParameterDescription)
	MAP_INTERFACE(Tr2ShaderFloatDesc)
	MAP_INTERFACE(IInitialize)

	MAP_ATTRIBUTE
	(
		"defaultValue",
		m_defaultValue,
		"Default value",
		Be::READWRITE | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"minimumValue",
		m_minimumValue,
		"Minimum value",
		Be::READWRITE | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"maximumValue",
		m_maximumValue,
		"Maximum value",
		Be::READWRITE | Be::PERSIST
	)
	
	MAP_ATTRIBUTE
	(
		"thumbnailResPath",
		m_thumbnailResPath,
		"Res-path for surface-style thumbnails",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"valueToNameMethod",
		m_valueToNameMethod,
		"Python method for mapping from a float value to a surface-style name",
		Be::READ | Be::PERSIST
	)

	MAP_ATTRIBUTE
	(
		"nameToValueMethod",
		m_nameToValueMethod,
		"Python method for mapping from a surface-style name to a float value",
		Be::READ | Be::PERSIST
	)

	MAP_METHOD_AND_WRAP( "CreateDefaultParameter", CreateDefaultParameter, "CreateDefaultParameter( )" );

	EXPOSURE_CHAINTO(Tr2ShaderParameterDescription)
}

const Be::ClassInfo* Tr2ShaderTexDesc::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ShaderTexDesc, "" )
		
	MAP_INTERFACE(Tr2ShaderTexDesc)
	MAP_INTERFACE(IInitialize)
	MAP_INTERFACE(Tr2ShaderParameterDescription)

	MAP_ATTRIBUTE
	(
		"defaultTexture",
		m_defaultValue,
		"Default texture for a new material",
		Be::READ | Be::PERSIST
	)

	MAP_METHOD_AND_WRAP( "CreateDefaultParameter", CreateDefaultParameter, "CreateDefaultParameter( )" );

	EXPOSURE_CHAINTO(Tr2ShaderParameterDescription)
}
