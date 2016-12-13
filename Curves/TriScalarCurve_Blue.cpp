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
			"Adds a new key to the curve\n"
			":param time: key time\n"
			":param value: key value\n"
			":param leftTangent: left tangent value\n"
			":param rightTangent: right tangent value\n"
			":param interpolation: interpolation type\n"
			":rtype: None"
		)

		////////////////////////////////////////////////////////////////////////////
		//               GetKey
		MAP_METHOD_AS_METHOD
		( 
			"GetKey",
			PyGetKey,
			"Get key at the specified index\n"
			":param idx: key index\n"
			":type idx: int\n"
			":rtype: TriScalarKey"
		)

		////////////////////////////////////////////////////////////////////////////
		//               SetKey
		MAP_METHOD_AS_METHOD
		( 
			"SetKey",
			PySetKey,
			"Change the key at the specified index\n"
			":param idx: key index\n"
			":type idx: int\n"
			":param key: new key\n"
			":type key: TriScalarKey\n"
			":rtype: None"
		)

		////////////////////////////////////////////////////////////////////////////
		//               RemoveKey
		MAP_METHOD_AS_METHOD
		( 
			"RemoveKey",
			PyRemoveKey,
			"Removes the key at the specified index\n"
			":param idx: key index\n"
			":type idx: int\n"
			":rtype: None"
		)

		////////////////////////////////////////////////////////////////////////////
		//               GetCurrentPos
		MAP_METHOD_AND_WRAP
		( 
			"GetCurrentPos",
			GetCurrentPos,
			"Maps the given time to curve time\n"
			":param time: input time"
		)

		////////////////////////////////////////////////////////////////////////////
		//               Sort
		MAP_METHOD_AND_WRAP
		( 
			"Sort",
			Sort,                      
			"This function should be called if keys are added to the\r\n"
			"key list with other methods than 'curve.AddKey()'.\r\n" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               ScaleTime
		MAP_METHOD_AND_WRAP
		( 
			"ScaleTime",
			ScaleTime,                      
			"Rescales time for all keys\n"
			":param scale: time scale"
		)

		////////////////////////////////////////////////////////////////////////////
		//               ScaleValue
		MAP_METHOD_AND_WRAP
		( 
			"ScaleValue",
			ScaleValue,
			"Rescales values for all keys\n"
			":param scale: value scale"
		)

	EXPOSURE_END()

}
