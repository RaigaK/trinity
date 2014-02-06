#include "StdAfx.h"
#include "TriVectorCurve.h"

BLUE_DEFINE( TriVectorCurve );

const Be::ClassInfo* TriVectorCurve::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriVectorCurve, TRIVECTORCURVE_Description)
		MAP_INTERFACE( ITriFunction)
		MAP_INTERFACE( ITriDuration)
		MAP_INTERFACE( ITriVectorFunction )
		MAP_INTERFACE( ITriVectorCurve )
		MAP_INTERFACE( IListNotify )

		////////////////////////////////////////////////////////////////////////////
		//               name
		MAP_ATTRIBUTE
		(  
			"name",          
			mName,     
			"na", 
			Be::READWRITE | Be::PERSIST
		)			
		
		////////////////////////////////////////////////////////////////////////////
		//               start
		MAP_ATTRIBUTE
		( 
			"start",         
			mStart,        
			"na", 
			Be::READWRITE | Be::PERSIST
		)			
		
		////////////////////////////////////////////////////////////////////////////
		//               length
		MAP_ATTRIBUTE
		(  
			"length",        
			mLength,        
			"na", 
			Be::READ | Be::PERSIST
		)
		
		////////////////////////////////////////////////////////////////////////////
		//               value
		MAP_ATTRIBUTE
		(  
			"value",         
			mValue,         
			"na", 
			Be::READWRITE | Be::PERSIST
		)
		
		////////////////////////////////////////////////////////////////////////////
		//               extrapolation
		MAP_ATTRIBUTE_WITH_CHOOSER
		(   
			"extrapolation", 
			mExtrapolation, 
			"na", 
			Be::READWRITE | Be::PERSIST | Be::ENUM, 
			TriExtrapolation
		)

		////////////////////////////////////////////////////////////////////////////
		//               keys
		MAP_ATTRIBUTE
		(  
			"keys",          
			mKeys,          
			"na", 
			Be::READWRITE | Be::PERSIST
		)

		////////////////////////////////////////////////////////////////////////////
		//               AddKey
		MAP_METHOD_AND_WRAP
		(
			"AddKey",
			AddKey,                    
			"use:  curve.AddKey( t, v, l, r, i )\r\n" 
			"pre:  't' is of type double. 'v', 'l', 'r' are tuples of three floats.\r\n"				
			"      'i' is of type integer.\r\n" 
			"post: A key with time, value, left, right and interpolation\r\n" 
			"      according to arguments has been added to 'curve' and the\r\n" 
			"      curve has been updated accordingly.\r\n" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               GetKey
		MAP_METHOD_AS_METHOD
		( 
			"GetKey",
			PyGetKey,
			"use:  curve.GetKey( i )\r\n" 				
			"pre: 'i' is of type int\r\n" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               SetKey
		MAP_METHOD_AS_METHOD
		( 
			"SetKey",
			PySetKey,
			"use:  curve.SetKey( i, key )\r\n" 				
			"pre: 'i' is of type int and key is of type TriVectorKey\r\n" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               RemoveKey
		MAP_METHOD_AS_METHOD
		( 
			"RemoveKey",
			PyRemoveKey,
			"use:  curve.RemoveKey( i )\r\n" 				
			"pre: 'i' is of type int\r\n" 
			"post: The key at index 'i' has been removed\r\n"
		)

#if BLUE_WITH_PYTHON
		////////////////////////////////////////////////////////////////////////////
		//               GetCurrentPos
		MAP_METHOD_AND_WRAP
		( 
			"GetCurrentPos",
			GetCurrentPos,
			"use:  curve.GetCurrentPos( )\r\n" 				
		)
#endif

		////////////////////////////////////////////////////////////////////////////
		//               Sort
		MAP_METHOD_AND_WRAP
		( 
			"Sort",
			Sort,                      
			"use:  curve.Sort( t )\r\n" 				
			"post: The keys of the curve have been sorted and 'curve.length'\r\n" 
			"      updated.\r\n"
			"note: This function should be called if keys are added to the\r\n"
			"      key list with other methods than 'curve.AddKey()'.\r\n" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               ScaleTime
		MAP_METHOD_AND_WRAP
		( 
			"ScaleTime",
			ScaleTime,                      
			"use:  curve.ScaleTime( s )\r\n" 				
			"pre: 's' is of type float\r\n" 
			"post: All keys of 'curve' have had their time scaled by 's'\r\n"
		)

		////////////////////////////////////////////////////////////////////////////
		//               ScaleValue
		MAP_METHOD_AND_WRAP
		( 
			"ScaleValue",
			ScaleValue,
			"use:  curve.ScaleValue( s )\r\n" 				
			"pre: 's' is of type float\r\n" 
			"post: All keys of 'curve' have had their value scaled by 's'\r\n"
		)

		////////////////////////////////////////////////////////////////////////////
		//               CheckProximity
		MAP_METHOD_AS_METHOD
		( 
			"CheckProximity",
			PyCheckProximity,
			"use:  curve.CheckProximity( curve, range, stopAtFirst )\r\n" 				
			"pre: 'curve' is of type TriVectorCurve\r\n" 
			"post: Returns a list of time ranges at which the proximity between\r\n"
			"this and 'curve' is less than 'range'\r\n"
		)

		////////////////////////////////////////////////////////////////////////////
		//               CheckProximityToPoint
		MAP_METHOD_AS_METHOD
		( 
			"CheckProximityToPoint",
			PyCheckProximityToPoint,
			"use:  curve.CheckProximityToPoint( point, range ,stopAtFirst )\r\n" 				
			"pre: 'point' is of type TriVector\r\n" 
			"post: Returns a list of time ranges at which the proximity between\r\n"
			"this and 'point' is less than 'range'\r\n"
		)

	EXPOSURE_END()

}
