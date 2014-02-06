#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "blue/include/IBlueResMan.h"

#include "Utilities/BoundingBox.h"
#include "TriDevice.h"
#include "Interior/Tr2InteriorConstantBufferFormats.h" // For MAX_INTERIOR_LIGHTS_PER_OBJECT - TODO: Remove

#include "WodPlaceable.h"
#include "WodPlaceableRes.h"


WodPlaceable::WodPlaceable( IRoot* lockobj ) : 
    m_umbraObject( NULL ),
	m_umbraModel( NULL ),
    m_cell(NULL),
    PARENTLOCK( m_transform, IInitialize ),
	m_fading( false ),
	m_lightsAndTransforms( NULL ),
	PARENTLOCK( m_lightSources ),
	PARENTLOCK( m_curveSets ),
	m_perObjectDataOnAllocator( NULL ),
	m_highlightColor(0.0f, 0.0f, 0.0f, 0.0f)
{
    D3DXMatrixIdentity( &m_transform );

	for( unsigned i = 0; i < 8; i++ )
	{
		m_umbraLightROIObjects[i] = NULL;
		m_umbraLightROIModels[i] = NULL;
	}
}

WodPlaceable::~WodPlaceable()
{
	DestroyUmbraObjects();

	if( m_cell )
	{
		m_cell->release();
		m_cell = NULL;
	}
}

void WodPlaceable::ReleaseUmbraROIObjects( int index )
{
	if( index < 0)
	{
		for( unsigned i = 0; i < 8; ++i )
		{
			if( m_umbraLightROIModels[i] )
			{
				m_umbraLightROIModels[i]->release();
				m_umbraLightROIModels[i] = NULL;
			}

			if( m_umbraLightROIObjects[i] )
			{
				m_umbraLightROIObjects[i]->setCell( NULL );
				m_umbraLightROIObjects[i]->release();
				m_umbraLightROIObjects[i] = NULL;
			}
		}
	} 
	else 
	{
		if( m_umbraLightROIModels[index] )
		{
			m_umbraLightROIModels[index]->release();
			m_umbraLightROIModels[index] = NULL;
		}

		if( m_umbraLightROIObjects[index] ) 
		{
			m_umbraLightROIObjects[index]->setCell( NULL );
			m_umbraLightROIObjects[index]->release();
			m_umbraLightROIObjects[index] = NULL;
		}
	}
}

void WodPlaceable::GetBatches( ITriRenderBatchAccumulator* batches, 
							   TriBatchType batchType, 
							   const Tr2PerObjectData* perObjectData )
{
	if( m_placeableRes && (m_visibilityMode != VISIBILITYMODE_HIDDEN))
	{
		m_placeableRes->GetBatches( batches, batchType, m_transform, perObjectData );
	}
}

bool WodPlaceable::HasTransparentBatches() 
{
	if( m_placeableRes )
	{
		return m_placeableRes->HasTransparency(); 
	}
	return false;
}

float WodPlaceable::GetSortValue()
{
    return CalculateCameraDistance();
}

float WodPlaceable::CalculateCameraDistance() 
{
	Vector3 cameraPos;
	gTriDev->GetCameraPosition(&cameraPos);
	cameraPos.x -= m_transform._41;
	cameraPos.y -= m_transform._42;
	cameraPos.z -= m_transform._43;
	return D3DXVec3LengthSq(&cameraPos);
}

float WodPlaceable::CalculateCameraDistanceFromAABB() 
{
    Vector3 cameraPos;
    gTriDev->GetCameraPosition(&cameraPos);
	AxisAlignedBoundingBox aabb = GetBoundingBoxInWorldSpace();
    Vector3 nearestPoint;
    GetNearestPointOnAABB(nearestPoint, cameraPos, aabb.m_min, aabb.m_max);
    return D3DXVec3LengthSq(&(nearestPoint - cameraPos));
}

std::string WodPlaceable::GetPlaceableResPath() const
{
    return m_placeableResPath;
}

void WodPlaceable::SetPlaceableResPath( const std::string& val )
{
    m_placeableResPath = val;
	IRootPtr p;
	p.Attach( BeResMan->GetObject( m_placeableResPath.c_str() ) );
	m_placeableRes = nullptr;
	BlueQIPtrAssign( (IRoot**)&m_placeableRes, p, BlueInterfaceIID<WodPlaceableRes>() );

	UpdateLightOverrides();
}

