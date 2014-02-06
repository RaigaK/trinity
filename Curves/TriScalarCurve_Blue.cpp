#include "StdAfx.h"
#include "TriScalarCurve.h"

BLUE_DEFINE( TriScalarCurve );

const Be::ClassInfo* TriScalarCurve::ExposeToBlue()
{
	EXPOSURE_BEGIN( TriScalarCurve, TRISCALARCURVE_Description )
		MAP_INTERFACE( ITriFunction )
		MAP_INTERFACE( ITriDuration)
		MAP_INTERFACE( ITriScalarFunction )
		MAP_INTERFACE( ITriScalarCurve )
		MAP_INTERFACE( IListNotify )

		////////////////////////////////////////////////////////////////////////////
		//               name
		MAP_ATTRIBUTE
		(  
			"name",          
			mName,     
			"Yes you can name your curves", 
			Be::READWRITE | Be::PERSIST
		)		
		
		////////////////////////////////////////////////////////////////////////////
		//               start
		MAP_ATTRIBUTE
		( 
			"start",         
			mStart,        
			"The time at which the curve should begin", 
			Be::READWRITE | Be::PERSIST
		)			
		
		////////////////////////////////////////////////////////////////////////////
		//               length
		MAP_ATTRIBUTE
		(  
			"length",        
			mLength,        
			"The length of the curve, updated with calls to Sort()", 
			Be::READ | Be::PERSIST
		)
		
		////////////////////////////////////////////////////////////////////////////
		//               value
		MAP_ATTRIBUTE
		(  
			"value",         
			mValue,         
			"The last value of the curve, can be set externally, wont be changed on Update() if lenght is 0", 
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE( "timeOffset", m_timeOffset, "An internal offset to the curve's timing", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "timeScale", m_timeScale, "An internal scaling to the curve's timing", Be::READWRITE | Be::PERSIST )
		
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
			"These are the keys of the curve, if you manipulate them directly then it is wise to call Sort()", 
			Be::READWRITE | Be::PERSIST
		)

		////////////////////////////////////////////////////////////////////////////
		//               AddKey
		MAP_METHOD_AND_WRAP
		(
			"AddKey",
			AddKey,                    
			"use:  curve.AddKey( t, v, l, r, i )\r\n" 
			"pre:  't' is of type double. 'v', 'l', 'r' are of type float.\r\n"				
			"      'i' is of type integer.\r\n" 
			"post: A key with time, value, left, right and interpolation\r\n" 
			"      according to arguments has been added to 'curve' and the\r\n" 
			"      curve has been updated acordingly." 
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
			"pre: 'i' is of type int and key is of type TriScalarKey\r\n" 
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

		////////////////////////////////////////////////////////////////////////////
		//               GetCurrentPos
		MAP_METHOD_AND_WRAP
		( 
			"GetCurrentPos",
			GetCurrentPos,
			"use:  curve.GetCurrentPos( )\r\n" 				
		)

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
			"      key list with other methods than 'curve.AddKey()'" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               ScaleTime
		MAP_METHOD_AND_WRAP
		( 
			"ScaleTime",
			ScaleTime,                      
			"use:  curve.ScaleTime( s )\r\n" 				
			"pre: 's' is of type float\r\n" 
			"post: All keys of 'curve' have had their time scaled by 's'"
		)

		////////////////////////////////////////////////////////////////////////////
		//               ScaleValue
		MAP_METHOD_AND_WRAP
		( 
			"ScaleValue",
			ScaleValue,
			"use:  curve.ScaleValue( s )\r\n" 				
			"pre: 's' is of type float\r\n" 
			"post: All keys of 'curve' have had their value scaled by 's'"
		)

	EXPOSURE_END()

}
