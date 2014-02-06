////////////////////////////////////////////////////////////
//
//    Created:   September 2013
//    Copyright: CCP 2013
//

#include "StdAfx.h"
#include "Tr2RenderTargetGrabber.h"
#include "Tr2CapturedBuffer.h"
#include "TriDevice.h"
#include "Tr2Renderer.h"

using namespace Tr2RenderContextEnum;

Tr2RenderTargetGrabber::Tr2RenderTargetGrabber( IRoot* lockobj )
	:m_originalRenderTarget( nullptr ),
	m_availableBuffers( "Tr2RenderTargetGrabber::m_capturedBuffers" ),
	m_lockIndex( GRABBED_BACK_BUFFER_COUNT ),
	m_grabIndex( 0 ),
	m_getIndex( 0 )
{
}

Tr2RenderTargetGrabber::~Tr2RenderTargetGrabber()
{
	Destroy();
}

// --------------------------------------------------------------------------------------
// Description:
//   Creates the grabber for the given render target.
// Arguments:
//   renderTarget - render target to grab
// Return Value:
//   true On success; false otherwise
// --------------------------------------------------------------------------------------
bool Tr2RenderTargetGrabber::Create( Tr2RenderTargetAL& renderTarget, ITriDevice* device )
{
	Destroy();

	USE_MAIN_THREAD_RENDER_CONTEXT();
	for( auto it = std::begin( m_fences ); it != std::end( m_fences ); ++it )
	{
		CR_RETURN_VAL( it->Create( renderContext ), false );
	}
	for( auto it = std::begin( m_readableRenderTargets ); it != std::end( m_readableRenderTargets ); ++it )
	{
		CR_RETURN_VAL( it->Create( renderTarget.GetWidth(), renderTarget.GetHeight(), 1, PIXEL_FORMAT_B8G8R8A8_UNORM, 1, 0, renderContext ), false );
	}
	m_originalRenderTarget = &renderTarget;
	if( renderTarget.GetFormat() != PIXEL_FORMAT_B8G8R8A8_UNORM )
	{
		CR_RETURN_VAL( m_textureableRenderTarget.Create( renderTarget.GetWidth(), renderTarget.GetHeight(), 1, renderTarget.GetFormat(), 1, 0, renderContext ), false );
	}
	device->RegisterDeviceCallback( DEVICE_CALLBACK_FRAME_BEGIN, OnBeginFrame, this );
	return true;
}

void Tr2RenderTargetGrabber::OnBeginFrame( ITriDevice*, void* userData )
{
	reinterpret_cast<Tr2RenderTargetGrabber*>( userData )->PrepareLocks();
}

// --------------------------------------------------------------------------------------
// Description:
//   Destroys all resources hold by the grabber.
// --------------------------------------------------------------------------------------
void Tr2RenderTargetGrabber::Destroy()
{
	m_originalRenderTarget = nullptr;
	m_textureableRenderTarget.Destroy();
	m_availableBuffers.clear();
	m_grabIndex = 0;
	m_getIndex = 0;
	m_lockIndex = GRABBED_BACK_BUFFER_COUNT;
	for( uint32_t i = 0; i < GRABBED_BACK_BUFFER_COUNT; ++i )
	{
		m_lockedRenderTargets[i].Unlock();
	}
	for( auto it = std::begin( m_fences ); it != std::end( m_fences ); ++it )
	{
		it->Destroy();
	}
	for( auto it = std::begin( m_readableRenderTargets ); it != std::end( m_readableRenderTargets ); ++it )
	{
		it->Destroy();
	}
	
	gTriDev->UnregisterDeviceCallback( DEVICE_CALLBACK_FRAME_BEGIN, OnBeginFrame, this );
}

// --------------------------------------------------------------------------------------
// Description:
//   Check if the grabber is valid.
// Return Value:
//   true If grabber is valid; false otherwise
// --------------------------------------------------------------------------------------
bool Tr2RenderTargetGrabber::IsValid() const
{
	return m_originalRenderTarget != nullptr;
}

