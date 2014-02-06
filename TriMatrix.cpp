#include "StdAfx.h"
#include "include/TriMatrix.h"
#include "include/TriVector.h"
#include "include/TriQuaternion.h"


#if BLUE_WITH_PYTHON
/////////////////////////////////////////////////////////////////////////////////////////
// IPythonMethods Impl
/////////////////////////////////////////////////////////////////////////////////////////

void TriMatrix::Destroy(
	)
{
	//delete this;
}


PyObject* TriMatrix::GetAttr( 
	const char* name, 
	bool* handled
	)
{
	return 0;
}


bool TriMatrix::SetAttr(
	const char* name, 
	PyObject* v, 
	bool* handled 
	)
{
	return true;
}


PyObject* TriMatrix::Repr(
	bool* handled
	)
{
	*handled = true;
	char buf[256];
	sprintf_s(buf, "<Instance of 'TriMatrix'\r\n"
		"( %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f\r\n"
		"  %0.1f %0.1f %0.1f %0.1f )>", 
		_11, _12, _13, _14,
		_21, _22, _23, _24,
		_31, _32, _33, _34,
		_41, _42, _43, _44		
		);
	return PyString_FromString(buf);
}
#endif


/////////////////////////////////////////////////////////////////////////////////////////
// TriMatrix
/////////////////////////////////////////////////////////////////////////////////////////

TriMatrix::TriMatrix(IRoot* lockobj) :
	Matrix(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f)
{
}


TriMatrix::~TriMatrix()
{
}


/////////////////////////////////////////////////////////////////////////////////////////
// ITriMatrix Impl
/////////////////////////////////////////////////////////////////////////////////////////

void TriMatrix::SetPivots(
	float _11_, float _12_, float _13_, float _14_,
	float _21_, float _22_, float _23_, float _24_,
	float _31_, float _32_, float _33_, float _34_,
	float _41_, float _42_, float _43_, float _44_
	)
{
	_11 = _11_; _12 = _12_; _13 = _13_; _14 = _14_;
	_21 = _21_; _22 = _22_; _23 = _23_; _24 = _24_;
	_31 = _31_; _32 = _32_; _33 = _33_; _34 = _34_;
	_41 = _41_; _42 = _42_; _43 = _43_; _44 = _44_;
}

void TriMatrix::SetMatrix(
	const Matrix* m
	)
{
	_11 = m->_11; _12 = m->_12; _13 = m->_13; _14 = m->_14;
	_21 = m->_21; _22 = m->_22; _23 = m->_23; _24 = m->_24;
	_31 = m->_31; _32 = m->_32; _33 = m->_33; _34 = m->_34;
	_41 = m->_41; _42 = m->_42; _43 = m->_43; _44 = m->_44;

}

const Matrix* TriMatrix::GetMatrix(
	) const
{
	return this;
}

Matrix* TriMatrix::CopyMatrix(
	Matrix* in
	) const
{
	*in = *this;
	return in;
}

void TriMatrix::AffineTransformation(
	float scaling,
	const Vector3* pRotationCenter,
	const Quaternion* pRotation,
	const Vector3* pTranslation
	)
{
	D3DXMatrixAffineTransformation(
		this,
		scaling,
		pRotationCenter,
		pRotation,
		pTranslation
		);
}

float TriMatrix::Determinant(	  
	) 
{
	return D3DXMatrixDeterminant(this);
}

void TriMatrix::Identity(
	) 
{
	D3DXMatrixIdentity(this);
}

float TriMatrix::Inverse(
	) 
{
	float ret;
	D3DXMatrixInverse(this, &ret, this);
	return ret;
}

bool TriMatrix::IsIdentity(
	) 
{
	return D3DXMatrixIsIdentity(this) != 0;
}

void TriMatrix::LookAtRH(	  
	const Vector3* pEye,
	const Vector3* pAt,
	const Vector3* pUp
	) 
{
	D3DXMatrixLookAtRH(
		this,
		pEye,
		pAt,
		pUp);
}

void TriMatrix::LookAtLH(
	const Vector3* pEye,
	const Vector3* pAt,
	const Vector3* pUp
	) 
{
	D3DXMatrixLookAtLH(
		this,
		pEye,
		pAt,
		pUp);
}

void TriMatrix::Multiply(		  
	const Matrix* pM2
	) 
{
	D3DXMatrixMultiply(this, this, pM2);
}
void TriMatrix::OrthoRH(		
	float w,
	float h,
	float zn,
	float zf
	) 
{
	D3DXMatrixOrthoRH(
		this,
		w,
		h,
		zn,
		zf);
}

void TriMatrix::OrthoLH(
	float w,
	float h,
	float zn,
	float zf
	) 
{
	D3DXMatrixOrthoLH(
		this,
		w,
		h,
		zn,
		zf);
}

void TriMatrix::OrthoOffCenterRH(
	float l,
	float r,
	float t,
	float b,
	float zn,
	float zf
	) 
{
	D3DXMatrixOrthoOffCenterRH(
		this,
		l,
		r,
		t,
		b,
		zn,
		zf);
}

void TriMatrix::OrthoOffCenterLH(
	float l,
	float r,
	float t,
	float b,
	float zn,
	float zf
	) 
{
	D3DXMatrixOrthoOffCenterLH(
		this,
		l,
		r,
		t,
		b,
		zn,
		zf);
}

void TriMatrix::PerspectiveRH(
	float w,
	float h,
	float zn,
	float zf
	) 
{
	D3DXMatrixPerspectiveRH(
		this,
		w,
		h,
		zn,
		zf);
}

void TriMatrix::PerspectiveFovLH(
	float fovy,
	float Aspect,
	float zn,
	float zf
	) 
{
	D3DXMatrixPerspectiveFovLH(
		this,
		fovy,
		Aspect,
		zn,
		zf);
}

