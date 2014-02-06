#include "StdAfx.h"
#include "Tr2Sprite2dStretchVertical.h"

BLUE_DEFINE( Tr2Sprite2dStretchVertical );

const Be::ClassInfo* Tr2Sprite2dStretchVertical::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2Sprite2dStretchVertical, "" )
        MAP_INTERFACE( Tr2Sprite2dStretchVertical )

		MAP_ATTRIBUTE
		(
			"topEdgeSize", 
			m_topEdgeSize, 
			"Number of fixed pixels on the top edge of the texture", 
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"bottomEdgeSize", 
			m_bottomEdgeSize, 
			"Number of fixed pixels on the bottom edge of the texture", 
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"texturePrimary",
			m_texture,
			"Texture for this frame",
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"fillCenter",
			m_fillCenter,
			"If set, the center of the sprite is filled (this is the default).",
			Be::READWRITE | Be::PERSIST
		)

	EXPOSURE_CHAINTO( Tr2SpriteObject )
}
