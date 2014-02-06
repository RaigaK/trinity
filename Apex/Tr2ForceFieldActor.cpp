#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2ForceFieldActor.h"

#if USE_APEX_FORCE_FIELD

#include "Tr2ApexRes.h"
#include "TriSettingsRegistrar.h"
#include "blue/include/IBlueResMan.h"
#include "Resources/TriGrannyRes.h"

#include "Apex.h"

#include "NxFieldBoundaryActor.h"
#include "NxFieldBoundaryAsset.h"
#include "NxParamUtils.h"

static bool s_apexHardwareClothEnabled = true;
TRI_REGISTER_SETTING( "apexHardwareClothEnabled", s_apexHardwareClothEnabled );

Tr2ForceFieldActor::Tr2ForceFieldActor( IRoot* lockobj ) :
	m_forcefieldActor( NULL ),
	m_isInScene( false ),
	m_maxDistance( 100.0f ),
	m_distanceWeight( 1.0f ),
	m_bias( 0.0f ),
	m_benefitBias( 0.0f )
{
}

Tr2ForceFieldActor::~Tr2ForceFieldActor()
{
	Cleanup();

	if( m_apexRes )
	{
		m_apexRes->RemoveNotifyTarget( this );
	}

}

bool Tr2ForceFieldActor::Initialize()
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

void Tr2ForceFieldActor::AddToApexScene()
{
	m_isInScene = true;

	if( !m_apexRes )
	{
		// No forcefield resource, can't create the actor.
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
		CCP_LOGERR( "Tr2ForceFieldActor::AddToApexScene: %S has no forcefield asset", m_apexRes->GetPath() );
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

	m_forcefieldActor = static_cast<physx::apex::NxFieldBoundaryActor*>(apexActor);
}

void Tr2ForceFieldActor::RemoveFromApexScene()
{
	m_isInScene = false;
	Cleanup();
}

void Tr2ForceFieldActor::ReleaseCachedData( BlueAsyncRes* p )
{
	Cleanup();
}

void Tr2ForceFieldActor::RebuildCachedData( BlueAsyncRes* p )
{
	if( m_isInScene )
	{
		AddToApexScene();
	}
}

const std::string& Tr2ForceFieldActor::GetResPath() const
{
	return m_resPath;
}

void Tr2ForceFieldActor::SetResPath( const std::string& val )
{
	m_resPath = val;
	Initialize();
}

void Tr2ForceFieldActor::Cleanup()
{
	if( m_forcefieldActor )
	{
		if( g_Tr2Apex->ApexIsClothSimInProgress() )
		{
			g_Tr2Apex->ApexDelayReleaseActor( m_forcefieldActor );
		}
		else
		{
			m_forcefieldActor->release();
		}
		m_forcefieldActor = NULL;
	}

}

void Tr2ForceFieldActor::SetVisualize( bool b )
{
	CCP_ASSERT(m_forcefieldActor);
	if ( m_forcefieldActor )
	{
		// TODO:JWR
	}
}

bool Tr2ForceFieldActor::GetVisualize()
{
	bool ret = false;
	CCP_ASSERT(m_forcefieldActor);
	if ( m_forcefieldActor )
	{
		// TODO:JWR
	}
	return ret;
}


#endif

#endif