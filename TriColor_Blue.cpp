#include "StdAfx.h"
#include "include/TriColor.h"
#include "Include/ITriVector.h"

#if BLUE_WITH_PYTHON
BLUE_DEFINE( TriColor );

const Be::ClassInfo* TriColor::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriColor, TRICOLOR_Description)
		MAP_INTERFACE(ITriColor)
		MAP_INTERFACE(IPythonMethods)

		////////////////////////////////////////////////////////////////////////////
		//               r
		MAP_ATTRIBUTE
		( 
			"r", 
			r, 
			"", 
			Be::READWRITE | Be::PERSIST
		)

		////////////////////////////////////////////////////////////////////////////
		//               g
		MAP_ATTRIBUTE
		( 
			"g", 
			g, 
			"", 
			Be::READWRITE | Be::PERSIST
		)

		////////////////////////////////////////////////////////////////////////////
		//               b
		MAP_ATTRIBUTE
		( 
			"b", 
			b, 
			"", 
			Be::READWRITE | Be::PERSIST
		)

		////////////////////////////////////////////////////////////////////////////
		//               a
		MAP_ATTRIBUTE
		( 
			"a", 
			a, 
			"", 
			Be::READWRITE | Be::PERSIST
		)

		////////////////////////////////////////////////////////////////////////////
		//               __init__
		MAP_METHOD_AND_WRAP_OPTIONAL_ARGS
		( 
			"__init__",
			Py__init__, 
			4,
			"Constructor arguments" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               SetRGB
		MAP_METHOD_AND_WRAP_OPTIONAL_ARGS
		( 
			"SetRGB",
			PySetRGB, 
			4,
			"Sets the RGB values of the color" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               SetHSV
		MAP_METHOD_AND_WRAP_OPTIONAL_ARGS
		( 
			"SetHSV",
			PySetHSV, 
			4,
			"Sets the HSV values of the color \r\n"
			"h = [0,360], s = [0,1], v = [0,1]"
			"if s == 0, then h = -1 (undefined)"
		)

		////////////////////////////////////////////////////////////////////////////
		//               SetVector
		MAP_METHOD_AND_WRAP_OPTIONAL_ARGS
		( 
			"SetVector",
			PySetVector, 
			1,
			"Finds the color of the vector and uses that." 
		)

		////////////////////////////////////////////////////////////////////////////
		//               GetHSV
		MAP_METHOD_AND_WRAP
		( 
			"GetHSV",
			PyGetHSV, 
			"Returns the HSV values of the color\r\n" 				
			"h = [0,360], s = [0,1], v = [0,1]\r\n"
			"if s == 0, then h = -1 (undefined)"
		)

		////////////////////////////////////////////////////////////////////////////
		//               FromInt
		MAP_METHOD_AND_WRAP
		( 
			"FromInt",
			PyFromInt, 
			"Changes thie color to the one reprecented by the integer" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               AsInt
		MAP_METHOD_AND_WRAP
		( 
			"AsInt",
			PyAsInt, 
			"Returns an integer reprecenting the color" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               Add
		MAP_METHOD_AS_METHOD
		( 
			"Add",
			PyAdd, 
			"Adds a color to this color." 
		)
		////////////////////////////////////////////////////////////////////////////
		//               AdjustContrast
		MAP_METHOD_AND_WRAP
		( 
			"AdjustContrast",
			AdjustContrast, 
			"Adjusts the contrast value of a color." 
		)

		////////////////////////////////////////////////////////////////////////////
		//               AdjustSaturation
		MAP_METHOD_AND_WRAP
		( 
			"AdjustSaturation",
			AdjustSaturation, 
			"Adjusts the saturation value of a color." 
		)

		////////////////////////////////////////////////////////////////////////////
		//               Lerp
		MAP_METHOD_AS_METHOD
		( 
			"Lerp",
			PyLerp, 
			"Uses linear interpolation to modify this color value" 
		)

		////////////////////////////////////////////////////////////////////////////
		//               Modulate
		MAP_METHOD_AS_METHOD
		( 
			"Modulate",
			PyModulate, 
			"Blends a color with this color." 
		)

		////////////////////////////////////////////////////////////////////////////
		//               Negative
		MAP_METHOD_AND_WRAP
		( 
			"Negative",
			Negative, 
			"Creates the negative color value of a color value." 
		)

		////////////////////////////////////////////////////////////////////////////
		//               Scale
		MAP_METHOD_AND_WRAP
		( 
			"Scale",
			Scale, 
			"Scales the value of the color." 
		)
	EXPOSURE_END()

}
#endif
