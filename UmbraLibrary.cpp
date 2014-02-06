#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "UmbraLibrary.h"

CCP_STATS_DECLARE( umbraMemoryUsed, "Trinity/Umbra/MemoryUsed", false, CST_MEMORY, "Amount of memory used by Umbra." );
CCP_STATS_DECLARE( umbraLiveCameraCount, "Trinity/Umbra/LiveCameraCount", false, CST_COUNTER_LOW, "Number of live Umbra cameras." );
CCP_STATS_DECLARE( umbraLiveCellCount, "Trinity/Umbra/LiveCellCount", false, CST_COUNTER_LOW, "Number of live Umbra cells." );
CCP_STATS_DECLARE( umbraLiveModelCount, "Trinity/Umbra/LiveModelCount", false, CST_COUNTER_HIGH, "Number of live Umbra models." );
CCP_STATS_DECLARE( umbraLiveObjectCount, "Trinity/Umbra/LiveObjectCount", false, CST_COUNTER_HIGH, "Number of live Umbra objects." );
CCP_STATS_DECLARE( umbraLivePortalCount, "Trinity/Umbra/LivePortalCount", false, CST_COUNTER_LOW, "Number of live Umbra portals." );
CCP_STATS_DECLARE( umbraLiveROICount, "Trinity/Umbra/LiveROICount", false, CST_COUNTER_HIGH, "Number of live Umbra ROIs." );
CCP_STATS_DECLARE( umbraLiveNodeCount, "Trinity/Umbra/LiveNodeCount", false, CST_COUNTER_HIGH, "Number of live Umbra nodes." );
CCP_STATS_DECLARE( umbraLiveInstanceCount, "Trinity/Umbra/LiveInstanceCount", false, CST_COUNTER_HIGH, "Number of live Umbra instances." );
CCP_STATS_DECLARE( umbraFrustumCulledObjectCount, "Trinity/Umbra/FrustumCulledObjectCount", false, CST_COUNTER_LOW, "Number of frustum-culled Umbra objects." );
CCP_STATS_DECLARE( umbraFrustumTestedObjectCount, "Trinity/Umbra/FrustumTestedObjectCount", false, CST_COUNTER_LOW, "Number of frustum-tested Umbra objects." );
CCP_STATS_DECLARE( umbraOcclusionCulledObjectCount, "Trinity/Umbra/OcclusionCulledObjectCount", false, CST_COUNTER_LOW, "Number of occlusion-culled Umbra objects." );
CCP_STATS_DECLARE( umbraOcclusionTestedObjectCount, "Trinity/Umbra/OcclusionTestedObjectCount", false, CST_COUNTER_LOW, "Number of occlusion-tested Umbra objects." );

UmbraLibrary::UmbraLibrary( IRoot* lockobj /*= 0 */ )
{
}

void UmbraLibrary::SetUmbraLineDrawFlag( bool val, Umbra::LibraryDefs::LineType lt )
{
	if ( val )
	{
		Umbra::Library::setFlags( Umbra::LibraryDefs::LINEDRAW, lt );
	}
	else
	{
		Umbra::Library::clearFlags( Umbra::LibraryDefs::LINEDRAW, lt );
	}
}

void UmbraLibrary::UpdateStatistics( void )
{
	CCP_STATS_SET( umbraMemoryUsed, GetMemoryUsed() );
	CCP_STATS_SET( umbraLiveCameraCount, GetLiveCameraCount() );
	CCP_STATS_SET( umbraLiveCellCount, GetLiveCellCount() );
	CCP_STATS_SET( umbraLiveModelCount, GetLiveModelCount() );
	CCP_STATS_SET( umbraLiveObjectCount, GetLiveObjectCount() );
	CCP_STATS_SET( umbraLivePortalCount, GetLivePortalCount() );
	CCP_STATS_SET( umbraLiveROICount, GetLiveROICount() );
	CCP_STATS_SET( umbraLiveNodeCount, GetLiveNodeCount() );
	CCP_STATS_SET( umbraLiveInstanceCount, GetLiveInstanceCount() );
	CCP_STATS_SET( umbraFrustumCulledObjectCount, GetFrustumCulledObjectCount() );
	CCP_STATS_SET( umbraFrustumTestedObjectCount, GetFrustumTestedObjectCount() );
	CCP_STATS_SET( umbraOcclusionCulledObjectCount, GetOcclusionCulledObjectCount() );
	CCP_STATS_SET( umbraOcclusionTestedObjectCount, GetOcclusionTestedObjectCount() );
}