void WodPlaceable::UpdateLightOverrides()
{
	if( m_placeableRes )
	{
		WodLightSourceVector* resLightSources = m_placeableRes->GetLightSources();

		if( resLightSources->size() > m_lightSources.size() )
		{
			// We need more light sources
			unsigned int resLightCount = (unsigned int)resLightSources->size();
			unsigned int lightsourcesCount = (unsigned int)m_lightSources.size();
			for( unsigned int i = lightsourcesCount; i < resLightCount; i++ )
			{
				WodLightSourceOverridePtr p;
				p.CreateInstance();
				m_lightSources.Insert(-1, p );
			}
		} 
		else if ( resLightSources->size() < m_lightSources.size() )
		{
			// We have too many light sources
			unsigned originalLen = (unsigned int)m_lightSources.size();
			for( unsigned i = (unsigned int)resLightSources->size(); i < originalLen; ++i )
			{
				unsigned x = (unsigned int)resLightSources->size();
				m_lightSources.Remove( x );
				ReleaseUmbraROIObjects( x );
			}

		}

		for( unsigned i = 0; i < m_lightSources.size(); ++i)
		{
			m_lightSources[i]->SetParent( (*resLightSources)[i] );
		}
	}
	else
	{
		// There's no res, kill all the override lights
		m_lightSources.Remove( -1 );
		ReleaseUmbraROIObjects();
	}
}

void WodPlaceable::RemoveFromCell()
{
	if( m_umbraObject )
	{
		m_umbraObject->setCell( NULL );
	}

	ReleaseUmbraROIObjects();

	if( m_cell )
	{
		m_cell->release();
		m_cell = NULL;
	}
}

int WodPlaceable::AddToCell( Umbra::Cell* cell )
{
    if( !m_placeableRes )
    {
        return WcoFailed;
    }

    if( !m_cell )
    {
        m_cell = cell;
        m_cell->addReference();
    }
    else
    {
        // We've technically been added to the cell, but resources hadn't loaded.
        // Make sure we're not being added to a different cell.
        CCP_ASSERT( m_cell == cell );
    }

	DestroyUmbraObjects();

    int res = m_placeableRes->PrepareUmbraCell( this );
	if(res == WcoOK)
	{
		AssignLights();

		// Add light sources to Umbra as regions of influence

		const unsigned lightSourceCount = (unsigned int)m_lightSources.size();
		for( unsigned i = 0; i < lightSourceCount; ++i )
		{
			CCP_ASSERT( m_umbraLightROIObjects[i] == NULL );

			m_umbraLightROIModels[i] = (Umbra::Model*)Umbra::SphereModel::create( (Umbra::Vector3&)Vector3(0.0f,0.0f,0.0f), m_lightSources[i]->GetRadius() );
			m_umbraLightROIObjects[i] = Umbra::RegionOfInfluence::create( m_umbraLightROIModels[i] );
			if( m_umbraLightROIObjects[i] )
			{

				// The scaling on the object doesn't affect the range of the light
				// Work out the full transformation, but only add that to the position to umbra
				// Having checked, many objects are being given scalings that don't affect the light radius
				Matrix worldTransform, parentTransform( &m_transform._11 );
				D3DXMatrixMultiply( &parentTransform, &m_lightSources[i]->GetTransform(), &parentTransform );
				D3DXMatrixIdentity( &worldTransform );
				worldTransform._41 = parentTransform._41;
				worldTransform._42 = parentTransform._42;
				worldTransform._43 = parentTransform._43;

				// Set the full transformation to the WodLightSourceOverride
				// Need this so we can take the rotation in the pixel shader
				// Pixel shader works in world position anyway, so the transform doesn't matter
				m_lightSources[i]->SetWorldTransform( parentTransform );

				m_umbraLightROIObjects[i]->setCell( m_cell );
				m_umbraLightROIObjects[i]->setObjectToCellMatrix( AS_UMBRA_MATRIX( worldTransform ) );
				m_umbraLightROIObjects[i]->setUserPointer( m_lightSources[i]->GetRawRoot() );
			}
			else
			{
				m_umbraLightROIModels[i]->release();
				m_umbraLightROIModels[i] = NULL;
			}
		}
	}

	return res;
}

bool WodPlaceable::OnModified( Be::Var* value )
{
    if( IsMatch( value, m_placeableResPath ) )
    {
        // HACK: Blue doesn't support accessors...
        // HACK: BlueStr doesn't support assignment to itself
        std::string tmp = m_placeableResPath;
        SetPlaceableResPath( tmp );
    }

    return true;
}

bool WodPlaceable::Initialize()
{
	IRootPtr p;
	p.Attach( BeResMan->GetObject( m_placeableResPath.c_str() ) );
	BlueQIPtrAssign( (IRoot**)&m_placeableRes, p, BlueInterfaceIID<WodPlaceableRes>() );

	UpdateLightOverrides();
    return true;
}

void WodPlaceable::SetUmbraObject( Umbra::Object* obj )
{
    if( m_umbraObject )
    {
        m_umbraObject->release();
    }

    m_umbraObject = obj;

    if( m_umbraObject )
    {
        m_umbraObject->addReference();
    }
}

