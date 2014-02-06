////////////////////////////////////////////////////////////
//
//    Created:   June 2010
//    Copyright: CCP 2010
//
#pragma once
#ifndef EveOccluder_H
#define EveOccluder_H

#include "ITr2Renderable.h"
#include "TriRenderBatch.h"
#include "../Tr2DeviceResource.h"

// forwards
class TriFrustum;
BLUE_DECLARE( EveTransform );
BLUE_DECLARE_VECTOR( EveTransform );
BLUE_DECLARE( Tr2Effect );

// --------------------------------------------------------------------------------
// Description:
//   EveOccluder is used to do occlusion queries for suns and
//   lensflares. Basically it renders a sprite with and without
//   depth testing and the resulting ratio is the visible amount.
//   An EveOccluder can have multiple sprites, each result is
//   multiplied with the previous one to get a final value.
// SeeAlso:
//   EveLensflare
// --------------------------------------------------------------------------------
class EveOccluder :
	public IRoot,
	public Tr2DeviceResource
{
public:
	EXPOSE_TO_BLUE();

	using IRoot::Lock;
	using IRoot::Unlock;

	EveOccluder(IRoot* lockobj = NULL);
	~EveOccluder();

    /////////////////////////////////////////////////////////////////////////////
    // ITriDeviceResource
private:
	bool OnPrepareResources();
public:
    void ReleaseResources( TriStorage s );

	// do the occlusion rendering/querying
	void RunQuery( Tr2RenderContext& renderContext, const TriFrustum& frustum, const Matrix& transform );

	// access result
	float GetValue() const;

private:
	// name
	std::string m_name;
	// toggle display
	bool m_display;

	// current occlusion values
	uint32_t m_totalNumOfPixels, m_actualNumOfPixels;
	float m_value;

	// states
	bool m_isTotalQueryIssued, m_isActualQueryIssued;

	// dx query objects
	Tr2OcclusionQueryAL m_totalQuery;
	Tr2OcclusionQueryAL m_actualQuery;

	// shader to render the 2d sprite
	Tr2EffectPtr m_actualEffect;

	// a vector with all the sprites this occluder is using
	PEveTransformVector m_sprites;

	// we have our own accumulator
	TriRenderBatchAccumulator<EffectKeyGenerator>* m_batches;
};

TYPEDEF_BLUECLASS( EveOccluder );
BLUE_DECLARE_VECTOR( EveOccluder );

#endif // EveOccluder_H
