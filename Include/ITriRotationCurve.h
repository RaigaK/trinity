/* 
	*************************************************************************

	ITriRotationCurve.h

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

#ifndef _ITRIROTATIONCURVE_H_
#define _ITRIROTATIONCURVE_H_

#include "ITriFunction.h"

BLUE_INTERFACE(ITriRotationCurve) : public ITriQuaternionFunction
{
	virtual void AddKey(
		float t, 
		const Quaternion& v, 
		const Quaternion& l,
		const Quaternion& r,
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