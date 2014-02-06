#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "Tr2InteriorProbeVolume.h"

BLUE_DEFINE( Tr2InteriorProbeVolume );

// ------------------------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2InteriorProbeVolume::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2InteriorProbeVolume, "" )
        MAP_INTERFACE( Tr2InteriorProbeVolume )
		MAP_INTERFACE( IInitialize )

		MAP_ATTRIBUTE( "transform", m_transform, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "resX", m_lightProbeResX, "", Be::PERSISTONLY )
		MAP_ATTRIBUTE( "resY", m_lightProbeResY, "", Be::PERSISTONLY )
		MAP_ATTRIBUTE( "resZ", m_lightProbeResZ, "", Be::PERSISTONLY )

		MAP_PROPERTY_READONLY( "parentTransform", GetParentTransform, "Matrix specifying the position and rotation of the parent cell in the world" )

		// Bounding boxes
		MAP_METHOD_AND_WRAP( "GetBoundingBoxInLocalSpace", GetBoundingBoxInLocalSpace, "Gets the bounding box in local space" )
		MAP_METHOD_AND_WRAP( "GetBoundingBoxInWorldSpace", GetBoundingBoxInWorldSpace, "Gets the bounding box in world space" )

		MAP_PROPERTY( "resolutionX", GetResolutionX, SetResolutionX, "Probe resolution in X direction" )
		MAP_PROPERTY( "resolutionY", GetResolutionY, SetResolutionY, "Probe resolution in Y direction" )
		MAP_PROPERTY( "resolutionZ", GetResolutionZ, SetResolutionZ, "Probe resolution in Z direction" )

		MAP_ATTRIBUTE( "drawBoundingBox", m_drawBoundingBox, "renderDebugInfo must be on!", Be::READWRITE )
		MAP_ATTRIBUTE( "drawLightProbes", m_bDrawLightProbes, "draw light probe debug information (renderDebugInfo must be on)", Be::READWRITE )

		MAP_ATTRIBUTE( "drawSphereProbes", m_sphereProbes, "Draw colored spheres in probe positions", Be::READWRITE )
		MAP_ATTRIBUTE( "drawProbeCulling", m_drawProbeCulling, "Draw probe cull status (only when drawSphereProbes is on)", Be::READWRITE )
		MAP_ATTRIBUTE( "hasValidProbes", m_validProbes, "True if the volume contains valid (built) probe data", Be::READ )
	EXPOSURE_END()
}

#endif
