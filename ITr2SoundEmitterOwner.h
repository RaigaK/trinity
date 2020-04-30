////////////////////////////////////////////////////////////
//
//    Created:   October 2018
//    Copyright: CCP 2018
//

#pragma once


BLUE_DECLARE_INTERFACE( ITr2AudEmitter );

BLUE_INTERFACE( ITr2SoundEmitterOwner ): public IRoot
{
	virtual ITr2AudEmitterPtr FindSoundEmitter( const char* name ) = 0;
};
