#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "UmbraLibrary.h"

BLUE_DEFINE( UmbraLibrary );

const Be::ClassInfo* UmbraLibrary::ExposeToBlue()
{
	EXPOSURE_BEGIN( UmbraLibrary, "" )
		MAP_INTERFACE( UmbraLibrary )

		MAP_PROPERTY( "drawBoundingBoxes", GetDrawBoundingBoxes, SetDrawBoundingBoxes, "" )
		MAP_PROPERTY( "drawRegionsOfInfluence", GetDrawRegionsOfInfluence, SetDrawRegionsOfInfluence, "" )
		MAP_PROPERTY( "drawVirtualCameraAxii", GetDrawVirtualCameraAxii, SetDrawVirtualCameraAxii, "" )
		MAP_PROPERTY( "drawWriteModels", GetDrawWriteModels, SetDrawWriteModels, "" )

		MAP_PROPERTY_READONLY( "memoryUsed", GetMemoryUsed, "" )
		MAP_PROPERTY_READONLY( "liveCameraCount", GetLiveCameraCount, "" )
		MAP_PROPERTY_READONLY( "liveCellCount", GetLiveCellCount, "" )
		MAP_PROPERTY_READONLY( "liveModelCount", GetLiveModelCount, "" )
		MAP_PROPERTY_READONLY( "liveObjectCount", GetLiveObjectCount, "" )
		MAP_PROPERTY_READONLY( "livePortalCount", GetLivePortalCount, "" )
		MAP_PROPERTY_READONLY( "liveROICount", GetLiveROICount, "" )
		MAP_PROPERTY_READONLY( "liveNodeCount", GetLiveNodeCount, "" )
		MAP_PROPERTY_READONLY( "liveInstanceCount", GetLiveInstanceCount, "" )

		EXPOSURE_END()
}

#endif
