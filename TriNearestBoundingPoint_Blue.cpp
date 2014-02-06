#include "StdAfx.h"
#include "TriNearestBoundingPoint.h"

BLUE_DEFINE( TriNearestBoundingPoint );

const Be::ClassInfo* TriNearestBoundingPoint::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriNearestBoundingPoint, TRINEARESTBOUNDINGPOINT_Description)
		MAP_INTERFACE( ITriVectorFunction )

		////////////////////////////////////////////////////////////////////////////
		//               Parent
		MAP_ATTRIBUTE
		( 
			"parentPositionCurve",        
			m_parentPositionCurve,
			"na", 
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(    
			"parentRotationCurve",
			m_parentRotationCurve,
			"na",
			Be::READWRITE
		)
		////////////////////////////////////////////////////////////////////////////
		//               Align
		MAP_ATTRIBUTE
		( 
			"alignPositionCurve",        
			m_alignPositionCurve,
			"na", 
			Be::READWRITE | Be::PERSIST
		)		
		////////////////////////////////////////////////////////////////////////////
		//               value
		MAP_ATTRIBUTE
		(  
			"value",         
			m_value,         
			"na", 
			Be::READWRITE | Be::PERSIST
		)
		////////////////////////////////////////////////////////////////////////////
		//               value
		MAP_ATTRIBUTE
		(  
			"boundingSize",         
			m_boundingBoxSize,         
			"na", 
			Be::READWRITE | Be::PERSIST
		)

	EXPOSURE_END()
}