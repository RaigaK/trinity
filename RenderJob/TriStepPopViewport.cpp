#include "StdAfx.h"
#include "TriStepPopViewport.h"
#include "Tr2Renderer.h"

TriStepResult TriStepPopViewport::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	Tr2Renderer::PopViewport();
	return RS_OK;
}
