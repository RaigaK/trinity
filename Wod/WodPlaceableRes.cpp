#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "WodPlaceableRes.h"
#include "TriRenderBatch.h"
#include "Resources/TriGrannyRes.h"
#include "Tr2MeshArea.h"
#include "UmbraTypes.h"
#include "umbra.hpp"
#include "Utilities/BoundingBox.h"

WodPlaceableRes::WodPlaceableRes( IRoot* lockobj ) : 
	m_farFadeDistance( 100.0f*100.0f ),
	m_nearFadeDistance( 50.0f*50.0f  ),
	m_isBackgroundProxy( false ),
	m_isShadowCaster( true ),
    m_bIsReady(false),
    PARENTLOCK( m_minBounds ),
    PARENTLOCK( m_maxBounds ),
    PARENTLOCK( m_lightSources ),
	PARENTLOCK( m_curveSets )
{

}

WodPlaceableRes::~WodPlaceableRes()
{
}

void WodPlaceableRes::GetBatches( ITriRenderBatchAccumulator* batches,
								  TriBatchType batchType,
								  const Matrix& m , 
								  const Tr2PerObjectData* data )
{
    if( m_visualModel )
    {
        m_visualModel->GetBatches( batches, batchType, m, data );
    }
}

int WodPlaceableRes::PrepareUmbraCell( WodPlaceable* owner )
{
    if ( !IsReady() )
    {
        return WcoNotReady;
    }
    Vector3 vMin;
    Vector3 vMax; 
    m_visualModel->GetBoundingBox(vMin,vMax);
    BoundingBoxInitialize( m_minBounds, m_maxBounds );
    BoundingBoxUpdate( m_minBounds, m_maxBounds, vMin );
    BoundingBoxUpdate( m_minBounds, m_maxBounds, vMax );

	owner->m_umbraModel = (Umbra::Model*)Umbra::OBBModel::create( *((Umbra::Vector3*)m_minBounds.GetVector()), *((Umbra::Vector3*)m_maxBounds.GetVector()) );
	owner->m_umbraObject = Umbra::Object::create( owner->m_umbraModel );

	if( owner->m_umbraObject )
	{
		owner->m_umbraObject->setCell( owner->m_cell );

		owner->m_umbraObject->setObjectToCellMatrix( AS_UMBRA_MATRIX( *owner->m_transform.GetMatrix() ) );

		ITr2Renderable * Ptr ( owner );
		owner->m_umbraObject->setUserPointer( Ptr );
	}
	else
	{
		owner->m_umbraModel->release();
		owner->m_umbraModel = NULL;
	}

    return WcoOK;
}

bool WodPlaceableRes::IsReady()
{
    if( m_bIsReady)
    {
        return true;
    }
    Umbra::Vector3 myMin;
    Umbra::Vector3 myMax;

    BoundingBoxInitialize( myMin, myMax );
    Vector3 meshMin;
    Vector3 meshMax;

    if( !m_visualModel->GetBoundingBox( meshMin, meshMax ) )
    {
        return false;
    }

    BoundingBoxUpdate( myMin, myMax, meshMin );
    BoundingBoxUpdate( myMin, myMax, meshMax );

    m_minBounds.SetVector( (Vector3*)&myMin );
    m_maxBounds.SetVector( (Vector3*)&myMax );

    m_bIsReady = true;

	return true;
}

bool WodPlaceableRes::HasTransparency()
{
    if( m_visualModel )
    {
        return m_visualModel->HasTransparency(); 
    }
    return false;
}

#endif
