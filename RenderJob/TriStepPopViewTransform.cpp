#include "StdAfx.h"
#include "TriStepPopViewTransform.h"
#include "Tr2Renderer.h"

TriStepResult TriStepPopViewTransform::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	Tr2Renderer::PopViewTransform();
	return RS_OK;
}
