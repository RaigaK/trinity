#include "StdAfx.h"
#include "TriStepPushProjection.h"
#include "Tr2Renderer.h"

TriStepResult TriStepPushProjection::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	Tr2Renderer::PushProjection();
	return RS_OK;
}
