#pragma once

#ifndef Tr2Sprite2dStretch_h
#define Tr2Sprite2dStretch_h


#include "Tr2SpriteObject.h"

BLUE_DECLARE( Tr2Sprite2dStretch );
BLUE_DECLARE( Tr2Sprite2dTexture );

enum Tr2StretchScaleBehavior
{
	S2D_SSC_ALIGN_BOTTOMRIGHT,
	S2D_SSC_ALIGN_TOPLEFT,
	S2D_SSC_SCALE
};

//////////////////////////////////////////////////////////////////////////
// Tr2Sprite2dFrame implements the ITr2SpriteObject interface and is used with the 
// Tr2Sprite2dScene to render 2D scenes.
//
// It renders a sprite by cutting a texture into three pieces and stretching the 
// center piece appropriately according to the dimensions of the sprite.
//////////////////////////////////////////////////////////////////////////
class Tr2Sprite2dStretch:
	public Tr2SpriteObject
{
public:
	EXPOSE_TO_BLUE();
	Tr2Sprite2dStretch( IRoot* lockobj = NULL );

	//////////////////////////////////////////////////////////////////////////
	// ITr2SpriteObject
	unsigned int GetVertexCount();
	void GatherSprites( Tr2Sprite2dScene* renderer );
	ITr2SpriteObject* PickPoint( float x, float y, Tr2Sprite2dScene* renderer );

private:
	// Resource path used to load a Tr2Sprite2dTexture stored in m_texture
	std::string m_resPath;

	// Number of pixels on the left edge of the texture
	unsigned int m_leftEdgeSize;

	// Number of pixels on the right edge of the texture
	unsigned int m_rightEdgeSize;

	// Offset the sprite. Positive values will make it smaller horizontally,
	// and negative bigger. The sprite is shifted vertically by this offset.
	int m_offset;

	// If true, the center piece of the texture is stretched to fill
	// the display width of the stretch sprite.
	bool m_fillCenter;

	Tr2StretchScaleBehavior m_dpiScaleBehavior;

	// Cached values for width, height and corner size. If these are
	// the same as current width, height and corner size the vertices
	// are up to date and are not updated when rendering.
	float m_cachedWidth;
	float m_cachedHeight;
	unsigned int m_cachedCornerSize;

	// The texture object, loaded from the resource pointed to with m_resPath
	Tr2Sprite2dTexturePtr m_texture;

	// The buffer of vertices used to render the sprite
	Tr2Sprite2dD3DVertex m_vertices[8];
};

TYPEDEF_BLUECLASS( Tr2Sprite2dStretch );

#endif //Tr2Sprite2dFrame_h
