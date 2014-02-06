////////////////////////////////////////////////////////////
//
//    Created:   March 2011
//    Copyright: CCP 2011
//
#include "StdAfx.h"
#include "EveSpaceSceneLightMgr.h"

// --------------------------------------------------------------------------------
// Description:
//   Nothing here atm
// --------------------------------------------------------------------------------
EveSpaceScenePointLight::EveSpaceScenePointLight( IRoot* lockobj ) :
	m_display( true ),
	m_position( 0.f, 0.f, 0.f ),
	m_outerRadius( 100.f ),
	m_color( 1.f, 1.f, 1.f, 1.f )
{
}

// --------------------------------------------------------------------------------
// Description:
//   Nothing here atm
// --------------------------------------------------------------------------------
bool EveSpaceScenePointLight::IsDisplay() const
{
	return m_display;
}

// --------------------------------------------------------------------------------
// Description:
//   Nothing here atm
// --------------------------------------------------------------------------------
const Vector3& EveSpaceScenePointLight::GetPosition() const
{
	return m_position;
}

// --------------------------------------------------------------------------------
// Description:
//   Nothing here atm
// --------------------------------------------------------------------------------
float EveSpaceScenePointLight::GetOuterRadius() const
{
	return m_outerRadius;
}

// --------------------------------------------------------------------------------
// Description:
//   Nothing here atm
// --------------------------------------------------------------------------------
const Color& EveSpaceScenePointLight::GetColor() const
{
	return m_color;
}






// --------------------------------------------------------------------------------
// Description:
//   Nothing here atm
// --------------------------------------------------------------------------------
EveSpaceSceneLightMgr::EveSpaceSceneLightMgr( IRoot* lockobj ) :
	PARENTLOCK( m_staticPointlights )
{
}

// --------------------------------------------------------------------------------
// Description:
//   Cleanup
// --------------------------------------------------------------------------------
EveSpaceSceneLightMgr::~EveSpaceSceneLightMgr()
{
}

// --------------------------------------------------------------------------------
// Description:
//   Nothing here atm
// --------------------------------------------------------------------------------
bool EveSpaceSceneLightMgr::Initialize()
{
	return true;
}

// --------------------------------------------------------------------------------
// Description:
//   Nothing here atm
// --------------------------------------------------------------------------------
bool EveSpaceSceneLightMgr::OnModified( Be::Var* val )
{
	return true;
}

// --------------------------------------------------------------------------------
// Description:
//   Nothing here atm
// --------------------------------------------------------------------------------
unsigned int EveSpaceSceneLightMgr::GetStaticPointlightCount() const
{
	return std::min( (unsigned int)m_staticPointlights.size(), (unsigned int)EVE_MAX_POINTLIGHT_COUNT );
}

// --------------------------------------------------------------------------------
// Description:
//   Nothing here atm
// --------------------------------------------------------------------------------
const EveSpaceScenePointLightPtr EveSpaceSceneLightMgr::GetStaticPointlight( unsigned int n )
{
	// sanity check!
	if( n >= m_staticPointlights.size() )
	{
		CCP_LOGERR( "Index out of bounds: idx: %d, size: %d", n, m_staticPointlights.size() );
		return NULL;
	}
	return m_staticPointlights[ n ];
}

