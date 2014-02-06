#include "StdAfx.h"
#include "Tr2FloatParameter.h"

BLUE_DEFINE( Tr2FloatParameter );

const Be::ClassInfo* Tr2FloatParameter::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2FloatParameter, "" )
		MAP_INTERFACE( ITriEffectParameter )
		MAP_INTERFACE( ITriReroutable )
		MAP_INTERFACE( IInitialize )

		////////////////////////////////////////////////////////////////////////////
		//               name
		MAP_ATTRIBUTE
		( 
			"name",    
			m_name,    
			"na", 
			Be::READWRITE | Be::NOTIFY | Be::PERSIST 
		)
		////////////////////////////////////////////////////////////////////////////
		//
		MAP_ATTRIBUTE( "value", m_value, "", Be::PERSISTONLY  )
		MAP_PROPERTY( "value", GetValue, SetValue, "Value of this parameter" )


		////////////////////////////////////////////////////////////////////////////
		MAP_ATTRIBUTE("usedByCurrentTechnique", m_isUsedByEffect, "na", Be::READ )
		MAP_ATTRIBUTE("usedByCurrentEffect", m_isUsedByEffect, "na", Be::READ )
		MAP_ATTRIBUTE("allowRerouting", m_allowRerouting, "na", Be::READWRITE | Be::PERSIST )
	EXPOSURE_END()
}
