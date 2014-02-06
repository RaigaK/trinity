////////////////////////////////////////////////////////////
//
//    Created:   August 2012
//    Copyright: CCP 2012
//

#include "StdAfx.h"
#include "Tr2ConstGeometry.h"

namespace
{
	// --------------------------------------------------------------------------------------
	// Description:
	//   Managed immutable vertex buffer created from constant data. The class will re-create
	//   and re-fill vertex buffer when needed. 
	// --------------------------------------------------------------------------------------
	struct ConstVB: public Tr2DeviceResource
	{
		ConstVB()
			:m_data( nullptr ),
			m_size( 0 )
		{
		}

		void ReleaseResources( TriStorage s )
		{
			if( m_VB.GetMemoryClass() & s )
			{
				m_VB.Destroy();
			}
		}
		bool OnPrepareResources()
		{
			if( !m_VB.IsValid() )
			{
				USE_MAIN_THREAD_RENDER_CONTEXT();
				m_VB.Create( m_size, Tr2RenderContextEnum::USAGE_IMMUTABLE, m_data, renderContext );
			}
			return true;
		}
		
		const void* m_data;
		unsigned m_size;
		Tr2VertexBufferAL m_VB;
	};

	// --------------------------------------------------------------------------------------
	// Description:
	//   Managed immutable index buffer created from constant data. The class will re-create
	//   and re-fill index buffer when needed. 
	// --------------------------------------------------------------------------------------
	struct ConstIB: public Tr2DeviceResource
	{
		ConstIB()
			:m_data( nullptr ),
			m_count( 0 )
		{
		}

		void ReleaseResources( TriStorage s )
		{
			if( m_IB.GetMemoryClass() & s )
			{
				m_IB.Destroy();
			}
		}
		bool OnPrepareResources()
		{
			if( !m_IB.IsValid() )
			{
				USE_MAIN_THREAD_RENDER_CONTEXT();
				m_IB.Create( m_count, Tr2RenderContextEnum::USAGE_IMMUTABLE, m_bitCount, m_data, renderContext );
			}
			return true;
		}

		const void* m_data;
		unsigned m_count;
		Tr2RenderContextEnum::IndexBufferBitcount m_bitCount;
		Tr2IndexBufferAL m_IB;
	};

	// Constant vertex buffers indexed by their data
	std::map<const void*, ConstVB*> s_constVBs;
	// Constant index buffers indexed by their data
	std::map<const void*, ConstIB*> s_constIBs;
}

// --------------------------------------------------------------------------------------
// Description:
//   Gets/creates an immutable vertex buffer containing specified data. The function will
//   return the same buffer when called with the same vertices argument. The vertices
//   argument is supposed to be static and remain valid until the end of program.  
// Arguments:
//   vertices - Contents of the vertex buffer
//   size - Size of the vertex buffer
// Return Value:
//   Vertex buffer containing specified data
// --------------------------------------------------------------------------------------
Tr2VertexBufferAL* Tr2ConstGeometry::GetVB( const void* vertices, unsigned size )
{
	auto& found = s_constVBs[vertices];
	if( !found )
	{
		found = new ConstVB();
		found->m_data = vertices;
		found->m_size = size;
		found->PrepareResources();
	}
	return &found->m_VB;
}

// --------------------------------------------------------------------------------------
// Description:
//   Gets/creates an immutable index buffer containing specified data. The function will
//   return the same buffer when called with the same indices argument. The indices
//   argument is supposed to be static and remain valid until the end of program.  
// Arguments:
//   vertices - Contents of the index buffer
//   size - Size of the index buffer
// Return Value:
//   Index buffer containing specified data
// --------------------------------------------------------------------------------------
Tr2IndexBufferAL* Tr2ConstGeometry::GetIB( Tr2RenderContextEnum::IndexBufferBitcount bitCount, const void* indices, unsigned indexCount )
{
	auto& found = s_constIBs[indices];
	if( !found )
	{
		found = new ConstIB();
		found->m_data = indices;
		found->m_count = indexCount;
		found->m_bitCount = bitCount;
		found->PrepareResources();
	}
	return &found->m_IB;
}
