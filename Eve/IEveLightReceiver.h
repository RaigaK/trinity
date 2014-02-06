////////////////////////////////////////////////////////////
//
//    Created:   November 2012
//    Copyright: CCP 2012
//
#pragma once
#ifndef IEveLightReceiver_h
#define IEveLightReceiver_h



BLUE_DECLARE( EveSpaceSceneLightMgr );

BLUE_INTERFACE( IEveLightReceiver ) : public IRoot
{
	// call to set light data
	virtual void SetLights( EveSpaceSceneLightMgrPtr lightMgr ) = 0;
};

#endif
