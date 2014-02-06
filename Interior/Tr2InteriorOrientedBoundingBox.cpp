////////////////////////////////////////////////////////////
//
//    Created:   September 2011
//    Copyright: CCP 2011
//

#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "Tr2InteriorOrientedBoundingBox.h"

// --------------------------------------------------------------------------------------
// Description:
//   Tr2InteriorOrientedBoundingBox default constructor
// --------------------------------------------------------------------------------------
Tr2InteriorOrientedBoundingBox::Tr2InteriorOrientedBoundingBox( IRoot* lockobj )
{
	D3DXMatrixIdentity( &m_transform );
}

// --------------------------------------------------------------------------------------
// Description:
//   Tr2InteriorOrientedBoundingBox destructor.
// --------------------------------------------------------------------------------------
Tr2InteriorOrientedBoundingBox::~Tr2InteriorOrientedBoundingBox()
{
}

// --------------------------------------------------------------------------------------
// Description:
//   Implements INotify interface.  Allows the bounding box to notify its owners when
//   its transform has changed.
// Arguments:
//   value - The Blue-exposed parameter that changed
// Return Value:
//   true always
// --------------------------------------------------------------------------------------
bool Tr2InteriorOrientedBoundingBox::OnModified( Be::Var* value )
{
	for( NotifyTargetList::iterator it = m_notifyTargets.begin(); it != m_notifyTargets.end(); ++it )
	{
		( *it )->OnModified( value );
	}
	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Adds an INotify notification target to be notified when the transform changes.
// Arguments:
//   target - Notification target
// --------------------------------------------------------------------------------------
void Tr2InteriorOrientedBoundingBox::AddNotifyTarget( INotify* target )
{
	m_notifyTargets.insert( target );
}

// --------------------------------------------------------------------------------------
// Description:
//   Removes an INotify from the list of notification targets.
// Arguments:
//   target - Notification target
// --------------------------------------------------------------------------------------
void Tr2InteriorOrientedBoundingBox::RemoveNotifyTarget( INotify* target )
{
	m_notifyTargets.erase( target );
}

// --------------------------------------------------------------------------------------
// Description:
//   Returns bounding box world transform.  
// Return Value:
//   Bounding box world transform
// --------------------------------------------------------------------------------------
const Matrix& Tr2InteriorOrientedBoundingBox::GetTransform() const
{
	return m_transform;
}

// --------------------------------------------------------------------------------------
// Description:
//   Sets a new bounding box transform and notifies owners of the change.
// Arguments:
//   transform - New world transform
// --------------------------------------------------------------------------------------
void Tr2InteriorOrientedBoundingBox::SetTransform( const Matrix& transform )
{
	m_transform = transform;
	for( NotifyTargetList::iterator it = m_notifyTargets.begin(); it != m_notifyTargets.end(); ++it )
	{
		( *it )->OnModified( ( Be::Var* )&m_transform );
	}
}

// -------------------------------------------------------------
// Description:
//   Blue-exposed function that returns AABB for the box in its
//   local coordinate space.
// Return value:
//   AABB for the box in its local coordinate space
// -------------------------------------------------------------
AxisAlignedBoundingBox Tr2InteriorOrientedBoundingBox::GetBoundingBoxInLocalSpace() const
{
	return AxisAlignedBoundingBox( 
		Vector3( -0.5f, -0.5f, -0.5f ), 
		Vector3( 0.5f, 0.5f, 0.5f ) );
}

#endif