// --------------------------------------------------------------------------------------
// Description:
//   Get grabbed render target data. The grabber will return render target with latency
//   to avoid stalling, so this method must be called continiously every frame until it 
//   returns the buffer.
// Arguments:
//   buffer - (out) pointer to the buffer that will contain render target data; if the
//            data is not yet ready, "buffer" is set to NULL
// Return Value:
//   true On success (check for *buffer == NULL though); false on error
// --------------------------------------------------------------------------------------
bool Tr2RenderTargetGrabber::GetData( ITr2CapturedBuffer** buffer )
{
	CCP_STATS_ZONE( __FUNCTION__ );

	*buffer = nullptr;
	if( !IsValid() )
	{
		return false;
	}
	if( m_getIndex >= m_grabIndex )
	{
		return true;
	}

	uint32_t nextIndex = m_getIndex % GRABBED_BACK_BUFFER_COUNT;
	if( !m_lockedRenderTargets[nextIndex] )
	{
		return true;
	}

	USE_MAIN_THREAD_RENDER_CONTEXT();
	if( !renderContext.IsValid() )
	{
		return false;
	}
	bool isReached;
	CR_RETURN_VAL( m_fences[nextIndex].IsReached( isReached, renderContext ), false );
	if( !isReached )
	{
		return true;
	}
	m_availableBuffers.push_back( m_lockedRenderTargets[nextIndex] );
	*buffer = m_lockedRenderTargets[nextIndex].Detach();

	++m_getIndex;
	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Grab data render target from render target. Grabbed data can be accessed with 
//   GetData method. Grabbed render target will not be available at least until next 
//   frame.
// Return Value:
//   true On success; false on error
// --------------------------------------------------------------------------------------
bool Tr2RenderTargetGrabber::GrabData()
{
	CCP_STATS_ZONE( __FUNCTION__ );

	USE_MAIN_THREAD_RENDER_CONTEXT();
	if( !IsValid() || !renderContext.IsValid() )
	{
		return false;
	}

	uint32_t grabbedIndex = m_grabIndex % GRABBED_BACK_BUFFER_COUNT;

	if( m_readableRenderTargets[grabbedIndex].GetFormat() == m_originalRenderTarget->GetFormat() )
	{
		CR_RETURN_VAL( m_readableRenderTargets[grabbedIndex].CopySubresourceRegion( 0, 0, *m_originalRenderTarget, nullptr, renderContext ), false );
	}
	else
	{
		CR_RETURN_VAL( m_textureableRenderTarget.CopySubresourceRegion( 0, 0, *m_originalRenderTarget, nullptr, renderContext ), false );
		Tr2Renderer::PushDepthStencilBuffer( nullDS, renderContext );
		Tr2Renderer::PushRenderTarget( m_readableRenderTargets[grabbedIndex], renderContext );
		Tr2Renderer::DrawTexture( m_textureableRenderTarget.GetTexture() );
		Tr2Renderer::PopRenderTarget( renderContext );
		Tr2Renderer::PopDepthStencilBuffer( renderContext );
	}
	m_lockIndex = grabbedIndex;
	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Transfers recently grab back buffer data from an off-screen render target to system
//   memory asyncronously. 
// --------------------------------------------------------------------------------------
void Tr2RenderTargetGrabber::PrepareLocks()
{
	if( m_lockIndex < GRABBED_BACK_BUFFER_COUNT )
	{
		CCP_STATS_ZONE( __FUNCTION__ );

		USE_MAIN_THREAD_RENDER_CONTEXT();

		for( auto it = std::begin( m_availableBuffers ); it != std::end( m_availableBuffers ); ++it )
		{
			if( !( *it )->IsLocked() )
			{
				m_lockedRenderTargets[m_lockIndex] = *it;
				m_availableBuffers.erase( it );
				break;
			}
		}
		if( !m_lockedRenderTargets[m_lockIndex] )
		{
			m_lockedRenderTargets[m_lockIndex].CreateInstance();
		}

		CR_RETURN( m_readableRenderTargets[m_lockIndex].GetLockedRenderTarget( 0, nullptr, m_lockedRenderTargets[m_lockIndex]->GetLockedRenderTarget(), renderContext ) );
		CR_RETURN( m_fences[m_lockIndex].PutFence( renderContext ) );
		m_lockIndex = GRABBED_BACK_BUFFER_COUNT;
		++m_grabIndex;
	}
}

// --------------------------------------------------------------------------------------
// Description:
//   Implements Tr2DeviceResource. Destroys all grabber resources when device is lost.
// --------------------------------------------------------------------------------------
void Tr2RenderTargetGrabber::ReleaseResources( TriStorage )
{
	Destroy();
}

// --------------------------------------------------------------------------------------
// Description:
//   Implements Tr2DeviceResource. Does nothing: grabber cannot recover from lost device
//   on its own.
// Return Value:
//   true always
// --------------------------------------------------------------------------------------
bool Tr2RenderTargetGrabber::OnPrepareResources()
{
	return true;
}