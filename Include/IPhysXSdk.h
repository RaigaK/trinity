#pragma once
#ifndef IPhysxSdk_h
#define IPhysxSdk_h

namespace PLATFORM_ANALYZER
{
	class PlatformAnalyzer;
};

BLUE_INTERFACE( IPhysXSdk ) : public IRoot
{
	virtual class NxPhysicsSDK* GetSdk() = 0;
	virtual PLATFORM_ANALYZER::PlatformAnalyzer * GetPlatformAnalyzer(void) = 0;
};


BLUE_INTERFACE( IPhysXScene ) : public IRoot
{
	virtual class NxScene* GetScene() = 0;
	virtual bool CreatePlane( Vector3 position, Vector3 normal, float distance ) = 0;

};

#endif
