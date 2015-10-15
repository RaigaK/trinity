////////////////////////////////////////////////////////////
//
//    Created:   June 2010
//    Copyright: CCP 2010
//

#ifndef Tr2ShaderManager_H
#define Tr2ShaderManager_H

BLUE_DECLARE( Tr2ShaderManager );
BLUE_DECLARE( Tr2HighLevelShader );
BLUE_DECLARE_VECTOR( Tr2HighLevelShader );

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ShaderManager is a class that provides high level shader name to pointer binding.
// SeeAlso:
//   Tr2ShaderMaterial, Tr2HighLevelShader
// --------------------------------------------------------------------------------------
BLUE_CLASS( Tr2ShaderManager ) : public IRoot
{
public:
	
	Tr2ShaderManager( IRoot* lockobj = NULL );	

	EXPOSE_TO_BLUE();

	Tr2HighLevelShader* FindShaderByName( const char* name );

private:
	PTr2HighLevelShaderVector m_shaderLibrary;
};

TYPEDEF_BLUECLASS( Tr2ShaderManager );

Tr2ShaderManager* GetShaderManager();

#endif
