#include "StdAfx.h"
#include "Tr2CpuSkinnedModel.h"

BLUE_DEFINE( Tr2CpuSkinnedModel );

// ------------------------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2CpuSkinnedModel::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2CpuSkinnedModel, "" )

		MAP_INTERFACE( Tr2CpuSkinnedModel )

	EXPOSURE_CHAINTO( Tr2SkinnedModel )
}
