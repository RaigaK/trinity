#pragma once

#ifndef UmbraLibrary_h
#define UmbraLibrary_h

BLUE_DECLARE( UmbraLibrary );

// The UmbraLibrary class wraps Umbra functions for setting flags and getting
// statistics so that these can easily be exposed to Python and displayed in
// Jessica.
class UmbraLibrary : public IRoot
{
public:
	UmbraLibrary( IRoot* lockobj = 0 );

	EXPOSE_TO_BLUE();

	void UpdateStatistics( void );
	void SetUmbraLineDrawFlag( bool val, Umbra::LibraryDefs::LineType lt );
	bool GetUmbraLineDrawFlag( Umbra::LibraryDefs::LineType lt );
	bool GetDrawBoundingBoxes();
	void SetDrawBoundingBoxes( bool val );
	bool GetDrawRegionsOfInfluence();
	void SetDrawRegionsOfInfluence( bool val );
	bool GetDrawVirtualCameraAxii();
	void SetDrawVirtualCameraAxii( bool val );
	bool GetDrawWriteModels();
	void SetDrawWriteModels( bool val );
	unsigned int GetMemoryUsed();
	unsigned int GetLiveCameraCount();
	unsigned int GetLiveCellCount();
	unsigned int GetLiveModelCount();
	unsigned int GetLiveObjectCount();
	unsigned int GetLivePortalCount();
	unsigned int GetLiveROICount();
	unsigned int GetLiveNodeCount();
	unsigned int GetLiveInstanceCount();
	unsigned int GetFrustumCulledObjectCount();
	unsigned int GetFrustumTestedObjectCount();
	unsigned int GetOcclusionCulledObjectCount();
	unsigned int GetOcclusionTestedObjectCount();

};

TYPEDEF_BLUECLASS( UmbraLibrary );

#endif
