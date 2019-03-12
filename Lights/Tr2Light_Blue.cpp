#include "StdAfx.h"
#include "Tr2Light.h"

BLUE_DEFINE_ABSTRACT( Tr2Light );

const Be::ClassInfo* Tr2Light::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2Light, "" )
		MAP_INTERFACE( Tr2Light )

		EXPOSURE_END()
}
