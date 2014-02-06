////////////////////////////////////////////////////////////
//
//    Created:   August 2013
//    Copyright: CCP 2013
//
#include "StdAfx.h"
#include "EveSOFDataMgr.h"

BLUE_DEFINE( EveSOFDataMgr );

const Be::ClassInfo* EveSOFDataMgr::ExposeToBlue()
{
    EXPOSURE_BEGIN( EveSOFDataMgr, "" )
        MAP_INTERFACE( EveSOFDataMgr )

		MAP_METHOD_AND_WRAP( "LoadData", LoadData, "Inject all the data into this mgr" )

		MAP_METHOD_AND_WRAP( "HasFactionData", HasFactionData, "Does this faction exist?" )
		MAP_METHOD_AND_WRAP( "HasHullData", HasHullData, "Does this hull exist?" )
		MAP_METHOD_AND_WRAP( "HasRaceData", HasRaceData, "Does this race exist?" )

    EXPOSURE_END()
}
