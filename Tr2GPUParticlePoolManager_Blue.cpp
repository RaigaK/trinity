#include "StdAfx.h"
#include "Tr2GPUParticlePoolManager.h"

BLUE_DEFINE( Tr2GPUParticlePoolManager );

const Be::ClassInfo *Tr2GPUParticlePoolManager::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2GPUParticlePoolManager, "" )
		MAP_INTERFACE( Tr2GPUParticlePoolManager )
		MAP_METHOD_AND_WRAP( "Add", Add, "Add new particles" )		
		MAP_ATTRIBUTE("particles", m_particles, "List of stateful particles", Be::READ)
		MAP_ATTRIBUTE( "lastEgoTranslation", m_lastEgoTranslation, "last update to ego ball", Be::READ )
	EXPOSURE_END()
}