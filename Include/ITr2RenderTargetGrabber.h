////////////////////////////////////////////////////////////
//
//    Created:   September 2013
//    Copyright: CCP 2013
//

#pragma once

#ifndef ITr2RenderTargetGrabber_H
#define ITr2RenderTargetGrabber_H

BLUE_DECLARE_INTERFACE( ITr2CapturedBuffer );

// --------------------------------------------------------------------------------------
// Description:
//   An interface to Trinity object that manages sync render target grabbing.
// --------------------------------------------------------------------------------------
BLUE_INTERFACE( ITr2RenderTargetGrabber ): public IRoot
{
	virtual bool IsValid() const = 0;
	virtual bool GetData( ITr2CapturedBuffer** buffer ) = 0;
	virtual bool GrabData() = 0;
};

#endif