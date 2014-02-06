#include "StdAfx.h"

#if APEX_ENABLED

#include "Apex.h"

BLUE_DEFINE_NONEXPOSED( Tr2Apex );

const Be::ClassInfo* Tr2Apex::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2Apex, "" )
		MAP_INTERFACE( Tr2Apex )
		MAP_PROPERTY
		( 
			"isVisualizationEnabled", 
			GetIsVisualizationEnabled, 
			SetIsVisualizationEnabled,
			""
		)
		MAP_PROPERTY
		( 
			"visualizeCollisionShapes", 
			GetVisualizeCollisionShapes, 
			SetVisualizeCollisionShapes, 
			"" 
		)
		MAP_PROPERTY
		(
			"parallelClothSim",
			GetClothSimParallel,
			SetClothSimParallel,
			"When set, cloth simulation is allowed to run in parallel with the game engine."
			"\nThis implies that cloth simulation results lag behind the animation and"
			"\nthe skinning of objects is delayed accordingly. This can greatly improve"
			"\nperformance."
		)
		MAP_PROPERTY
		(
			"parallelPhysxMeshSkinning",
			GetParallelPhysxMeshSkinning,
			SetParallelPhysxMeshSkinning,
			"If set, cloth mesh skinning for physics is done during simulation instead of\n"
			"before. This will cause the simulation to lag one frame behind. Setting this\n"
			"property will apply it to all current cloth meshes and adjust the frame delay\n"
			"appropriately."
		)

		MAP_PROPERTY
		(
			"parallelMeshMeshSkinning",
			GetParallelMeshMeshSkinning,
			SetParallelMeshMeshSkinning,
			"If set, cloth mesh-mesh skinning from physical to graphical mesh is done during\n"
			"next simulation step and not after the current one. This will cause the\n"
			"simulation to lag one frame behind. Setting this property will apply it\n"
			"to all current cloth meshes and adjust the frame delay appropriately."
		)

		MAP_PROPERTY
		(
			"parallelCpuSkinning",
			GetParallelCpuSkinning,
			SetParallelCpuSkinning,
			"All graphical vertices without correspondence to physical vertices or triangles are skinned normally.\n"
			"This flag specifies whether this happens during Physics scene simulation, or after."
		)

		MAP_PROPERTY
		( 
			"rendererVerbose", 
			GetRendererVerbose, 
			SetRendererVerbose, 
			"When set, the Apex renderer logs information on D3D structures created." 
		)
		MAP_PROPERTY
		( 
			"visualizeOnly", 
			GetVisualizeOnly, 
			SetVisualizeOnly, 
			"When set, only Apex visualization is rendered - the cloth meshes themselves are not rendered." 
		)
		
		MAP_PROPERTY
		(
		"fallbackSkinning",
		GetFallbackSkinning,
		SetFallbackSkinning,
		"Whether or not to use 'fallback' skinning for clothing"
		)

		MAP_PROPERTY
		(
		"enableLOD",
		GetEnableLOD,
		SetEnableLOD,
		"Whether or not to use LOD levels"
		)

		MAP_PROPERTY
		(
		"lodBenefitValue",
		GetLodBenefitValue,
		SetLodBenefitValue,
		"The benefit value for clothing LOD computations"
		)

		
		MAP_METHOD_AND_WRAP
		(
		"CoreDumpScene",
		CoreDumpScene,
		"Save a Core Dump file to disk"
		)
		MAP_METHOD_AND_WRAP
		(
		"MemoryUsageReport",
		MemoryUsageReport,
		"Save a memory usage report to disk"
		)


	EXPOSURE_END()
}

#endif // APEX_ENABLED
