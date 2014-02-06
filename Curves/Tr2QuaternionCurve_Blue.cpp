#include "StdAfx.h"
#include "Tr2QuaternionCurve.h"

BLUE_DEFINE( Tr2QuaternionCurve );
BLUE_DEFINE( Tr2QuaternionKey );

Be::VarChooser QuaternionInterpolationChooser[] =
{
	{ 
		"CONSTANT", 
		BeCast(CONSTANT), 
		"Performs a constant interpolation" 
	},
	{ 
		"SPHERICAL_LINEAR", 
		BeCast(SPHERICAL_LINEAR), 
		"Performs a spherical linear interpolation" 
	},
	{ 0 }
};

// --------------------------------------------------------------------------------------
// Description:
//   Builds the ClassInfo for exposing Tr2QuaternionKey to Blue.
// Return Value:
//   A ClassInfo containing exposure metadata for the Tr2QuaternionKey.
// --------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2QuaternionKey::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2QuaternionKey, "" )
		MAP_INTERFACE( Tr2QuaternionKey )

		MAP_ATTRIBUTE( "time", m_time, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE_WITH_CHOOSER( "interpolation", m_interpolation, "", Be::READWRITE | Be::PERSIST | Be::ENUM, QuaternionInterpolationChooser )
		MAP_ATTRIBUTE( "value", m_value, "", Be::READWRITE | Be::PERSIST )

	EXPOSURE_END()
}

// --------------------------------------------------------------------------------------
// Description:
//   Builds the ClassInfo for exposing Tr2QuaternionCurve to Blue.
// Return Value:
//   A ClassInfo containing exposure metadata for the Tr2QuaternionCurve.
// --------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2QuaternionCurve::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2QuaternionCurve, "" )
		MAP_INTERFACE( Tr2QuaternionCurve )
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

		MAP_ATTRIBUTE_WITH_CHOOSER( "interpolation", m_interpolation, "", Be::READWRITE | Be::PERSIST | Be::ENUM, QuaternionInterpolationChooser )
		MAP_ATTRIBUTE( "keys", m_keys, "These are the keys of the curve", Be::PERSISTONLY )

		MAP_METHOD_AND_WRAP( "AddKey", AddKey, "AddKey( time, value )" );
		MAP_METHOD_AND_WRAP( "RemoveKey", RemoveKey, "RemoveKey( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyCount", GetKeyCount, "GetKeyCount( )" );
		MAP_METHOD_AND_WRAP( "GetValueAt", GetValueAt, "GetValueAt( time )" );
		MAP_METHOD_AND_WRAP( "GetKeyValue", GetKeyValue, "GetKeyValue( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyTime", GetKeyTime, "GetKeyTime( index ). \nYou need to call Sort() afterwards, to make sure the keys are in the correct order." );
		MAP_METHOD_AND_WRAP( "GetKeyInterpolation", GetKeyInterpolation, "GetKeyInterpolation( index )" );
		MAP_METHOD_AND_WRAP( "SetKeyValue", SetKeyValue, "SetKeyValue( index, value )" );
		MAP_METHOD_AND_WRAP( "SetKeyTime", SetKeyTime, "SetKeyTime( index, time )" );
		MAP_METHOD_AND_WRAP( "SetKeyInterpolation", SetKeyInterpolation, "SetKeyInterpolation( index, interpolation )" );
		MAP_METHOD_AND_WRAP( "Sort", Sort, "Sort the keys by time" );

	EXPOSURE_END()
}
