////////////////////////////////////////////////////////////
//
//    Created:   March 2011
//    Copyright: CCP 2011
//
#include "StdAfx.h"
#include "EveSpaceSceneLightMgr.h"

BLUE_DEFINE( EveSpaceScenePointLight );

const Be::ClassInfo* EveSpaceScenePointLight::ExposeToBlue()
{
	EXPOSURE_BEGIN( EveSpaceScenePointLight, "" )
        MAP_INTERFACE( EveSpaceScenePointLight )
        MAP_INTERFACE( IRoot )

		MAP_ATTRIBUTE( "name", m_name, "Just to identify this", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "display", m_display, "Debug helper: toggle on and off", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "position", m_position, "Position of the point light in render-space", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "outerRadius", m_outerRadius, "The outer radius. Beyond that no influence", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "color", m_color, "Color of the light", Be::READWRITE | Be::PERSIST )

	EXPOSURE_END()
}


BLUE_DEFINE( EveSpaceSceneLightMgr );

const Be::ClassInfo* EveSpaceSceneLightMgr::ExposeToBlue()
{
	EXPOSURE_BEGIN( EveSpaceSceneLightMgr, "" )
        MAP_INTERFACE( EveSpaceSceneLightMgr )
        MAP_INTERFACE( IInitialize )
        MAP_INTERFACE( INotify )

		MAP_ATTRIBUTE( "staticPointlights", m_staticPointlights, "A list of all static point lights", Be::READWRITE | Be::PERSIST )

	EXPOSURE_END()
}
