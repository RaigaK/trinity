////////////////////////////////////////////////////////////
//
//    Created:   September 2011
//    Copyright: CCP 2011
//

#pragma once

#ifndef Tr2InteriorOrientedBoundingBox_H
#define Tr2InteriorOrientedBoundingBox_H

#include "Utilities/BoundingBox.h"

BLUE_DECLARE( Tr2InteriorOrientedBoundingBox );

// --------------------------------------------------------------------------------------
// Description:
//   Tr2InteriorOrientedBoundingBox represents an oriented bounding box. Bounds in its
//	 local space are assumed to be [-0.5, 0.5].
// See Also:
//   Tr2InteriorLightSource
// --------------------------------------------------------------------------------------
class Tr2InteriorOrientedBoundingBox :
	public INotify
{
public:
	Tr2InteriorOrientedBoundingBox( IRoot* lockobj = 0 ) ;
	~Tr2InteriorOrientedBoundingBox();


	EXPOSE_TO_BLUE();

	/////////////////////////////////////////////////////////////////////////////////////
	// INotify
	virtual bool OnModified( Be::Var* value );

	void AddNotifyTarget( INotify* target );
	void RemoveNotifyTarget( INotify* target );

	const Matrix& GetTransform() const;
	void SetTransform( const Matrix& transform );
private:
	AxisAlignedBoundingBox GetBoundingBoxInLocalSpace() const;

	// Box transform
	Matrix m_transform;
	// List of owner objects
	typedef std::set<BlueWeakRef<INotify> > NotifyTargetList;
	NotifyTargetList m_notifyTargets;
};

TYPEDEF_BLUECLASS( Tr2InteriorOrientedBoundingBox );
BLUE_DECLARE_VECTOR( Tr2InteriorOrientedBoundingBox );

#endif // Tr2InteriorOrientedBoundingBox_H

