#pragma once
#ifndef Tr2ExplosionActor_h
#define Tr2ExplosionActor_h

#include "Apex.h"
#if USE_APEX_EXPLOSION

#include "blue\include\BlueAsyncRes.h"
#include "NxMat34.h"

BLUE_DECLARE( Tr2ExplosionActor );
BLUE_DECLARE( Tr2ApexRes );

namespace physx
{
	class PxMat34;

	namespace apex {
		class NxExplosionActor;
		class NxApexRenderable;
	}
}

// The Tr2ExplosionActor class is a wrapper around the NxExplosionActor class
// from Apex. It is an instance of a piece of explosion coming from a explosion
// asset (NxExplosionAsset), wrapped in a Tr2ApexRes.
class Tr2ExplosionActor:
	public IInitialize,
	public IBlueAsyncResNotifyTarget
{
public:
	EXPOSE_TO_BLUE();
	using IInitialize::Lock;
	using IInitialize::Unlock;

	Tr2ExplosionActor( IRoot* lockobj = NULL );
	~Tr2ExplosionActor();

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
	physx::apex::NxExplosionActor* m_explosionActor;

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

TYPEDEF_BLUECLASS( Tr2ExplosionActor );

#endif

#endif //Tr2ExplosionActor_h
