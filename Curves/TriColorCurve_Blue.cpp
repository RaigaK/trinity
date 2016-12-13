#include "StdAfx.h"
#include "TriColorCurve.h"

BLUE_DEFINE( TriColorCurve );

const Be::ClassInfo* TriColorCurve::ExposeToBlue()
{
	EXPOSURE_BEGIN( TriColorCurve, TRICOLORCURVE_Description )

		MAP_INTERFACE( ITriFunction)
		MAP_INTERFACE( ITriDuration)
		MAP_INTERFACE( ITriColorFunction )
		MAP_INTERFACE( ITriColorCurve )
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
		//               extrapolation
		MAP_ATTRIBUTE
		(   
			"useHSV", 
			mUseHSV, 
			"Animate as HSV instead of RGB", 
			Be::READWRITE | Be::PERSIST
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
		MAP_METHOD_AS_METHOD
		(
			"AddKey",
			PyAddKey,                    
			"Adds a new key to the curve\n"
			":param time: key time\n"
			":type time: float\n"
			":param value: key value\n"
			":type value: ITriColor | (float, float, float, float)\n" 
			":param leftTangent: left tangent value\n"
			":type leftTangent: ITriColor | (float, float, float, float)\n" 
			":param rightTangent: right tangent value\n"
			":type rightTangent: ITriColor | (float, float, float, float)\n" 
			":param interpolation: interpolation type\n"
			":type interpolation: int\n"
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
