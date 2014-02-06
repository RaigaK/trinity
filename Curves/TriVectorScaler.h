#pragma once
#ifndef TriVectorScaler_h
#define TriVectorScaler_h


#include "include/ITriFunction.h"

BLUE_DECLARE( TriVectorScaler );

class TriVectorScaler:
	public ITriVectorFunction
{
public:
	EXPOSE_TO_BLUE();
	TriVectorScaler( IRoot* lockobj = NULL );

	//////////////////////////////////////////////////////////////////////////
	// ITriFunction
	void UpdateValue( double time );
	Vector3* Update( Vector3* in, Be::Time time );
	Vector3* Update( Vector3* in, double time );
	Vector3* GetValueAt( Vector3* in, Be::Time time );
	Vector3* GetValueAt( Vector3* in, double time );
	Vector3* GetValueDotAt( Vector3* in, Be::Time time );
	Vector3* GetValueDotAt( Vector3* in, double time );
	Vector3* GetValueDoubleDotAt( Vector3* in, Be::Time time );
	Vector3* GetValueDoubleDotAt( Vector3* in, double time );
	Vector3d* InterpolatedPosition(Vector3d* out, Be::Time time);

private:
	std::string m_name;
	Vector3 m_value;
	Vector3 m_scalingFactor;
	ITriVectorFunctionPtr m_parentObject;
};

TYPEDEF_BLUECLASS( TriVectorScaler );
#endif //TriVectorScaler_h
