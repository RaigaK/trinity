#include <StdAfx.h>

#include "Tr2GPUParticleType.h"

extern Be::VarChooser GPUParticleRenderMode[];


BLUE_DEFINE( Tr2GPUParticleType );
const Be::ClassInfo *Tr2GPUParticleType::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2GPUParticleType, "" )
		MAP_INTERFACE( Tr2GPUParticleType )
		
		MAP_ATTRIBUTE( "name", m_name, "Name of this particle behaviour, must be set", Be::READWRITE | Be::PERSIST | Be::NOTIFY  )

		MAP_ATTRIBUTE_WITH_CHOOSER("renderMode", m_renderMode, "Rendering mode for this particle type (determines pool drawn from)", 
			Be::READWRITE | Be::ENUM | Be::PERSIST | Be::NOTIFY, GPUParticleRenderMode )

		MAP_ATTRIBUTE( "color0", m_behaviour.colour[0], "First colour (spawn)", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "color1", m_behaviour.colour[1], "Second colour (~33% life)", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "color2", m_behaviour.colour[2], "Third colour (~66% life)", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "color3", m_behaviour.colour[3], "Final colour (death)", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "size", m_behaviour.size, "Three sizes stored in a vector, will be interpolated in bezier fashion over particle lifespan", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "sizeVariance", m_behaviour.sizeVariance, "Percentage variation in particle size", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "textureWindow", m_behaviour.textureWindow, "Where in the sprite sheet/atlas this particle's texture might be found", Be::READ )
		MAP_ATTRIBUTE( "gradientWindow", m_behaviour.gradientWindow, "Where in the gradient atlas this particle's gradient might be found", Be::READ )
		MAP_ATTRIBUTE( "texturePath", m_behaviour.texturePath, "Resource path for this particle's texture", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "gradientPath", m_behaviour.gradientPath, "Resource path for this particle's gradient", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		
		MAP_ATTRIBUTE( "lifespan", m_behaviour.lifespan, "Particle lifespan in seconds", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "lifespanVariance", m_behaviour.lifespanVariance, "Lifespan variation, as a percentage", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "deathTransition", m_deathTransition, "Name of particle behaviour to swap to at death", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "collideTransition", m_collideTransition, "Name of particle behaviour to swap to on collision", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "dragFactor", m_behaviour.dragFactor, "Higher values mean the particle decelerates faster, zero indicates no drag", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "angularVelocity", m_behaviour.angularVelocity, "Rotation rate of particle in Hz, negative values are interpreted as particle stretch factor", Be::READWRITE | Be::PERSIST )
		
		MAP_ATTRIBUTE( "turbulenceWeight", m_behaviour.turbulenceWeight, "How much this particle is influenced by the turbulence effect", Be::READWRITE | Be::PERSIST  )
		MAP_ATTRIBUTE( "gravityWeight", m_behaviour.gravityWeight, "How much this particle is affected by gravity", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "attractorWeight", m_behaviour.attractorWeight, "How much this particle is affected by attractors", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "vortexWeight", m_behaviour.vortexWeight, "How much this particle is affected by vortices", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "needsPush", m_needsPush, "Update the behaviour", Be::READWRITE );
		MAP_METHOD_AND_WRAP( "PushToPool", PushToPool, "" )
	EXPOSURE_END()
}

