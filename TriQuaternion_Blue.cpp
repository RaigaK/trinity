#include "StdAfx.h"
#include "include/TriQuaternion.h"
#include "Include/ITriVector.h"
#include "Include/ITriMatrix.h"

#if BLUE_WITH_PYTHON
BLUE_DEFINE( TriQuaternion );

const Be::ClassInfo* TriQuaternion::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriQuaternion, TRIQUATERNION_Description)
		MAP_INTERFACE(ITriQuaternion)
		MAP_INTERFACE(IPythonMethods)			

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
		//               w
		MAP_ATTRIBUTE
		( 
			"w", 
			w, 
			"", 
			Be::READWRITE | Be::PERSIST 
		)


		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP_OPTIONAL_ARGS( 
			"__init__",
			Py__init__, 
			4,
			"Constructor arguments" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP( 
			"SetXYZW",
			SetXYZW, 
			"sets the quaternion")

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Conjugate",
			PyConjugate, 
			"conjugates the quaternion.")

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Dot",
			PyDot, 
			"Accepts one argument, a quaternion. The result is a Dot product of this quaternion"
			"and argument 1" )

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Exp",
			PyExp, 
			"exponents the quaternion.")

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Identity",
			PyIdentity, 
			"Makes the quaternion an identity quaternion")

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Inverse",
			PyInverse, 
			"inverses the quaternion")
		
		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"IsIdentity",
			PyIsIdentity, 
			"Determines if a quaternion is an identity quaternion")

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Length",
			PyLength, 
			"Returns the length of a quaternion")

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"LengthSq",
			PyLengthSq, 
			"Returns the square of the length of a quaternion.")

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Ln",
			PyLn, 
			"Sets this quaternion to its natural algoritm")

		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Multiply",
			PyMultiply, 
			"Multiplies a quaternion with this quaternion" )
			
		////////////////////////////////////////////////////////////////////////////			
		MAP_METHOD_AND_WRAP( 
			"Normalize",
			PyNormalize, 
			"Normalizes this quaternion" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP( 
			"RotationAxis",
			PyRotationAxis, 
			"Set the rotation of the quaternion" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP( 
			"RotationMatrix",
			PyRotationMatrix, 
			"Set the rotation of the quaternion" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP( 
			"YawPitchRoll",
			PyYawPitchRoll, 
			"Set the rotation of the quaternion" )

		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AND_WRAP( 
			"Slerp",
			PySlerp, 
			"" )
			
		////////////////////////////////////////////////////////////////////////////
		MAP_METHOD_AS_METHOD( 
			"ToAxisAngle",
			PyToAxisAngle, 
			"" )


		////////////////////////////////////////////////////////////////////////////
		//               SetIdentity
		MAP_METHOD_AND_WRAP
		(
			"SetIdentity",
			SetIdentity, 
			"Sets quaternion to identity quaternion" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               SetRotationAxis
		MAP_METHOD_AND_WRAP
		( 
			"SetRotationAxis",
			PySetRotationAxis, 
			"Set the rotation of the quaternion" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               GetRotationAxis
		MAP_METHOD_AS_METHOD
		( 
			"GetRotationAxis",
			PyGetRotationAxis, 
			"Get the rotation of the quaternion" 
		)			

		////////////////////////////////////////////////////////////////////////////
		//               SetYawPitchRoll
		MAP_METHOD_AND_WRAP
		( 
			"SetYawPitchRoll",
			SetYawPitchRoll, 
			"Set the yaw pitch roll of the quaternion" 
		)			

		////////////////////////////////////////////////////////////////////////////
		//               GetYawPitchRoll
		MAP_METHOD_AND_WRAP
		( 
			"GetYawPitchRoll",
			PyGetYawPitchRoll, 
			"Get the yaw pitch roll of the quaternion" 
		)			

		////////////////////////////////////////////////////////////////////////////
		//               IncreaseYawPitchRoll
		MAP_METHOD_AND_WRAP
		( 
			"IncreaseYawPitchRoll",
			IncreaseYawPitchRoll, 
			"Increases the rotation of the quaternion" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               IncreaseLocalYawPitchRoll
		MAP_METHOD_AND_WRAP
		( 
			"IncreaseLocalYawPitchRoll",
			IncreaseLocalYawPitchRoll, 
			"Increases the rotation of the quaternion," 
			"relative to the current rotation" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               SetRotationArc
		MAP_METHOD_AND_WRAP
		( 
			"SetRotationArc",
			PySetRotationArc, 
			"Set the rotation of the quaternion from one vector to another" 
		)			

		////////////////////////////////////////////////////////////////////////////
		//               MultiplyQuaternion
		MAP_METHOD_AND_WRAP
		( 
			"MultiplyQuaternion",
			PyMultiplyQuaternion, 
			"Multiplies a quaternion with this quaternion" 
		)
		////////////////////////////////////////////////////////////////////////////
		//               SetSLERP
		MAP_METHOD_AND_WRAP
		( 
			"SetSLERP",
			PySetSLERP, 
			"Sets this quaternion to the spherical linear interpolation between the first one and the second. The t determines how far to interpolate." 
		)
		////////////////////////////////////////////////////////////////////////////
		//               Scale
		MAP_METHOD_AND_WRAP
		( 
			"Scale",
			PyScale, 
			"Scales the quaternion" 
		)
		////////////////////////////////////////////////////////////////////////////
		//               SetExp
		MAP_METHOD_AND_WRAP
		( 
			"SetExp",
			PySetExp, 
			"Sets this quaternion as the exponential of 'in'" 
		)
		////////////////////////////////////////////////////////////////////////////
		//               SetLn
		MAP_METHOD_AND_WRAP
		( 
			"SetLn",
			PySetLn, 
			"Sets this quaternion as the logarithm of 'in'" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               SetPower
		MAP_METHOD_AND_WRAP
		( 
			"Pow",
			PyPow, 
			"Sets this quaternion as this**pow" 
		)

	EXPOSURE_END()

}

#endif
