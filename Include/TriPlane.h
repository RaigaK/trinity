/* 
	*************************************************************************************

	TriPlane.h

	Author:    Hilmar Veigar Pétursson
	Created:   September 2001
	OS:        Win32
	Project:   Trinity

	Description:   

		See TRIPLANE_Description


	Dependencies:

		DirectX 9.0, Blue

	(c) CCP 2000

	*************************************************************************************
*/


#ifndef _TRIPlANE_H_
#define _TRIPLANE_H_

#define TRIPLANE_Description \
"Simple mapping of D3DXPLANE over to Blue so that it can be used in Python"

#include "ITriPlane.h"
#include "include/TriMath.h"

#include <blue/include/IBlueOS.h>
#include <blue/include/IBluePython.h>

#pragma warning (disable: 4275) // non dll-interface struct 'D3DXPLANE'

#if BLUE_WITH_PYTHON
class TriPlane :
	public ITriPlane,
	public IPythonMethods,
	public D3DXPLANE
{
public:
	EXPOSE_TO_BLUE();

	TriPlane(IRoot* lockobj = NULL);
	~TriPlane();

	/////////////////////////////////////////////////////////////////////////////////////
	// ITriPlane
	/////////////////////////////////////////////////////////////////////////////////////
	void SetABCD(
		float a, 
		float b, 
		float c,
		float d
		);

	void SetPlane(
		const D3DXPLANE* p
		);

	const D3DXPLANE* GetPlane(
		) const;

	D3DXPLANE* CopyPlane(
		D3DXPLANE* in
		) const;

	D3DXPLANE* Plane(
		);

	void Normalize(
		);
	
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
	void Py__init__( float _a, float _b, float _c, Be::Optional<float> _d );
};
TYPEDEF_BLUECLASS(TriPlane);

#endif
#endif

