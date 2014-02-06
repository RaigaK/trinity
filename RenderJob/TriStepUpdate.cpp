#include "StdAfx.h"
#include "TriStepUpdate.h"

TriStepUpdate::TriStepUpdate( IRoot* lockobj )
{
}

TriStepUpdate::~TriStepUpdate(void)
{
}

void TriStepUpdate::SetUpdateable( ITr2Updateable* obj )
{
	m_object = obj;
}

TriStepResult TriStepUpdate::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	if( m_object )
	{
		m_object->Update( time );
	}
	return RS_OK;
}