void TriMatrix::PerspectiveFovRH(
	float fovy,
	float Aspect,
	float zn,
	float zf
	) 
{
	D3DXMatrixPerspectiveFovRH(
		this,
		fovy,
		Aspect,
		zn,
		zf);
}

void TriMatrix::PerspectiveLH(	
	float w,
	float h,
	float zn,
	float zf
	) 
{
	D3DXMatrixPerspectiveLH(
		this,
		w,
		h,
		zn,
		zf);
}

void TriMatrix::PerspectiveOffCenterRH(		
	float l,
	float r,
	float t,
	float b,
	float zn,
	float zf
	) 
{
	D3DXMatrixPerspectiveOffCenterRH(
		this,
		l,
		r,
		t,
		b,
		zn,
		zf);
}

void TriMatrix::PerspectiveOffCenterLH(
	float l,
	float r,
	float t,
	float b,
	float zn,
	float zf
	) 
{
	D3DXMatrixPerspectiveOffCenterLH(
		this,
		l,
		r,
		t,
		b,
		zn,
		zf);
}

void TriMatrix::Reflect(	
	const D3DXPLANE* pPlane
	) 
{
	D3DXMatrixReflect(
		this,
		pPlane);
}

void TriMatrix::RotationAxis(	  
	const Vector3* pV,
	float Angle
	) 
{
	D3DXMatrixRotationAxis(
		this,
		pV,
		Angle);
}

void TriMatrix::RotationQuaternion(	
	const Quaternion* pQ
	) 
{
	D3DXMatrixRotationQuaternion(
		this,
		pQ);
}

void TriMatrix::RotationX(	  
	float Angle
	) 
{
	D3DXMatrixRotationX(this, Angle);
}

void TriMatrix::RotationY(
	float Angle
	) 
{
	D3DXMatrixRotationY(this, Angle);
}

void TriMatrix::RotationYawPitchRoll(
	float Yaw,
	float Pitch,
	float Roll
	) 
{
	D3DXMatrixRotationYawPitchRoll(
		this,
		Yaw,
		Pitch,
		Roll);
}

void TriMatrix::RotationZ(
	float Angle
	) 
{
	D3DXMatrixRotationZ(this, Angle);
}

void TriMatrix::Scaling(	  
	float sx,
	float sy,
	float sz
	) 
{
	D3DXMatrixScaling(this, sx, sy, sz);
}

void TriMatrix::Shadow(	  
	const Vector4* pLight,
	const D3DXPLANE* pPlane
	) 
{
	D3DXMatrixShadow(
		this,
		pLight,
		pPlane);
}

void TriMatrix::Transformation(	  
	const Vector3* pScalingCenter,
	const Quaternion* pScalingRotation,
	const Vector3* pScaling,
	const Vector3* pRotationCenter,
	const Quaternion* pRotation,
	const Vector3* pTranslation
	) 
{
	D3DXMatrixTransformation(
		this,
		pScalingCenter,
		pScalingRotation,
		pScaling,
		pRotationCenter,
		pRotation,
		pTranslation);
}

void TriMatrix::Translation(	  
	float x,
	float y,
	float z
	) 
{
	D3DXMatrixTranslation(
		this,
		x,
		y,
		z);
}

void TriMatrix::Transpose(	  	  
	)
{
	D3DXMatrixTranspose(
		this,
		this);
}


#if BLUE_WITH_PYTHON
/////////////////////////////////////////////////////////////////////////////////////////
// Python thunkers for ITriMatrix interface
/////////////////////////////////////////////////////////////////////////////////////////

PyObject* TriMatrix::Py__init__(
	PyObject* args
	)
{		
	if (!PyArg_ParseTuple(args, "|ffffffffffffffff", 
		&_11, &_12, &_13, &_14,
		&_21, &_22, &_23, &_24,
		&_31, &_32, &_33, &_34,
		&_41, &_42, &_43, &_44))
		return NULL;	
	
	Py_INCREF(Py_None);
	return Py_None;
}
#endif


void TriMatrix::PyAffineTransformation( 
	float scaling, 
	ITriVector* rotationCenter, 
	ITriQuaternion* rotation, 
	ITriVector* translation )
{
	AffineTransformation(
		scaling,
		rotationCenter->GetVector(),
		rotation->GetQuaternion(),
		translation->GetVector() );
}

void TriMatrix::PyLookAtRH( ITriVector* eye, ITriVector* at, ITriVector* up ) 
{
	LookAtRH(
		eye->GetVector(),
		at->GetVector(),
		up->GetVector() );
}

void TriMatrix::PyLookAtLH( ITriVector* eye, ITriVector* at, ITriVector* up ) 
{
	LookAtLH(
		eye->GetVector(),
		at->GetVector(),
		up->GetVector() );
}

void TriMatrix::PyMultiply( ITriMatrix* other )
{
	Multiply( other->GetMatrix() );
}

void TriMatrix::PyRotationAxis( ITriVector* axis, float angle )
{
	RotationAxis( axis->GetVector(), angle );
}

void TriMatrix::PyRotationQuaternion( ITriQuaternion* quaternion )
{
	RotationQuaternion( quaternion->GetQuaternion() );
}

void TriMatrix::PyTransformation( 
	ITriVector* scalingCenter,
	ITriQuaternion* scalingRotation,
	ITriVector* scaling,
	ITriVector* rotationCenter,
	ITriQuaternion* rotation,
	ITriVector* translation )
{
	Transformation(
		scalingCenter->GetVector(),
		scalingRotation->GetQuaternion(),
		scaling->GetVector(),
		rotationCenter->GetVector(),
		rotation->GetQuaternion(),
		translation->GetVector() );		
}
