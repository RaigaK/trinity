#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2DestructibleActor.h"

#if USE_APEX_DESTRUCTION
#include "Tr2ApexRes.h"
#include "TriSettingsRegistrar.h"
#include "blue/include/IBlueResMan.h"
#include "Resources/TriGrannyRes.h"

#include "Apex.h"

#include "NxDestructibleActor.h"
#include "NxDestructibleAsset.h"
#include "NxParamUtils.h"

static bool s_apexHardwareClothEnabled = true;
TRI_REGISTER_SETTING( "apexHardwareClothEnabled", s_apexHardwareClothEnabled );

Tr2DestructibleActor::Tr2DestructibleActor( IRoot* lockobj ) :
	m_destructibleActor( NULL ),
	m_isInScene( false ),
	m_useTransparentBatches( false ),
	m_useSHLighting( false ),
	m_maxDistance( 100.0f ),
	m_distanceWeight( 1.0f ),
	m_bias( 0.0f ),
	m_benefitBias( 0.0f )
{
}

Tr2DestructibleActor::~Tr2DestructibleActor()
{
	Cleanup();

	if( m_apexRes )
	{
		m_apexRes->RemoveNotifyTarget( this );
	}

}

bool Tr2DestructibleActor::Initialize()
{
	Cleanup();

	if( m_apexRes )
	{
		m_apexRes->RemoveNotifyTarget( this );
	}

	IBlueResource* p = BeResMan->GetResource( m_resPath, "apex" );
	m_apexRes.Attach( dynamic_cast<Tr2ApexRes*>( p ) );

	if( m_apexRes )
	{
		m_apexRes->AddNotifyTarget( this );
	}	

	return true;
}

void Tr2DestructibleActor::AddToApexScene()
{
	m_isInScene = true;

	if( !m_apexRes )
	{
		// No destructible resource, can't create the actor.
		return;
	}

	if( m_apexRes->IsLoading() )
	{
		// Not finished loading - we'll come back once it is.
		return;
	}

	physx::apex::NxApexAsset* asset = m_apexRes->GetAsset();
	if( !asset )
	{
		CCP_LOGERR( "Tr2DestructibleActor::AddToApexScene: %S has no destructible asset", m_apexRes->GetPath() );
		return;
	}

	Cleanup();

	NxParameterized::Interface* actorDesc = asset->getDefaultActorDesc();
	CCP_ASSERT( actorDesc != NULL );

	{
		#define VERIFY_PARAM(_A) { NxParameterized::ErrorType error = _A; CCP_ASSERT(error == NxParameterized::ERROR_NONE); }

		NxParameterized::Handle actorHandle(*actorDesc);

		// No util method for this
	}


	// create the actor
	physx::apex::NxApexActor* apexActor = asset->createApexActor( *actorDesc, *g_Tr2Apex->GetApexScene() );
	CCP_ASSERT( apexActor );

	m_destructibleActor = static_cast<physx::apex::NxDestructibleActor*>(apexActor);
}

void Tr2DestructibleActor::RemoveFromApexScene()
{
	m_isInScene = false;
	Cleanup();
}

void Tr2DestructibleActor::ReleaseCachedData( BlueAsyncRes* p )
{
	Cleanup();
}

void Tr2DestructibleActor::RebuildCachedData( BlueAsyncRes* p )
{
	if( m_isInScene )
	{
		AddToApexScene();
	}
}

const std::string& Tr2DestructibleActor::GetResPath() const
{
	return m_resPath;
}

void Tr2DestructibleActor::SetResPath( const std::string& val )
{
	m_resPath = val;
	Initialize();
}

void Tr2DestructibleActor::Cleanup()
{
	if( m_destructibleActor )
	{
		if( g_Tr2Apex->ApexIsClothSimInProgress() )
		{
			g_Tr2Apex->ApexDelayReleaseActor( m_destructibleActor );
		}
		else
		{
			m_destructibleActor->release();
		}
		m_destructibleActor = NULL;
	}

}

physx::apex::NxApexRenderable* Tr2DestructibleActor::GetApexRenderable()
{
	return m_destructibleActor;
}

void Tr2DestructibleActor::SetVisualize( bool b )
{
	CCP_ASSERT(m_destructibleActor);
	if ( m_destructibleActor )
	{
		// TODO:JWR
	}
}

bool Tr2DestructibleActor::GetVisualize()
{
	bool ret = false;
	CCP_ASSERT(m_destructibleActor);
	if ( m_destructibleActor )
	{
		// TODO:JWR
	}
	return ret;
}

ITr2ShaderMaterial* Tr2DestructibleActor::GetEffect()
{
	return m_effect;
}

ITr2ShaderMaterial* Tr2DestructibleActor::GetDepthEffect()
{
	return m_depthEffect;
}

ITr2ShaderMaterial* Tr2DestructibleActor::GetDepthNormalEffect()
{
	return m_depthNormalEffect;
}

// -------------------------------------------------------------
// Description:
//   Returns an effect to use with reversed order of triangle 
//   rendering for forward rendering.
// Return value:
//   An effect to use with reversed triangle order for forward redering 
// -------------------------------------------------------------
ITr2ShaderMaterial* Tr2DestructibleActor::GetEffectReversed()
{
	return m_effectReversed;
}

// -------------------------------------------------------------
// Description:
//   Returns an effect to use with reversed order of triangle 
//   rendering for shadow rendering.
// Return value:
//   An effect to use with reversed triangle order for shadow redering 
// -------------------------------------------------------------
ITr2ShaderMaterial* Tr2DestructibleActor::GetDepthEffectReversed()
{
	return m_depthEffectReversed;
}

// -------------------------------------------------------------
// Description:
//   Returns an effect to use with reversed order of triangle 
//   rendering for prepass depth/normal rendering.
// Return value:
//   An effect to use with reversed triangle order for prepass 
//   depth/normal redering 
// -------------------------------------------------------------
ITr2ShaderMaterial* Tr2DestructibleActor::GetDepthNormalEffectReversed()
{
	return m_depthNormalEffectReversed;
}


bool Tr2DestructibleActor::GetUseTransparentBatches() const
{
	return m_useTransparentBatches;
}

// --------------------------------------------------------------------------------------
// Description:
//   Returns a flag indicating that the mesh requires SH lighting coefficients for 
//   rendering instead of normal direct lighting. Only used for transparent meshes
//   (when GetUseTransparentBatches() is true).
// Return Value:
//   true If mesh requires SH lighting
//   false If mesh requires direct lighting
// --------------------------------------------------------------------------------------
bool Tr2DestructibleActor::GetUseSHLighting() const
{
	return m_useSHLighting;
}

#endif

#endif