WodLightSourceOverrideVector* WodPlaceable::GetLightSources()
{
    if( m_placeableRes )
    {
        return &m_lightSources;
    }

    return NULL;
}

void WodPlaceable::AssignLights()
{
	if( m_lightsAndTransforms )
	{
		AxisAlignedBoundingBox aabb = GetBoundingBoxInWorldSpace();
		ClearLights();
		AddMostSignificantLights(m_lightsAndTransforms, aabb.m_min, aabb.m_max );
	}
}

// -------------------------------------------------------------
// Description:
//   Blue-exposed function that returns AABB for the object in its
//   local coordinate space.
// Return value:
//   AABB for the object in its local coordinate space
// -------------------------------------------------------------
AxisAlignedBoundingBox WodPlaceable::GetBoundingBoxInLocalSpace() const
{
	AxisAlignedBoundingBox result( Vector3( 0.f, 0.f, 0.f ), Vector3( 0.f, 0.f, 0.f ) );
	if ( m_placeableRes )
	{
		m_placeableRes->GetBoundingBox( result.m_min, result.m_max );
	}
	return result;
}

// -------------------------------------------------------------
// Description:
//   Blue-exposed function that returns AABB for the object in the
//   world coordinate space.
// Return value:
//   AABB for the object in the world coordinate space
// -------------------------------------------------------------
AxisAlignedBoundingBox WodPlaceable::GetBoundingBoxInWorldSpace() const
{
	AxisAlignedBoundingBox result( Vector3( 0.f, 0.f, 0.f ), Vector3( 0.f, 0.f, 0.f ) );
	if ( m_placeableRes )
	{
		m_placeableRes->GetBoundingBox( result.m_min, result.m_max );
		result.Transform( m_transform );
	}
	return result;
}

Tr2PerObjectData* WodPlaceable::GetPerObjectData( ITriRenderBatchAccumulator* accumulator )
{
	m_perObjectDataOnAllocator = accumulator->Allocate<Tr2LitPerObjectData>();

	if( !m_perObjectDataOnAllocator )
	{
		return nullptr;
	}

	Tr2PerObjectPSData perObjectPSBuffer;
	Tr2PerObjectVSData perObjectVSBuffer;

	// column_major for shaders
	D3DXMatrixTranspose( &perObjectVSBuffer.WorldMat, &m_transform );

	if( m_placeableRes )
	{
		perObjectPSBuffer.farFadeDistance = m_placeableRes->GetFarFadeDistance();
		perObjectPSBuffer.nearFadeDistance = m_placeableRes->GetNearFadeDistance();
	}

	for(unsigned int i = 0; i < 8; i++)
	{
		if( i < m_lightInstances.size() )
		{
			perObjectPSBuffer.pointLights[i].position =  *((Vector3 *)&(m_lightInstances[i].m_worldTransform._41));
			m_lightInstances[i].m_light->PopulateLightData( &perObjectPSBuffer.pointLights[i] );
		}
		else
		{
			perObjectPSBuffer.pointLights[i].position = Vector3(0,0,0);
			perObjectPSBuffer.pointLights[i].color = Vector3(0,0,0);
			perObjectPSBuffer.pointLights[i].radius = 1.0f;
            perObjectPSBuffer.pointLights[i].direction = Vector3(0.0f,-1.0f,0.0f);
			perObjectPSBuffer.pointLights[i].pointLightProportion = 0.1f;
			perObjectPSBuffer.pointLights[i].spotLightConeAngleCos = cosf( 3.141592653f / 4.0f );
		}
	}
	const int numLights = min((int)m_lightInstances.size(), MAX_INTERIOR_LIGHTS_PER_OBJECT);
	m_perObjectDataOnAllocator->SetLightsActive( numLights, 0 );

	perObjectPSBuffer.highlightColor = m_highlightColor;

	// Do the copy
	m_perObjectDataOnAllocator->CopyToVSFloatBuffer( perObjectVSBuffer );
	m_perObjectDataOnAllocator->CopyToPSFloatBuffer( perObjectPSBuffer );

	return m_perObjectDataOnAllocator;
}

void WodPlaceable::Update( Be::Time time )
{
	// This only gets called if the WodPlaceable is added to the WodCity updatableObjects list
	for( TriCurveSetVector::iterator i = m_curveSets.begin(); i != m_curveSets.end(); ++i )
	{
		(*i)->Update( TimeAsDouble(time) );
	}
}

void WodPlaceable::DestroyUmbraObjects( void )
{
	if( m_umbraModel )
	{
		m_umbraModel->release();
		m_umbraModel = NULL;
	}

	if( m_umbraObject )
	{
		m_umbraObject->setCell( NULL );
		m_umbraObject->release();
		m_umbraObject = NULL;
	}

	ReleaseUmbraROIObjects();
}

#endif
