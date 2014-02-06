#include "StdAfx.h"
#include "Tr2DynamicMesh.h"

BLUE_DEFINE( Tr2DynamicMesh );

// ------------------------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2DynamicMesh::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2DynamicMesh, "" )

		MAP_INTERFACE( Tr2DynamicMesh )

	EXPOSURE_CHAINTO( Tr2Mesh )
}

