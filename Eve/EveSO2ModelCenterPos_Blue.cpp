#include "StdAfx.h"
#include "EveSO2ModelCenterPos.h"

BLUE_DEFINE( EveSO2ModelCenterPos );

const Be::ClassInfo* EveSO2ModelCenterPos::ExposeToBlue()
{

	EXPOSURE_BEGIN(EveSO2ModelCenterPos,"A function that returns the center of an EveSpaceObject2 model")
		MAP_INTERFACE( ITriVectorFunction )

		////////////////////////////////////////////////////////////////////////////
		//               name
		MAP_ATTRIBUTE
		(  
			 "name",          
			 mName,     
			 "Yes you can name your function", 
			 Be::READWRITE | Be::PERSIST 
		 )		
		 ////////////////////////////////////////////////////////////////////////////
		 //               Parent
		 MAP_ATTRIBUTE
		 ( 
			 "parent",        
			 m_parentObject,
			 "na", 
			 Be::READWRITE
		 )				
		 ////////////////////////////////////////////////////////////////////////////
		 //               value
		 MAP_ATTRIBUTE
		 (  
			 "value",         
			 mValue,         
			 "na", 
			 Be::READWRITE | Be::PERSIST
		 )

	EXPOSURE_END()

}