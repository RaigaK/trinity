////////////////////////////////////////////////////////////
//
//    Created:   September 2013
//    Copyright: CCP 2013
//

#include "StdAfx.h"
#include "Tr2CapturedBuffer.h"

Tr2CapturedBuffer::Tr2CapturedBuffer( IRoot* lockobj )
	:m_locked( 0 ),
	m_data( nullptr )
{
}

// --------------------------------------------------------------------------------------
// Description:
//   Returns data contained in the buffer.
// Return Value:
//   Data contained in the buffer
// --------------------------------------------------------------------------------------
const void* Tr2CapturedBuffer::GetData() const
{
	return m_data;
}

// --------------------------------------------------------------------------------------
// Description:
//   Locks the data: locked data is not supposed to be modified.
// --------------------------------------------------------------------------------------
void Tr2CapturedBuffer::LockData()
{
	CCP_STATS_ZONE( __FUNCTION__ );

	if( !m_locked )
	{
		USE_MAIN_THREAD_RENDER_CONTEXT();
		uint32_t pitch;
		m_rt.Lock( m_data, pitch, renderContext );
	}
	++m_locked;
}

// --------------------------------------------------------------------------------------
// Description:
//   Unlocks the data: the number of unlocks should correspond to the number of locks for
//   data to become writable.
// --------------------------------------------------------------------------------------
void Tr2CapturedBuffer::UnlockData()
{
	CCP_STATS_ZONE( __FUNCTION__ );

	--m_locked;
	if( !m_locked )
	{
		USE_MAIN_THREAD_RENDER_CONTEXT();
		m_rt.Unlock( renderContext );
	}
}

// --------------------------------------------------------------------------------------
// Description:
//   Returns locked render target encapsulated in the object.  
// Return Value:
//   Locked render target
// --------------------------------------------------------------------------------------
Tr2LockedRenderTargetAL& Tr2CapturedBuffer::GetLockedRenderTarget()
{
	return m_rt;
}

// --------------------------------------------------------------------------------------
// Description:
//   Queries if the buffer is "locked".  
// Return Value:
//   true If the buffer is locked
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2CapturedBuffer::IsLocked() const
{
	return m_locked != 0;
}
