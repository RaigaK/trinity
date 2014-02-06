#pragma once
#ifndef Tr2ScalarBezierCurve_h
#define Tr2ScalarBezierCurve_h

// Trinity headers

#include "include/Tr2Curve.h"


// --------------------------------------------------------------------------------------
// Description:
//   Tr2ScalarBezierKey is a specialization of Tr2Key for Bezier curves.  It provides
//   left and right control points for each key, in addition to the floating point key
//   value.
// SeeAlso:
//   Tr2Key, Tr2ScalarBezierCurve
// --------------------------------------------------------------------------------------
BLUE_CLASS( Tr2ScalarBezierKey ) :
	public IRoot,
	public Tr2Key<float>
{
public:
	// Constructor
	Tr2ScalarBezierKey( IRoot* lockobj = NULL );

	EXPOSE_TO_BLUE();

	// Control points
	Vector2	m_leftControlPoint;
	Vector2	m_rightControlPoint;
};
BLUE_DECLARE_VECTOR( Tr2ScalarBezierKey );

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ScalarBezierCurve is a specialization of Tr2Curve for evaluating a Bezier curve.
// SeeAlso:
//   Tr2Curve, Tr2ScalarBezierKey
// --------------------------------------------------------------------------------------
BLUE_CLASS( Tr2ScalarBezierCurve ) :
	public Tr2Curve<Tr2ScalarBezierKey, PTr2ScalarBezierKeyVector, float>
{
public:
	// Constructor
	Tr2ScalarBezierCurve( IRoot* lockobj = NULL );

	EXPOSE_TO_BLUE();

	// Gets left control point for a given key index
	const Vector2& GetKeyLeftControlPoint( unsigned int idx ) const;
	// Sets left control point for a given key value
	void SetKeyLeftControlPoint( unsigned int idx, const Vector2& val );

	// Gets right control point for a given key index
	const Vector2& GetKeyRightControlPoint( unsigned int idx ) const;
	// Sets right control point for a given key index
	void SetKeyRightControlPoint( unsigned int idx, const Vector2& val );

	// Sort keys into ascending order by key time
	void Sort();
	// Interpolate between Bezier key values
	float* Interpolate( float* out, Tr2ScalarBezierKey* startKey, Tr2ScalarBezierKey* endKey );

	// Control points
	Vector2	m_controlPointA;
	Vector2	m_controlPointB;

private:
	void AddKey_( float time, const float& value );
};

TYPEDEF_BLUECLASS( Tr2ScalarBezierCurve );
TYPEDEF_BLUECLASS( Tr2ScalarBezierKey );

#endif //Tr2ScalarBezierCurve_h