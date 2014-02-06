#include "StdAfx.h"
#include "TriProjection.h"

BLUE_DEFINE( TriProjection );

const Be::ClassInfo* TriProjection::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriProjection, "" )

		MAP_INTERFACE( TriProjection )
		MAP_INTERFACE( IRoot )

		MAP_METHOD_AND_WRAP( "PerspectiveFov",			PerspectiveFov,			"Set the transform to a Field of View perspective (LH)" )
		MAP_METHOD_AND_WRAP( "PerspectiveOffCenter",	PerspectiveOffCenter,	"Set the transform to an off center perspective view (LH)")
		MAP_METHOD_AND_WRAP( "PerspectiveOrthographic",	PerspectiveOrthographic,"Set the transform to an orthographic perspective view (LH)")
		MAP_METHOD_AND_WRAP( "GetProjectionType",		GetProjectionType,		"1=Fov, 2=OffCenter, 3=Ortho, 4=Custom")
		MAP_METHOD_AND_WRAP( "CustomProjection",		CustomProjection,		"Set a transform directly from a matrix")

		MAP_PROPERTY_READONLY( "transform", GetTransform, "Gets the transformation matrix according to current settings.")

	EXPOSURE_END()
}
