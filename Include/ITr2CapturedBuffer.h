////////////////////////////////////////////////////////////
//
//    Created:   September 2013
//    Copyright: CCP 2013
//

#pragma once
#ifndef ITr2CapturedBuffer_H
#define ITr2CapturedBuffer_H

// --------------------------------------------------------------------------------------
// Description:
//   An interface to captured back buffer (or render target) data.
// See also:
//   ITriDevice
// --------------------------------------------------------------------------------------
BLUE_INTERFACE( ITr2CapturedBuffer ): public IRoot
{
	virtual const void* GetData() const = 0;
	virtual void LockData() = 0;
	virtual void UnlockData() = 0;
};

#endif