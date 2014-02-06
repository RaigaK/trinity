#include "StdAfx.h"
#include "EveSO2ModelCenterPos.h"
#include "Vector3d.h"


EveSO2ModelCenterPos::EveSO2ModelCenterPos(IRoot* lockobj)
{
}

EveSO2ModelCenterPos::~EveSO2ModelCenterPos()
{
}
/////////////////////////////////////////////////////////////////////////////////////
// ITriFunction
/////////////////////////////////////////////////////////////////////////////////////


Vector3* EveSO2ModelCenterPos::Update( Vector3* in, Be::Time t )
{	
	if( m_parentObject )
	{
		Vector3 tr;
		m_parentObject->GetModelCenterWorldPosition( tr, t );

		in->x = tr.x;
		in->y = tr.y;
		in->z = tr.z;
		mValue.x = tr.x;
		mValue.y = tr.y;
		mValue.z = tr.z;
	}
	return in;
}

Vector3* EveSO2ModelCenterPos::Update( Vector3* in, double t )
{
	return in;
}


Vector3* EveSO2ModelCenterPos::GetValueAt( Vector3* in, Be::Time now )
{
	in->x = mValue.x;
	in->y = mValue.y;
	in->z = mValue.z;
	Update( in, now );
	return in;
}



Vector3* EveSO2ModelCenterPos::GetValueAt( Vector3* in, double pos )
{
	in->x = mValue.x;
	in->y = mValue.y;
	in->z = mValue.z;

	return in;
}

Vector3* EveSO2ModelCenterPos::GetValueDoubleDotAt( Vector3* in, Be::Time now )
{
	return in;
}


Vector3* EveSO2ModelCenterPos::GetValueDoubleDotAt( Vector3* in, double pos )
{
	return in;
}


Vector3* EveSO2ModelCenterPos::GetValueDotAt( Vector3* in, Be::Time now )
{
	return in;
}

Vector3* EveSO2ModelCenterPos::GetValueDotAt( Vector3* in, double pos )
{
	return in;
}

Vector3d*  EveSO2ModelCenterPos::InterpolatedPosition( Vector3d* out, Be::Time time )
{
	out->x = mValue.x;
	out->y = mValue.y;
	out->z = mValue.z;

	return out;
}