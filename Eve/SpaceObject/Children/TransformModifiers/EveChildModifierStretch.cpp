////////////////////////////////////////////////////////////
//
//    Created:   2020
//    Copyright: CCP 2020
//
#include "StdAfx.h"
#include "EveChildModifierStretch.h"

EveChildModifierStretch::EveChildModifierStretch( IRoot* lockobj )
{
}

EveChildModifierStretch::~EveChildModifierStretch()
{
}
 
void EveChildModifierStretch::SetSource( ITriVectorFunction* source )
{
	m_source = source;
}

void EveChildModifierStretch::SetDest( ITriVectorFunction* dest ) 
{
	m_dest = dest;
}

Matrix EveChildModifierStretch::ApplyTransform( const Matrix& transform, size_t, const granny_matrix_3x4* ) const
{
	if( !m_source || !m_dest )
	{
		return transform;
	}
	
	Vector3 start, end, diff, dir;
	
	Be::Time now = BeOS->GetCurrentFrameTime();
	m_source->GetValueAt( &start, now );
	m_dest->GetValueAt( &end, now );
	
	diff = end - start;
	dir = Normalize( diff );
	
	float length = Length( diff );
	Vector3 scale = Vector3( 1, 1, length );

	float yaw = atan2( dir.x, dir.z );
	float pitch = asin( -dir.y );
	float roll = 0;

	Quaternion rotation = RotationQuaternion( yaw, pitch, roll );

	return TransformationMatrix( scale, rotation, start + diff / 2.0f ) * transform;
}