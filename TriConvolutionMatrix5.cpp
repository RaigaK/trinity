#include "StdAfx.h"

#if BLUE_WITH_PYTHON
#if DEPRECATED_ENABLED

#include "TriConvolutionMatrix5.h"


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//
// TriConvolutionMatrix3
//
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix3 IPythonMethods Impl
/////////////////////////////////////////////////////////////////////////////////////////

void TriConvolutionMatrix3::Destroy(
	)
{
	//delete this;
}


PyObject* TriConvolutionMatrix3::GetAttr( 
	const char* name, 
	bool* handled
	)
{
	return 0;
}


bool TriConvolutionMatrix3::SetAttr(
	const char* name, 
	PyObject* v, 
	bool* handled 
	)
{
	return true;
}


PyObject* TriConvolutionMatrix3::Repr(
	bool* handled
	)
{
	*handled = true;
	char buf[1024];
	sprintf_s(buf, "<Instance of 'TriConvolutionMatrix3'\r\n"
		"( %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f )>", 
		_11, _12, _13,
		_21, _22, _23,
		_31, _32, _33
		);
	return PyString_FromString(buf);
}


/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix3
/////////////////////////////////////////////////////////////////////////////////////////

TriConvolutionMatrix3::TriConvolutionMatrix3(IRoot* lockobj)
{
	SetPivots(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
		);
}


TriConvolutionMatrix3::~TriConvolutionMatrix3()
{
}


/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix3 ITriMatrix Impl
/////////////////////////////////////////////////////////////////////////////////////////

void TriConvolutionMatrix3::SetPivots(
	float _11_, float _12_, float _13_,
	float _21_, float _22_, float _23_,
	float _31_, float _32_, float _33_
	)
{
	_11 = _11_; _12 = _12_; _13 = _13_;
	_21 = _21_; _22 = _22_; _23 = _23_;
	_31 = _31_; _32 = _32_; _33 = _33_;
}


const D3DXCONVOLUTIONMATRIX3* TriConvolutionMatrix3::GetMatrix(
	) const
{
	return this;
}


/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix3 Python thunkers for ITriMatrix interface
/////////////////////////////////////////////////////////////////////////////////////////

