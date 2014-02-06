////////////////////////////////////////////////////////////
//
//    Created:   January 2014
//    Copyright: CCP 2014
//
#include "StdAfx.h"
#include "EveMetaballItem.h"

#include "Include/TriMath.h"
#include "Utilities/BoundingBox.h"

// --------------------------------------------------------------------------------
// Description:
//   Initialize data members
// --------------------------------------------------------------------------------
EveMetaballItem::EveMetaballItem( IRoot* lockobj ) :
	m_position( 0.f, 0.f, 0.f ),
	m_radius( 10.f ),
	m_strength( 1.f )
{
}

// --------------------------------------------------------------------------------
// Description:
//   tear down
// --------------------------------------------------------------------------------
EveMetaballItem::~EveMetaballItem()
{
}

// --------------------------------------------------------------------------------
// Description:
// --------------------------------------------------------------------------------
float EveMetaballItem::GetNormalizedDistanceTo( const Vector3* samplePosition ) const
{
	Vector3 centerPos = *samplePosition - m_position;
	return D3DXVec3Length( &centerPos ) / m_radius;
}

// --------------------------------------------------------------------------------
// Description:
// --------------------------------------------------------------------------------
float EveMetaballItem::GetSmoothness( const Vector3* samplePosition ) const
{
	Vector3 centerPos = *samplePosition - m_position;
	return abs( powf( D3DXVec3Length( &centerPos ) - m_radius, m_strength ) );
}

// --------------------------------------------------------------------------------
// Description:
// --------------------------------------------------------------------------------
void EveMetaballItem::AddToBoundingBox( Vector3& min, Vector3& max ) const
{
	BoundingBoxUpdate( min, max, Vector4( m_position, m_radius ) );
}












