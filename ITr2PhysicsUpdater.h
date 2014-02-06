#pragma once
#ifndef __ITr2PhysicsUpdater_H__
#define __ITr2PhysicsUpdater_H__

#include "include/IPhysXSdk.h"

BLUE_INTERFACE( ITr2PhysicsUpdater ) : public IPhysXScene
{
	virtual void PrePhysics( Be::Time time ) = 0;
	virtual void SimulatePhysics( void ) = 0;
};

#define BE_TIME_ONE_MSEC		(10000L)
#define BE_TIME_ONE_SEC			(1000 * BE_TIME_ONE_MSEC)

#endif // __ITr2PhysicsUpdater_H__