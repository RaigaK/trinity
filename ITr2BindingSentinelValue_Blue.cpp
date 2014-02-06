////////////////////////////////////////////////////////////
//
//    Creator:   David Plunkett
//    Created:   Oct 2011
//    Copyright: CCP 2011
//

#include "StdAfx.h"

#include "include/ITr2BindingSentinelValue.h"

BLUE_DEFINE( ITr2BindingSentinelValue );

const Be::ClassInfo* ITr2BindingSentinelValue::ExposeToBlue()
{
	EXPOSURE_BEGIN(ITr2BindingSentinelValue, "" )
		MAP_INTERFACE( ITr2BindingSentinelValue )

		MAP_ATTRIBUTE( "externalBind", 
						m_externalBind, 
						"Existence of this object attached to a binding indicates external value binding.", 
						Be::READ )

		EXPOSURE_END()
}