#pragma once
#ifndef TriStepPopDepthStencil_h_
#define TriStepPopDepthStencil_h_


#include "TriRenderStep.h"

BLUE_CLASS( TriStepPopDepthStencil ) : public TriRenderStep
{
public:
	EXPOSE_TO_BLUE();
	
	TriStepPopDepthStencil( IRoot* lockobj = 0);
	~TriStepPopDepthStencil(void);

	//IRenderStep
	TriStepResult Execute( Be::Time time, Tr2RenderContext& renderContext );
};

TYPEDEF_BLUECLASS( TriStepPopDepthStencil );

#endif
