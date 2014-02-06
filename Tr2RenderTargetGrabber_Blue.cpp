////////////////////////////////////////////////////////////
//
//    Created:   September 2013
//    Copyright: CCP 2013
//

#include "StdAfx.h"
#include "Tr2RenderTargetGrabber.h"

BLUE_DEFINE_NONEXPOSED( Tr2RenderTargetGrabber );

const Be::ClassInfo* Tr2RenderTargetGrabber::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2RenderTargetGrabber, "" )
		MAP_INTERFACE( Tr2RenderTargetGrabber )
    EXPOSURE_END()
}
