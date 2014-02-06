#pragma once
#ifndef Tr2Vector2Curve_h
#define Tr2Vector2Curve_h

#include "include/Tr2Curve.h"

BLUE_CLASS( Tr2Vector2Key ) :
	public IRoot,
	public Tr2Key<Vector2>
{
public:
	Vector2	m_leftTangent;
	Vector2	m_rightTangent;

	EXPOSE_TO_BLUE();
	Tr2Vector2Key( IRoot* lockobj = NULL );
};
BLUE_DECLARE_VECTOR( Tr2Vector2Key );

BLUE_CLASS( Tr2Vector2Curve ):
	public Tr2Curve<Tr2Vector2Key, PTr2Vector2KeyVector, Vector2>
{
public:

	Vector2		m_startTangent;
	Vector2		m_endTangent;

	EXPOSE_TO_BLUE();
	Tr2Vector2Curve( IRoot* lockobj = NULL );

	Vector2 GetKeyLeftTangent( unsigned int idx );
	void SetKeyLeftTangent( unsigned int idx, Vector2 tangent );

	Vector2 GetKeyRightTangent( unsigned int idx );
	void SetKeyRightTangent( unsigned int idx, Vector2 tangent );

	void Sort( );
	Vector2* Interpolate( Vector2* out, Tr2Vector2Key* lastKey, Tr2Vector2Key* nextKey );

private:
	void AddKey_( float time, const Vector2& value );
};

TYPEDEF_BLUECLASS( Tr2Vector2Curve );
TYPEDEF_BLUECLASS( Tr2Vector2Key );
#endif //Tr2Vector2Curve_h
