#pragma once
#ifndef Tr2Vector3Curve_h
#define Tr2Vector3Curve_h

#include "include/Tr2Curve.h"

BLUE_CLASS( Tr2Vector3Key ):
	public IRoot,
	public Tr2Key<Vector3>
{
public:
	Vector3	m_leftTangent;
	Vector3	m_rightTangent;

	EXPOSE_TO_BLUE();
	Tr2Vector3Key( IRoot* lockobj = NULL );
};
BLUE_DECLARE_VECTOR( Tr2Vector3Key );

BLUE_CLASS( Tr2Vector3Curve ) :
	public Tr2Curve<Tr2Vector3Key, PTr2Vector3KeyVector, Vector3>
{
public:

	Vector3		m_startTangent;
	Vector3		m_endTangent;

	EXPOSE_TO_BLUE();
	Tr2Vector3Curve( IRoot* lockobj = NULL );

	Vector3 GetKeyLeftTangent( unsigned int idx );
	void SetKeyLeftTangent( unsigned int idx, Vector3 tangent );

	Vector3 GetKeyRightTangent( unsigned int idx );
	void SetKeyRightTangent( unsigned int idx, Vector3 tangent );
	
	void Sort( );
	Vector3* Interpolate( Vector3* out, Tr2Vector3Key* lastKey, Tr2Vector3Key* nextKey );

private:
	void AddKey_( float time, const Vector3& value );
};

TYPEDEF_BLUECLASS( Tr2Vector3Curve );
TYPEDEF_BLUECLASS( Tr2Vector3Key );
#endif //Tr2Vector3Curve_h