bool UmbraLibrary::GetUmbraLineDrawFlag( Umbra::LibraryDefs::LineType lt )
{
	bool res = (Umbra::Library::getFlags( Umbra::LibraryDefs::LINEDRAW ) & lt) != 0;
	return res;
}

bool UmbraLibrary::GetDrawBoundingBoxes()
{
	return GetUmbraLineDrawFlag( Umbra::LibraryDefs::LINE_OBJECT_OBBS );
}

void UmbraLibrary::SetDrawBoundingBoxes( bool val )
{
	SetUmbraLineDrawFlag( val, Umbra::LibraryDefs::LINE_OBJECT_OBBS );
}

bool UmbraLibrary::GetDrawRegionsOfInfluence()
{
	return GetUmbraLineDrawFlag( Umbra::LibraryDefs::LINE_REGIONS_OF_INFLUENCE );
}

void UmbraLibrary::SetDrawRegionsOfInfluence( bool val )
{
	SetUmbraLineDrawFlag( val, Umbra::LibraryDefs::LINE_REGIONS_OF_INFLUENCE );
}

bool UmbraLibrary::GetDrawVirtualCameraAxii()
{
	return GetUmbraLineDrawFlag( Umbra::LibraryDefs::LINE_VIRTUAL_CAMERA_AXII );
}

void UmbraLibrary::SetDrawVirtualCameraAxii( bool val )
{
	SetUmbraLineDrawFlag( val, Umbra::LibraryDefs::LINE_VIRTUAL_CAMERA_AXII );
}

bool UmbraLibrary::GetDrawWriteModels()
{
	return GetUmbraLineDrawFlag( Umbra::LibraryDefs::LINE_OBJECT_WRITE_MODEL );
}

void UmbraLibrary::SetDrawWriteModels( bool val )
{
	SetUmbraLineDrawFlag( val, Umbra::LibraryDefs::LINE_OBJECT_WRITE_MODEL );
}

unsigned int UmbraLibrary::GetMemoryUsed()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_MEMORYUSED );
}

unsigned int UmbraLibrary::GetLiveCameraCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_LIVECAMERAS );
}

unsigned int UmbraLibrary::GetLiveCellCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_LIVECELLS );
}

unsigned int UmbraLibrary::GetLiveModelCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_LIVEMODELS );
}

unsigned int UmbraLibrary::GetLiveObjectCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_LIVEOBJECTS );
}

unsigned int UmbraLibrary::GetLivePortalCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_LIVEPHYSICALPORTALS );
}

unsigned int UmbraLibrary::GetLiveROICount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_LIVEREGIONSOFINFLUENCE );
}

unsigned int UmbraLibrary::GetLiveNodeCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_LIVENODES );
}

unsigned int UmbraLibrary::GetLiveInstanceCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_LIVEINSTANCES );
}

unsigned int UmbraLibrary::GetFrustumCulledObjectCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_DATABASEOBSVFCULLED );
}

unsigned int UmbraLibrary::GetFrustumTestedObjectCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_DATABASEOBSVFTESTED );
}

unsigned int UmbraLibrary::GetOcclusionCulledObjectCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_DATABASEOBSOCCLUSIONCULLED );
}

unsigned int UmbraLibrary::GetOcclusionTestedObjectCount()
{
	return (unsigned int)Umbra::Library::getStatistic( Umbra::LibraryDefs::STAT_DATABASEOBSOCCLUSIONTESTED );
}

#endif
