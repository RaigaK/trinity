////////////////////////////////////////////////////////////
//
//    Created:   Sept 2012
//    Copyright: CCP 2012
//
#pragma once
#ifndef EveLODHelper_h
#define EveLODHelper_h

extern float g_eveSpaceSceneLowUpdateRate;
extern float g_eveSpaceSceneMediumUpdateRate;


enum BoundingSphereQuery { EVE_BOUNDS_NORMAL, EVE_BOUNDS_WITH_CHILDREN };

// TODO: Change to use Tr2Lod
enum LodLevel
{
	LOD_INVALID = -1,
	
	LOD_HIGH = 0,
	LOD_MEDIUM,
	LOD_LOW,
};

class EveLODHelper
{
public:
	// --------------------------------------------------------------------------------
	// Description:
	//   Determines weather an object should be updated depending on LOD and time since
	//   last update
	// Arguments:
	//   lod - an object's LOD
	//   timeSinceUpdate - time since last update in seconds
	// Return value:
	//   Returns true if caller should be updated.
	// --------------------------------------------------------------------------------
	static inline bool ShouldUpdate( LodLevel lod, float timeSinceUpdate )
	{
		switch( lod )
		{
		case LOD_INVALID:
		case LOD_LOW:
			return timeSinceUpdate >= g_eveSpaceSceneLowUpdateRate;
			break;
		case LOD_MEDIUM:
			return timeSinceUpdate >= g_eveSpaceSceneMediumUpdateRate;
			break;
		default:
			break;
		}

		return true;
	}

	// --------------------------------------------------------------------------------
	// Description:
	//   Examines the two LODs and returns the higher(valid) of the two
	// Arguments:
	//   lod0 - first LOD to examine
	//   lod1 - second LOD to examine
	// Return value:
	//   Returns the higher(valid) LOD of the two LODs passed in, or LOD_INVALID if
	//   neither LOD is valid.
	// --------------------------------------------------------------------------------
	static inline LodLevel MergeLOD( LodLevel lod0, LodLevel lod1 )
	{
		if( lod0 == LOD_INVALID || lod1 == LOD_INVALID )
		{
			return ( lod0 == LOD_INVALID ) ? lod1 : lod0;
		}
		return ( lod0 < lod1 ) ? lod0 : lod1;
	}
};


#endif