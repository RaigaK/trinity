////////////////////////////////////////////////////////////
//
//    Created:   November 2010
//    Copyright: CCP 2010
//

#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "Tr2InteriorDirectionalLight.h"

#include "TriConstants.h"

BLUE_DEFINE( Tr2InteriorDirectionalLight );


static Be::VarChooser ShadowResolutionChooser[] =
{
	{
		"32",     
		BeCast( 32 ),     
		"32"
	},
	{
		"64",     
		BeCast( 64 ),     
		"64"
	},
	{
		"128",     
		BeCast( 128 ),     
		"128"
	},
	{
		"256",     
		BeCast( 256 ),     
		"256"
	},
	{
		"512",     
		BeCast( 512 ),     
		"512"
	},
	{ 0 }
};

static Be::VarChooser ShadowFilterChooser[] =
{
	{
		"None",     
		BeCast( Tr2InteriorDirectionalLight::ST_NONE ),     
		"No shadow"
	},
	{
		"StaticsOnly",     
		BeCast( Tr2InteriorDirectionalLight::ST_STATICS_ONLY ),     
		"Generate shadows from statics only"
	},
	{
		"DynamicOnly",     
		BeCast( Tr2InteriorDirectionalLight::ST_DYNAMICS_ONLY ),     
		"Generate shadows from statics only"
	},
	{
		"All",     
		BeCast( Tr2InteriorDirectionalLight::ST_ALL ),     
		"Generate shadows from statics and dynamics"
	},
	{ 0 }
};

static Be::VarChooser DebugTypeChooser[] =
{
	{
		"WhiteVolumes",     
		BeCast( ITr2InteriorLight::DI_WHITE_VOLUMES ),     
		"Render light as white volume"
	},
	{
		"LightColor",     
		BeCast( ITr2InteriorLight::DI_LIGHT_COLOR ),     
		"Render light using the actual light source color"
	},
	{ 0 }
};

const Be::ClassInfo* Tr2InteriorDirectionalLight::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2InteriorDirectionalLight, "" )
        MAP_INTERFACE( Tr2InteriorDirectionalLight )
        MAP_INTERFACE( IInitialize )
		MAP_INTERFACE( INotify )
		MAP_INTERFACE( ITr2InteriorLight )

		MAP_ATTRIBUTE( "name", m_name, "The name of this interior light source", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "direction", m_direction, "Direction of the light", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "useExplicitBounds", m_useExplicitBounds, "Use explicitely set bounds or automatically generated from all scene cells", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "explicitBoundsMin", m_explicitBoundsMin, "Min explicit bounds", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "explicitBoundsMax", m_explicitBoundsMax, "Max explicit bounds", Be::READWRITE | Be::PERSIST | Be::NOTIFY )

		MAP_ATTRIBUTE( "color", m_color, "The light's color", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "specularIntensity", m_specularIntensity, "Additional specular light intensity multiplier", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "kelvinColor", m_kelvinColor, "Kelvin color temperature", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "useKelvinColor", m_useKelvinColor, "Use Kelvin color or RGB?", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "secondaryLightingMultiplier", m_secondaryLightingMultiplier, "A factor to multiply into the contribution that this light makes to the radiosity", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "primaryLighting", m_primaryLighting, "Does this lightsource contribute to primary lighting?", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "secondaryLighting", m_secondaryLighting, "Does this lightsource contribute to secondary lighting?", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "affectTransparentObjects", m_affectTransparentObjects, "Does this lightsource affect transparent objects?", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "renderDebugInfo", m_renderDebugInfo, "Render debug information", Be::READWRITE )
		MAP_ATTRIBUTE_WITH_CHOOSER( "renderDebugType", m_renderDebugType, "Type of debug visualization to use for light source (renderDebugInfo must be on)", Be::READWRITE | Be::ENUM, DebugTypeChooser )
		MAP_ATTRIBUTE_WITH_CHOOSER( "shadowResolution", m_shadowResolution, "Resolution of the shadow map for spot light", Be::READWRITE | Be::PERSIST | Be::NOTIFY | Be::ENUM, ShadowResolutionChooser )
		MAP_ATTRIBUTE_WITH_CHOOSER( "shadowCasterTypes", m_shadowCasterTypes, "Types of objects that cast shadow from this light source", Be::READWRITE | Be::PERSIST | Be::NOTIFY | Be::ENUM, ShadowFilterChooser )
		MAP_ATTRIBUTE( "shadowImportance", m_shadowImportance, "How important is this lightsource for shadowcasting", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "LODDistribution", m_LODDistribution, "Shadow LOD size distibution (from 0 to 1: 0 - linear, 1 - exponential)", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "shadowLODs", m_shadowLODs, "Number of shadow LODs for this light (1 to 6)", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "LODBlendRegion", m_LODBlendRegion, "Size of blending region on borders of shadow LODS (0 to 1)", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "debugShadowLODs", m_debugShadowLODs, "Show shadow LODs with different colors", Be::READWRITE | Be::NOTIFY )

		MAP_PROPERTY( "isStatic", IsStatic, SetStatic, "Should this light be treated as static by Enlighten?  Toggling forces a rebuild of cached input lighting!" )

		MAP_ATTRIBUTE( "curveSets", m_curveSets, "Curve sets to animate light attributes", Be::READWRITE | Be::PERSIST )
	EXPOSURE_END()
}

#endif
