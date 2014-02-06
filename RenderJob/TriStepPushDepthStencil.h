#pragma once
#ifndef TriStepPushDepthStencil_h_
#define TriStepPushDepthStencil_h_


#include "TriRenderStep.h"

BLUE_DECLARE( Tr2DepthStencil );

BLUE_CLASS( TriStepPushDepthStencil ) : public TriRenderStep
{
public:
	EXPOSE_TO_BLUE();
	
	TriStepPushDepthStencil( IRoot* lockobj = 0);
	~TriStepPushDepthStencil(void);

	void py__init__( Be::Optional<Tr2DepthStencil*> depthStencil );

	//IRenderStep
	TriStepResult Execute( Be::Time time, Tr2RenderContext& renderContext );

	Tr2DepthStencilPtr	m_depthStencil;
	bool				m_pushCurrent;
};

TYPEDEF_BLUECLASS( TriStepPushDepthStencil );

#endif