// Precompiled header
#include "StdAfx.h"

#if INTERIORS_ENABLED

// WodInteriorPlaceable.h header
#include "Tr2InteriorPlaceable.h"

BLUE_DEFINE( Tr2InteriorPlaceable );

const Be::ClassInfo* Tr2InteriorPlaceable::ExposeToBlue()
{
    EXPOSURE_BEGIN(Tr2InteriorPlaceable, "")
		MAP_INTERFACE( Tr2InteriorPlaceable )
		MAP_INTERFACE( ITr2Interior )
		MAP_INTERFACE( ITr2InteriorDynamic )
		MAP_INTERFACE( INotify )
		MAP_INTERFACE( IInitialize )
		MAP_INTERFACE( ITr2Renderable )
		MAP_INTERFACE( ITr2Pickable )
		MAP_INTERFACE( ITr2BoundingBox )

		MAP_ATTRIBUTE
		(
			"name",
			m_name,
			"Name of this placeable",
			Be::READWRITE | Be::PERSIST
		)
		
		MAP_ATTRIBUTE_WITH_CHOOSER( "placeableResPath", m_placeableResPath, "", Be::READWRITE | Be::PERSIST | Be::NOTIFY, NULL )
		MAP_ATTRIBUTE( "isUnique", m_isUniqueInstance, "When true, the placeable res is a copy, rather than a shared instance", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "isStatic", m_isStatic, "When true, the placeable generates shadows with other static objects", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "placeableRes", m_placeableRes, "", Be::READ )
		MAP_ATTRIBUTE( "transform", m_transform, "", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "display", m_display, "Boolean flag indicating whether or not to render this static object", Be::READWRITE )

		MAP_ATTRIBUTE( "visibleLightCount", m_visibleLightCount, "The total number of visible lights affecting this placeable, taking into account the current view", Be::READ )

#if BLUE_WITH_PYTHON
		// Bounding sphere data
		MAPFLOATARRAYSIZE( "boundingSphereCenter", m_boundingSphere, BlueDefaultIID, "bounding sphere center", Be::READ, 3 )
#endif

		MAP_ATTRIBUTE( "boundingSphereRadius", m_boundingSphere[3], "bounding sphere radius", Be::READ )

		MAP_ATTRIBUTE( "visualizeLightProbes", m_visualizeLightProbes, "Draw lines to the nearest contributing light probes", Be::READWRITE )
		MAP_ATTRIBUTE( "visualizeVisibleLights", m_drawLightSpider, "Draw lines to light sources affecting this placable", Be::READWRITE )

		// Translation, rotation, scaling
		MAP_PROPERTY( "translation", GetPosition, SetPosition, "Position of the placeable" )
		MAP_PROPERTY( "rotation", GetRotation, SetRotation, "Rotation of the placeable" )
		MAP_PROPERTY( "scaling", GetScaling, SetScaling, "Scale of the placeable" )

		// Bounding boxes
		MAP_METHOD_AND_WRAP( "GetBoundingBoxInLocalSpace", GetBoundingBoxInLocalSpace, "Gets the bounding box in local space" )
		MAP_METHOD_AND_WRAP( "GetBoundingBoxInWorldSpace", GetBoundingBoxInWorldSpace, "Gets the bounding box in world space" )
		MAP_METHOD_AND_WRAP( "MarkAsDirty", MarkAsDirty, "Marks the placeable as dirty (triggers Umbra objects, mirrors, shadows cast to be rebuilt" )
		MAP_METHOD_AND_WRAP( "BoundingBoxReset", BoundingBoxReset, "Resets the bounding box, removing any overrides" )
		MAP_METHOD_AND_WRAP( "BoundingBoxOverride", BoundingBoxOverride, "Override the object's bounding box with the one provided" )

		MAP_ATTRIBUTE( "attachedObjects", m_attachedObjects, "Vector of renderables that are associated with this object.", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "variableStore", m_variableStore, "Local variable store for this object", Be::READ )
		MAP_ATTRIBUTE( "probeOffset", m_probeOffset, "Offset for Enlighten SH probe position (in world space)", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "depthOffset", m_depthOffset, "Depth offset for transparency sorting", Be::READWRITE | Be::PERSIST )
		
		MAP_METHOD_AND_WRAP( "BindLowLevelShaders", BindLowLevelShaders, "Binds low level shaders for all meshes of the placeable." );

	EXPOSURE_END()
}

#endif
