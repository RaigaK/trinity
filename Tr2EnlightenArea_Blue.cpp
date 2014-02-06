#include "StdAfx.h"
#include "Tr2EnlightenArea.h"

BLUE_DEFINE( Tr2EnlightenArea );

const Be::ClassInfo* Tr2EnlightenArea::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2EnlightenArea, "" )
		MAP_INTERFACE( Tr2EnlightenArea )
		MAP_INTERFACE( INotify )

		MAP_ATTRIBUTE( "albedoColor", m_albedoColor, "The color that enlighten uses to reflect light for this surface", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "emissiveColor", m_emissiveColor, "The color that enlighten uses to emit light from this surface", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "isEmissive", m_isEmissive, "", Be::READWRITE | Be::PERSIST | Be::NOTIFY )

	EXPOSURE_CHAINTO( Tr2MeshArea )
}
