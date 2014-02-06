#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2ApexEmitterActor.h"

#if USE_APEX_PARTICLES
#include "Resources/TriGrannyRes.h"

BLUE_DEFINE( Tr2ApexEmitterActor );

const Be::ClassInfo* Tr2ApexEmitterActor::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2ApexEmitterActor, "" )
        MAP_INTERFACE( Tr2ApexEmitterActor )
		MAP_INTERFACE( IInitialize )

		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST )
		MAP_PROPERTY( "resPath", GetResPath, SetResPath, "Resource path to ApexEmitter asset file" )
		MAP_ATTRIBUTE( "resPath", m_resPath, "", Be::PERSISTONLY )
		MAP_ATTRIBUTE( "ApexRes", m_apexRes, "Resource loaded from resPath", Be::READ )

		MAP_PROPERTY( "resIofxPath", GetResIofxPath, SetResIofxPath, "Resource path to Apex IOFX asset file" )
		MAP_ATTRIBUTE( "resIofxPath", m_resIofxPath, "", Be::PERSISTONLY )
		MAP_ATTRIBUTE( "ApexIofxRes", m_apexIofxRes, "Apex IOFX Resource loaded from resPath", Be::READ )

		MAP_PROPERTY( "resIosPath", GetResIosPath, SetResIosPath, "Resource path to Apex IOS asset file" )
		MAP_ATTRIBUTE( "resIosPath", m_resIosPath, "", Be::PERSISTONLY )
		MAP_ATTRIBUTE( "ApexIosRes", m_apexIosRes, "Apex IOS Resource loaded from resPath", Be::READ )


		MAP_PROPERTY
		( 
			"visualize", 
			GetVisualize, 
			SetVisualize, 
			"Enable PhysX debug visualization for this particular actor."
		)

		MAP_ATTRIBUTE( "isInScene", m_isInScene, "Has the actor been added to a scene.", Be::READ )


		MAP_METHOD_AND_WRAP
		(
		"AddToApexScene",
		AddToApexScene,
		"Add this object to the currently active apex scene"
		)

		MAP_METHOD_AND_WRAP
		(
		"AssetsLoaded",
		AssetsLoaded,
		"Returns true if the assets have been loaded"
		)

		MAP_METHOD_AND_WRAP
		(
		"LaunchApexParamEditor",
		LaunchApexParamEditor,
		"Returns true if the Apex Parameter Editor has been succesfully launched"
		)


	EXPOSURE_END()
}

#endif
#endif
