////////////////////////////////////////////////////////////
//
//    Created:   June 2010
//    Copyright: CCP 2010
//

#include "StdAfx.h"

#include "Tr2ShaderPermuteTag.h"

Tr2ShaderPermuteTag::Tr2ShaderPermuteTag( IRoot * lock ) :
	m_tagName(),
	m_permuteDefine(),
	m_tagHash( 0 ),
	m_tagBits( 0 ),
	m_precompileHint( 0 )
{
}

Tr2ShaderPermuteTag::~Tr2ShaderPermuteTag()
{
}

unsigned int Tr2ShaderPermuteTag::GetTagBits() const
{
	return m_tagBits;
}

unsigned int Tr2ShaderPermuteTag::GetPermuteNameHash() const
{
	return m_tagHash;
}

const char * Tr2ShaderPermuteTag::GetPermuteDefine() const
{
	return m_permuteDefine.c_str();
}


Tr2ShaderPermuteTag::PrecompileHint Tr2ShaderPermuteTag::GetPrecompileHint() const
{
	return (PrecompileHint)m_precompileHint;
}

bool Tr2ShaderPermuteTag::Initialize()
{
	m_tagHash = CcpHashFNV1( m_tagName.c_str(), m_tagName.length() );
	m_precompileHint = std::min( 1, std::max( m_precompileHint, -1 ) );

	return true;
}

