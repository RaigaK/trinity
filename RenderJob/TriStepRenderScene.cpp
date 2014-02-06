#include "StdAfx.h"
#include "TriStepRenderScene.h"


TriStepRenderScene::TriStepRenderScene( IRoot* lockobj )
{
}

TriStepRenderScene::~TriStepRenderScene(void)
{
}

void TriStepRenderScene::py__init__( ITr2Scene* scene )
{
	m_scene = scene;
}

TriStepResult TriStepRenderScene::Execute( Be::Time time, Tr2RenderContext& renderContext )
{
	if( m_scene )
	{
		m_scene->Render( renderContext );
	}
	return RS_OK;
}