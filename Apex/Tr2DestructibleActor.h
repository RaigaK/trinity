#pragma once
#ifndef Tr2DestructibleActor_h
#define Tr2DestructibleActor_h

#include "Apex/Apex.h"

#if USE_APEX_DESTRUCTION


#include "blue\include\BlueAsyncRes.h"
#include "NxMat34.h"

BLUE_DECLARE( Tr2DestructibleActor );
BLUE_DECLARE( Tr2ApexRes );
BLUE_DECLARE_INTERFACE( ITr2ShaderMaterial );
BLUE_DECLARE( TriGrannyRes );

namespace physx
{
	class PxMat34;

	namespace apex {
		class NxDestructibleActor;
		class NxApexRenderable;
	}
}

// The Tr2DestructibleActor class is a wrapper around the NxDestructibleActor class
// from Apex. It is an instance of a piece of destructible coming from a destructible
// asset (NxDestructibleAsset), wrapped in a Tr2ApexRes.
class Tr2DestructibleActor:
	public IInitialize,
	public IBlueAsyncResNotifyTarget
{
public:
	EXPOSE_TO_BLUE();
	using IInitialize::Lock;
	using IInitialize::Unlock;

	Tr2DestructibleActor( IRoot* lockobj = NULL );
	~Tr2DestructibleActor();

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

	ITr2ShaderMaterial* GetEffect();
	ITr2ShaderMaterial* GetDepthEffect();
	ITr2ShaderMaterial* GetDepthNormalEffect();

	ITr2ShaderMaterial* GetEffectReversed();
	ITr2ShaderMaterial* GetDepthEffectReversed();
	ITr2ShaderMaterial* GetDepthNormalEffectReversed();

	bool GetUseTransparentBatches() const;
	bool GetUseSHLighting() const;


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
	physx::apex::NxDestructibleActor* m_destructibleActor;

	// Keep track of whether the object is in a scene. We may be added
	// to a scene before the resource has finished loading - in that
	// case we must create the actor as soon as the get the load finished
	// notification.
	bool m_isInScene;

	ITr2ShaderMaterialPtr m_effect;
	ITr2ShaderMaterialPtr m_depthEffect;
	ITr2ShaderMaterialPtr m_depthNormalEffect;

	ITr2ShaderMaterialPtr m_effectReversed;
	ITr2ShaderMaterialPtr m_depthEffectReversed;
	ITr2ShaderMaterialPtr m_depthNormalEffectReversed;

	bool m_useTransparentBatches;
	bool m_useSHLighting;

	// LOD weights
	float m_maxDistance;
	float m_distanceWeight;
	float m_bias;
	float m_benefitBias;

#endif // APEX_ENABLED

};

TYPEDEF_BLUECLASS( Tr2DestructibleActor );

#endif //

#endif //Tr2DestructibleActor_h
