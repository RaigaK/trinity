#include "StdAfx.h"
#include "TriRenderStep.h"
#include "ITriRenderStep.h"

BLUE_DEFINE_INTERFACE( ITriRenderStep );

TriRenderStep::TriRenderStep( IRoot* lockobj )
:	m_enabled( true )
{
}

TriRenderStep::~TriRenderStep()
{
}

bool TriRenderStep::IsEnabled() const
{
	return m_enabled;
}