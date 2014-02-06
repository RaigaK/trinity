/* 
	*************************************************************************

	ITriVertexElement.h

	Author:    Hilmar Veigar Pétursson
	Created:   May 2002
	OS:        Win32
	Project:   Trinity

	Description:   

		Yeap


	Dependencies:

		DirectX 9.0, Probably more, ytbd.

	(c) CCP 2000

	*************************************************************************
*/


#ifndef _ITRIVERTEXELEMENT_H_
#define _ITRIVERTEXELEMENT_H_

#include <blue/include/Blue.h>
#include <d3d9types.h>


BLUE_INTERFACE( ITriVertexElement ) : public IRoot	
{
	// Construction and data access
	virtual void SetComponents(
		BYTE stream, 
		BYTE offset, 
		BYTE type, 
		BYTE method,
		BYTE usage,
		BYTE usageIdx
		) = 0;

	virtual void SetElement(
		const D3DVERTEXELEMENT9* c
		) = 0;

	virtual const D3DVERTEXELEMENT9* GetElement(
		) const = 0;

	virtual D3DVERTEXELEMENT9* CopyElement(
		D3DVERTEXELEMENT9 * in
		) const = 0;

	virtual D3DVERTEXELEMENT9* Element(
		) = 0;
};

#endif