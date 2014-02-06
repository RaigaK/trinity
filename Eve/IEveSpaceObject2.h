#ifndef IEveSpaceObject2_H
#define IEveSpaceObject2_H

#include "EveLODHelper.h"

struct ITr2Renderable;
struct ViewDistanceInfo;
class TriFrustum;
class Tr2RenderContext;
class EveUpdateContext;

BLUE_INTERFACE( IEveSpaceObject2 ) : public IRoot
{
	virtual void Update( EveUpdateContext& updateContext ) = 0;
	virtual void RenderDebugInfo( Tr2RenderContext& renderContext ) = 0;
	virtual void GetRenderables( const TriFrustum& frustum, std::vector<ITr2Renderable*>& renderables, const Matrix& parentTransform ) = 0;
	virtual bool GetBoundingSphere( Vector4& sphere, BoundingSphereQuery query=EVE_BOUNDS_NORMAL ) const = 0;
	virtual void UpdateViewDistanceInfo( const TriFrustum& frustum, ViewDistanceInfo& viewDistance ) const = 0;

	virtual void UpdateWorldTransform( Be::Time time ) = 0;
	// This version of the function should perform an update on the model / ball position
	virtual void GetModelCenterWorldPosition( Vector3 &position, Be::Time t ) = 0;

	// This version of the function should not update the object
	virtual void GetCurrentModelCenterWorldPosition( Vector3 &position ) = 0;

	// If possible, return an AABB in local coordinates
	virtual bool GetLocalBoundingBox( Vector3 &min, Vector3 &max ) = 0;
	// Get the local to world transform
	virtual void GetLocalToWorldTransform( Matrix &transform ) = 0;
};

BLUE_DECLARE_IVECTOR( IEveSpaceObject2 );

#endif