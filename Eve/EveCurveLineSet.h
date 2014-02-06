#pragma once
#ifndef EveCurveLineSet_H
#define EveCurveLineSet_H

#include "../Tr2CurveLineSet.h"
#include "IEveTransform.h"
#include "IEveSpaceObject2.h"

BLUE_DECLARE( EveCurveLineSet );

class Tr2PerObjectData;
class Tr2PerObjectDataStandard;

class EveCurveLineSet : 
	public Tr2CurveLineSet,
	public IEveTransform,
	public IEveSpaceObject2
{
public:
	EXPOSE_TO_BLUE();

	EveCurveLineSet(IRoot* lockobj = NULL);
	~EveCurveLineSet();
	
	void RenderDebugInfo( Tr2RenderContext& renderContext );

	Tr2PerObjectData* GetPerObjectData( ITriRenderBatchAccumulator* accumulator );

	//////////////////////////////////////////////////////////////////////////////////////
	// IEveSpaceObject2
	void Update( EveUpdateContext& updateContext );
	void GetRenderables( const TriFrustum& frustum, std::vector<ITr2Renderable*>& renderables, const Matrix& parentTransform );
	bool GetBoundingSphere( Vector4& sphere, BoundingSphereQuery query=EVE_BOUNDS_NORMAL ) const;
	void UpdateViewDistanceInfo( const TriFrustum& frustum, ViewDistanceInfo& viewDistance ) const;
	void UpdateWorldTransform( Be::Time time );

	/////////////////////////////////////////////////////////////////////////////////////
	// IEveTransform
	void UpdateViewDependentData( const Matrix& parentTransform );
	void SetLowDetail( bool b ) {};
	LodLevel GetLODLevel() const { return LOD_HIGH; }

	// No sensible implementation?
	void GetModelCenterWorldPosition( Vector3 &position, Be::Time t ) {}
	void GetCurrentModelCenterWorldPosition( Vector3 &position ) {}
	bool GetLocalBoundingBox( Vector3 &min, Vector3 &max ) { return false; }
	void GetLocalToWorldTransform( Matrix &transform ) { D3DXMatrixIdentity( &transform ); }
};

TYPEDEF_BLUECLASS( EveCurveLineSet );
BLUE_DECLARE_VECTOR( EveCurveLineSet );

#endif