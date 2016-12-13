#include "StdAfx.h"
#if APEX_ENABLED

#include "Tr2ApexScene.h"

BLUE_DEFINE_NONEXPOSED( Tr2ApexScene );

const Be::ClassInfo* Tr2ApexScene::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ApexScene, "" )
		MAP_INTERFACE( Tr2ApexScene )
		
		MAP_PROPERTY
		( 
			"isVisualizationEnabled", 
			GetIsVisualizationEnabled, 
			SetIsVisualizationEnabled,
			""
		)
		MAP_PROPERTY
		( 
			"visualizeClothingSkinnedPositions", 
			GetVisualizeClothingSkinnedPositions, 
			SetVisualizeClothingSkinnedPositions, 
			"Marks each animation position with a small cross. Blue for static vertices, black to white for increasing max distance." 
		)
		MAP_PROPERTY
		( 
			"visualizeClothingSphereCollisions", 
			GetVisualizeClothingSphereCollisions, 
			SetVisualizeClothingSphereCollisions, 
			"The part of the mesh with backstop is solidly rendered. Red for front faces, blue for back faces." 
		)
		MAP_PROPERTY
		( 
			"visualizeClothingMaxDistanceOut", 
			GetVisualizeClothingMaxDistanceOut, 
			SetVisualizeClothingMaxDistanceOut, 
			"Draws a line from the skinned position along the skinned normal with the length of the max distance this vertex is allowed to move." 
		)
		MAP_PROPERTY
		( 
			"visualizeClothingMaxDistanceIn", 
			GetVisualizeClothingMaxDistanceIn, 
			SetVisualizeClothingMaxDistanceIn, 
			"Same as VISUALIZE_CLOTHING_MAX_DISTANCE_OUT but to the other side. Bounded by backstop" 
		)
		MAP_PROPERTY
		( 
		"visualizeClothingAllSkinMap", 
		GetVisualizeClothingAllSkinMap, 
		SetVisualizeClothingAllSkinMap, 
		"Draws the full support mesh for mesh-mesh skinning." 
		)
		MAP_PROPERTY
		( 
		"visualizeClothingBadSkinMap", 
		GetVisualizeClothingBadSkinMap, 
		SetVisualizeClothingBadSkinMap, 
		"Draws the support mesh for mesh-mesh skinning. But only for vertices that actually lie outisde of the support mesh and could cause problems" 
		)
		MAP_PROPERTY
		( 
			"visualizeClothingSkinMap", 
			GetVisualizeClothingSkinMap, 
			SetVisualizeClothingSkinMap, 
			"Draws the actual support mesh for mesh-mesh skinning. Only the parts that are effectively used." 
		)
		MAP_PROPERTY
		( 
			"visualizeClothingRenderNormals", 
			GetVisualizeClothingRenderNormals, 
			SetVisualizeClothingRenderNormals, 
			"Draws the normals (blue) of the rendered mesh. (scalable)"
		)
		MAP_PROPERTY
		( 
			"visualizeClothingRenderTangents", 
			GetVisualizeClothingRenderTangents, 
			SetVisualizeClothingRenderTangents, 
			"Draws the tangent (red) and bitangent (green) of the rendered mesh. (scalable)" 
		)
		MAP_PROPERTY
		( 
			"visualizeClothingPhysicsMeshWire", 
			GetVisualizeClothingPhysicsMeshWire, 
			SetVisualizeClothingPhysicsMeshWire, 
			"Draws the simulation mesh, only the active region. Yellow turns to red the closer a vertex gets to its max distance. (scalable)" 
		)
#if 0 // not implemented
		MAP_PROPERTY
		( 
			"visualizeClothingPhysicsMeshSolid", 
			GetVisualizeClothingPhysicsMeshSolid, 
			SetVisualizeClothingPhysicsMeshSolid, 
			"Same as VISUALIZE_CLOTHING_PHYSICS_MESH_WIRE but with solid triangles." 
		)
#endif
		MAP_PROPERTY
		( 
			"visualizeClothingSkeleton", 
			GetVisualizeClothingSkeleton, 
			SetVisualizeClothingSkeleton, 
			"Draws lines from parent to child bones. Active ones in purple, passive in blue" 
		)
		MAP_PROPERTY
		( 
		"visualizeClothingBoneFrames", 
		GetVisualizeClothingBoneFrames, 
		SetVisualizeClothingBoneFrames, 
		"Draws the frame of each bone. (scalable)" 
		)
		MAP_PROPERTY
		( 
		"visualizeClothingBoneNames", 
		GetVisualizeClothingBoneNames, 
		SetVisualizeClothingBoneNames, 
		"Displays the name of each bone. (scalable)" 
		)
		MAP_PROPERTY
		(	
			"visualizeClothingVelocities", 
			GetVisualizeClothingVelocities, 
			SetVisualizeClothingVelocities, 
			"Draws lines for each simulated vertex' velocity. (scalable)" 
		)
		MAP_PROPERTY
		( 
			"visualizeClothingGraphicalVertexBones", 
			GetVisualizeClothingGraphicalVertexBones, 
			SetVisualizeClothingGraphicalVertexBones, 
			"Draws colored lines from each graphical vertex to the bones it uses for skinning. White to black for decreasing weights." 
		)
		MAP_PROPERTY
		( 
			"visualizeClothingPhysicalVertexBones", 
			GetVisualizeClothingPhysicalVertexBones, 
			SetVisualizeClothingPhysicalVertexBones, 
			"Draws colored lines from each simulation vertex to the bones it uses for skinning. White to black for decreasing weights." 
		)
		MAP_PROPERTY
		( 
		"visualizeClothingAcollisionUmbrellas", 
		GetVisualizeClothingAcollisionUmbrellas, 
		SetVisualizeClothingAcollisionUmbrellas, 
		"Draws small segments of the backstop sphere for each simulation vertex. (scalable)" 
		)

		MAP_PROPERTY_READONLY
		(
			"nbActorsInPhysxScene",
			GetNbActorsInPhysxScene,
			"The number of actors in the PhysX scene"
		)
		MAP_PROPERTY_READONLY
		(
			"nbStaticShapesInPhysxScene",
			GetNbStaticShapesInPhysxScene,
			"The number of static shapes in the PhysX scene"
		)
		MAP_PROPERTY_READONLY
		(
			"nbDynamicShapesInPhysxScene",
			GetNbDynamicShapesInPhysxScene,
			"The number of dynamic shapes in the PhysX scene"
		)
		MAP_PROPERTY_READONLY
		(
			"nbJointsInPhysxScene",
			GetNbJointsInPhysxScene,
			"The number of joints in the PhysX scene"
		)
		MAP_PROPERTY_READONLY
		(
			"nbEffectorsInPhysxScene",
			GetNbEffectorsInPhysxScene,
			"The number of effectors in the PhysX scene"
		)

		MAP_METHOD_AND_WRAP
		(
			"DumpStats",
			DumpStats,
			"Dump Apex scene stats to log"
		)

		MAP_METHOD_AND_WRAP
		(
			"CreatePlane",
			CreatePlane,
			"Convenience helper method to create a plane in the physx scene\n"
			":param position: point on a plane\n"
			":param normal: plane normal\n"
			":param distance: "
		)


	EXPOSURE_END()
}

#endif // APEX_ENABLED
