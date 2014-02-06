#pragma once
#ifndef TriStepPopRenderTarget_h_
#define TriStepPopRenderTarget_h_


#include "TriRenderStep.h"

BLUE_CLASS( TriStepPopRenderTarget ) : public TriRenderStep
{
public:
	EXPOSE_TO_BLUE();
	
	TriStepPopRenderTarget( IRoot* lockobj = 0);
	~TriStepPopRenderTarget(void);

	//IRenderStep
	TriStepResult Execute( Be::Time time, Tr2RenderContext& renderContext );
};

TYPEDEF_BLUECLASS( TriStepPopRenderTarget );

#endif
