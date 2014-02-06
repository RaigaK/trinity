#include "StdAfx.h"
#include "Tr2ScalarBezierCurve.h"

BLUE_DEFINE( Tr2ScalarBezierCurve );
BLUE_DEFINE( Tr2ScalarBezierKey );

// --------------------------------------------------------------------------------------
// Description:
//   Builds the ClassInfo for exposing Tr2ScalarBezierKey to Blue.
// Return Value:
//   A ClassInfo containing exposure metadata for the Tr2ScalarBezierKey.
// --------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2ScalarBezierKey::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ScalarBezierKey, "" )
		MAP_INTERFACE( Tr2ScalarBezierKey )

		MAP_ATTRIBUTE( "time", m_time, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "value", m_value, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "leftControlPoint", m_leftControlPoint, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "rightControlPoint", m_rightControlPoint, "", Be::READWRITE | Be::PERSIST )

		EXPOSURE_END()
}

// --------------------------------------------------------------------------------------
// Description:
//   Builds the ClassInfo for exposing Tr2ScalarBezierCurve to Blue.
// Return Value:
//   A ClassInfo containing exposure metadata for the Tr2ScalarBezierCurve.
// --------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2ScalarBezierCurve::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ScalarBezierCurve, "" )
		MAP_INTERFACE( Tr2ScalarBezierCurve )
		MAP_INTERFACE( ITriFunction )
		MAP_INTERFACE( IInitialize )
		MAP_INTERFACE( ITriCurveLength )

		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "length", m_length, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "cycle", m_cycle, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "reversed", m_reversed, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "startValue", m_startValue, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "currentValue", m_currentValue, "", Be::READ )
		MAP_ATTRIBUTE( "endValue", m_endValue, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "controlPointA", m_controlPointA, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "controlPointB", m_controlPointB, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "keys", m_keys, "These are the keys of the curve", Be::PERSISTONLY )

		MAP_METHOD_AND_WRAP( "AddKey", AddKey, "AddKey( time, value )" );
		MAP_METHOD_AND_WRAP( "RemoveKey", RemoveKey, "RemoveKey( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyCount", GetKeyCount, "GetKeyCount( )" );
		MAP_METHOD_AND_WRAP( "GetValueAt", GetValueAt, "GetValueAt( time )" );
		MAP_METHOD_AND_WRAP( "GetKeyValue", GetKeyValue, "GetKeyValue( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyTime", GetKeyTime, "GetKeyTime( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyInterpolation", GetKeyInterpolation, "GetKeyInterpolation( index )" );
		MAP_METHOD_AND_WRAP( "SetKeyValue", SetKeyValue, "SetKeyValue( index, value )" );
		MAP_METHOD_AND_WRAP( "SetKeyTime", SetKeyTime, "SetKeyTime( index, time ). \nYou need to call Sort() afterwards, to make sure the keys are in the correct order." );	
		MAP_METHOD_AND_WRAP( "SetKeyRightControlPoint", SetKeyRightControlPoint, "SetKeyRightControlPoint( index, value )" );
		MAP_METHOD_AND_WRAP( "SetKeyLeftControlPoint", SetKeyLeftControlPoint, "SetKeyLeftControlPoint( index, value )" );
		MAP_METHOD_AND_WRAP( "GetKeyRightControlPoint", GetKeyRightControlPoint, "GetKeyRightControlPoint( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyLeftControlPoint", GetKeyLeftControlPoint, "GetKeyLeftControlPoint( index )" );
		MAP_METHOD_AND_WRAP( "SetKeyInterpolation", SetKeyInterpolation, "SetKeyInterpolation( index, interpolation )" );
		MAP_METHOD_AND_WRAP( "Sort", Sort, "Sort the keys by time" );
	EXPOSURE_END()
}
