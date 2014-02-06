#include "StdAfx.h"
#include "Tr2GPUParticlePoolManager.h"
#include "Tr2GPUParticlePool.h"

Tr2GPUParticlePoolManager::Tr2GPUParticlePoolManager( IRoot* lockobj ):
PARENTLOCK( m_particles )
{
}

void Tr2GPUParticlePoolManager::Add()
{
	Tr2GPUParticlePoolPtr particles;
	particles.CreateInstance();
	if( particles ) 
	{
		m_particles.Insert( -1, particles );
	}
}
