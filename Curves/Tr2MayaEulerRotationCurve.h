#pragma once
#ifndef Tr2MayaEulerRotationCurve_h
#define Tr2MayaEulerRotationCurve_h
#include "Tr2MayaAnimationEngine.h"
#include "include/ITriFunction.h"
#include "include/ITriCurveLength.h"

#if BLUE_WITH_PYTHON

BLUE_CLASS( Tr2MayaEulerRotationCurve ):
public ITriFunction,
	public IInitialize,
	public ITriCurveLength,
	public INotify
{
public:
	EXPOSE_TO_BLUE();
	Tr2MayaEulerRotationCurve( IRoot* lockobj = NULL );

	//////////////////////////////////////////////////////////////////////////
	// ITriFunction
	void UpdateValue( double time );

	//////////////////////////////////////////////////////////////////////////
	// IInitialize
	bool Initialize();

	//////////////////////////////////////////////////////////////////////////
	// INotify
	virtual bool OnModified( Be::Var* value );

	//////////////////////////////////////////////////////////////////////////
	// ITriCurveLength
	float Length() { return m_length; }	

	// Accessors
	void	setXIndex( int index );
	int		getXIndex( void ) const { return m_xIndex; }

	void	setYIndex( int index );
	int		getYIndex( void ) const { return m_yIndex; }

	void	setZIndex( int index );
	int		getZIndex( void ) const { return m_zIndex; }

	Vector3 GetEulerValueAt( double time ) const;
	Quaternion GetValueAt( double time ) const;

private:

	int							m_xIndex;
	int							m_yIndex;
	int							m_zIndex;
	Tr2MayaAnimationEnginePtr	m_animationEngine;
	float						m_length;
	Vector3						m_eulerValue;
	Quaternion					m_quatValue;
	bool						m_updateQuaternion;
	std::string					m_name;
	void	ComputeLength();

};


TYPEDEF_BLUECLASS( Tr2MayaEulerRotationCurve );

#endif

#endif //Tr2MayaEulerRotationCurve_h
