#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2WindActor.h"
#if USE_APEX_WIND

#include "Tr2ApexRes.h"
#include "TriSettingsRegistrar.h"
#include "blue/include/IBlueResMan.h"
#include "Resources/TriGrannyRes.h"

#include "Apex.h"

#include "NxWindActor.h"
#include "NxWindAsset.h"
#include "NxParamUtils.h"

static bool s_apexHardwareClothEnabled = true;
TRI_REGISTER_SETTING( "apexHardwareClothEnabled", s_apexHardwareClothEnabled );

Tr2WindActor::Tr2WindActor( IRoot* lockobj ) :
	m_windActor( NULL ),
	m_isInScene( false ),
	m_maxDistance( 100.0f ),
	m_distanceWeight( 1.0f ),
	m_bias( 0.0f ),
	m_benefitBias( 0.0f )
{
}

Tr2WindActor::~Tr2WindActor()
{
	Cleanup();

	if( m_apexRes )
	{
		m_apexRes->RemoveNotifyTarget( this );
	}

}

bool Tr2WindActor::Initialize()
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

void Tr2WindActor::AddToApexScene()
{
	m_isInScene = true;

	if( !m_apexRes )
	{
		// No wind resource, can't create the actor.
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
		CCP_LOGERR( "Tr2WindActor::AddToApexScene: %S has no wind asset", m_apexRes->GetPath() );
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

	m_windActor = static_cast<physx::apex::NxWindActor*>(apexActor);
}

void Tr2WindActor::RemoveFromApexScene()
{
	m_isInScene = false;
	Cleanup();
}

void Tr2WindActor::ReleaseCachedData( BlueAsyncRes* p )
{
	Cleanup();
}

void Tr2WindActor::RebuildCachedData( BlueAsyncRes* p )
{
	if( m_isInScene )
	{
		AddToApexScene();
	}
}

const std::string& Tr2WindActor::GetResPath() const
{
	return m_resPath;
}

void Tr2WindActor::SetResPath( const std::string& val )
{
	m_resPath = val;
	Initialize();
}

void Tr2WindActor::Cleanup()
{
	if( m_windActor )
	{
		if( g_Tr2Apex->ApexIsClothSimInProgress() )
		{
			g_Tr2Apex->ApexDelayReleaseActor( m_windActor );
		}
		else
		{
			m_windActor->release();
		}
		m_windActor = NULL;
	}

}

void Tr2WindActor::SetVisualize( bool b )
{
	CCP_ASSERT(m_windActor);
	if ( m_windActor )
	{
		// TODO:JWR
	}
}

bool Tr2WindActor::GetVisualize()
{
	bool ret = false;
	CCP_ASSERT(m_windActor);
	if ( m_windActor )
	{
		// TODO:JWR
	}
	return ret;
}


#endif

#endif