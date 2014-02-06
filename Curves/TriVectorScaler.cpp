#include "StdAfx.h"
#include "TriVectorScaler.h"
#include "Vector3d.h"

TriVectorScaler::TriVectorScaler( IRoot* lockobj /*= NULL */ ):
	m_scalingFactor( 1.0f, 1.0f, 1.0f ),
	m_value( 0.0f, 0.0f, 0.0f )
{

}

void TriVectorScaler::UpdateValue( double time )
{

}

/////////////////////////////////////////////////////////////////////////////////////
// ITriFunction
/////////////////////////////////////////////////////////////////////////////////////


Vector3* TriVectorScaler::Update( Vector3* in, Be::Time t )
{	
	if( m_parentObject )
	{
		Vector3 tr;
		m_parentObject->Update( &tr, t );

		tr.x *= m_scalingFactor.x;
		tr.y *= m_scalingFactor.y;
		tr.z *= m_scalingFactor.z;

		m_value = tr;
		*in = tr; 
	}
	return in;
}

Vector3* TriVectorScaler::Update( Vector3* in, double t )
{
	return in;
}


Vector3* TriVectorScaler::GetValueAt( Vector3* in, Be::Time now )
{
	in->x = m_value.x;
	in->y = m_value.y;
	in->z = m_value.z;

	return in;
}



Vector3* TriVectorScaler::GetValueAt( Vector3* in, double pos )
{
	in->x = m_value.x;
	in->y = m_value.y;
	in->z = m_value.z;

	return in;
}

Vector3* TriVectorScaler::GetValueDoubleDotAt( Vector3* in, Be::Time now )
{
	return in;
}


Vector3* TriVectorScaler::GetValueDoubleDotAt( Vector3* in, double pos )
{
	return in;
}


Vector3* TriVectorScaler::GetValueDotAt( Vector3* in, Be::Time now )
{
	return in;
}

Vector3* TriVectorScaler::GetValueDotAt( Vector3* in, double pos )
{
	return in;
}

Vector3d*  TriVectorScaler::InterpolatedPosition( Vector3d* out, Be::Time time )
{
	out->x = m_value.x;
	out->y = m_value.y;
	out->z = m_value.z;

	return out;
}