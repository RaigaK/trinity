#include "StdAfx.h"
#include "Tr2Sprite2dLayer.h"

BLUE_DEFINE( Tr2Sprite2dLayer );

const Be::ClassInfo* Tr2Sprite2dLayer::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2Sprite2dLayer, "" )
        MAP_INTERFACE( Tr2Sprite2dLayer )

		MAP_ATTRIBUTE
		(
			"backgroundColor", 
			m_backgroundColor, 
			"Background color for this layer", 
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"clearBackground",
			m_clearBackground,
			"If set, background is cleared to 'backgroundColor'",
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"children",
			m_children,
			"Children of this Layer",
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"isDirty",
			m_isDirty,
			"",
			Be::READWRITE
		)

	EXPOSURE_CHAINTO( Tr2Sprite2dContainer )
}
