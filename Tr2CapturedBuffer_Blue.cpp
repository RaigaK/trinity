////////////////////////////////////////////////////////////
//
//    Created:   September 2013
//    Copyright: CCP 2013
//

#include "StdAfx.h"
#include "Tr2CapturedBuffer.h"

BLUE_DEFINE_NONEXPOSED( Tr2CapturedBuffer );

const Be::ClassInfo* Tr2CapturedBuffer::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2CapturedBuffer, "" )
		MAP_INTERFACE( Tr2CapturedBuffer )
    EXPOSURE_END()
}
