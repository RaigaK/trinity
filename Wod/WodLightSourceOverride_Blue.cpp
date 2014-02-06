#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "WodLightSourceOverride.h"

BLUE_DEFINE( WodLightSourceOverride );

const Be::ClassInfo* WodLightSourceOverride::ExposeToBlue()
{
	EXPOSURE_BEGIN( WodLightSourceOverride, "" )
		MAP_INTERFACE( WodLightSourceOverride )
		MAP_INTERFACE( WodLightSource )
		MAP_INTERFACE( IInitialize )

		MAP_ATTRIBUTE( "parent", m_parent, "", Be::READ )
		MAP_ATTRIBUTE
		(
			"override_color",
			m_overrideColor,
			"Determines if this class inherits the 'color' value from the res, or overrides it",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"override_radius",
			m_overrideRadius,
			"Determines if this class inherits the 'radius' value from the res, or overrides it",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"override_pointLight",
			m_overridePointLightProportion,
			"Determines if this class inherits the 'pointLight' value from the res, or overrides it",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"override_direction",
			m_overrideDirection,
			"Determines if this class inherits the 'direction' value from the res, or overrides it",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"override_spotlightConeAngle",
			m_overrideSpotlightConeAngle,
			"Determines if this class inherits the 'pointlightConeAngle' value from the res, or overrides it",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"override_distanceFalloffKneeRadius",
			m_overrideDistanceFalloffKneeRadius,
			"Determines if this class inherits the 'distanceFalloffKneeRadius' value from the res, or overrides it",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"override_distanceFalloffKneeValue",
			m_overrideDistanceFalloffKneeValue,
			"Determines if this class inherits the 'distanceFalloffKneeValue' value from the res, or overrides it",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"override_specularRadiusMultiplier",
			m_overrideSpecularRadiusMultiplier,
			"Determines if this class inherits the 'specularRadiusMultiplier' value from the res, or overrides it",
			Be::READWRITE | Be::PERSIST
		)
	EXPOSURE_CHAINTO( WodLightSource )
}

#endif
