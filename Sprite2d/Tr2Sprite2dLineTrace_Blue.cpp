//////////////////////////////////////////////////////////////////////////
//
// Created: December 2010
// Copyright CCP 2010
//

#include "StdAfx.h"
#include "Tr2Sprite2dLineTrace.h"

BLUE_DEFINE( Tr2Sprite2dLineTraceVertex );
BLUE_DEFINE( Tr2Sprite2dLineTrace );

const Be::ClassInfo* Tr2Sprite2dLineTrace::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2Sprite2dLineTrace, "" )
        MAP_INTERFACE( Tr2Sprite2dLineTrace )

		MAP_ATTRIBUTE
		(
			"vertices", 
			m_vertices, 
			"Vertices used to render line trace", 
			Be::READWRITE | Be::NOTIFY
		)

		MAP_ATTRIBUTE
		(
			"lineWidth",
			m_lineWidth,
			"Width of line rendered",
			Be::READWRITE | Be::NOTIFY
		)

		MAP_ATTRIBUTE
		(
			"textureWidth",
			m_textureWidth,
			"Width of the texture along the line",
			Be::READWRITE | Be::NOTIFY
		)

		MAP_ATTRIBUTE
		(
			"textureOffset",
			m_textureOffset,
			"Offset of the texture along the line. Can be used for animations",
			Be::READWRITE | Be::NOTIFY
		)
		
		MAP_ATTRIBUTE
		(
			"start",
			m_start,
			"Relative start of line trace - from 0 to 1",
			Be::READWRITE | Be::NOTIFY
		)
		
		MAP_ATTRIBUTE
		(
			"end",
			m_end,
			"Relative end of line trace - from 0 to 1",
			Be::READWRITE | Be::NOTIFY
		)
		
		MAP_ATTRIBUTE
		(
			"isLoop",
			m_isLoop,
			"If set, the line trace is treated as a closed loop",
			Be::READWRITE | Be::NOTIFY
		)

		MAP_ATTRIBUTE
		(
			"cornerType",
			m_cornerType,
			"Determines the shapes of corners connecting the line segments",
			Be::READWRITE | Be::NOTIFY
		)
		
	EXPOSURE_CHAINTO( Tr2TexturedSpriteObject )
}


const Be::ClassInfo* Tr2Sprite2dLineTraceVertex::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2Sprite2dLineTraceVertex, "" )
        MAP_INTERFACE( Tr2Sprite2dLineTraceVertex )

		MAP_ATTRIBUTE
		(
			"name", 
			m_name, 
			"Name of this vertex", 
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"position", 
			m_position, 
			"Position of the vertex", 
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"color", 
			m_color, 
			"Color of the vertex", 
			Be::READWRITE | Be::PERSIST
		)
	EXPOSURE_END()
}

