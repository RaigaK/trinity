////////////////////////////////////////////////////////////
//
//    Created:   2017
//    Copyright: CCP 2017
//
#pragma once
#ifndef EveChildModifierLookAtCamera_H
#define EveChildModifierLookAtCamera_H

#include "IEveChildTransformModifier.h"

BLUE_CLASS( EveChildModifierLookAtCamera ) :
	public IEveChildTransformModifier
{
public:
	EXPOSE_TO_BLUE();

	EveChildModifierLookAtCamera( IRoot* lockobj = NULL );
	~EveChildModifierLookAtCamera();

	Matrix ApplyTransform( const Matrix& transform ) const;
};

TYPEDEF_BLUECLASS( EveChildModifierLookAtCamera );

#endif