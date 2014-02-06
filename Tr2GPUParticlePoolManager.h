#pragma once
#ifndef Tr2GPUParticlePoolManager_h
#define Tr2GPUParticlePoolManager_h
#include "Vector3.h"

class Tr2GPUParticlePool;
BLUE_DECLARE_VECTOR( Tr2GPUParticlePool );

//A small, stupid class that holds a collection of particle pools.
//Particles being global in some sense rather than associated with any given renderable object,
// this seems like the most sensible way to manage them.
class Tr2GPUParticlePoolManager : public IRoot {
public:
	EXPOSE_TO_BLUE();
	Tr2GPUParticlePoolManager( IRoot* lockobj = NULL );
	Vector3 GetLastEgoTranslation() const { return m_lastEgoTranslation; }

	void Add();
	PTr2GPUParticlePoolVector m_particles;
	Vector3 m_lastEgoTranslation;
};

TYPEDEF_BLUECLASS( Tr2GPUParticlePoolManager );
BLUE_DECLARE( Tr2GPUParticlePoolManager );
#endif //Tr2GPUParticlePoolManager_h
