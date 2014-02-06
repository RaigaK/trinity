#pragma once

#ifndef Tr2Sprite2dFrame_h
#define Tr2Sprite2dFrame_h


#include "Tr2SpriteObject.h"
#include "ITr2Sprite2dTexture.h"

BLUE_DECLARE( Tr2Sprite2dFrame );
BLUE_DECLARE( Tr2Sprite2dTexture );

//////////////////////////////////////////////////////////////////////////
// Tr2Sprite2dFrame implements the ITr2SpriteObject interface and is used with the 
// Tr2Sprite2dScene to render 2D scenes.
//
// It renders a frame by cutting a texture in nine pieces and stretching them 
// appropriately according to the dimensions of the frame.
//
// See http://carbon/wiki/Tr2Sprite2dFrame for more details.
//////////////////////////////////////////////////////////////////////////
class Tr2Sprite2dFrame:
	public Tr2SpriteObject,
	public ITr2Sprite2dTextureNotifyTarget
{
public:
    EXPOSE_TO_BLUE();
    Tr2Sprite2dFrame( IRoot* lockobj = NULL );
	~Tr2Sprite2dFrame();

	Tr2Sprite2dTexture* GetTexture() const;
	void SetTexture( Tr2Sprite2dTexture* val );

	//////////////////////////////////////////////////////////////////////////
	// ITr2SpriteObject
	unsigned int GetVertexCount();
	void GatherSprites( Tr2Sprite2dScene* renderer );
	ITr2SpriteObject* PickPoint( float x, float y, Tr2Sprite2dScene* renderer );

	//////////////////////////////////////////////////////////////////////////
	// ITr2Sprite2dTextureNotifyTarget
	void Sprite2dTextureChanged( ITr2Sprite2dTexture* p );

private:
	// Resource path used to load a Tr2Sprite2dTexture stored in m_texture
	std::string m_resPath;

	unsigned int m_cornerSize;

	// Offset the frame. Positive values will make it smaller, and negative bigger.
	int m_offset;

	// If true, the center piece of the texture is stretched to fill
	// the display extents of the frame. If false, the center is left
	// empty.
	bool m_fillCenter;

	// Cached values that affect the vertices. If none of them have
	// changed the vertices are up to date and are not updated when rendering.
	Vector2 m_cachedTranslation;
	float m_cachedWidth;
	float m_cachedHeight;
	unsigned int m_cachedCornerSize;

	// The texture object, loaded from the resource pointed to with m_resPath
	Tr2Sprite2dTexturePtr m_texture;

	// The buffer of vertices used to render the frame
	Tr2Sprite2dD3DVertex m_vertices[16];
};

TYPEDEF_BLUECLASS( Tr2Sprite2dFrame );

#endif //Tr2Sprite2dFrame_h
