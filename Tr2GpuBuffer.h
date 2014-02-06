////////////////////////////////////////////////////////////
//
//    Created:   February 2013
//    Copyright: CCP 2013
//

#pragma once
#ifndef Tr2GpuBuffer_H
#define Tr2GpuBuffer_H

#include "include/ITr2GpuBuffer.h"

// --------------------------------------------------------------------------------------
// Description:
//   A Blue-exposed wrapper around Tr2GpuBufferAL class for typed buffers, i.e. buffers
//   that have a valid pixel format. The creation parameters for the class are persisted,
//   but the contents of the buffer is not.
// See Also:
//   Tr2GpuBufferAL
// --------------------------------------------------------------------------------------
BLUE_CLASS( Tr2GpuBuffer ): 
	public ITr2GpuBuffer,
	public INotify,
	public IInitialize
{
public:
	EXPOSE_TO_BLUE();

	using IInitialize::Lock;
	using IInitialize::Unlock;

    Tr2GpuBuffer( IRoot* = 0 );
	~Tr2GpuBuffer();

	bool Initialize();

	bool OnModified( Be::Var* value );

	Tr2GpuBufferAL* GetGpuBuffer( unsigned index );

	ALResult Create( uint32_t count, Tr2RenderContextEnum::PixelFormat format, bool cpuWritable, bool drawIndirect );
	bool IsValid() const;
private:
	ALResult __init__( Be::Optional<uint32_t> count, Be::Optional<Tr2RenderContextEnum::PixelFormat> format, bool cpuWritable, bool drawIndirect );

	ALResult CreateBuffer();

	// AL buffer
	Tr2GpuBufferAL	m_buffer;

	// Number of elements in the buffer
	uint32_t m_count;
	// Type of elements
	Tr2RenderContextEnum::PixelFormat m_format;
	// Can the buffer be locked with write-only access
	bool m_cpuWritable;
	// Is the buffer used for indirect draw calls
	bool m_drawIndirect;
};

TYPEDEF_BLUECLASS( Tr2GpuBuffer );

#endif