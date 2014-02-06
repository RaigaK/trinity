/* 
	*************************************************************************

	ITriTransform.h

	Author:    Hilmar Veigar Pétursson
	Created:   November 2000
	OS:        Win32
	Project:   Trinity

	Description:   

		Yeap


	Dependencies:

		DirectX 9.0, Probably more, ytbd.

	(c) CCP 2000

	*************************************************************************
*/

#ifndef _ITRITRANSFORM_H_
#define _ITRITRANSFORM_H_

#include "ITriRenderObject.h"
#include "ITriConstants.h"
#include "ITriVector.h"


struct ITriVector;
struct Collidee;
struct ID3DXMatrixStack;

BLUE_INTERFACE(ITriSplTransform) : public ITriRenderObject
{
	virtual void IncreaseLocalTranslation(
		float x, 
		float y, 
		float z
		) = 0;

	virtual bool RandomSurfacePoint(
		Vector3* point
		) = 0;

	virtual bool GetBoundingBox(
		Vector3* min,
		Vector3* max
		) = 0;

	virtual bool GetLocalBoundingBox(
		Vector3* min,
		Vector3* max
		) = 0;

	virtual float GetBoundingSphereRadius(
		) = 0;

	virtual float GetBoundingSphereScreenRadius(
		) = 0;

	virtual bool GetIntersection(
		Vector3* point,
		const Vector3* start
		) = 0;

	virtual bool Pick(
		ID3DXMatrixStack *stack,
		const Vector3* start, 
		const Vector3* dir, 
		Collidee* res, 
		bool top = false
		) =  0;

	virtual bool PickParticle(
		const Vector3* start, 
		const Vector3* end, 
		const Matrix* view,
		Collidee* res, 
		int* particleNum,
		float* dist
		) =  0;

	virtual bool GetBoundingSphereCenter(
		Vector3* center, 
		bool worldCoords = false
		) = 0;

	/////////////////////////////////////////////////////////////////////////////////////
	// access functions to local transform properties
	virtual const Vector3* GetTranslation(
		) = 0;

	virtual const Vector3* GetScaling(
		) = 0;

	virtual const Quaternion* GetRotation(
		) = 0;

	virtual const Matrix* GetLocalMatrix(
		) = 0;

	virtual void SetTranslation(
		const Vector3* tr
		) = 0;

	virtual void SetScaling(
		const Vector3* sc
		) = 0;

	virtual void SetRotation(
		const Quaternion* ro
		) = 0;

	/////////////////////////////////////////////////////////////////////////////////////
	// access function to world matrix transform properties
	virtual const Vector3* GetWorldPosition(
		) = 0;

	virtual const Quaternion* GetWorldRotation(
		) = 0;

	virtual const Matrix* GetWorldMatrix(
		) = 0;	
};

BLUE_INTERFACE(ITriTransform) : public ITriSplTransform
{
		virtual float GetCameraDistanceSq() = 0;
		virtual ITriRenderObjectPtr GetObject() 
		{	// Returning a NULL pointer - this is how you do it in crazy land:
			return ITriRenderObjectPtr();  
		};
};

BLUE_INTERFACE(ITriCplTransform) : public ITriTransform
{
};

#endif