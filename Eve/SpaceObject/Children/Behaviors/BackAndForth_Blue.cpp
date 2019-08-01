#include "StdAfx.h"
#include "BackAndForth.h"

BLUE_DEFINE( BackAndForth );

const Be::ClassInfo* BackAndForth::ExposeToBlue()
{
	EXPOSURE_BEGIN( BackAndForth, "" )
		MAP_INTERFACE( BackAndForth )
		MAP_INTERFACE( IBehavior )

		MAP_ATTRIBUTE( "arrivedRadius", m_arrivedRadius, ":jessica-group: BackAndForth", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "slowDownRadius", m_slowDownRadius, ":jessica-group: BackAndForth", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "backAndForthWeight", m_backAndForthWeight, ":jessica-group: BackAndForth", Be::READWRITE | Be::PERSIST )

	EXPOSURE_END()
}