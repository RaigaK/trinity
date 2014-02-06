/* 
	*************************************************************************

	ITriColorCurve.h

	Author:    Hilmar Veigar Pétursson
	Created:   Novembar 2001
	OS:        Win32
	Project:   Trinity

	Description:   

		Yeap


	Dependencies:

		DirectX 9.0, Probably more, ytbd.

	(c) CCP 2000

	*************************************************************************
*/

#ifndef _ITRICOLORCURVE_H_
#define _ITRICOLORCURVE_H_

#include "ITriFunction.h"

BLUE_INTERFACE(ITriColorCurve) : public ITriColorFunction
{
	virtual void AddKey(
		float t, 
		const Color& v, 
		const Color& l, 
		const Color& r, 
		TRIINTERPOLATION i
		) = 0;
	
	virtual void Sort(
		) = 0;

	virtual void ScaleTime(
		float s
		) = 0;

	virtual void ScaleValue(
		float s
		) = 0;

	virtual float Length(
		) = 0;
};

#endif