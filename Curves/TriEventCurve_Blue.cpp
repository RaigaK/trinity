#include "StdAfx.h"
#include "TriEventCurve.h"
#include "TriConstants.h"

BLUE_DEFINE( TriEventCurve );
BLUE_DEFINE_INTERFACE( IBlueEventListener );

const Be::ClassInfo* TriEventCurve::ExposeToBlue()
{
    EXPOSURE_BEGIN( TriEventCurve, "" )
        MAP_INTERFACE( TriEventCurve )
		MAP_INTERFACE( ITriFunction )
		MAP_INTERFACE( IInitialize )
		MAP_INTERFACE( ITriCurveLength )

		MAP_ATTRIBUTE
		(
			"name",
			m_name,
			"",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(
			"time",
			m_time,
			"Current time of the curve",
			Be::READ
		)
		MAP_ATTRIBUTE
		(
			"length",
			m_length,
			"Length of the curve",
			Be::READ
		)
		MAP_ATTRIBUTE
		(
			"localTime",
			m_localTime,
			"Local time - reset to 0 when curve cycles.",
			Be::READ
		)
		MAP_ATTRIBUTE
		(
			"value",
			m_value,
			"The string value of the last key triggered.",
			Be::READWRITE | Be::PERSIST
		)
		MAP_ATTRIBUTE
		(  
			"keys",          
			m_keys,          
			"These are the keys of the curve", 
			Be::PERSISTONLY
		)
		MAP_ATTRIBUTE_WITH_CHOOSER
		(   
			"extrapolation", 
			m_extrapolation, 
			"This controls how time values outside the range of the curve are handled", 
			Be::READWRITE | Be::PERSIST | Be::ENUM, 
			TriExtrapolation
		)
		MAP_ATTRIBUTE
		(
			"eventListener",
			m_eventListener,
			"",
			Be::READWRITE
		)

		MAP_METHOD_AND_WRAP
		( 
			"AddKey", 
			AddKey, 
			"Adds a key with a string value. This string value is passed to\n"
			"the handler when the key is triggered."
		)

#if BLUE_WITH_PYTHON
		MAP_METHOD_AND_WRAP
		( 
			"AddCallableKey", 
			AddCallableKey, 
			"Adds a key with a callable. This callable is called when the key\n"
			"is triggered."
		)
#endif

		MAP_METHOD_AND_WRAP( "RemoveKey", RemoveKey, "" );
		MAP_METHOD_AND_WRAP( "GetKeyCount", GetKeyCount, "" );
		MAP_METHOD_AND_WRAP( "GetKeyTime", GetKeyTime, "" );
		MAP_METHOD_AND_WRAP( "GetKeyValue", GetKeyValue, "" );
		MAP_METHOD_AND_WRAP( "SetKeyTime", SetKeyTime, "" );
		MAP_METHOD_AND_WRAP( "SetKeyValue", SetKeyValue, "" );
#if BLUE_WITH_PYTHON
        MAP_METHOD_AND_WRAP( "GetCallableKeyValue", GetCallableKeyValue, "" );
        MAP_METHOD_AND_WRAP( "GetCallableKeyArgs", GetCallableKeyArgs, "" );
#endif

    EXPOSURE_END()
}
