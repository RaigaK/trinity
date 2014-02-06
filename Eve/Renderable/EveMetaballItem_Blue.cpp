////////////////////////////////////////////////////////////
//
//    Created:   January 2014
//    Copyright: CCP 2014
//
#include "StdAfx.h"
#include "EveMetaballItem.h"

BLUE_DEFINE( EveMetaballItem );

const Be::ClassInfo* EveMetaballItem::ExposeToBlue()
{
    EXPOSURE_BEGIN( EveMetaballItem, "" )
        MAP_INTERFACE( EveMetaballItem )

		MAP_ATTRIBUTE( "position", m_position, "Center position", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "radius", m_radius, "Radius", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "strength", m_strength, "debug", Be::READWRITE | Be::PERSIST )

    EXPOSURE_END()
}
