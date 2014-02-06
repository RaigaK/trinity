#include "StdAfx.h"
#include "TriStepPopRenderTarget.h"
#include "Tr2Renderer.h"


TriStepPopRenderTarget::TriStepPopRenderTarget( IRoot* lockobj )
{
}

TriStepPopRenderTarget::~TriStepPopRenderTarget(void)
{
}

TriStepResult TriStepPopRenderTarget::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	Tr2Renderer::PopRenderTarget( renderContext );
	return RS_OK;
}