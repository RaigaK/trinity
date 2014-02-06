////////////////////////////////////////////////////////////
//
//    Creator:   David Plunkett
//    Created:   Oct 2011
//    Copyright: CCP 2011
//

#pragma once
#ifndef ITr2BindingSentinelValue_H
#define ITr2BindingSentinelValue_H

// -------------------------------------------------------------
// NOTE:
// Any new Tr2BindingSentinelValue classes added that need to talk 
// to Athena will need to add code in Python (currently 
// ParticleEffectClient.py) to correctly deal with the new class.
// -------------------------------------------------------------

// -------------------------------------------------------------
// Description:
//   ITr2BindingSentinelValue is the parent class for all 
//	 Tr2PyBindingSentinel"Vars". Tr2BindingSentinel"Vars" 
//	 are used to signal python that the content creators 
//   expect the binding it is attached to should be 
//   externally bound by some game system.
// SeeAlso:
//   TriValueBinding
// -------------------------------------------------------------
BLUE_INTERFACE( ITr2BindingSentinelValue ) : public IRoot
{
	EXPOSE_TO_BLUE();

	ITr2BindingSentinelValue( IRoot* lockobj = NULL ) : m_externalBind(true) {};
	~ITr2BindingSentinelValue(){};

	// Because the inheritance from this class is not exposed by Blue to Python
	// The exposure of the existance of this variable to Python allows us to
	// find Python classes derived from this object
	const bool m_externalBind;
};

TYPEDEF_BLUECLASS( ITr2BindingSentinelValue );


#endif