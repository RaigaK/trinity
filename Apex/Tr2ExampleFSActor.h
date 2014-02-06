#pragma once
#ifndef Tr2ExampleFSActor_h
#define Tr2ExampleFSActor_h

#include "Apex.h"
#if USE_APEX_FIELD_SAMPLER

#include "blue\include\BlueAsyncRes.h"
#include "NxMat34.h"

BLUE_DECLARE( Tr2ExampleFSActor );
BLUE_DECLARE( Tr2ApexRes );

namespace physx
{
	class PxMat34;

	namespace apex {
		class NxExampleFSActor;
		class NxApexRenderable;
	}
}

// The Tr2ExampleFSActor class is a wrapper around the NxExampleFSActor class
// from Apex. It is an instance of a piece of exampleFS coming from a exampleFS
// asset (NxExampleFSAsset), wrapped in a Tr2ApexRes.
class Tr2ExampleFSActor:
	public IInitialize,
	public IBlueAsyncResNotifyTarget
{
public:
	EXPOSE_TO_BLUE();
	using IInitialize::Lock;
	using IInitialize::Unlock;

	Tr2ExampleFSActor( IRoot* lockobj = NULL );
	~Tr2ExampleFSActor();

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
	physx::apex::NxExampleFSActor* m_exampleFSActor;

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

TYPEDEF_BLUECLASS( Tr2ExampleFSActor );
#endif

#endif //Tr2ExampleFSActor_h
