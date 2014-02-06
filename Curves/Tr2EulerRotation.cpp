#include "StdAfx.h"
#include "Tr2EulerRotation.h"

// --------------------------------------------------------------------------------------
// Description:
//   Default constructor.
// --------------------------------------------------------------------------------------
Tr2EulerRotation::Tr2EulerRotation( IRoot* lockobj ) :
    m_currentValue( XMQuaternionIdentity() )
{
}

// --------------------------------------------------------------------------------------
// Description:
//   Gets the overall length of the rotation curve by examining the lengths of the
//   individual scalar euler curves.
// Return Value:
//   Overall length of the rotation curve.
// --------------------------------------------------------------------------------------
float Tr2EulerRotation::Length()
{
	float length = 0.0f;
	if( m_yawCurve != NULL )
	{
		length = m_yawCurve->Length();
	}
	else if( m_pitchCurve != NULL && m_pitchCurve->Length() > length )
	{
		length = m_pitchCurve->Length();
	}
	else if( m_rollCurve != NULL && m_rollCurve->Length() > length )
	{
		length = m_rollCurve->Length();
	}
	return length;
}

// --------------------------------------------------------------------------------------
// Description:
//   Computes the value of the rotation quaternion at a particular point in time.
// Arguments:
//   time - The time at which to evaluate the rotation curves
// Return Value:
//   The rotation quaternion implied by the Euler angles at the given point in time.
// --------------------------------------------------------------------------------------
Quaternion Tr2EulerRotation::GetValueAt( double time )
{
	float yaw = m_yawCurve ? m_yawCurve->GetValueAt( time ) : 0.0f;
	float pitch = m_pitchCurve ? m_pitchCurve->GetValueAt( time ) : 0.0f;
	float roll = m_rollCurve ? m_rollCurve->GetValueAt( time ) : 0.0f;

	return Quaternion( XMQuaternionRotationRollPitchYaw( pitch, yaw, roll ) );
}