#pragma once
#if !defined( TriTextureCubeParameter_H)
#define TriTextureCubeParameter_H

#include "TriTexture2DParameter.h"

BLUE_DECLARE( TriTextureCubeParameter );
BLUE_CLASS_ALLOW_DELAYED_DELETE( TriTextureCubeParameter );

class TriTextureCubeParameter:
	public TriTexture2DParameter
{
public:
	EXPOSE_TO_BLUE();

	// This class doesn't need to do anything differently from its base,
	// but we want a separate type for cube maps - hence this empty class
	// definition.
};

TYPEDEF_BLUECLASS(TriTextureCubeParameter);

#endif 
