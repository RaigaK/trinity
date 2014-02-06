#include "StdAfx.h"
#include "TriNearestBoundingPoint.h"

TriNearestBoundingPoint::TriNearestBoundingPoint(IRoot* lockobj) :
	m_value( 0.0f, 0.0f, 0.0f ),
	m_boundingBoxSize( 0.0f, 0.0f, 0.0f )
{	
}

TriNearestBoundingPoint::~TriNearestBoundingPoint()
{
}
/////////////////////////////////////////////////////////////////////////////////////
// ITriFunction
/////////////////////////////////////////////////////////////////////////////////////


Vector3* TriNearestBoundingPoint::Update(
	Vector3* in,
	Be::Time t
	)
{	
	if (m_parentPositionCurve && m_alignPositionCurve && m_parentRotationCurve)
	{
		
		Vector3 pt;
		Vector3 at;
		Quaternion parentRotation;

		m_parentPositionCurve->GetValueAt( &pt, t );
		m_alignPositionCurve->GetValueAt( &at, t );
		m_parentRotationCurve->GetValueAt( &parentRotation, t );

		Vector3 dir = at - pt;
		D3DXVec3Normalize(&dir, &dir);

		/*	--------------------------------------------------------------------------------------------------
		*	What we actually want to calculate is the point of intersection with the line
		*	defined by the direction vector, but what we definitely don't need is the direction that
		*	this point lies on (we have it already). We want to rotate the direction vector into the coordinate
		*	system of the parent transform, then solve the question of how much it needs to be scaled by to reach
		*	the bounding sphere, then perform this on the un-transformed vector. (which, like the object itself, is pre-transformed)
		*	-------------------------------------------------------------------------------------------------- */
	
		Matrix matInv;
		D3DXQuaternionNormalize( &parentRotation, &parentRotation );
		D3DXQuaternionInverse( &parentRotation, &parentRotation );
		D3DXMatrixRotationQuaternion( &matInv, &parentRotation );
		
		Vector3 transformedDir;
		D3DXVec3TransformCoord(&transformedDir, &dir, &matInv);

		// Dir is now transformed into the direction in relation to the rotation of the ship
		// We can now compute the scaling that's required on the vector using a standard ellipsiod equation

		float scalingValue = 0.0f;

		// if the object is really small (or the bounding size is erroring), just use the center of it, rather than
		// giving a NaN result in this formula
		if ((m_boundingBoxSize.x > 10.0)&&(m_boundingBoxSize.y > 10.0)&&(m_boundingBoxSize.z > 10.0))
		{
			// Forumula for an ellipsiod is
			// 1 = (x^2 / a^2) + (y^2 / b^2) + (z^2 / c^2)
			// now we need to solve the question, how much do we need to scale the vector 
			// (all three axes equally) for the vector to satisfy the ellipsiod equation
			// solution to 1 = (x*theta)^2/a^2 + ....
			// (always want the positive answer)
			scalingValue = fabs(
								(m_boundingBoxSize.x * m_boundingBoxSize.y * m_boundingBoxSize.z) /
								sqrt(
									(transformedDir.x * transformedDir.x) * (m_boundingBoxSize.y * m_boundingBoxSize.y) * (m_boundingBoxSize.z * m_boundingBoxSize.z) + 
									(transformedDir.y * transformedDir.y) * (m_boundingBoxSize.x * m_boundingBoxSize.x) * (m_boundingBoxSize.z * m_boundingBoxSize.z) + 
									(transformedDir.z * transformedDir.z) * (m_boundingBoxSize.x * m_boundingBoxSize.x) * (m_boundingBoxSize.y * m_boundingBoxSize.y)
								) 
								);
		}

		// Apply the scaling to the original direction vector
		m_value.x = pt.x + (dir.x * scalingValue);
		m_value.y = pt.y + (dir.y * scalingValue);
		m_value.z = pt.z + (dir.z * scalingValue);

		in->x = m_value.x;
		in->y = m_value.y;
		in->z = m_value.z;
	}
	else if (m_parentPositionCurve)
	{
		Vector3 pt;
		m_parentPositionCurve->GetValueAt( &pt, t );
		// If we don't have an align transform, just put it at the center of the Parent
		m_value.x = pt.x;
		m_value.y = pt.y;
		m_value.z = pt.z;

		in->x = m_value.x;
		in->y = m_value.y;
		in->z = m_value.z;
	}
	return in;
}

Vector3* TriNearestBoundingPoint::Update(
	Vector3* in,
	double t
	)
{
	return in;
}


Vector3* TriNearestBoundingPoint::GetValueAt(
	Vector3* in,
	Be::Time now
	)
{
	return in;
}

	

Vector3* TriNearestBoundingPoint::GetValueAt(
	Vector3* in,
	double pos
	)
{
	return in;
}

Vector3* TriNearestBoundingPoint::GetValueDoubleDotAt(
	Vector3* in,
	Be::Time now
	)
{
	return in;
}


Vector3* TriNearestBoundingPoint::GetValueDoubleDotAt(
	Vector3* in,
	double pos
	)
{
	return in;
}


Vector3* TriNearestBoundingPoint::GetValueDotAt(
	Vector3* in,
	Be::Time now
	)
{
	return in;
}

Vector3* TriNearestBoundingPoint::GetValueDotAt(
	Vector3* in,
	double pos
	)
{
	return in;
}

Vector3d*  TriNearestBoundingPoint::InterpolatedPosition(
	Vector3d* out,
	Be::Time time
	)
{
	return out;
}