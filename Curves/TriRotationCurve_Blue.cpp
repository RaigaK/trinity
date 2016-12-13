#include "StdAfx.h"
#include "TriRotationCurve.h"

BLUE_DEFINE( TriRotationCurve );

const Be::ClassInfo* TriRotationCurve::ExposeToBlue()
{
	EXPOSURE_BEGIN( TriRotationCurve, TRIROTATIONCURVE_Description )
		MAP_INTERFACE( ITriFunction)
		MAP_INTERFACE( ITriDuration)
		MAP_INTERFACE( ITriQuaternionFunction )
		MAP_INTERFACE( ITriRotationCurve )
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
		MAP_METHOD_AS_METHOD
		(
			"AddKey",
			PyAddKey,                    
			"Adds a new key to the curve\n"
			":param time: key time\n"
			":type time: float\n"
			":param value: key value\n"
			":type value: ITriQuaternion | (float, float, float, float)\n" 
			":param leftTangent: left tangent value\n"
			":type leftTangent: ITriQuaternion | (float, float, float, float)\n" 
			":param rightTangent: right tangent value\n"
			":type rightTangent: ITriQuaternion | (float, float, float, float)\n" 
			":param interpolation: interpolation type\n"
			":type interpolation: int\n"
			":rtype: None"
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

		////////////////////////////////////////////////////////////////////////////
		//               GetKey
		MAP_METHOD_AS_METHOD
		( 
			"GetKey",
			PyGetKey,
			"Get key at the specified index\n"
			":param idx: key index\n"
			":type idx: int\n"
			":rtype: TriQuaternionKey"
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
			":type key: TriQuaternionKey\n"
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

	EXPOSURE_END()
}
