#include "StdAfx.h"
#include "TriStepPopProjection.h"
#include "Tr2Renderer.h"

TriStepResult TriStepPopProjection::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	Tr2Renderer::PopProjection();
	return RS_OK;
}
