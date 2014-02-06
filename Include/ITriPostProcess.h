/* 
	*************************************************************************

	ITriPostProcess.h

	Created:   June 2006
	OS:        Win32
	Project:   Trinity

	Description:   

		ITriPostProcess is a specialisation of the RenderObject interface, designed to allow a blue pointer object to the TriPostProcess type.

	Dependencies:

		DirectX 9.0c, Probably more, ytbd.

	(c) CCP 2005

	*************************************************************************
*/

#ifndef _ITRIPOSTPROCESS_H_
#define _ITRIPOSTPROCESS_H_

#include <blue/include/Blue.h>

BLUE_INTERFACE(ITriPostProcess) : public IRoot
{
	virtual void RebuildCachedData() = 0;

	virtual bool Render( IDirect3DTexture9* hdrTexture, IDirect3DSurface9* ldrSurface ) = 0;
    virtual bool IsEnabled() = 0;
};

#endif