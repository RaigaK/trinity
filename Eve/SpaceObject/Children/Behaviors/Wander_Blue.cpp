#include "StdAfx.h"
#include "Wander.h"


BLUE_DEFINE( Wander );

const Be::ClassInfo* Wander::ExposeToBlue()
{
	EXPOSURE_BEGIN( Wander, "" )
		MAP_INTERFACE( Wander )
		MAP_INTERFACE( IBehavior )

		MAP_ATTRIBUTE( "weightWander", m_weightWander, ":jessica-group: Wander", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "rand1", rand1, ":jessica-group: Wander", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "rand2", rand2, ":jessica-group: Wander", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "rand3", rand3, ":jessica-group: Wander", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "freq", m_freq, ":jessica-group: Wander", Be::READWRITE | Be::PERSIST )



	EXPOSURE_END()
}