PyObject* TriConvolutionMatrix3::Py__init__(
	PyObject* args
	)
{		
	if (!PyArg_ParseTuple(args, "|fffffffff", 
		&_11, &_12, &_13,
		&_21, &_22, &_23,
		&_31, &_32, &_33))
		return NULL;
	
	Py_INCREF(Py_None);
	return Py_None;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//
// TriConvolutionMatrix5
//
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix5 IPythonMethods Impl
/////////////////////////////////////////////////////////////////////////////////////////

void TriConvolutionMatrix5::Destroy(
	)
{
	//delete this;
}


PyObject* TriConvolutionMatrix5::GetAttr( 
	const char* name, 
	bool* handled
	)
{
	return 0;
}


bool TriConvolutionMatrix5::SetAttr(
	const char* name, 
	PyObject* v, 
	bool* handled 
	)
{
	return true;
}


PyObject* TriConvolutionMatrix5::Repr(
	bool* handled
	)
{
	*handled = true;
	char buf[1024];
	sprintf_s(buf, "<Instance of 'TriConvolutionMatrix5'\r\n"
		"( %0.1f %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f %0.1f )>", 
		_11, _12, _13, _14, _15,
		_21, _22, _23, _24, _25,
		_31, _32, _33, _34, _35,
		_41, _42, _43, _44, _45,		
		_51, _52, _53, _54, _55
		);
	return PyString_FromString(buf);
}


/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix5
/////////////////////////////////////////////////////////////////////////////////////////

TriConvolutionMatrix5::TriConvolutionMatrix5(IRoot* lockobj)
{
	SetPivots(
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,		
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,		
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		);
}


TriConvolutionMatrix5::~TriConvolutionMatrix5()
{
}


/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix5 ITriMatrix Impl
/////////////////////////////////////////////////////////////////////////////////////////

void TriConvolutionMatrix5::SetPivots(
	float _11_, float _12_, float _13_, float _14_, float _15_,
	float _21_, float _22_, float _23_, float _24_, float _25_,
	float _31_, float _32_, float _33_, float _34_, float _35_,
	float _41_, float _42_, float _43_, float _44_, float _45_,
	float _51_, float _52_, float _53_, float _54_, float _55_
	)
{
	_11 = _11_; _12 = _12_; _13 = _13_; _14 = _15_;
	_21 = _21_; _22 = _22_; _23 = _23_; _24 = _25_;
	_31 = _31_; _32 = _32_; _33 = _33_; _34 = _35_;
	_41 = _41_; _42 = _42_; _43 = _43_; _44 = _45_;
	_51 = _51_; _52 = _52_; _53 = _53_; _54 = _55_;
}


const D3DXCONVOLUTIONMATRIX5* TriConvolutionMatrix5::GetMatrix(
	) const
{
	return this;
}


/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix5 Python thunkers for ITriMatrix interface
/////////////////////////////////////////////////////////////////////////////////////////

PyObject* TriConvolutionMatrix5::Py__init__(
	PyObject* args
	)
{		
	if (!PyArg_ParseTuple(args, "|fffffffffffffffffffffffff", 
		&_11, &_12, &_13, &_14, &_15,
		&_21, &_22, &_23, &_24, &_25,
		&_31, &_32, &_33, &_34, &_35,
		&_41, &_42, &_43, &_44, &_45,
		&_51, &_52, &_53, &_54, &_55))
		return NULL;
	
	Py_INCREF(Py_None);
	return Py_None;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//
// TriConvolutionMatrix7
//
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix7 IPythonMethods Impl
/////////////////////////////////////////////////////////////////////////////////////////

void TriConvolutionMatrix7::Destroy(
	)
{
	//delete this;
}


PyObject* TriConvolutionMatrix7::GetAttr( 
	const char* name, 
	bool* handled
	)
{
	return 0;
}


bool TriConvolutionMatrix7::SetAttr(
	const char* name, 
	PyObject* v, 
	bool* handled 
	)
{
	return true;
}


PyObject* TriConvolutionMatrix7::Repr(
	bool* handled
	)
{
	*handled = true;
	char buf[1024];
	sprintf_s(buf, "<Instance of 'TriConvolutionMatrix5'\r\n"
		"( %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f %0.1f  %0.1f %0.1f)>", 
		_11, _12, _13, _14, _15, _16, _17,
		_21, _22, _23, _24, _25, _26, _27,
		_31, _32, _33, _34, _35, _36, _37,
		_41, _42, _43, _44, _45, _46, _47,
		_51, _52, _53, _54, _55, _56, _57,
		_61, _62, _63, _64, _65, _66, _67,
		_71, _72, _73, _74, _75, _76, _77
		);
	return PyString_FromString(buf);
}


/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix7
/////////////////////////////////////////////////////////////////////////////////////////

TriConvolutionMatrix7::TriConvolutionMatrix7(IRoot* lockobj)
{
	SetPivots(
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		);
}


TriConvolutionMatrix7::~TriConvolutionMatrix7()
{
}


/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix7 ITriMatrix Impl
/////////////////////////////////////////////////////////////////////////////////////////

void TriConvolutionMatrix7::SetPivots(
	float _11_, float _12_, float _13_, float _14_, float _15_, float _16_, float _17_,
	float _21_, float _22_, float _23_, float _24_, float _25_, float _26_, float _27_,
	float _31_, float _32_, float _33_, float _34_, float _35_, float _36_, float _37_,
	float _41_, float _42_, float _43_, float _44_, float _45_, float _46_, float _47_,
	float _51_, float _52_, float _53_, float _54_, float _55_, float _56_, float _57_,
	float _61_, float _62_, float _63_, float _64_, float _65_, float _66_, float _67_,
	float _71_, float _72_, float _73_, float _74_, float _75_, float _76_, float _77_
	)
{
	_11 = _11_; _12 = _12_; _13 = _13_; _14 = _15_; _16 = _16_; _17 = _17_;
	_21 = _21_; _22 = _22_; _23 = _23_; _24 = _25_; _26 = _26_; _27 = _27_;
	_31 = _31_; _32 = _32_; _33 = _33_; _34 = _35_; _36 = _36_; _37 = _37_;
	_41 = _41_; _42 = _42_; _43 = _43_; _44 = _45_; _46 = _46_; _47 = _47_;
	_51 = _51_; _52 = _52_; _53 = _53_; _54 = _55_; _56 = _56_; _57 = _57_;
	_61 = _61_; _62 = _62_; _63 = _63_; _64 = _65_; _66 = _66_; _67 = _67_;
	_71 = _71_; _72 = _72_; _73 = _73_; _74 = _75_; _76 = _76_; _77 = _77_;
}


const D3DXCONVOLUTIONMATRIX7* TriConvolutionMatrix7::GetMatrix(
	) const
{
	return this;
}


/////////////////////////////////////////////////////////////////////////////////////////
// TriConvolutionMatrix7 Python thunkers for ITriMatrix interface
/////////////////////////////////////////////////////////////////////////////////////////

PyObject* TriConvolutionMatrix7::Py__init__(
	PyObject* args
	)
{		
	if (!PyArg_ParseTuple(args, "|fffffffffffffffffffffffffffffffffffffffffffffffff", 
		&_11, &_12, &_13, &_14, &_15, &_16, &_17,
		&_21, &_22, &_23, &_24, &_25, &_26, &_27,
		&_31, &_32, &_33, &_34, &_35, &_36, &_37,
		&_41, &_42, &_43, &_44, &_45, &_46, &_47,
		&_51, &_52, &_53, &_54, &_55, &_56, &_57,
		&_61, &_62, &_63, &_64, &_65, &_66, &_67,
		&_71, &_72, &_73, &_74, &_75, &_76, &_77))
		return NULL;
	
	Py_INCREF(Py_None);
	return Py_None;
}

#endif
#endif
