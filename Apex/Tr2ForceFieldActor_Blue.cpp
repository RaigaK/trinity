#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2ForceFieldActor.h"
#if USE_APEX_FORCE_FIELD
#include "Resources/TriGrannyRes.h"

BLUE_DEFINE( Tr2ForceFieldActor );

const Be::ClassInfo* Tr2ForceFieldActor::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2ForceFieldActor, "" )
        MAP_INTERFACE( Tr2ForceFieldActor )
		MAP_INTERFACE( IInitialize )

		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST )
		MAP_PROPERTY( "resPath", GetResPath, SetResPath, "Resource path to ForceField asset file" )
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
