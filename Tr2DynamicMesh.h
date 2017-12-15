#ifndef TR2DYNAMICMESH_H
#define TR2DYNAMICMESH_H

#include "Tr2Mesh.h"
#include "Tr2DeviceResource.h"

// ------------------------------------------------------------------------------------------------------
BLUE_DECLARE( Tr2DynamicMesh );
class Tr2DynamicMesh:
	public Tr2Mesh,
	public Tr2DeviceResource
{
public:
	EXPOSE_TO_BLUE();

	Tr2DynamicMesh( IRoot* lockobj = NULL );
	~Tr2DynamicMesh();

	using Tr2Mesh::Lock;
	using Tr2Mesh::Unlock;

	/////////////////////////////////////////////////////////////////////////////////////
	// ITriDeviceResource
	void ReleaseResources( TriStorage s );
private:
	bool OnPrepareResources();
public:	
#if TRINITYDEV
	void GetDescription( std::string& desc ) { desc = "Tr2CpuSkinnedModel"; }
#endif

	/////////////////////////////////////////////////////////////////////////////////////
	// IAsyncLoadedResNotifyTarget
	virtual void ReleaseCachedData( BlueAsyncRes* p );
	virtual void RebuildCachedData( BlueAsyncRes* p );


	// access to the dynamic vertex buffer
	Tr2BufferAL& GetDynamicVertexBuffer()			{ return m_dynamicVertexBuffer; }
	unsigned int GetDynamicVertexBufferSizeInBytes() const { return m_dynamicBufferSizeInBytes; }

	// access to the joint mapping, so the cpu skinner can have it
	unsigned int GetJointMapping( unsigned int boneIx ) const;

private:
	// buffer for dynamic vertex data
	Tr2BufferAL m_dynamicVertexBuffer;
	unsigned int m_dynamicBufferSizeInBytes;
};
TYPEDEF_BLUECLASS( Tr2DynamicMesh );
BLUE_DECLARE_VECTOR( Tr2DynamicMesh );

#endif
