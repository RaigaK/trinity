#include <StdAfx.h>
#include "Tr2GPUParticleEmitter.h"



BLUE_DEFINE( Tr2GPUParticleSubEmitter );

const Be::ClassInfo *Tr2GPUParticleSubEmitter::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2GPUParticleSubEmitter, "" )
		MAP_INTERFACE( Tr2GPUParticleSubEmitter )
		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST  )
		MAP_ATTRIBUTE( "behaviourName", m_behaviourName, "Name of particle type to emit", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "emissionRate", m_emissionRate, "Number of particles to emit per second", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "emissionDensity", m_emissionDensity, "Number of particles to emit per unit distance", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "inheritVelocity", m_inheritVelocity, "Portion of parent velocity to inherit (may be negative)", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "velocityScale", m_velocityScale, "Multiplier for velocity texture when spawning", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "positionScale", m_positionScale, "Multiplier for position texture when spawning", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "burstTime", m_burstTime, "Local time at which to emit a burst of particles", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "burstTimeLocal", m_burstTimeLocal, "Current local time, reset to zero if re-using emitters", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "burstCount", m_burstCount, "Number of particles to emit when bursting", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "burstCycle", m_burstCycle, "If set to > 0, after the initial burst will continue to burst with this period", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "offset", m_offset, "Sub-emitter offset, relative to parent emitter", Be::READWRITE | Be::PERSIST )
	EXPOSURE_END()
}

BLUE_DEFINE( Tr2GPUParticleEmitter );

const Be::ClassInfo *Tr2GPUParticleEmitter::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2GPUParticleEmitter, "" )
		MAP_INTERFACE( Tr2GPUParticleEmitter )
		MAP_INTERFACE( INotify )
		MAP_INTERFACE( ITr2GenericEmitter )
		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST  )
		MAP_ATTRIBUTE( "particleTypes", m_particleTypes, "Types of particles to emit (full description)", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "subEmitters", m_subEmitters, "Emitters for specific particle types", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "positionScale", m_positionScale, "Scale particle spawn volume", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "velocityScale", m_velocityScale, "Scale particle spawn velocity", Be::READWRITE )
		MAP_ATTRIBUTE( "positionTexturePath", m_positionTexturePath, "Texture defining valid spawn points", Be::READWRITE | Be::PERSIST | Be::NOTIFY  )
		MAP_ATTRIBUTE( "velocityTexturePath", m_velocityTexturePath, "Texture defining initial velocity distribution", Be::READWRITE | Be::PERSIST | Be::NOTIFY  )
		MAP_ATTRIBUTE( "offset", m_offset, "Position offset from parent object", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "lastUpdatePosition", m_lastUpdatePosition, "debug: last position", Be::READ )
		MAP_ATTRIBUTE( "lastUpdateVelocity", m_lastUpdateVelocity, "debug: last velocity", Be::READ )
		MAP_ATTRIBUTE( "lastPosValid", m_lastPosValid, "Whether the last position is valid, set to false when about to reuse an emitter", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "maximumTranslationPerFrame", m_maximumTranslationPerFrame, "Maximum translation in a single frame; any movement in excess of this will cause no particles to be emitted this frame", Be::READWRITE | Be::PERSIST )
		
	EXPOSURE_END()
}
