#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "WodLightSource.h"
#include "TriConstants.h"
#include "Tr2Effect.h"

BLUE_DEFINE( WodLightSource );
BLUE_DEFINE_INTERFACE( IWodHaveLightSources );


const Be::ClassInfo* WodLightSource::ExposeToBlue()
{
    EXPOSURE_BEGIN( WodLightSource, "" )
        MAP_INTERFACE( WodLightSource )
        MAP_INTERFACE( IInitialize )

        MAP_ATTRIBUTE
        (
            "glow",
            m_glowing,
            "Determines whether a light has a glow",
            Be::READWRITE | Be::PERSIST
        )

		MAP_ATTRIBUTE
        (
            "reflect",
            m_reflecting,
            "Determines whether a light reflects on the wet ground",
            Be::READWRITE | Be::PERSIST
        )
		MAP_ATTRIBUTE
		(
			"transform",
			m_transform,
			"Transform to place and orient the light source in the world",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE( "color", m_color , "color of light", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "direction", m_direction , "the direction of the light", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "radius", m_radius, "falloff distance of light", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "specularRadiusMultiplier", m_specularRadiusMultiplier, "the angle at which the falloff of the spot decreases to the minAngularFalloff", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "pointLight", m_pointLightProportion, "1.0 = Point light, 0.0 = spot light", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "spotlightConeAngle", m_spotLightConeAngle, "the angle at which the falloff of the spot decreases to the minAngularFalloff", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "distanceFalloffKneeValue", m_distanceFalloffKneeValue, "the value of the falloff at falloffPoint0Proportion", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "distanceFalloffKneeRadius", m_distanceFalloffKneeRadius, "the proportion of the distance to the maximum falloff distance that the falloff reaches falloffPoint0Value", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "glowConeColor", m_glowConeColor , "Color of glow cone", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "glowConeEffect", m_glowConeEffect, "na",	Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "glowHaloEffect", m_glowHaloEffect, "na",	Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "glowHaloColor", m_glowHaloColor , "Color of glow halo", Be::READWRITE | Be::PERSIST )
		
		MAP_ATTRIBUTE( "glowHaloScale", m_glowHaloScale, "Scale of glow halo (in addition to light source scale)", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "glowHaloZOffset", m_glowHaloZOffset, "Z offset of glow halo", Be::READWRITE | Be::PERSIST )
		
		MAP_ATTRIBUTE( "glowFlareEffect", m_glowFlareEffect, "na",	Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "glowFlareColor", m_glowFlareColor , "Color of glow flare", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "glowFlareScaleX", m_glowFlareScale.x, "Scale of the glow flare", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "glowFlareScaleY", m_glowFlareScale.y, "Scale of the glow flare", Be::READWRITE | Be::PERSIST )

    EXPOSURE_END()
}

#endif
