////////////////////////////////////////////////////////////
//
//    Created:   2015
//    Copyright: CCP 2015
//
#pragma once
#ifndef EveSwarm_H
#define EveSwarm_H

#include "Eve/IEveSpaceObject2.h"
#include "ITr2Renderable.h"
#include "include/ITriFunction.h"

#include "Eve/SpaceObject/EveShip2.h"


BLUE_CLASS( EveSwarmRenderable ) :
	public ITr2Renderable
{
public:
	EXPOSE_TO_BLUE();

	EveSwarmRenderable( IRoot* lockobj = NULL );
	~EveSwarmRenderable();
	
	/////////////////////////////////////////////////////////////////////////////////////
	// ITr2Renderable
	void GetBatches( ITriRenderBatchAccumulator* batches, TriBatchType batchType, const Tr2PerObjectData* perObjectData );
	void GetShadowBatches( ITriRenderBatchAccumulator* batches, const Tr2PerObjectData* perObjectData );

    bool HasTransparentBatches();
    float GetSortValue(); 

	Tr2PerObjectData* GetPerObjectData( ITriRenderBatchAccumulator* accumulator );

	
	/////////////////////////////////////////////////////////////////////////////////////
	// PerObjectData
	void UpdatePerObjectBuffer( Tr2RenderContextEnum::ShaderType shaderType, uint32_t size, void* );
	uint32_t GetPerObjectDataSize( Tr2RenderContextEnum::ShaderType shaderType ) const;

	
	/////////////////////////////////////////////////////////////////////////////////////
	// EveSwarmRenderable
	void SetMesh( Tr2MeshBase* mesh );
	void SetWorldTransform( const Matrix& transform );
	Matrix GetWorldTransform() { return m_worldTransform; }

private:
	Tr2MeshBasePtr m_mesh;
	Matrix m_worldTransform;
	
	Tr2PersistentPerObjectData<EveSwarmRenderable> m_perObjectDataVs;
	Tr2PersistentPerObjectData<EveSwarmRenderable> m_perObjectDataPs;
	EveSpaceObjectPSData m_psData;
	EveSpaceObjectVSData m_vsData;
};
TYPEDEF_BLUECLASS( EveSwarmRenderable );
BLUE_DECLARE_VECTOR( EveSwarmRenderable );

struct SwarmVehicle
{
public:
	SwarmVehicle() :
		rotation( 0, 0, 0, 1 ),
		acceleration( 0, 0, 0 ),
		velocity( 0, 0, 0 ),
		position( 0, 0, 0 ),
		wanderTarget( 0, 0, 0 )
	{}

	Quaternion rotation;
	Vector3 acceleration;
	Vector3 velocity;
	Vector3 position;
	Vector3 wanderTarget;
};


struct SwarmBehavior
{
public:
	SwarmBehavior() :
		m_wanderDistance( 100.f ),
		m_wanderRadius( 80.f ),
		m_wanderFluctuation( 0.05f ),
		m_weightAlign( 0.1f ),
		m_weightAnchor( 0.5f ),
		m_weightCohesion( 0.1f ),
		m_weightSeparation( 0.1f ),
		m_weightWander( 0.25f ),
		m_separationDistance( 250.f )
	{}

	Vector3 CalculateForces( int i0, std::vector<SwarmVehicle>& swarmers, Vector3 anchorPosition, float timeSeconds );

//private:
	float m_weightCohesion;
	float m_weightSeparation;
	float m_weightAlign;
	float m_weightWander;
	float m_weightAnchor;

	float m_wanderFluctuation;
	float m_wanderDistance;
	float m_wanderRadius;

	float m_separationDistance;


	Vector3 Calculate_Cohesion( Vector3 p0, Vector3 p1 );
	Vector3 Calculate_Separation( Vector3 p0, Vector3 p1 );
	Vector3 Calculate_Wander( SwarmVehicle& s, float wanderDistance, float radius, float fluctuation, float t );
};

BLUE_CLASS( EveSwarm ) :
	public EveSpaceObject2
{
public:
	EXPOSE_TO_BLUE();

	EveSwarm( IRoot* lockobj = NULL );
	~EveSwarm();
	
	/////////////////////////////////////////////////////////////////////////////////////
	// EveSwarm
	void AddSwarmer();
	//void 

	/////////////////////////////////////////////////////////////////////////////////////
	// IEveSpaceObject2 / EVESpaceObject2
	void UpdateSyncronous( EveUpdateContext& updateContext );
	void UpdateAsyncronous( EveUpdateContext& updateContext );
	void RenderDebugInfo( Tr2RenderContext& renderContext );
	void GetRenderables( const TriFrustum& frustum, std::vector<ITr2Renderable*>& renderables, const Matrix& parentTransform );
	bool GetBoundingSphere( Vector4& sphere, BoundingSphereQuery query=EVE_BOUNDS_NORMAL ) const;

	// This version of the function should perform an update on the model / ball position
	void GetModelCenterWorldPosition( Vector3 &position, Be::Time t );

	// This version of the function should not update the object
	void GetCurrentModelCenterWorldPosition( Vector3 &position );

	// If possible, return an AABB in local coordinates
	bool GetLocalBoundingBox( Vector3 &min, Vector3 &max );
	// Get the local to world transform
	void GetLocalToWorldTransform( Matrix &transform ) const;
	
	virtual void RegisterWithQuadRenderer( Tr2QuadRenderer& quadRenderer );
	virtual void AddQuadsToQuadRenderer( Tr2QuadRenderer& quadRenderer );

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	virtual bool Initialize();
	
	/////////////////////////////////////////////////////////////////////////////////////
	// INotify
	bool OnModified( Be::Var* val );

private:
	Tr2MeshBasePtr m_mesh;

	std::vector<SwarmVehicle> m_vehicles;
	PEveSwarmRenderableVector m_renderables;

	// Swarming properties
	int m_count;
	float m_debugSize;
	
	float m_mass;
	float m_maxSpeed;
	float m_maxAcceleration;
	
	float m_maxOffset;
	float m_timeMultiplier;
	// Never update by more than this, anything too long and things stop looking right
	float m_maxTime;

	SwarmBehavior m_behavior;

	// Positional data
	Vector3 m_rootVelocity;
	Vector3 m_rootPosition;
	Vector3 m_squadBoundsMin;
	Vector3 m_squadBoundsMax;
};
TYPEDEF_BLUECLASS( EveSwarm );

#endif