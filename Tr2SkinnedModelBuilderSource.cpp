#include "StdAfx.h"
#include "Tr2SkinnedModelBuilderSource.h"

#define NO_OVERRIDE	-1

// ------------------------------------------------------------------------------------------------------
Tr2SkinnedModelBuilderSource::Tr2SkinnedModelBuilderSource( IRoot* lockobj ) :
	PARENTLOCK( m_overrideMaterial0 ),
	PARENTLOCK( m_overrideMaterial1 ),	
	m_enableCutMask( false )
{
}

// ------------------------------------------------------------------------------------------------------
bool Tr2SkinnedModelBuilderSource::isMeshExcluded( const char* meshName ) const
{
	for( std::vector<std::string>::const_iterator it = m_excludeMeshes.begin(); it != m_excludeMeshes.end(); ++it )
	{
		if( it->compare( meshName ) == 0 )
		{
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------------------------------------------
Tr2MeshAreaPtr Tr2SkinnedModelBuilderSource::getMeshOverrideMaterial( 
					const std::vector<std::string> & overrideMaterialMeshes, 
					const PTr2MeshAreaVector & overrideMaterial,
					const char* const meshName, 
					const unsigned digit ) const
{
	// always check if both arrays have the same size!
	if( overrideMaterialMeshes.size() != overrideMaterial.size() )
	{
		CCP_LOGERR( "Tr2SkinnedModelBuilder::getMeshOverrideMaterial: array of override material%d and array of mesh names differ in size! Not doing any override on '%s'\n", digit, meshName );
		return NULL;
	}

	// find material with name
	PTr2MeshAreaVector::const_iterator materialIt = overrideMaterial.begin();
	for( std::vector<std::string>::const_iterator meshIt = overrideMaterialMeshes.begin(); meshIt != overrideMaterialMeshes.end(); ++meshIt )
	{
		// if the meshname is of length 0 (ie empty), always return material right away: this way override everything
		if( meshIt->empty() || ( meshIt->compare( meshName ) == 0 ) )
		{
			return *materialIt;
		}
		++materialIt;
	}
	return NULL;
}

Tr2MeshAreaPtr Tr2SkinnedModelBuilderSource::getMeshOverrideMaterial0( const char* meshName ) const
{
	return getMeshOverrideMaterial( m_overrideMaterial0Meshes, m_overrideMaterial0, meshName, 0 );
	
}

// ------------------------------------------------------------------------------------------------------
Tr2MeshAreaPtr Tr2SkinnedModelBuilderSource::getMeshOverrideMaterial1( const char* meshName ) const
{
	return getMeshOverrideMaterial( m_overrideMaterial1Meshes, m_overrideMaterial1, meshName, 0 );	
}
