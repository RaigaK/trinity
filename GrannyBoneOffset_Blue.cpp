#include "StdAfx.h"
#ifndef GAMEWORLD_64

#include "GrannyBoneOffset.h"

BLUE_DEFINE( GrannyBoneOffset );

const Be::ClassInfo* GrannyBoneOffset::ExposeToBlue()
{
    EXPOSURE_BEGIN( GrannyBoneOffset, "" )
		MAP_INTERFACE( GrannyBoneOffset )
		MAP_INTERFACE( IInitialize )

		MAP_METHOD_AND_WRAP( 
			"SetOffset",
			SetOffset,
			"Set an offset for the bone with the given name" 
			"\n"
			"\nArguments:"
			"\nboneName - Name of the bone; not existing in the current skeleton is OK"
			"\nx, y, z  - Offset in bindpose/worldspace coordinates (ie. post-animation)"
			)

		MAP_METHOD_AND_WRAP( 
			"SetRotation", 
			SetRotation,
			"Set a quaternion rotation offset for the bone with the given name" 
			"\n"
			"\nArguments:"
			"\nboneName - Name of the bone; not existing in the current skeleton is OK"
			"\nr, i, j, k  - Rotation quaternion in bone-space (ie. pre-animation)"
			)

		MAP_METHOD_AND_WRAP( 
			"ClearTransforms", 
			ClearTransforms,
			"Clear out all offsets and rotations" 
			"\n"				
			)	
    EXPOSURE_END()
}

#endif /* GAMEWORLD_64 */
