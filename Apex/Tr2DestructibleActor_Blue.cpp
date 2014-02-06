#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2DestructibleActor.h"

#if USE_APEX_DESTRUCTION

#include "Resources/TriGrannyRes.h"

BLUE_DEFINE( Tr2DestructibleActor );

const Be::ClassInfo* Tr2DestructibleActor::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2DestructibleActor, "" )
        MAP_INTERFACE( Tr2DestructibleActor )
		MAP_INTERFACE( IInitialize )

		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST )
		MAP_PROPERTY( "resPath", GetResPath, SetResPath, "Resource path to an APEX asset file" )
		MAP_ATTRIBUTE( "resPath", m_resPath, "", Be::PERSISTONLY )
		MAP_ATTRIBUTE( "ApexRes", m_apexRes, "Resource loaded from resPath", Be::READ )

		MAP_ATTRIBUTE( "effect", m_effect, "Effect used to render the cloth asset", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "depthEffect", m_depthEffect, "Effect used to render the  asset into shadow map", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "depthNormalEffect", m_depthNormalEffect, "Effect used to render the asset during pre pass", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "effectReversed", m_effectReversed, "Effect used to render the destructible asset with triangles in reversed order", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "depthEffectReversed", m_depthEffectReversed, "Effect used to render the destrtructible asset into shadow map with triangles in reversed order", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "depthNormalEffectReversed", m_depthNormalEffectReversed, "Effect used to render the destructible asset during pre pass with triangles in reversed order", Be::READWRITE | Be::PERSIST )

		MAP_PROPERTY
		( 
			"visualize", 
			GetVisualize, 
			SetVisualize, 
			"Enable PhysX debug visualization for this particular actor."
		)

		MAP_ATTRIBUTE( "isInScene", m_isInScene, "Has the actor been added to a scene.", Be::READ )

		MAP_ATTRIBUTE
		(
			"useTransparentBatches",
			m_useTransparentBatches,
			"Emit this apex mesh as transparent batches? False by default, making it Decal.",
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"useSHLighting",
			m_useSHLighting,
			"Use SH lighting instead of direct (for transparent meshes only). False by default.",
			Be::READWRITE | Be::PERSIST
		)


		MAP_METHOD_AND_WRAP
		(
		"AddToApexScene",
		AddToApexScene,
		"Add this object to the currently active apex scene"
		)

	EXPOSURE_END()
}

#endif
#endif
