#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "WodPlaceable.h"

BLUE_DEFINE( WodPlaceable );

const Be::ClassInfo* WodPlaceable::ExposeToBlue()
{
    EXPOSURE_BEGIN(WodPlaceable, "")
        MAP_INTERFACE( WodPlaceable )
        MAP_INTERFACE( INotify )
        MAP_INTERFACE( IInitialize )
        MAP_INTERFACE( ITr2Renderable )
		MAP_INTERFACE( ITr2Updateable )
		MAP_INTERFACE( ITr2Pickable )
		MAP_INTERFACE( WodReceivesLights )			
        MAP_INTERFACE( IWodHaveLightSources )

        MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "grouping", m_grouping, "", Be::READWRITE | Be::PERSIST )
        MAP_ATTRIBUTE_WITH_CHOOSER( "placeableResPath", m_placeableResPath, "", Be::READWRITE | Be::PERSIST | Be::NOTIFY, NULL )
        MAP_ATTRIBUTE( "placeableRes", m_placeableRes, "", Be::READ )
		MAP_ATTRIBUTE( "locationName", m_locationName, "", Be::READWRITE | Be::PERSIST )
        MAP_ATTRIBUTE( "transform", m_transform, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "isFading", m_fading, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "lightSources", m_lightSources, "", Be::READ | Be::PERSIST )
		MAP_ATTRIBUTE( "curveSets", m_curveSets, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "highlightColor", m_highlightColor, "Highlights the entire object in this color", Be::READWRITE )

		MAP_METHOD_AND_WRAP( "GetBoundingBoxInLocalSpace", GetBoundingBoxInLocalSpace, "Gets the bounding box in local space")
		MAP_METHOD_AND_WRAP( "GetBoundingBoxInWorldSpace", GetBoundingBoxInWorldSpace, "Gets the bounding box in world space")
	
    EXPOSURE_CHAINTO(WodReceivesLights)
}

#endif
