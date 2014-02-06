#pragma once
#ifndef Tr2ForceFieldActor_h
#define Tr2ForceFieldActor_h

#include "Apex.h"

#if USE_APEX_FORCE_FIELD

#include "blue\include\BlueAsyncRes.h"
#include "NxMat34.h"

BLUE_DECLARE( Tr2ForceFieldActor );
BLUE_DECLARE( Tr2ApexRes );

namespace physx
{
	class PxMat34;

	namespace apex {
		class NxFieldBoundaryActor;
		class NxApexRenderable;
	}
}

// The Tr2ForceFieldActor class is a wrapper around the NxFieldBoundaryActor class
// from Apex. It is an instance of a piece of forcefield coming from a forcefield
// asset (NxFieldBoundaryAsset), wrapped in a Tr2ApexRes.
class Tr2ForceFieldActor:
	public IInitialize,
	public IBlueAsyncResNotifyTarget
{
public:
	EXPOSE_TO_BLUE();
	using IInitialize::Lock;
	using IInitialize::Unlock;

	Tr2ForceFieldActor( IRoot* lockobj = NULL );
	~Tr2ForceFieldActor();

	physx::apex::NxApexRenderable* GetApexRenderable();

	void AddToApexScene();
	void RemoveFromApexScene();

	//////////////////////////////////////////////////////////////////////////
	// IInitialize
	bool Initialize();

	//////////////////////////////////////////////////////////////////////////
	// IBlueAsyncResNotifyTarget
	void ReleaseCachedData( BlueAsyncRes* p );
	void RebuildCachedData( BlueAsyncRes* p );

#if APEX_ENABLED


protected:
	// Sets the resource path, triggering the resource load via the resource
	// manager. Note that the resource is loaded asynchronously so if it wasn't
	// already in memory it may take some time before the actor is fully active.
	void SetResPath( const std::string& val );
	const std::string& GetResPath() const;

	void SetVisualize( bool b );
	bool GetVisualize();


	void Cleanup();

protected:
	std::string m_name;
	std::string m_resPath;

	// Data used for driving the apex morph target features.

	Tr2ApexResPtr m_apexRes;
	physx::apex::NxFieldBoundaryActor* m_forcefieldActor;

	// Keep track of whether the object is in a scene. We may be added
	// to a scene before the resource has finished loading - in that
	// case we must create the actor as soon as the get the load finished
	// notification.
	bool m_isInScene;

	// LOD weights
	float m_maxDistance;
	float m_distanceWeight;
	float m_bias;
	float m_benefitBias;

#endif // APEX_ENABLED

};

TYPEDEF_BLUECLASS( Tr2ForceFieldActor );
#endif

#endif //Tr2ForceFieldActor_h
