#include "StdAfx.h"
#include "Tr2DynamicMesh.h"
#include "Resources/TriGeometryRes.h"

using namespace Tr2RenderContextEnum;

// ------------------------------------------------------------------------------------------------------
Tr2DynamicMesh::Tr2DynamicMesh( IRoot* lockobj ) : 
	Tr2Mesh( lockobj ),
	m_dynamicBufferSizeInBytes( 0 )
{
	// set an extension string to the resource creation, so base class knows what resource to create
	m_geomResourceEx = "dyn";
}

// ------------------------------------------------------------------------------------------------------
Tr2DynamicMesh::~Tr2DynamicMesh()
{
}

// ------------------------------------------------------------------------------------------------------
void Tr2DynamicMesh::RebuildCachedData( BlueAsyncRes* p )
{
	CCP_ASSERT( p == m_geometryResource );

	// now that the geometry resource is loaded we know the size of the vertex buffer we need for dynamic data
	TriGeometryResMeshData* resMeshData = m_geometryResource->GetMeshData( m_meshIndex );
	if( resMeshData )
	{
		// fill it with size! the actual buffer gets created in ::PrepareResources()
		m_dynamicBufferSizeInBytes = resMeshData->m_vertexCount * resMeshData->m_bytesPerVertex;
		// create buffer
		USE_MAIN_THREAD_RENDER_CONTEXT();
		CR( m_dynamicVertexBuffer.Create(
			resMeshData->m_bytesPerVertex,
			resMeshData->m_vertexCount,
			Tr2GpuUsage::VERTEX_BUFFER,
			Tr2CpuUsage::WRITE_OFTEN,
			nullptr, 
			renderContext ) );
	}

	// up the chain
	Tr2Mesh::RebuildCachedData( p );
}

// ------------------------------------------------------------------------------------------------------
void Tr2DynamicMesh::ReleaseCachedData( BlueAsyncRes* p )
{
	// release the dynamic vertexbuffer cause the underlying geometry might has changed
	m_dynamicVertexBuffer = Tr2BufferAL();
	m_dynamicBufferSizeInBytes = 0;

	// up the chain
	Tr2Mesh::ReleaseCachedData( p );
}

// ------------------------------------------------------------------------------------------------------
bool Tr2DynamicMesh::OnPrepareResources()
{
	// create buffer of we know size!
	if( m_dynamicBufferSizeInBytes == 0 )
	{
		return false;
	}
	USE_MAIN_THREAD_RENDER_CONTEXT();
	CR( m_dynamicVertexBuffer.Create(	
		1, 
		m_dynamicBufferSizeInBytes, 
		Tr2GpuUsage::VERTEX_BUFFER,
		Tr2CpuUsage::WRITE_OFTEN,
		nullptr, 
		renderContext ) );

	return true;
}

// ------------------------------------------------------------------------------------------------------
void Tr2DynamicMesh::ReleaseResources( TriStorage s )
{
	// just release the dx buffer
	m_dynamicVertexBuffer = Tr2BufferAL();
}

// ------------------------------------------------------------------------------------------------------
unsigned int Tr2DynamicMesh::GetJointMapping( unsigned int boneIx ) const
{
	if( m_jointMappingAnimRig.size() > boneIx )
	{
		return m_jointMappingAnimRig[boneIx];
	}
	return 0;
}

