#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2ExplosionActor.h"
#if USE_APEX_EXPLOSION
#include "Tr2ApexRes.h"
#include "TriSettingsRegistrar.h"
#include "blue/include/IBlueResMan.h"
#include "Resources/TriGrannyRes.h"

#include "Apex.h"

#include "NxExplosionActor.h"
#include "NxExplosionAsset.h"
#include "NxParamUtils.h"

static bool s_apexHardwareClothEnabled = true;
TRI_REGISTER_SETTING( "apexHardwareClothEnabled", s_apexHardwareClothEnabled );

Tr2ExplosionActor::Tr2ExplosionActor( IRoot* lockobj ) :
	m_explosionActor( NULL ),
	m_isInScene( false ),
	m_maxDistance( 100.0f ),
	m_distanceWeight( 1.0f ),
	m_bias( 0.0f ),
	m_benefitBias( 0.0f )
{
}

Tr2ExplosionActor::~Tr2ExplosionActor()
{
	Cleanup();

	if( m_apexRes )
	{
		m_apexRes->RemoveNotifyTarget( this );
	}

}

bool Tr2ExplosionActor::Initialize()
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

void Tr2ExplosionActor::AddToApexScene()
{
	m_isInScene = true;

	if( !m_apexRes )
	{
		// No explosion resource, can't create the actor.
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
		CCP_LOGERR( "Tr2ExplosionActor::AddToApexScene: %S has no explosion asset", m_apexRes->GetPath() );
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

	m_explosionActor = static_cast<physx::apex::NxExplosionActor*>(apexActor);
}

void Tr2ExplosionActor::RemoveFromApexScene()
{
	m_isInScene = false;
	Cleanup();
}

void Tr2ExplosionActor::ReleaseCachedData( BlueAsyncRes* p )
{
	Cleanup();
}

void Tr2ExplosionActor::RebuildCachedData( BlueAsyncRes* p )
{
	if( m_isInScene )
	{
		AddToApexScene();
	}
}

const std::string& Tr2ExplosionActor::GetResPath() const
{
	return m_resPath;
}

void Tr2ExplosionActor::SetResPath( const std::string& val )
{
	m_resPath = val;
	Initialize();
}

void Tr2ExplosionActor::Cleanup()
{
	if( m_explosionActor )
	{
		if( g_Tr2Apex->ApexIsClothSimInProgress() )
		{
			g_Tr2Apex->ApexDelayReleaseActor( m_explosionActor );
		}
		else
		{
			m_explosionActor->release();
		}
		m_explosionActor = NULL;
	}

}

void Tr2ExplosionActor::SetVisualize( bool b )
{
	CCP_ASSERT(m_explosionActor);
	if ( m_explosionActor )
	{
		// TODO:JWR
	}
}

bool Tr2ExplosionActor::GetVisualize()
{
	bool ret = false;
	CCP_ASSERT(m_explosionActor);
	if ( m_explosionActor )
	{
		// TODO:JWR
	}
	return ret;
}

#endif

#endif