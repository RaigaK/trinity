#include "StdAfx.h"
#include "TriStepPopDepthStencil.h"
#include "Tr2Renderer.h"


TriStepPopDepthStencil::TriStepPopDepthStencil( IRoot* lockobj )
{
}

TriStepPopDepthStencil::~TriStepPopDepthStencil(void)
{
}

TriStepResult TriStepPopDepthStencil::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	Tr2Renderer::PopDepthStencilBuffer( renderContext );
	return RS_OK;
}