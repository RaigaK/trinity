
////////////////////////////////////////////////////////////
//
//    Created:   June 2010
//    Copyright: CCP 2010
//
#pragma once
#ifndef tr2shaderpermutetag_h
#define tr2shaderpermutetag_h

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ShaderPermuteTag is a class that creates a bit mask from the high level shader 
//   description .RED file.  The permute tag binds a situation to a #define in the HLSL. 
// SeeAlso:
//   Tr2HighLevelShader, Situation
// --------------------------------------------------------------------------------------
BLUE_CLASS( Tr2ShaderPermuteTag ) : public IInitialize
{
public:
	Tr2ShaderPermuteTag( IRoot * lockobj = NULL );
	~Tr2ShaderPermuteTag();

	EXPOSE_TO_BLUE();
	
	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	virtual bool Initialize();

	unsigned int GetTagBits() const;
	unsigned int GetExclusionMask() const;

	void SetExclusionMask( unsigned int bitmask );

	const char* GetPermuteDefine() const;
	unsigned int GetPermuteNameHash() const;

	enum PrecompileHint {
		PRECOMP_NEVER = -1,
		PRECOMP_SOMETIMES = 0,
		PRECOMP_ALWAYS = 1
	};

	PrecompileHint GetPrecompileHint() const;

private:
	std::string m_tagName;
	std::string m_permuteDefine;
	std::string m_predicate;
	std::string m_unused;
	unsigned int m_tagHash;
	unsigned int m_tagBits;
	int m_precompileHint;
};
TYPEDEF_BLUECLASS(Tr2ShaderPermuteTag);

#endif
