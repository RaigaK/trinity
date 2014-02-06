//////////////////////////////////////////////////////////////////////////
//
// Created: December 2010
// Copyright CCP 2010
//

#include "StdAfx.h"
#include "Tr2Sprite2dPolygon.h"
#include "Tr2Sprite2d.h"

BLUE_DEFINE( Tr2Sprite2dPolygon );
BLUE_DEFINE( Tr2Sprite2dVertex );
BLUE_DEFINE( Tr2Sprite2dTriangle );

const Be::ClassInfo* Tr2Sprite2dPolygon::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2Sprite2dPolygon, "" )
        MAP_INTERFACE( Tr2Sprite2dPolygon )

		MAP_ATTRIBUTE
		(
			"vertices", 
			m_vertices, 
			"Vertices used to render polygon", 
			Be::READWRITE
		)

		MAP_ATTRIBUTE
		(
			"triangles", 
			m_triangles, 
			"Triangles used to render polygon", 
			Be::READWRITE
		)

	EXPOSURE_CHAINTO( Tr2TexturedSpriteObject )
}


const Be::ClassInfo* Tr2Sprite2dVertex::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2Sprite2dVertex, "" )
        MAP_INTERFACE( Tr2Sprite2dVertex )

		MAP_ATTRIBUTE
		(
			"position", 
			position, 
			"Position of the vertex", 
			Be::READWRITE | Be::PERSIST
		)

		MAP_PROPERTY( "color", GetColor, SetColor, "vertex colour" )

		MAP_METHOD_AND_WRAP( "GetTexCoord", GetTexCoord, "returns indexed texture coordinate" )
		MAP_METHOD_AND_WRAP( "SetTexCoord", SetTexCoord, "sets indexed texture coordinate" )

	EXPOSURE_END()
}

const Be::ClassInfo* Tr2Sprite2dTriangle::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2Sprite2dTriangle, "" )
		MAP_INTERFACE( Tr2Sprite2dTriangle )

		MAP_ATTRIBUTE
		(
			"index0",
			m_index[0],
			"Index of first vertex in this triangle",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"index1",
			m_index[1],
			"Index of second vertex in this triangle",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"index2",
			m_index[2],
			"Index of third vertex in this triangle",
			Be::READWRITE | Be::PERSIST
		)
	EXPOSURE_END()
}


