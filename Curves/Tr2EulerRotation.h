#pragma once
#ifndef Tr2EulerRotation_h
#define Tr2EulerRotation_h

// Trinity headers

#include "Tr2ScalarCurve.h"

// --------------------------------------------------------------------------------------
// Description:
//   Tr2EulerRotation maintains a set of 3 Tr2ScalarCurves for yaw, pitch, and roll.  It
//   can provide a Quaternion generated from the euler angle curves at a particular time.
// SeeAlso:
//   Tr2ScalarCurve, Tr2QuaternionCurve, Quaternion
// --------------------------------------------------------------------------------------
BLUE_CLASS( Tr2EulerRotation ):
	public ITriFunction,
	public ITriCurveLength
{
public:
	// Constructor
	Tr2EulerRotation( IRoot* lockobj = NULL );

    EXPOSE_TO_BLUE();

	// Euler curves
	Tr2ScalarCurvePtr m_yawCurve;	
	Tr2ScalarCurvePtr m_pitchCurve;	
	Tr2ScalarCurvePtr m_rollCurve;

	// Updates the current value of the rotation quaternion
	void UpdateValue( double time ) { m_currentValue = GetValueAt( time ); }

	// Gets the overall length of the euler rotation curve
	float Length();

	// Computes the rotation quaternion at a particular time
	Quaternion GetValueAt( double time );

private:
	// Current rotation quaternion value
	Quaternion	m_currentValue;
	// Curve name
	std::string m_name;
};

TYPEDEF_BLUECLASS( Tr2EulerRotation );
#endif //Tr2EulerRotation_h