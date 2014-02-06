#pragma once

#ifndef Tr2Sprite2dLayer_h
#define Tr2Sprite2dLayer_h


#include "Tr2Sprite2dContainer.h"
#include "Tr2DeviceResource.h"

BLUE_DECLARE( Tr2Sprite2dLayer );
BLUE_DECLARE_IVECTOR( ITr2SpriteObject );
BLUE_DECLARE( Tr2Effect );

class Tr2Sprite2dLayer:
	public Tr2Sprite2dContainer,
	public Tr2DeviceResource
{
public:
	EXPOSE_TO_BLUE();
	Tr2Sprite2dLayer( IRoot* lockobj = NULL );
	~Tr2Sprite2dLayer();

	//////////////////////////////////////////////////////////////////////////
	// ITr2SpriteObject
	unsigned int GetVertexCount();
	void GatherSprites( Tr2Sprite2dScene* renderer );
	void SetChildDirty( ITr2SpriteObject* child );

	//////////////////////////////////////////////////////////////////////////
	// ITriDeviceResource
	void ReleaseResources( TriStorage s );
private:
	bool OnPrepareResources();

	void AllocateRenderTarget();
	void FreeRenderTarget();

private:
	Tr2RenderTargetAL m_renderTarget;
	
	// If m_clearBackground is set, background is cleared to this color
	Color m_backgroundColor;

	// Does this layer need a call to Clear before rendering children?
	bool m_clearBackground;
};

TYPEDEF_BLUECLASS( Tr2Sprite2dLayer );

#endif //Tr2Sprite2dLayer_h
