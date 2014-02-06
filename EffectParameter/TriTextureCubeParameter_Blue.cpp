#include "StdAfx.h"
#include "TriTextureCubeParameter.h"

BLUE_DEFINE( TriTextureCubeParameter );

const Be::ClassInfo* TriTextureCubeParameter::ExposeToBlue()
{
	EXPOSURE_BEGIN( TriTextureCubeParameter, "" )
	EXPOSURE_CHAINTO( TriTexture2DParameter )
}
