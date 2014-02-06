#include "StdAfx.h"
#include "TriStepPushViewport.h"
#include "Tr2Renderer.h"

TriStepResult TriStepPushViewport::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	Tr2Renderer::PushViewport();
	return RS_OK;
}
