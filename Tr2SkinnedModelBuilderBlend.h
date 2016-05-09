#pragma once
#ifndef Tr2SkinnedModelBuilderBlend_h
#define Tr2SkinnedModelBuilderBlend_h

/////////////////////////////////////////////////////////////////////////////////////
// blandshape data
/////////////////////////////////////////////////////////////////////////////////////
BLUE_DECLARE( Tr2SkinnedModelBuilderBlend );
BLUE_DECLARE_VECTOR( Tr2SkinnedModelBuilderBlend );
class Tr2SkinnedModelBuilderBlend :
     public IRoot
{
public:
    EXPOSE_TO_BLUE();

	Tr2SkinnedModelBuilderBlend( IRoot* lockobj = NULL ) 
		:m_power( 0 )
	{
	}
	~Tr2SkinnedModelBuilderBlend() {}

	// blendshape name
	std::string m_name;
	// power
	float m_power;
};
TYPEDEF_BLUECLASS( Tr2SkinnedModelBuilderBlend );

#endif //Tr2SkinnedModelBuilderBlend_h
