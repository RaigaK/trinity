#include "StdAfx.h"
#include "Tr2ScalarExprKeyCurve.h"

BLUE_DEFINE( Tr2ScalarExprKeyCurve );
BLUE_DEFINE( Tr2ScalarExprKey );

extern Be::VarChooser ScalarInterpolationChooser[];

const Be::ClassInfo* Tr2ScalarExprKey::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2ScalarExprKey, "" )
        MAP_INTERFACE( Tr2ScalarExprKey )
        MAP_INTERFACE( IInitialize )
        MAP_INTERFACE( INotify )
			
		MAP_ATTRIBUTE( "time", m_time, "Key time", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "value", m_value, "Key value", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "left", m_leftTangent, "Left tangent value", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "right", m_rightTangent, "Right tangent value", Be::READWRITE | Be::NOTIFY | Be::PERSIST )

		MAP_ATTRIBUTE( "timeExpression", m_timeExpression, "Math expression for key time", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "valueExpression", m_valueExpression, "Math expression for key value", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "leftTangentExpression", m_leftTangentExpression, "Math expression for key left tangent value", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "rightTangentExpression", m_rightTangentExpression, "Math expression for key right tangent value", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "input1", m_inputVar1, "Artbitrary input variable for key expressions", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "input2", m_inputVar2, "Artbitrary input variable for key expressions", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "input3", m_inputVar3, "Artbitrary input variable for key expressions", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "input4", m_inputVar4, "Artbitrary input variable for key expressions", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "randomConstant", m_randomConstant, "Random constant for key expressions", Be::READ )
		MAP_ATTRIBUTE( "randomMin", m_randomMin, "Min range for randomConstant", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "randomMax", m_randomMax, "Max range for randomConstant", Be::READWRITE | Be::NOTIFY | Be::PERSIST )

		MAP_ATTRIBUTE( "prevKeyTime", m_prevKeyTime, "Time of the previous key", Be::READ )
		MAP_ATTRIBUTE( "prevKeyValue", m_prevKeyValue, "Value of the previous key", Be::READ )


		MAP_ATTRIBUTE_WITH_CHOOSER( "interpolation", m_interpolation, "Curve interpolation at key", Be::READWRITE | Be::PERSIST | Be::ENUM, ScalarInterpolationChooser )

		MAP_METHOD_AND_WRAP( "RegenRandomConstant", RegenRandomConstant, "Regenerate the randomConstant variable for expressions")
	EXPOSURE_END()
}

const Be::ClassInfo* Tr2ScalarExprKeyCurve::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2ScalarExprKeyCurve, "" )
		MAP_INTERFACE( ITriFunction )
        MAP_INTERFACE( IInitialize )
		MAP_INTERFACE( ITriCurveLength )

		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST )
		MAP_PROPERTY_READONLY( "length", Length, "" )
		MAP_ATTRIBUTE( "cycle", m_cycle, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "reversed", m_reversed, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "timeOffset", m_timeOffset, "An internal offset to the curve's timing", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "timeScale", m_timeScale, "An internal scaling to the curve's timing", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "currentValue", m_currentValue, "", Be::READ )
		MAP_ATTRIBUTE_WITH_CHOOSER( "interpolation", m_interpolation, "", Be::READWRITE | Be::PERSIST | Be::ENUM, ScalarInterpolationChooser )
		MAP_ATTRIBUTE( "keys", m_keys, "These are the keys of the curve", Be::READWRITE | Be::PERSIST )

		MAP_METHOD_AND_WRAP_OPTIONAL_ARGS( "AddKey", AddKey, 3, "AddKey( time, value )" );
		MAP_METHOD_AND_WRAP( "RemoveKey", RemoveKey, "RemoveKey( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyCount", GetKeyCount, "GetKeyCount( )" );
		MAP_METHOD_AND_WRAP( "GetValueAt", GetValueAt, "GetValueAt( time )" );
		MAP_METHOD_AND_WRAP( "GetKeyValue", GetKeyValue, "GetKeyValue( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyTime", GetKeyTime, "GetKeyTime( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyLeftTangent", GetKeyLeftTangent, "GetKeyLeftTangent( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyRightTangent", GetKeyRightTangent, "GetKeyRightTangent( index )" );
		MAP_METHOD_AND_WRAP( "GetKeyInterpolation", GetKeyInterpolation, "GetKeyInterpolation( index )" );
		MAP_METHOD_AND_WRAP( "SetKeyValue", SetKeyValue, "SetKeyValue( index, value )" );
		MAP_METHOD_AND_WRAP( "SetKeyTime", SetKeyTime, "SetKeyTime( index, time ). \nYou need to call Sort() afterwards, to make sure the keys are in the correct order." );
		MAP_METHOD_AND_WRAP( "SetKeyLeftTangent", SetKeyLeftTangent, "SetKeyLeftTangent( index, value )" );
		MAP_METHOD_AND_WRAP( "SetKeyRightTangent", SetKeyRightTangent, "SetKeyRightTangent( index, value )" );
		MAP_METHOD_AND_WRAP( "SetKeyInterpolation", SetKeyInterpolation, "SetKeyInterpolation( index, interpolation )" );
		MAP_METHOD_AND_WRAP( "Sort", Sort, "Re-evaluate key expressions" );
    EXPOSURE_END()
}

