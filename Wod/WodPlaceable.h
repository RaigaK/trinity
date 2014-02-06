#pragma once
#ifndef WodPlaceable_H
#define WodPlaceable_H


#include "TriRenderBatch.h"
#include "include/TriMatrix.h"
#include "include/ITr2Updateable.h"
#include "ITr2Renderable.h"
#include "IWodUmbraObject.h"
#include "WodReceivesLights.h"
#include "Tr2LitPerObjectData.h"
#include "Curves/TriCurveSet.h"
#include "Utilities/BoundingBox.h"

BLUE_DECLARE( WodPlaceable );
BLUE_DECLARE( WodPlaceableRes );
BLUE_DECLARE( Tr2MeshArea );

namespace Umbra
{
    class Cell;
    class Object;
}

// -----------------------------------------------------------------------------
// Description:
//   WodPlaceable represents a small object in a city that does not occlude
//   anything. WodPlaceable holds only instance information (transformation etc)
//   while WodPlaceableRes contains the description of how to render the object.
//   It is not intended to be very dynamic (moving around a lot).
//   WodPlaceable also has a sibling called Tr2InteriorPlaceable, that performs
//   the same job for dynamic objects in interiors.
//   Individual placeables can override areas on their placeableRes' by name
//   by using the override list, to change shader properties on a per-instance
//   basis.
// SeeAlso:
//   WodCity, WodPlaceableRes, Tr2IntPlaceable
// -----------------------------------------------------------------------------
class WodPlaceable : 
    public INotify,
    public IInitialize,
    public IWodUmbraObject,
    public IWodHaveLightSources,
    public ITr2Renderable,
	public ITr2Updateable,
	public ITr2Pickable,
	public WodReceivesLights
{
public:
	EXPOSE_TO_BLUE();

	using INotify::Lock;
	using INotify::Unlock;
    
    WodPlaceable( IRoot* lockobj = NULL );
    ~WodPlaceable();

    std::string GetPlaceableResPath() const;
    void SetPlaceableResPath( const std::string& val );

    const Matrix& GetTransform() const { return m_transform; }

	// ITr2Pickable
	virtual IRoot *GetID() { return this->GetRawRoot(); }
	
	// INotify
    virtual bool OnModified( Be::Var* value );

    // IInitialize
    bool Initialize();

	////////////////////////////////////////////////////////////////////////////
	// ITr2Renderable
	virtual void GetBatches( ITriRenderBatchAccumulator* batches, 
							 TriBatchType batchType, 
							 const Tr2PerObjectData* perObjectData ); 

	virtual bool HasTransparentBatches();
    virtual float GetSortValue();

	virtual Tr2PerObjectData* GetPerObjectData( ITriRenderBatchAccumulator* accumulator );

	// ITr2Updateable
	virtual void Update( Be::Time time );
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // IWodUmbraObject
    virtual void RemoveFromCell();
    virtual int AddToCell( Umbra::Cell* cell );

    ////////////////////////////////////////////////////////////////////////////
    // IWodHaveLightSources
    virtual const Matrix& GetTransform() { return *m_transform.GetMatrix(); }
    virtual WodLightSourceOverrideVector* GetLightSources();

	void UpdateLightOverrides();
	void AssignLights();
	
	void SetLightsAndTransforms( std::vector<LightsAndTransform> *a ) 
	{ 
		m_lightsAndTransforms = a; 
	}

protected:
    Umbra::Cell* m_cell;
	PTriCurveSetVector m_curveSets;

private:
	void DestroyUmbraObjects( void );

private:
	AxisAlignedBoundingBox GetBoundingBoxInLocalSpace() const;
	AxisAlignedBoundingBox GetBoundingBoxInWorldSpace() const;

    friend class WodPlaceableRes;
	Tr2LitPerObjectData* m_perObjectDataOnAllocator;

	// Used to contain the per-instance lights gathered from the placeableRes
	PWodLightSourceOverrideVector m_lightSources;

	// The lights that affect this placeable
	std::vector<LightsAndTransform> *m_lightsAndTransforms;

    std::string m_name;
	std::string m_grouping;
    std::string m_placeableResPath;
	std::string m_locationName;
    WodPlaceableResPtr m_placeableRes;
    PTriMatrix m_transform;
    bool m_fading;
	Vector4 m_highlightColor;

	Umbra::Object* m_umbraObject;
	Umbra::Object* m_umbraLightROIObjects[8];
	Umbra::Model* m_umbraModel;
	Umbra::Model* m_umbraLightROIModels[8];

	float CalculateCameraDistance();
    float CalculateCameraDistanceFromAABB();
    void SetUmbraObject( Umbra::Object* obj );
	void ReleaseUmbraROIObjects( int index = -1 );

	enum
	{
		VISIBILITYMODE_NORMAL,
		VISIBILITYMODE_FADING,
		VISIBILITYMODE_HIDDEN,
	} m_visibilityMode;
};

TYPEDEF_BLUECLASS( WodPlaceable );

BLUE_DECLARE_VECTOR( WodPlaceable );
TYPEDEF_BLUECLASS( WodPlaceableVector );

#endif // WodPlaceable_H
