////////////////////////////////////////////////////////////
//
//    Created:   Februaru 2016
//    Copyright: CCP 2016
//

#include "StdAfx.h"
#include "EveLocatorSets.h"

// locator item definition
static BlueStructureDefinition LocatorStructureDef[] =
{
	{ "position", Be::FLOAT32_3, 0 },
	{ "direction", Be::FLOAT32_4, 12 },
	{ "boneIndex", Be::INT32_1, 28 },
	{ 0 }
};

// --------------------------------------------------------------------------------
// Description:
//   Initialize data members
// --------------------------------------------------------------------------------
EveLocatorSets::EveLocatorSets( IRoot* lockobj ) :
	PARENTLOCK( m_locators )
{
	m_locators.SetStructureDefinition( LocatorStructureDef );
}

// --------------------------------------------------------------------------------
// Description:
//   Byebye
// --------------------------------------------------------------------------------
EveLocatorSets::~EveLocatorSets()
{
}



