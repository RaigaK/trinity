#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2ExampleFSActor.h"

#if USE_APEX_FIELD_SAMPLER
#include "Tr2ApexRes.h"
#include "TriSettingsRegistrar.h"
#include "blue/include/IBlueResMan.h"
#include "Resources/TriGrannyRes.h"

#include "Apex.h"

#include "NxExampleFSActor.h"
#include "NxExampleFSAsset.h"
#include "NxParamUtils.h"

static bool s_apexHardwareClothEnabled = true;
TRI_REGISTER_SETTING( "apexHardwareClothEnabled", s_apexHardwareClothEnabled );

Tr2ExampleFSActor::Tr2ExampleFSActor( IRoot* lockobj ) :
	m_exampleFSActor( NULL ),
	m_isInScene( false ),
	m_maxDistance( 100.0f ),
	m_distanceWeight( 1.0f ),
	m_bias( 0.0f ),
	m_benefitBias( 0.0f )
{
}

Tr2ExampleFSActor::~Tr2ExampleFSActor()
{
	Cleanup();

	if( m_apexRes )
	{
		m_apexRes->RemoveNotifyTarget( this );
	}

}

bool Tr2ExampleFSActor::Initialize()
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

void Tr2ExampleFSActor::AddToApexScene()
{
	m_isInScene = true;

	if( !m_apexRes )
	{
		// No exampleFS resource, can't create the actor.
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
		CCP_LOGERR( "Tr2ExampleFSActor::AddToApexScene: %S has no exampleFS asset", m_apexRes->GetPath() );
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

	m_exampleFSActor = static_cast<physx::apex::NxExampleFSActor*>(apexActor);
}

void Tr2ExampleFSActor::RemoveFromApexScene()
{
	m_isInScene = false;
	Cleanup();
}

void Tr2ExampleFSActor::ReleaseCachedData( BlueAsyncRes* p )
{
	Cleanup();
}

void Tr2ExampleFSActor::RebuildCachedData( BlueAsyncRes* p )
{
	if( m_isInScene )
	{
		AddToApexScene();
	}
}

const std::string& Tr2ExampleFSActor::GetResPath() const
{
	return m_resPath;
}

void Tr2ExampleFSActor::SetResPath( const std::string& val )
{
	m_resPath = val;
	Initialize();
}

void Tr2ExampleFSActor::Cleanup()
{
	if( m_exampleFSActor )
	{
		if( g_Tr2Apex->ApexIsClothSimInProgress() )
		{
			g_Tr2Apex->ApexDelayReleaseActor( m_exampleFSActor );
		}
		else
		{
			m_exampleFSActor->release();
		}
		m_exampleFSActor = NULL;
	}

}

void Tr2ExampleFSActor::SetVisualize( bool b )
{
	CCP_ASSERT(m_exampleFSActor);
	if ( m_exampleFSActor )
	{
		// TODO:JWR
	}
}

bool Tr2ExampleFSActor::GetVisualize()
{
	bool ret = false;
	CCP_ASSERT(m_exampleFSActor);
	if ( m_exampleFSActor )
	{
		// TODO:JWR
	}
	return ret;
}

#endif

#endif