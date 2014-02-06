////////////////////////////////////////////////////////////
//
//    Created:   June 2010
//    Copyright: CCP 2010
//

#pragma once
#ifndef ITr2LightPrePassScene_H
#define ITr2LightPrePassScene_H

#include "blue/include/Blue.h"

// -------------------------------------------------------------
// Description:
//   ITr2LightPrePassScene is an interface for multi-pass rendering
//   of scenes.
// SeeAlso:
//   ITr2Scene
// -------------------------------------------------------------
BLUE_INTERFACE( ITr2LightPrePassScene ) : public IRoot
{
	enum PassType
	{
		RP_BEGIN_RENDER,
		RP_PRE_PASS,
		RP_LIGHT_PASS,
		RP_GATHER_PASS,
		RP_FLARE_PASS,
		RP_END_RENDER,
		RP_COUNT,
	};

	// Renders a given pass
	virtual void RenderPass( PassType pass ) = 0;
};

#endif // ITr2LightPrePassScene_H
