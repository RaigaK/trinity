#include "StdAfx.h"
#include "TriStepSetProjection.h"
#include "Tr2Renderer.h"


TriStepSetProjection::TriStepSetProjection( IRoot* lockobj )
{
}

TriStepSetProjection::~TriStepSetProjection(void)
{
}

void TriStepSetProjection::SetProjection( TriProjection* projection )
{
	m_projection = projection;
}

TriStepResult TriStepSetProjection::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	if( m_projection )
	{
		m_projection->SetProjection();
	}
	return RS_OK;
}