/* 
	*************************************************************************

	ITriTextureRes.h

	Created:   Nov. 2000
	OS:        Win32
	Project:   Yep

	Description:   

		Hemm...


	Dependencies:

		Blue, Trinity

	(c) CCP 2000

	*************************************************************************
*/

#ifndef _ITRITEXTURERES_H_
#define _ITRITEXTURERES_H_

#include "ITriRenderObject.h"


struct IDirect3DSurface9;
struct IDirect3DBaseTexture9;
class Tr2TextureAL;

BLUE_INTERFACE(ITriTextureRes) : 
	public IRoot
{
	virtual Tr2TextureAL* GetTexture() = 0;

	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
	virtual unsigned int GetMipLevelCount() const = 0;

	virtual void SetName( const char* name ) = 0;
	virtual const char* GetName() const = 0;

	virtual long UpdateSubresource( unsigned left, unsigned top, unsigned right, unsigned bottom, const void* source, unsigned sourcePitch ) { return -1; }
};


#endif


