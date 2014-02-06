#pragma once
#ifndef WodPlaceableRes_H
#define WodPlaceableRes_H


#include "TriRenderBatch.h"
#include "Resources/TriGrannyRes.h"
#include "Tr2Mesh.h"
#include "Tr2Model.h"
#include "WodPlaceable.h"
#include "WodLightSource.h"
#include "include/TriVector.h"

BLUE_DECLARE( WodPlaceableRes );
BLUE_DECLARE( TriRenderBatch );

BLUE_DECLARE( TriCurveSet );
BLUE_DECLARE_VECTOR( TriCurveSet );

namespace Umbra
{
    class Model;
    class MeshModel;
}

struct granny_mesh;

// See http://core/wiki/WodPlaceableRes
// A WodPlaceableRes object holds the geometry for rendering a placeable, 
// as well as data required for visibility determination. 
class WodPlaceableRes : 
	public IRoot 
{
public:
    EXPOSE_TO_BLUE();

    WodPlaceableRes( IRoot* lockobj = NULL );
    ~WodPlaceableRes();

    float GetNearFadeDistance() const { return m_nearFadeDistance; }
    float GetFarFadeDistance() const { return m_farFadeDistance; }
	bool IsBackgroundProxy( void ) const { return m_isBackgroundProxy; }

    void GetBatches( ITriRenderBatchAccumulator* batches, 
					 TriBatchType batchType,
					 const Matrix& m, 
					 const Tr2PerObjectData* data );

	bool HasTransparency();

	//////////////////////////////////////////////////////////////////////////////////////
	// Bounding Volumes
	void GetBoundingBox( Vector3& min, Vector3& max ) { IsReady(); min = m_minBounds; max = m_maxBounds; }

    int PrepareUmbraCell( WodPlaceable* owner );
    bool IsReady();
    WodLightSourceVector* GetLightSources() { return &m_lightSources; }
	bool IsShadowCaster( void ) const { return m_isShadowCaster; }

	Tr2ModelPtr GetVisualModel() { return m_visualModel; }

	TriCurveSetVector* GetCurveSets() { return &m_curveSets; }
private:
    Tr2ModelPtr m_visualModel;
    
    float m_nearFadeDistance;
    float m_farFadeDistance;

	bool m_isBackgroundProxy;
	bool m_isShadowCaster;

    PTriVector m_minBounds;
    PTriVector m_maxBounds;
    bool m_bIsReady;

    PWodLightSourceVector m_lightSources;

	PTriCurveSetVector m_curveSets;
};

TYPEDEF_BLUECLASS_WR( WodPlaceableRes );

#endif // WodPlaceableRes_H