/* 
	*************************************************************************

	ITriPostProcessStage.h

	Created:   June 2006
	OS:        Win32
	Project:   Trinity

	Description:   

		ITriPostProcessStage is a specialisation of the RenderObject interface, 
		designed to allow specific post processing objects to be listed. 
		This also allows a specialised Render function that can pass the post 
		processing state of the device to each child stage in the pipeline.

	Dependencies:

		DirectX 9.0c, Probably more, ytbd.

	(c) CCP 2005

	*************************************************************************
*/

#ifndef _ITRIPOSTPROCESSSTAGE_H_
#define _ITRIPOSTPROCESSSTAGE_H_

#include <blue/include/Blue.h>
#include "include/ITriPostProcess.h"

struct TriPostProcessState;

BLUE_INTERFACE(ITriPostProcessStage) : public ITriRenderObject
{
	virtual bool Render( TriPostProcessState* state) = 0; 
};

#endif