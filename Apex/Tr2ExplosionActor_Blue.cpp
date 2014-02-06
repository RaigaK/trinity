#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2ExplosionActor.h"

#if USE_APEX_EXPLOSION
#include "Resources/TriGrannyRes.h"

BLUE_DEFINE( Tr2ExplosionActor );

const Be::ClassInfo* Tr2ExplosionActor::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2ExplosionActor, "" )
        MAP_INTERFACE( Tr2ExplosionActor )
		MAP_INTERFACE( IInitialize )

		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST )
		MAP_PROPERTY( "resPath", GetResPath, SetResPath, "Resource path to Explosion asset file" )
		MAP_ATTRIBUTE( "resPath", m_resPath, "", Be::PERSISTONLY )
		MAP_ATTRIBUTE( "ApexRes", m_apexRes, "Resource loaded from resPath", Be::READ )


		MAP_PROPERTY
		( 
			"visualize", 
			GetVisualize, 
			SetVisualize, 
			"Enable PhysX debug visualization for this particular actor."
		)

		MAP_ATTRIBUTE( "isInScene", m_isInScene, "Has the actor been added to a scene.", Be::READ )

	EXPOSURE_END()
}
#endif
#endif
