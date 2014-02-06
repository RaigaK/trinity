#include "StdAfx.h"
#include "TriPoint.h"

#if BLUE_WITH_PYTHON

BLUE_DEFINE( TriPoint );

const Be::ClassInfo* TriPoint::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriPoint, TRIPOINT_Description)
		MAP_INTERFACE(ITriPoint)
		MAP_INTERFACE(IPythonMethods)

		////////////////////////////////////////////////////////////////////////////
		//               x
		MAP_ATTRIBUTE
		( 
			"x", 
			x, 
			"", 
			Be::READWRITE | Be::PERSIST 
		)

		////////////////////////////////////////////////////////////////////////////
		//               y
		MAP_ATTRIBUTE
		( 
			"y", 
			y, 
			"", 
			Be::READWRITE | Be::PERSIST 
		)

		////////////////////////////////////////////////////////////////////////////
		//               __init__
		MAP_METHOD_AND_WRAP_OPTIONAL_ARGS
		( 
            "__init__",
            SetXY,
			2,
			"Constructor arguments"
		)
		////////////////////////////////////////////////////////////////////////////
		//               SetPoint
        MAP_METHOD_AND_WRAP_OPTIONAL_ARGS
		(
            "SetPoint",
            PySetPoint,
			2,
			""
		)

	EXPOSURE_END()

}
#endif
