/* 
	*************************************************************************

	ITriConvolutionMatrix5.h

	Author:    Hilmar Veigar Pétursson
	Created:   September 2001
	OS:        Win32
	Project:   Trinity

	Description:   

		Interface for accessing 5x5 row Convolution Matrix that are used 
		in Trinity


	Dependencies:

		Probably, ytbd.

	(c) CCP 2000

	*************************************************************************
*/

#ifndef _ITRICONVOLUTIONMATRIX5_H_
#define _ITRICONVOLUTIONMATRIX5_H_

#include <blue/include/Blue.h>

struct Vector3;
struct D3DXCONVOLUTIONMATRIX3;
struct D3DXCONVOLUTIONMATRIX5;
struct D3DXCONVOLUTIONMATRIX7;

BLUE_INTERFACE( ITriConvolutionMatrix3 ) : public IRoot
{
	// Construction and data access
	virtual void SetPivots(
		float _11, float _12, float _13,
		float _21, float _22, float _23,
		float _31, float _32, float _33
		) = 0;

	 virtual const D3DXCONVOLUTIONMATRIX3* GetMatrix(
		) const = 0;

};

BLUE_INTERFACE( ITriConvolutionMatrix5 ) : public IRoot
{
	// Construction and data access
	virtual void SetPivots(
		float _11, float _12, float _13, float _14, float _15,
		float _21, float _22, float _23, float _24, float _25,
		float _31, float _32, float _33, float _34, float _35,
		float _41, float _42, float _43, float _44, float _45,
		float _51, float _52, float _53, float _54, float _55
		) = 0;

	 virtual const D3DXCONVOLUTIONMATRIX5* GetMatrix(
		) const = 0;

};

BLUE_INTERFACE( ITriConvolutionMatrix7 ) : public IRoot
{
	// Construction and data access
	virtual void SetPivots(
		float _11, float _12, float _13, float _14, float _15, float _16, float _17,
		float _21, float _22, float _23, float _24, float _25, float _26, float _27,
		float _31, float _32, float _33, float _34, float _35, float _36, float _37,
		float _41, float _42, float _43, float _44, float _45, float _46, float _47,
		float _51, float _52, float _53, float _54, float _55, float _56, float _57,
		float _61, float _62, float _63, float _64, float _65, float _66, float _67,
		float _71, float _72, float _73, float _74, float _75, float _76, float _77
		) = 0;

	 virtual const D3DXCONVOLUTIONMATRIX7* GetMatrix(
		) const = 0;

};

#endif