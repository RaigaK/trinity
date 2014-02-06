#include "StdAfx.h"
#include "Tr2LineSet.h"

BLUE_DEFINE( Tr2LineSet );

const Be::ClassInfo* Tr2LineSet::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2LineSet, "" )
		MAP_INTERFACE( IInitialize )
		MAP_INTERFACE( Tr2LineSet )
		MAP_INTERFACE( ITr2Renderable )
		MAP_INTERFACE( Tr2PrimitiveSet )
		MAP_INTERFACE( ITr2Pickable )

		MAP_METHOD_AND_WRAP( "AddPickingTriangle", AddPickingTriangle, 
			"(pos1, pos2, pos3)\n"
			"Add a triangle to serve as a picking area for the lineset" 
		)
		MAP_METHOD_AND_WRAP( "AddLine", AddLine, 
			"( startPosition, startColor, endPosition, endColor )\n"
			"Adds a line to the line set, but does not submit it." 
		)
		MAP_METHOD_AND_WRAP( "ClearLines", ClearLines, 
			"Clears all lines. Requires a call to SubmitChanges to complete." 
		)
		MAP_METHOD_AND_WRAP( "ClearPickingTriangles", ClearPickingTriangles, 
			"Clears all picking triangles. Requires a call to SubmitChanges to complete." 
		)
		MAP_METHOD_AND_WRAP( "SubmitChanges", SubmitChanges, 
			"Submits changes to the vertex buffer" 
		)
		
	EXPOSURE_CHAINTO( Tr2PrimitiveSet )	
}