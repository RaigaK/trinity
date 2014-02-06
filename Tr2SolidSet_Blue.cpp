#include "StdAfx.h"
#include "Tr2SolidSet.h"

BLUE_DEFINE( Tr2SolidSet );

const Be::ClassInfo* Tr2SolidSet::ExposeToBlue()
{
	EXPOSURE_BEGIN(Tr2SolidSet, "no comment")
		MAP_INTERFACE( Tr2SolidSet )
		MAP_INTERFACE( IInitialize )		
		MAP_INTERFACE( Tr2PrimitiveSet )

		MAP_METHOD_AND_WRAP( "AddTriangle", AddTriangle, 
			"( pos1, color1, pos2, color2, pos3, color3 )\n"
			"Adds a triangle to the triangle set, but does not submit it." 
		)
		MAP_METHOD_AND_WRAP( "ClearTriangles", ClearTriangles, 
			"Clears all triangles. Requires a call to SubmitChanges to complete." 
		)
		MAP_METHOD_AND_WRAP( "SubmitChanges", SubmitChanges, 
			"Submits changes to the vertex buffer" 
		)	
	EXPOSURE_CHAINTO( Tr2PrimitiveSet )
}
