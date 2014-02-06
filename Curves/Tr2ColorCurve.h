#pragma once
#ifndef Tr2ColorCurve_h
#define Tr2ColorCurve_h

// Trinity headers

#include "include/Tr2Curve.h"


// --------------------------------------------------------------------------------------
// Description:
//   Tr2ColorKey is a specialization of Tr2Key for colors.
// SeeAlso:
//   Tr2Key, Tr2ColorCurve
// --------------------------------------------------------------------------------------
BLUE_CLASS( Tr2ColorKey ):
	public IRoot,
	public Tr2Key<Color>
{
public:
	// Constructor
	Tr2ColorKey( IRoot* lockobj = NULL );

	EXPOSE_TO_BLUE();
};
BLUE_DECLARE_VECTOR( Tr2ColorKey );

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ColorCurve is a specialization of Tr2Curve for interpolating between color keys.
// SeeAlso:
//   Tr2Curve, Tr2ColorKey
// --------------------------------------------------------------------------------------
BLUE_CLASS( Tr2ColorCurve ):
	public Tr2Curve<Tr2ColorKey, PTr2ColorKeyVector, Color>
{
public:
	// Constructor
	Tr2ColorCurve( IRoot* lockobj = NULL );

	EXPOSE_TO_BLUE();

	// Sort keys into ascending order by key time
	void Sort();

	// Interpolate between color key values
	Color* Interpolate( Color* out, Tr2ColorKey* startKey, Tr2ColorKey* endKey );

private:
	// Virtual function to add a color key at a specific time
	void AddKey_( float time, const Color& value );
};

TYPEDEF_BLUECLASS( Tr2ColorCurve );
TYPEDEF_BLUECLASS( Tr2ColorKey );
#endif // Tr2ColorCurve_h
