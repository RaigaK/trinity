#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "WodReceivesLights.h"

BLUE_DEFINE( WodReceivesLights );

const Be::ClassInfo* WodReceivesLights::ExposeToBlue()
{
    EXPOSURE_BEGIN( WodReceivesLights, "" )
        MAP_INTERFACE( WodReceivesLights )
        MAP_INTERFACE( IRoot )

		MAP_ATTRIBUTE( "numLights", m_numLights, "Number of Lights", Be::READ )
		MAP_ATTRIBUTE( "receivedLights", m_receivedLights, "", Be::READ )

    EXPOSURE_END()
}

#endif
