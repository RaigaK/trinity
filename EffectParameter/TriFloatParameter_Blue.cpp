#include "StdAfx.h"
#include "TriFloatParameter.h"

BLUE_DEFINE( TriFloatParameter );
BLUE_DEFINE( TriAniFloatParameter );

const Be::ClassInfo* TriFloatParameter::ExposeToBlue()
{
	EXPOSURE_BEGIN( TriFloatParameter, TRIFLOATPARAMETER_Description )
		MAP_INTERFACE( ITriEffectParameter )
		MAP_INTERFACE( IInitialize )
		MAP_INTERFACE( INotify )
		
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
		MAP_ATTRIBUTE
		( 
			"value", 
			m_value, 
			"", 
			Be::READWRITE | Be::PERSIST | Be::NOTIFY
		)
		////////////////////////////////////////////////////////////////////////////
		MAP_ATTRIBUTE( "usedByCurrentTechnique", m_isUsedByEffect, "na", Be::READ )
		MAP_ATTRIBUTE( "usedByCurrentEffect", m_isUsedByEffect, "na", Be::READ )

	EXPOSURE_END()
}

const Be::ClassInfo* TriAniFloatParameter::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriAniFloatParameter, TRIFLOATPARAMETER_Description)
		MAP_INTERFACE( TriFloatParameter )

		////////////////////////////////////////////////////////////////////////////
		//               displayCurve
		MAP_ATTRIBUTE
		(    
			"valueCurve",
			mValueCurve,
			"na",
			Be::READWRITE | Be::PERSIST
		)

	EXPOSURE_CHAINTO( TriFloatParameter )
}