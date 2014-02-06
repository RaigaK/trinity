////////////////////////////////////////////////////////////
//
//    Created:   August 2011
//    Copyright: CCP 2011
//

#pragma once
#ifndef Tr2InteriorCurveLineSet_H
#define Tr2InteriorCurveLineSet_H

#include "Tr2CurveLineSet.h"
#include "include/ITr2Interior.h"

BLUE_DECLARE( Tr2ShaderMaterial );
BLUE_DECLARE( Tr2InteriorCurveLineSet );

// -------------------------------------------------------------
// Description:
//   An interior curve line set.
// SeeAlso:
//   Tr2CurveLineSet
// -------------------------------------------------------------
class Tr2InteriorCurveLineSet : 
	public Tr2CurveLineSet,
	public ITr2Interior,
	public ITr2InteriorAttachedObject
{
public:
	EXPOSE_TO_BLUE();

	Tr2InteriorCurveLineSet(IRoot* lockobj = NULL);
	~Tr2InteriorCurveLineSet();

	bool OnModified( Be::Var* val );

	Tr2PerObjectData* GetPerObjectData( ITriRenderBatchAccumulator* allocator );

	void SetSHProbeMatrices( const Matrix &redProbeMatrix, 
									 const Matrix &greenProbeMatrix, 
									 const Matrix &blueProbeMatrix );
	void SetWorldTransform( const Matrix &worldTransform );
	bool IsDirty() const;
	void ClearDirtyFlag();
	bool GetBoundingBox( Vector3 &minBounds, Vector3 &maxBounds );


    // Umbra culling
	void SetVisibility( bool bVisible );
	bool IsVisible( void ) const;

	// Interior lighting
	void SetVisibleLightCount( int visibleLights );
	void SetVisibleLightSet( const Tr2InteriorLightSet& visibleLightSet );

	// Per-object data for instanced lighting
	Tr2PerObjectData* GetPerObjectDataWithPerInstanceLighting( 
		ITriRenderBatchAccumulator* accumulator,
		Tr2InteriorLightSet* lightSet, 
		const Matrix& objectToWorldMatrix, 
		const Matrix& mirrorToWorldMatrix 
	);

	// Per-object data for pre-pass
	Tr2PerObjectData* GetPerObjectDataForPrePass(
		ITriRenderBatchAccumulator* accumulator,
		const Matrix& objectToWorldMatrix
	);

	void SetSHLightingSolver( ITr2InteriorSHLightingSolver* solver );

	bool CastsShadows() const { return false; }

	// Set the mirror depth
    void SetMirrorDepth( int depth ) {}

private:
	Matrix m_worldTransform;

	bool m_isVisible;

    bool m_perspectiveCorrection;
    
    // We need the actual materials to assign situation flags
    Tr2ShaderMaterialPtr m_lineEffectMaterial;
    Tr2ShaderMaterialPtr m_pickEffectMaterial;
};

TYPEDEF_BLUECLASS( Tr2InteriorCurveLineSet );
BLUE_DECLARE_VECTOR( Tr2InteriorCurveLineSet );

#endif
