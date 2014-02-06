/* 
	*************************************************************************

	ITriVectorCurve.h

	Author:    Hilmar Veigar Pétursson
	Created:   August 2001
	OS:        Win32
	Project:   Trinity

	Description:   

		Yeap


	Dependencies:

		DirectX 9.0, Probably more, ytbd.

	(c) CCP 2000

	*************************************************************************
*/

#ifndef _ITRIVECTORCURVE_H_
#define _ITRIVECTORCURVE_H_

#include "ITriFunction.h"

BLUE_INTERFACE(ITriVectorCurve) : public ITriVectorFunction
{
	virtual void AddKey(
		float t, 
		const Vector3& v, 
		const Vector3& l,
		const Vector3& r,
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