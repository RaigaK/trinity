#include "StdAfx.h"

#include "Tr2GPUParticlePool.h"
#include "Resources/TriTextureRes.h"

BLUE_DEFINE( Tr2GPUParticlePool );


Be::VarChooser GPUParticleTextureDebuggingView[] =
{
	{
		"Position",     
		BeCast( Tr2GPUParticlePool::ParticleDebugPosition ),     
		"Position texture"
	},
	{
		"Velocity",     
		BeCast( Tr2GPUParticlePool::ParticleDebugVelocity ),     
		"Velocity texture"
	},
	{
		"Behaviour",     
		BeCast( Tr2GPUParticlePool::ParticleDebugBehaviour ),     
		"Behaviour texture"
	},
	{ 0 }
};


Be::VarChooser GPUParticleRenderMode[] =
{
	{
		"Additive",     
		BeCast( GPUPRM_Additive ),     
		"Additive blending"
	},
	{
		"Transparent",     
		BeCast( GPUPRM_Transparent ),     
		"Transparent (srcAlpha, invSrcAlpha)"
	},
	{
		"PreMulAlpha",     
		BeCast( GPUPRM_PreMultipliedAlpha ),     
		"Pre-multiplied alpha transparency (one, invSrcAlpha)"
	},
	{
		"Distortion",     
		BeCast( GPUPRM_Distortion ),     
		"Distortion (signed additive, rendered to distortion buffer)"
	},
	{ 0 }
};


const Be::ClassInfo* Tr2GPUParticlePool::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2GPUParticlePool, "" )
        MAP_INTERFACE( Tr2GPUParticlePool )
		MAP_INTERFACE( ID3DTexture )

		MAP_METHOD_AND_WRAP( "ReInitialise", ReInitialise_Python, "Re-creates any GPU resources etc. using the last init. values" )
		MAP_METHOD_AND_WRAP( "SupportLudicrousParticleCount", SupportLudicrousParticleCount, "Bump the number of GPU particles to silly levels, for Jessica beauty shots" )

		MAP_METHOD_AND_WRAP( "SetDefaultSpawnTextures", SetDefaultSpawnTextures, "Set default position and velocity textures to use when spawning" )
		MAP_METHOD_AND_WRAP( "SetTurbulenceTexture", SetTurbulenceTexture, "Sets the volume texture to be used to simulate space-turbulence" )
		MAP_METHOD_AND_WRAP( "SetTurbulenceScale", SetTurbulenceScale, "Sets the tiling size of the volume texture used to simulate space-turbulence" )
		MAP_METHOD_AND_WRAP( "SetTurbulenceSpeed", SetTurbulenceSpeed, "Sets speed at which turbulence changes" )

		MAP_ATTRIBUTE_WITH_CHOOSER("renderMode", m_renderMode, "Rendering mode for this pool", Be::READ | Be::ENUM, GPUParticleRenderMode )
		
		MAP_ATTRIBUTE("name", m_name, "Name", Be::READWRITE)

		MAP_ATTRIBUTE("width", m_particleRTWidth, "Width of the render targets used by particles", Be::READ)
		MAP_ATTRIBUTE("height", m_particleRTHeight, "Height of the render targets used by particles", Be::READ)
		MAP_ATTRIBUTE("particleTotal", m_particleTotal, "Maximum particle count", Be::READ)
		MAP_ATTRIBUTE("activeParticleIndex", m_activeParticleIndex, "Position where new particles are being spawned in the buffer", Be::READ )
		MAP_ATTRIBUTE("behaviourCountMax", m_behaviourCountMax, "Number of supported particle behaviours", Be::READ)
		MAP_ATTRIBUTE("behaviourCount", m_behaviourCount, "Number of created particle behaviours", Be::READ)
		MAP_ATTRIBUTE("multipleParticleStreams", m_multipleParticleStreams, "Multiple vertex data streams enabled?", Be::READ )
		MAP_ATTRIBUTE("behaviourTextureWidth", m_behaviourTextureWidth, "Width of behaviour texture, indicates size of behaviour datum in float4s", Be::READ )
		
		MAP_ATTRIBUTE("spawnParticleShader", m_spawnParticleShader, "Shader used for spawning particles", Be::READ )
		MAP_ATTRIBUTE("updateParticleShader", m_updateParticleShader, "Shader used for updating particles", Be::READ )
		MAP_ATTRIBUTE("renderParticleShader", m_renderParticleShader, "Shader used for rendering particles", Be::READ )
		
		MAP_ATTRIBUTE("turbulenceOffset", m_turbulenceOffset, "Relative offset of turbulence cube", Be::READ )
		MAP_ATTRIBUTE("turbulenceAnim", m_turbulenceAnim, "Animation of turbulence cube", Be::READ )
		MAP_ATTRIBUTE("turbulenceScale", m_turbulenceScale, "Size of turbulence cube", Be::READ )
		MAP_ATTRIBUTE("turbulenceSpeed", m_turbulenceSpeed, "Speed of turbulence evolution", Be::READ )

		MAP_ATTRIBUTE_WITH_CHOOSER(
			"debuggingMode", 
			m_debuggingMode, 
			"Debugging mode (texture window visualisation)", 
			Be::READWRITE | Be::ENUM, 
			GPUParticleTextureDebuggingView )
		
		MAP_ATTRIBUTE( "textureAtlas", m_textureAtlas, "Atlas used for particle textures", Be::READ )
		MAP_ATTRIBUTE( "gradientAtlas", m_gradientAtlas, "Atlas used for particle gradients", Be::READ )
		MAP_ATTRIBUTE( "positionDefault", m_positionOffsetDefault, "Default position offset texture", Be::READWRITE )
		MAP_ATTRIBUTE( "velocityDefault", m_velocityOffsetDefault, "Default spawn velocity texture", Be::READWRITE )

		MAP_ATTRIBUTE( "debugSpawnQuadCounter", m_debugSpawnQuadCounter, "Debug spawn quad counter", Be::READ )
		MAP_ATTRIBUTE( "usageDensityModifier", m_usageDensityModifier, "Spawn rate modifier based on pool consumption rate", Be::READ )
		MAP_ATTRIBUTE( "usageDensityModifierTarget", m_usageDensityModifierTarget, "Desired spawn rate modifier based on pool consumption rate", Be::READ )
		MAP_ATTRIBUTE( "lastWrapTime", m_lastWrapTime, "Time the pool last filled completely and spawning wrapped to the beginning", Be::READ )
		MAP_ATTRIBUTE( "liveParticles", m_liveParticles, "Do we have any live particles? Conservative guess based on max lifespan and last spawn time.", Be::READ )

		MAP_METHOD_AND_WRAP
		(
			"HasALObject",
			HasALObject,
			"Returns True iff Tr2GPUParticlePool contains a reference to passed AL object ID.\n"
			"Used for debugging along with trinity.GetLiveALResources.\n"
			"Arguments:\n"
			"type - AL object type (trinity.AL_OBJECT_TYPE)\n"
			"object - AL object ID"
		)
	EXPOSURE_END()
}
