#include "StdAfx.h"
#include "TriStepPushViewTransform.h"
#include "Tr2Renderer.h"

TriStepResult TriStepPushViewTransform::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	Tr2Renderer::PushViewTransform();
	return RS_OK;
}
