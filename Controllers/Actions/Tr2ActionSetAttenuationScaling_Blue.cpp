////////////////////////////////////////////////////////////
//
//    Created:   May 2020
//    Copyright: CCP 2020
//

#include "StdAfx.h"
#include "Tr2ActionSetAttenuationScaling.h"


BLUE_DEFINE( Tr2ActionSetAttenuationScaling );

const Be::ClassInfo* Tr2ActionSetAttenuationScaling::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2ActionSetAttenuationScaling, "" )
		MAP_INTERFACE( Tr2ActionSetAttenuationScaling )
		MAP_INTERFACE( ITr2ControllerAction )

		MAP_ATTRIBUTE( "emitter",
                        m_emitterName,
                        "Emitter name",
                        Be::READWRITE | Be::PERSIST
                     )
		MAP_ATTRIBUTE( "controllerVariable", 
					   m_controllerVariableName, 
					   "Optionally use the value of a controller variable as a scaling factor. "
					   "This is affected by the scale by percent.",
					   Be::READWRITE | Be::PERSIST
				     )
		MAP_ATTRIBUTE( "scaleByPercent",
                       m_scalingPercent,
                       "The amount you want to scale attenuation by in percent. Applies to all sounds on an emitter.\n"
                       "Example values:\n"
                       "50 = halfing the attenuation range\n"
                       "100 = keeping the attenuation range as defined in Wwise\n"
                       "200 = Doubling attenuation range \n"
					   "Debug notes: \n"
			           "* You cannot see this visually represented without stopping the sound and starting it again.\n"
					   "* All emitters that are scaled by this will change their color to red",
                       Be::READWRITE | Be::PERSIST 
                     )
		// MAP_PROPERTY_READONLY is called regularly by Jessica so this will be updated at all times in Jessica.
		MAP_PROPERTY_READONLY("scalingFactor",
                              GetScalingFactor,
                              "The final scaling factor that will be sent to Wwise."
							  )
	EXPOSURE_END()
}
