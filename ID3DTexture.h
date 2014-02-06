#pragma once

#ifndef ID3DTexture_h
#define ID3DTexture_h

BLUE_INTERFACE( ID3DTexture ) : public IRoot
{
	virtual Tr2TextureAL* GetTexture() = 0;
};

#endif
