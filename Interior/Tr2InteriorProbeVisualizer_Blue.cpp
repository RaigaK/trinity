#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "Tr2InteriorProbeVisualizer.h"


BLUE_DEFINE( Tr2InteriorProbeVisualizer );

// ------------------------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2InteriorProbeVisualizer::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2InteriorProbeVisualizer, "" )
        MAP_INTERFACE( Tr2InteriorProbeVisualizer )
		MAP_ATTRIBUTE( "effect", m_effect, "Light probe debug effect", Be::READWRITE )
	EXPOSURE_END()
}

#endif
