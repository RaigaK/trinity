#include "StdAfx.h"

#if BLUE_WITH_PYTHON
#if DEPRECATED_ENABLED

#include "TriConvolutionMatrix5.h"

BLUE_DEFINE( TriConvolutionMatrix3 );
BLUE_DEFINE( TriConvolutionMatrix5 );
BLUE_DEFINE( TriConvolutionMatrix7 );

const Be::ClassInfo* TriConvolutionMatrix3::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriConvolutionMatrix3, TRICONVOLUTIONMATRIX3_Description)
		MAP_INTERFACE(ITriConvolutionMatrix3)
		MAP_INTERFACE(IPythonMethods)

		MAP_ATTRIBUTE( "_11", _11, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_12", _12, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_13", _13, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_21", _21, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_22", _22, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_23", _23, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_31", _31, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_32", _32, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_33", _33, "", Be::READWRITE | Be::PERSIST )

		////////////////////////////////////////////////////////////////////////////
		//               __init__
		MAPPYTHON
		( 
			__init__, 
			"Constructor arguments" 
		)	

	EXPOSURE_END()

}

const Be::ClassInfo* TriConvolutionMatrix5::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriConvolutionMatrix5, TRICONVOLUTIONMATRIX5_Description)
		MAP_INTERFACE(ITriConvolutionMatrix5)
		MAP_INTERFACE(IPythonMethods)

		MAP_ATTRIBUTE( "_11", _11, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_12", _12, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_13", _13, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_14", _14, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_15", _15, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_21", _21, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_22", _22, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_23", _23, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_24", _24, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_25", _25, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_31", _31, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_32", _32, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_33", _33, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_34", _34, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_35", _35, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_41", _41, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_42", _42, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_43", _43, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_44", _44, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_45", _45, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_51", _51, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_52", _52, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_53", _53, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_54", _54, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_55", _55, "", Be::READWRITE | Be::PERSIST )

		////////////////////////////////////////////////////////////////////////////
		//               __init__
		MAPPYTHON
		( 
			__init__, 
			"Constructor arguments" 
		)	

	EXPOSURE_END()

}

const Be::ClassInfo* TriConvolutionMatrix7::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriConvolutionMatrix7, TRICONVOLUTIONMATRIX7_Description)
		MAP_INTERFACE(ITriConvolutionMatrix7)
		MAP_INTERFACE(IPythonMethods)

		MAP_ATTRIBUTE( "_11", _11, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_12", _12, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_13", _13, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_14", _14, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_15", _15, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_16", _16, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_17", _17, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_21", _21, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_22", _22, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_23", _23, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_24", _24, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_25", _25, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_26", _26, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_27", _27, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_31", _31, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_32", _32, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_33", _33, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_34", _34, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_35", _35, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_36", _36, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_37", _37, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_41", _41, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_42", _42, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_43", _43, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_44", _44, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_45", _45, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_46", _46, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_47", _47, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_51", _51, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_52", _52, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_53", _53, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_54", _54, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_55", _55, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_56", _56, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_57", _57, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_61", _61, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_62", _62, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_63", _63, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_64", _64, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_65", _65, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_66", _66, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_67", _67, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_71", _71, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_72", _72, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_73", _73, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_74", _74, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_75", _75, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_76", _76, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "_77", _77, "", Be::READWRITE | Be::PERSIST )

		////////////////////////////////////////////////////////////////////////////
		//               __init__
		MAPPYTHON
		( 
			__init__, 
			"Constructor arguments" 
		)	

	EXPOSURE_END()

}

#endif
#endif
