#include "StdAfx.h"
#include "include/TriVector.h"
#include "TriViewport.h"
#include "Include/ITriMatrix.h"
#include "Include/ITriQuaternion.h"

BLUE_DEFINE( TriVector );

const Be::ClassInfo* TriVector::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriVector, "A 3-float vector.")
		MAP_INTERFACE(ITriVector)
#if BLUE_WITH_PYTHON
		MAP_INTERFACE(IPythonMethods)
		MAP_INTERFACE(IPythonNumeric)
#endif

		////////////////////////////////////////////////////////////////////////////
		//               x
		MAP_ATTRIBUTE
		( 
			"x", 
			x, 
			"", 
			Be::READWRITE | Be::PERSIST 
		)
		
		////////////////////////////////////////////////////////////////////////////
		//               y
		MAP_ATTRIBUTE
		( 
			"y", 
			y, 
			"", 
			Be::READWRITE | Be::PERSIST 
		)
		
		////////////////////////////////////////////////////////////////////////////
		//               z
		MAP_ATTRIBUTE
		( 
			"z", 
			z, 
			"", 
			Be::READWRITE | Be::PERSIST 
		)

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP_OPTIONAL_ARGS(		
			"__init__",
			SetXYZ, 
			3,
			"Constructor arguments" )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"SetXYZ",
			SetXYZ, 
			"sets the vector" )			
			
		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Add",
			PyAdd,
			"Accepts one argument, a vector, which is added to this vector" )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Cross",
			PyCross, 
			"Accepts one argument, a vector. The result is a Cross product of this vector"
			"and argument 1" )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Dot",
			PyDot, 
			"Accepts one argument, a vector. The result is a Dot product of this vector"
			"and argument 1" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP( 
			"Length",
			Length, 
			"Returns the length on the vector" )

		////////////////////////////////////////////////////////////////////////////		
		MAP_METHOD_AND_WRAP( 
			"LengthSq",
			LengthSq, 
			"Returns the square of the length of a 3-D vector." )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP(
			"Lerp",
			PyLerp, 
			"" )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP(
			"Maximize",
			PyMaximize, 
			"" )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP(
			"Minimize",
			PyMinimize, 
			"" )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Normalize",
			Normalize, 
			"Normalizes the vector" )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Project",
			PyProject, 
			"" )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP(
			"Scale",
			Scale, 
			"Scales the vector by a factor" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP(
			"Subtract",
			PySubtract, 
			"" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP(
			"TransformCoord",
			PyTransformCoord, 
			"" )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP(	
			"TransformNormal",
			PyTransformNormal, 
			"" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP(
			"Unproject",
			PyUnproject, 
			"" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP( 
			"SetCrossProduct",
			PySetCrossProduct, 
			"Sets this vector to a crossproduct of two vectors" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP( 
			"DotProduct",
			PyDotProduct, 
			"Get the dotproduct of two vectors" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP( 
			"TransformQuaternion",
			PyTransformQuaternion, 
			"Transforms this vector by the quaternion" )

	EXPOSURE_END()

}
