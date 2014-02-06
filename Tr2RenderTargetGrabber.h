////////////////////////////////////////////////////////////
//
//    Created:   September 2013
//    Copyright: CCP 2013
//

#pragma once
#ifndef Tr2RenderTargetGrabber_H
#define Tr2RenderTargetGrabber_H

#include "Include/ITr2RenderTargetGrabber.h"
#include "Tr2DeviceResource.h"

BLUE_DECLARE( Tr2CapturedBuffer );
BLUE_DECLARE_INTERFACE( ITriDevice );

// --------------------------------------------------------------------------------------
// Description:
//   An object that manages async render target grabbing (into CPU-accessible memory).
// --------------------------------------------------------------------------------------
BLUE_CLASS( Tr2RenderTargetGrabber ): 
	public ITr2RenderTargetGrabber,
	public Tr2DeviceResource
{
public:
	Tr2RenderTargetGrabber( IRoot* lockobj = nullptr );
	~Tr2RenderTargetGrabber();

	EXPOSE_TO_BLUE();

	bool Create( Tr2RenderTargetAL& renderTarget, ITriDevice* device );
	void Destroy();

	virtual bool IsValid() const;
	virtual bool GetData( ITr2CapturedBuffer** buffer );
	virtual bool GrabData();

	virtual void ReleaseResources( TriStorage s );
private:
	virtual bool OnPrepareResources();
private:
	static void OnBeginFrame( ITriDevice* device, void* userData );
	void PrepareLocks();

	// Potentially available locked buffers
	TrackableStdVector<Tr2CapturedBufferPtr> m_availableBuffers;

	Tr2RenderTargetAL* m_originalRenderTarget;
	Tr2RenderTargetAL m_textureableRenderTarget;

	// Ring buffer with back buffer copies, locked render targets and associated fences
	static const uint32_t GRABBED_BACK_BUFFER_COUNT = 2;
	Tr2CapturedBufferPtr m_lockedRenderTargets[GRABBED_BACK_BUFFER_COUNT];
	Tr2RenderTargetAL m_readableRenderTargets[GRABBED_BACK_BUFFER_COUNT];
	Tr2FenceAL m_fences[GRABBED_BACK_BUFFER_COUNT];

	// Index of a render target that was last updated from back buffer
	uint32_t m_lockIndex;
	// Index of render target to grab next (with GrabData)
	uint64_t m_grabIndex;
	// Index of render target to fetch next (with GetData)
	uint64_t m_getIndex;
};

TYPEDEF_BLUECLASS( Tr2RenderTargetGrabber );
#endif