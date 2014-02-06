#include "StdAfx.h"
#include "Tr2SkinnedModelBuilderBlend.h"

BLUE_DEFINE( Tr2SkinnedModelBuilderBlend );

const Be::ClassInfo* Tr2SkinnedModelBuilderBlend::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2SkinnedModelBuilderBlend, "" )
        MAP_INTERFACE( Tr2SkinnedModelBuilderBlend )

		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE )
		MAP_ATTRIBUTE( "power", m_power, "", Be::READWRITE )

	EXPOSURE_END()
}

