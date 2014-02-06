#include "StdAfx.h"
#include "Tr2MayaAnimationEngine.h"

#if BLUE_WITH_PYTHON

BLUE_DEFINE( Tr2MayaAnimationEngine );
BLUE_DEFINE( Tr2MayaAnimationEngineInfo );
BLUE_DEFINE( Tr2MayaAnimationCurveInfo );


const Be::ClassInfo* Tr2MayaAnimationEngine::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2MayaAnimationEngine, "" )
		MAP_INTERFACE( Tr2MayaAnimationEngine )
		MAP_ATTRIBUTE( "curves", m_curves, "", Be::READ | Be::PERSIST )		
		MAP_ATTRIBUTE( "hermiteSegments", m_hermiteSegments, "", Be::READ | Be::PERSIST )
		MAP_ATTRIBUTE( "bezierSegments", m_bezierSegments, "", Be::READ | Be::PERSIST )
		MAP_METHOD_AND_WRAP( "evaluate", evaluate, "(int curveIndex, float time)" )
	EXPOSURE_END()
}

const Be::ClassInfo* Tr2MayaAnimationCurveInfo::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2MayaAnimationCurveInfo, "" )
		MAP_INTERFACE( Tr2MayaAnimationCurveInfo )
		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "curveType", m_type, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "index", m_index, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "isStatic", m_isStatic, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "staticValue", m_staticValue, "", Be::READWRITE | Be::PERSIST )
	EXPOSURE_END()
}

const Be::ClassInfo* Tr2MayaAnimationEngineInfo::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2MayaAnimationEngineInfo, "" )
		MAP_INTERFACE( Tr2MayaAnimationEngineInfo )
		MAP_ATTRIBUTE( "fps", m_fps, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "curves", m_curves, "", Be::READWRITE | Be::PERSIST )
	EXPOSURE_END()
}

#endif
