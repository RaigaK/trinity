#pragma once
#ifndef WodBakingScene_H
#define WodBakingScene_H

#include "include/ITr2Scene.h"
#include "Tr2SkinnedObject.h"
#include "Interior/Tr2InteriorVisualization.h"
#include "TriPoolAllocator.h"
#include "TriRenderBatch.h"

BLUE_DECLARE( WodBakingScene );

class WodBakingScene:
	public ITr2Scene
{
public:
	WodBakingScene( IRoot* lockobj = NULL );
	~WodBakingScene();

	EXPOSE_TO_BLUE();

	virtual void Render( Tr2RenderContext& renderContext );	
	virtual void RenderDebugInfo( Tr2RenderContext& renderContext );
	virtual void Update(Be::Time time);

private:
	ITriRenderBatchAccumulator* m_opaqueRenderBatches;
	//TriRenderBatchAccumulator* m_transparentRenderBatches;
	Tr2SkinnedObjectPtr m_skinnedObject;

	// Visualization
	VisualizeMethod m_visualizeMethod;

	Tr2ConstantBufferAL	m_VSBuffer, m_PSBuffer;
};

TYPEDEF_BLUECLASS( WodBakingScene );

#endif