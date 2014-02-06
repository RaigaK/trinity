/* 
	*************************************************************************************

	TriConvolutionMatrix5.h

	Author:    Hilmar Veigar Pétursson
	Created:   September 2001
	OS:        Win32
	Project:   Trinity

	Description:   

		See TRICONVOLUTIONMATRIX5_Description


	Dependencies:

		DirectX 9.0, Blue

	(c) CCP 2000

	*************************************************************************************
*/


#ifndef _TRICONVOLUTIONMATRIX5_H_
#define _TRICONVOLUTIONMATRIX5_H_

#define TRICONVOLUTIONMATRIX3_Description \
"na"

#define TRICONVOLUTIONMATRIX5_Description \
"na"

#define TRICONVOLUTIONMATRIX7_Description \
"na"

#include "include/ITriConvolutionMatrix5.h"
#include "include/TriMath.h"

#include <blue/include/IBlueOS.h>
#include <blue/include/IBluePython.h>

#pragma warning (disable: 4275) // non dll-interface struct 'D3DXMATRIX'

typedef struct D3DXCONVOLUTIONMATRIX3 {
    union {
        struct {
            float        _11, _12, _13;
            float        _21, _22, _23;
            float        _31, _32, _33;
        };
        float m[3][3];
    };
} D3DXCONVOLUTIONMATRIX3;

typedef struct D3DXCONVOLUTIONMATRIX5 {
    union {
        struct {
            float        _11, _12, _13, _14, _15;
            float        _21, _22, _23, _24, _25;
            float        _31, _32, _33, _34, _35;
            float        _41, _42, _43, _44, _45;
			float        _51, _52, _53, _54, _55;
        };
        float m[5][5];
    };
} D3DXCONVOLUTIONMATRIX5;

typedef struct D3DXCONVOLUTIONMATRIX7 {
    union {
        struct {
            float        _11, _12, _13, _14, _15, _16, _17;
            float        _21, _22, _23, _24, _25, _26, _27;
            float        _31, _32, _33, _34, _35, _36, _37;
            float        _41, _42, _43, _44, _45, _46, _47;
			float        _51, _52, _53, _54, _55, _56, _57;
            float        _61, _62, _63, _64, _65, _66, _67;
            float        _71, _72, _73, _74, _75, _76, _77;
        };
        float m[7][7];
    };
} D3DXCONVOLUTIONMATRIX7;

#if BLUE_WITH_PYTHON
class TriConvolutionMatrix3 :
	public ITriConvolutionMatrix3,
	public IPythonMethods,
	D3DXCONVOLUTIONMATRIX3
{
public:
	EXPOSE_TO_BLUE();

	TriConvolutionMatrix3(IRoot* lockobj = NULL);
	~TriConvolutionMatrix3();

	/////////////////////////////////////////////////////////////////////////////////////
	// ITriMatrix
	/////////////////////////////////////////////////////////////////////////////////////
	void SetPivots(
		float _11, float _12, float _13,
		float _21, float _22, float _23,
		float _31, float _32, float _33
		);	 
	
	const D3DXCONVOLUTIONMATRIX3* GetMatrix(
		) const;



	/////////////////////////////////////////////////////////////////////////////////////
	// IPythonMethods
	/////////////////////////////////////////////////////////////////////////////////////
	void Destroy(
		);

	PyObject* GetAttr( 
		const char* name, 
		bool* handled
		);

	bool SetAttr(
		const char* name,
		PyObject* v,
		bool* handled
		);

	PyObject* Repr(
		bool* handled
		);

public:
	DECLARE_PYMETHOD( __init__ );
};
TYPEDEF_BLUECLASS(TriConvolutionMatrix3);


class TriConvolutionMatrix5 :
	public ITriConvolutionMatrix5,
	public IPythonMethods,
	D3DXCONVOLUTIONMATRIX5
{
public:
	EXPOSE_TO_BLUE();

	TriConvolutionMatrix5(IRoot* lockobj = NULL);
	~TriConvolutionMatrix5();

	/////////////////////////////////////////////////////////////////////////////////////
	// ITriMatrix
	/////////////////////////////////////////////////////////////////////////////////////
	void SetPivots(
		float _11, float _12, float _13, float _14, float _15,
		float _21, float _22, float _23, float _24, float _25,
		float _31, float _32, float _33, float _34, float _35,
		float _41, float _42, float _43, float _44, float _45,
		float _51, float _52, float _53, float _54, float _55
		);	 
	
	const D3DXCONVOLUTIONMATRIX5* GetMatrix(
		) const;



	/////////////////////////////////////////////////////////////////////////////////////
	// IPythonMethods
	/////////////////////////////////////////////////////////////////////////////////////
	void Destroy(
		);

	PyObject* GetAttr( 
		const char* name, 
		bool* handled
		);

	bool SetAttr(
		const char* name,
		PyObject* v,
		bool* handled
		);

	PyObject* Repr(
		bool* handled
		);

public:
	DECLARE_PYMETHOD( __init__ );
};
TYPEDEF_BLUECLASS(TriConvolutionMatrix5);

class TriConvolutionMatrix7 :
	public ITriConvolutionMatrix7,
	public IPythonMethods,
	D3DXCONVOLUTIONMATRIX7
{
public:
	EXPOSE_TO_BLUE();

	TriConvolutionMatrix7(IRoot* lockobj = NULL);
	~TriConvolutionMatrix7();

	/////////////////////////////////////////////////////////////////////////////////////
	// ITriMatrix
	/////////////////////////////////////////////////////////////////////////////////////
	void SetPivots(
		float _11, float _12, float _13, float _14, float _15, float _16, float _17,
		float _21, float _22, float _23, float _24, float _25, float _26, float _27,
		float _31, float _32, float _33, float _34, float _35, float _36, float _37,
		float _41, float _42, float _43, float _44, float _45, float _46, float _47,
		float _51, float _52, float _53, float _54, float _55, float _56, float _57,
		float _61, float _62, float _63, float _64, float _65, float _66, float _67,
		float _71, float _72, float _73, float _74, float _75, float _76, float _77
		);	 
	
	const D3DXCONVOLUTIONMATRIX7* GetMatrix(
		) const;



	/////////////////////////////////////////////////////////////////////////////////////
	// IPythonMethods
	/////////////////////////////////////////////////////////////////////////////////////
	void Destroy(
		);

	PyObject* GetAttr( 
		const char* name, 
		bool* handled
		);

	bool SetAttr(
		const char* name,
		PyObject* v,
		bool* handled
		);

	PyObject* Repr(
		bool* handled
		);

public:
	DECLARE_PYMETHOD( __init__ );
};
TYPEDEF_BLUECLASS(TriConvolutionMatrix7);

#endif

#endif

