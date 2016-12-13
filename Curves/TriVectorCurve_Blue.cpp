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
			":rtype: TriColorKey"
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
			":type key: TriColorKey\n"
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

#if BLUE_WITH_PYTHON
		////////////////////////////////////////////////////////////////////////////
		//               GetCurrentPos
		MAP_METHOD_AND_WRAP
		( 
			"GetCurrentPos",
			GetCurrentPos,
			"Maps the given time to curve time\n"
			":param time: input time"
		)
#endif

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

		////////////////////////////////////////////////////////////////////////////
		//               CheckProximity
		MAP_METHOD_AS_METHOD
		( 
			"CheckProximity",
			PyCheckProximity,
			"Returns a list of time ranges at which the proximity between\n"
			"this and 'curve' is less than 'range'\n"
			":param curve: another curve\n"
			":type curve: ITriVectorCurve\n"
			":param range: minimal distance\n"
			":type range: float\n"
			":param stopAtFirst:\n"
			":type stopAtFirst: Optional[int]\n"
			":rtype: list[long]"
		)

		////////////////////////////////////////////////////////////////////////////
		//               CheckProximityToPoint
		MAP_METHOD_AS_METHOD
		( 
			"CheckProximityToPoint",
			PyCheckProximityToPoint,
			"Returns a list of time ranges at which the proximity between\n"
			"this and 'point' is less than 'range'\n"
			":param point: point position\n"
			":type point: ITriVector\n"
			":param range: minimal distance\n"
			":type range: float\n"
			":param stopAtFirst:\n"
			":type stopAtFirst: Optional[int]\n"
			":rtype: list[long]"
		)

	EXPOSURE_END()

}
