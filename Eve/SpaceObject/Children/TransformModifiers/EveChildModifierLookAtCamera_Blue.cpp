////////////////////////////////////////////////////////////
//
//    Created:   2017
//    Copyright: CCP 2017
//
#include "StdAfx.h"
#include "EveChildModifierLookAtCamera.h"

BLUE_DEFINE( EveChildModifierLookAtCamera );

const Be::ClassInfo* EveChildModifierLookAtCamera::ExposeToBlue()
{
    EXPOSURE_BEGIN( EveChildModifierLookAtCamera, "" )
        MAP_INTERFACE( EveChildModifierLookAtCamera )
		MAP_INTERFACE( IEveChildTransformModifier )

    EXPOSURE_END()
}