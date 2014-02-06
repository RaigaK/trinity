////////////////////////////////////////////////////////////
//
//    Created:   September 2013
//    Copyright: CCP 2013
//

#pragma once
#ifndef Tr2CapturedBuffer_H
#define Tr2CapturedBuffer_H

#include "Include/ITr2CapturedBuffer.h"

// --------------------------------------------------------------------------------------
// Description:
//   An object that manages a block of data. The data can be "locked": in this state
//   the data should not be modified.
// --------------------------------------------------------------------------------------
BLUE_CLASS( Tr2CapturedBuffer ): public ITr2CapturedBuffer
{
public:
	Tr2CapturedBuffer( IRoot* lockobj = nullptr );

	EXPOSE_TO_BLUE();

	const void* GetData() const;
	void LockData();
	void UnlockData();

	Tr2LockedRenderTargetAL& GetLockedRenderTarget();
	bool IsLocked() const;
private:
	// A flag indicating that the data is locked
	int32_t m_locked;
	Tr2LockedRenderTargetAL m_rt;
	void* m_data;
};

TYPEDEF_BLUECLASS( Tr2CapturedBuffer );
BLUE_DECLARE_VECTOR( Tr2CapturedBuffer );

#endif