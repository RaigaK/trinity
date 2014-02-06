#include "StdAfx.h"
#include "TriVector4Parameter.h"

BLUE_DEFINE( TriVector4Parameter );

const Be::ClassInfo* TriVector4Parameter::ExposeToBlue()
{
	EXPOSURE_BEGIN( TriVector4Parameter, TRIVECTOR4PARAMETER_Description )
		MAP_INTERFACE( ITriEffectParameter )
		MAP_INTERFACE( TriVector4Parameter )
		MAP_INTERFACE( INotify )
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
		MAP_ATTRIBUTE
		( 
			"v1", 
			m_value.x, 
			"", 
			Be::READWRITE | Be::PERSIST  | Be::NOTIFY
		)
		MAP_ATTRIBUTE
		( 
			"v2", 
			m_value.y, 
			"", 
			Be::READWRITE | Be::PERSIST  | Be::NOTIFY
		)
		MAP_ATTRIBUTE
		( 
			"v3", 
			m_value.z, 
			"", 
			Be::READWRITE | Be::PERSIST  | Be::NOTIFY
		)
		MAP_ATTRIBUTE
		( 
			"v4", 
			m_value.w, 
			"", 
			Be::READWRITE | Be::PERSIST  | Be::NOTIFY
		)
		MAP_ATTRIBUTE
		(
			"value",
			m_value,
			"",
			Be::READWRITE | Be::NOTIFY
		)

		////////////////////////////////////////////////////////////////////////////
		MAP_ATTRIBUTE("usedByCurrentTechnique", m_isUsedByEffect, "na", Be::READ )
		MAP_ATTRIBUTE("usedByCurrentEffect", m_isUsedByEffect, "na", Be::READ )

	EXPOSURE_END()
}
