#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2ApexEmitterActor.h"

#if USE_APEX_PARTICLES

#include "Tr2ApexRes.h"
#include "TriSettingsRegistrar.h"
#include "blue/include/IBlueResMan.h"
#include "Resources/TriGrannyRes.h"

#include "Apex.h"

#include "NxApexEmitterActor.h"
#include "NxApexEmitterAsset.h"
#include "NxParamUtils.h"

static bool s_apexHardwareClothEnabled = true;
TRI_REGISTER_SETTING( "apexHardwareClothEnabled", s_apexHardwareClothEnabled );

Tr2ApexEmitterActor::Tr2ApexEmitterActor( IRoot* lockobj ) :
	m_emitterActor( NULL ),
	m_isInScene( false ),
	m_maxDistance( 100.0f ),
	m_distanceWeight( 1.0f ),
	m_bias( 0.0f ),
	m_benefitBias( 0.0f ),
	m_apexRes(NULL),
	m_apexIofxRes(NULL),
	m_apexIosRes(NULL)
{
}

#define REMOVE_NOTIFY_TARGET(x) if ( x ) { x->RemoveNotifyTarget(this); x = NULL; }

Tr2ApexEmitterActor::~Tr2ApexEmitterActor()
{
	Cleanup();
}

bool Tr2ApexEmitterActor::Initialize()
{
	Cleanup();
	return true;
}

bool Tr2ApexEmitterActor::LaunchApexParamEditor(void)
{
	bool ret = false;
	return ret;
}

bool Tr2ApexEmitterActor::AssetsLoaded(void)
{
	bool ret = false;

	// Begin loading the Apex Emitter Asset
	// Begin loading the IOFX asset
	if ( m_apexIofxRes == NULL )
	{
		REMOVE_NOTIFY_TARGET(m_apexIofxRes);
		IBlueResource* p = BeResMan->GetResource( m_resIofxPath, "apex" );
		m_apexIofxRes.Attach( dynamic_cast<Tr2ApexRes*>( p ) );
		if( m_apexIofxRes )
		{
			m_apexIofxRes->AddNotifyTarget( this );
		}	
	}
	// Begin loading the IOS asset
	else if ( m_apexIosRes == NULL )
	{
		REMOVE_NOTIFY_TARGET(m_apexIosRes);
		IBlueResource* p = BeResMan->GetResource( m_resIosPath, "apex" );
		m_apexIosRes.Attach( dynamic_cast<Tr2ApexRes*>( p ) );
		if( m_apexIosRes )
		{
			m_apexIosRes->AddNotifyTarget( this );
		}	
	}
	else if ( m_apexRes == NULL )
	{
		REMOVE_NOTIFY_TARGET(m_apexRes);
		IBlueResource* p = BeResMan->GetResource( m_resPath, "apex" );
		m_apexRes.Attach( dynamic_cast<Tr2ApexRes*>( p ) );
		if( m_apexRes )
		{
			m_apexRes->AddNotifyTarget( this );
		}	
	}


	if ( m_apexRes && m_apexIosRes && m_apexIofxRes && !m_apexRes->IsLoading() && !m_apexIofxRes->IsLoading() && !m_apexIosRes->IsLoading() )
	{
		physx::apex::NxApexAsset* asset = m_apexRes->GetAsset();
		if( !asset )
		{
			CCP_LOGERR( "Tr2ApexEmitterActor::AssetsLoaded %S has no emitter asset", m_apexRes->GetPath() );
		}
		else
		{
			asset = m_apexIofxRes->GetAsset();
			if( !asset )
			{
				CCP_LOGERR( "Tr2ApexEmitterActor::AssetsLoaded %S has no IOFX asset", m_apexRes->GetPath() );
			}
			else
			{
				asset = m_apexIosRes->GetAsset();
				if( !asset )
				{
					CCP_LOGERR( "Tr2ApexEmitterActor::AssetsLoaded %S has no IOS asset", m_apexRes->GetPath() );
				}
				else
				{
					ret = true;
				}
			}
		}
	}
	return ret;
}

void Tr2ApexEmitterActor::AddToApexScene()
{
	m_isInScene = true;

	if ( !AssetsLoaded() ) return;

	Cleanup();
	physx::apex::NxApexAsset* asset = m_apexRes->GetAsset();
	NxParameterized::Interface* actorDesc = asset->getDefaultActorDesc();
	CCP_ASSERT( actorDesc != NULL );

	{
		#define VERIFY_PARAM(_A) { NxParameterized::ErrorType error = _A; CCP_ASSERT(error == NxParameterized::ERROR_NONE); }

		NxParameterized::Handle actorHandle(*actorDesc);

		// No util method for this
	}

	// TODO...a

	// create the actor
	physx::apex::NxApexActor* apexActor = asset->createApexActor( *actorDesc, *g_Tr2Apex->GetApexScene() );
	CCP_ASSERT( apexActor );

	m_emitterActor = static_cast<physx::apex::NxApexEmitterActor*>(apexActor);
}

void Tr2ApexEmitterActor::RemoveFromApexScene()
{
	m_isInScene = false;
	Cleanup();
}

void Tr2ApexEmitterActor::ReleaseCachedData( BlueAsyncRes* p )
{
	Cleanup();
}

void Tr2ApexEmitterActor::RebuildCachedData( BlueAsyncRes* p )
{
	if( m_isInScene )
	{
		AddToApexScene();
	}
}

const std::string& Tr2ApexEmitterActor::GetResPath() const
{
	return m_resPath;
}

void Tr2ApexEmitterActor::SetResPath( const std::string& val )
{
	m_resPath = val;
	Initialize();
}

const std::string& Tr2ApexEmitterActor::GetResIofxPath() const
{
	return m_resIofxPath;
}

void Tr2ApexEmitterActor::SetResIofxPath( const std::string& val )
{
	m_resIofxPath = val;
	Initialize();
}

const std::string& Tr2ApexEmitterActor::GetResIosPath() const
{
	return m_resIosPath;
}

void Tr2ApexEmitterActor::SetResIosPath( const std::string& val )
{
	m_resIosPath = val;
	Initialize();
}


void Tr2ApexEmitterActor::Cleanup()
{
	if( m_emitterActor )
	{
		if( g_Tr2Apex->ApexIsClothSimInProgress() )
		{
			g_Tr2Apex->ApexDelayReleaseActor( m_emitterActor );
		}
		else
		{
			m_emitterActor->release();
		}
		m_emitterActor = NULL;
	}
	REMOVE_NOTIFY_TARGET(m_apexRes);
	REMOVE_NOTIFY_TARGET(m_apexIofxRes);
	REMOVE_NOTIFY_TARGET(m_apexIosRes);
}

void Tr2ApexEmitterActor::SetVisualize( bool b )
{
	CCP_ASSERT(m_emitterActor);
	if ( m_emitterActor )
	{
		// TODO:JWR
	}
}

bool Tr2ApexEmitterActor::GetVisualize()
{
	bool ret = false;
	CCP_ASSERT(m_emitterActor);
	if ( m_emitterActor )
	{
		// TODO:JWR
	}
	return ret;
}


#endif

#endif