////////////////////////////////////////////////////////////
//
//    Created:   June 2010
//    Copyright: CCP 2010
//

#include "StdAfx.h"

#include "Tr2ShaderManager.h"

#include "Tr2HighLevelShader.h"

Tr2ShaderManager::Tr2ShaderManager( IRoot* lockobj )
	: PARENTLOCK( m_shaderLibrary )
{
}

Tr2HighLevelShader* Tr2ShaderManager::FindShaderByName(const char* shaderName)
{
	Tr2HighLevelShaderVector::iterator walker( m_shaderLibrary.begin() ), 
		endOfList( m_shaderLibrary.end() );

	unsigned int hashedTestName = CcpHashFNV1( shaderName, strlen( shaderName ) );
	while( walker != endOfList )
	{
		Tr2HighLevelShader* shader = *walker;
		if( shader->GetNameHash() == hashedTestName )
		{
			return shader;
		}

		++walker;
	}

	return NULL;
}

Tr2ShaderManager* GetShaderManager()
{
	static CTr2ShaderManager shaderManager;
	return &shaderManager;
}
