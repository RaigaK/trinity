////////////////////////////////////////////////////////////
//
//    Created:   June 2010
//    Copyright: CCP 2010
//
#include "StdAfx.h"
#include "Tr2ShaderPermuteTag.h"
//#include "Tr2ShaderMaterialParameter.h"


BLUE_DEFINE( Tr2ShaderPermuteTag );

const Be::ClassInfo* Tr2ShaderPermuteTag::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ShaderPermuteTag, "" )
		
	MAP_INTERFACE(Tr2ShaderPermuteTag)
	MAP_INTERFACE(IInitialize)

		MAP_ATTRIBUTE
		( 
			"name",      
			m_tagName,
			"the tag name", 
			Be::READ | Be::PERSIST
		)
		
		MAP_ATTRIBUTE
		( 
			"permuteDefineString",      
			m_permuteDefine,
			"the tag name", 
			Be::READ | Be::PERSIST
		)

		// this may not persist at all, and instead be generated at runtime/compile time, though computing exclusions gets harder
		MAP_ATTRIBUTE
		( 
			"tagBits",      
			m_tagBits,
			"the bits that map to this permute", 
			Be::READ | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"precompileHint",
			m_precompileHint,
			"whether precompilation never (-1) or always (1) sets this flag, or compiles with it both enabled and disabled (0, default)",
			Be::READ | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"predicate",
			m_predicate,
			"python expression to determine when this flag is allowed during precompilation",
			Be::READ | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"unused",
			m_unused,
			"python expression to determine when this flag is unused during precompilation",
			Be::READ | Be::PERSIST
		)
		

	EXPOSURE_END()


}


