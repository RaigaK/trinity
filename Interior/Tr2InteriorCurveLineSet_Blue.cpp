#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "Tr2InteriorCurveLineSet.h"

BLUE_DEFINE( Tr2InteriorCurveLineSet );

const Be::ClassInfo* Tr2InteriorCurveLineSet::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2InteriorCurveLineSet, "" )
		MAP_INTERFACE( Tr2InteriorCurveLineSet )
        MAP_ATTRIBUTE
        ( 
            "perspectiveCorrection", 
            m_perspectiveCorrection, 
            "Sets weather the line is adjusted by perspective or has fixed width.", 
            Be::READWRITE | Be::NOTIFY | Be::PERSIST 
        )
	EXPOSURE_CHAINTO( Tr2CurveLineSet )
}

#endif
