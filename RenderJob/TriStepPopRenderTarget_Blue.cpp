#include "StdAfx.h"
#include "TriStepPopRenderTarget.h"
#include "TriRenderStep.h"


BLUE_DEFINE( TriStepPopRenderTarget );

const Be::ClassInfo* TriStepPopRenderTarget::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriStepPopRenderTarget, "" )

		MAP_INTERFACE( TriRenderStep )
		MAP_INTERFACE( TriStepPopRenderTarget )

	EXPOSURE_CHAINTO( TriRenderStep )
}