#include "StdAfx.h"
#include "TriVectorScaler.h"

BLUE_DEFINE( TriVectorScaler );

const Be::ClassInfo* TriVectorScaler::ExposeToBlue()
{
	EXPOSURE_BEGIN( TriVectorScaler, "" )
		MAP_INTERFACE( TriVectorScaler )
		MAP_INTERFACE( ITriVectorFunction )

		MAP_ATTRIBUTE
		(
			"name",
			m_name,
			"",
			Be::READWRITE | Be::PERSIST
		)
		////////////////////////////////////////////////////////////////////////////
		//               Parent
		MAP_ATTRIBUTE
		( 
			"parent",        
			m_parentObject,
			"The vector function to track", 
			Be::READWRITE
		)
		MAP_ATTRIBUTE
		(
			"scaling",
			m_scalingFactor,
			"The scaling to apply to the output of the vector function", 
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"value",
			m_value,
			"The last updated value", 
			Be::READWRITE | Be::PERSIST
		)

	EXPOSURE_END()
}
