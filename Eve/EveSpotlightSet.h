////////////////////////////////////////////////////////////
//
//    Created:   July 2012
//    Copyright: CCP 2012
//

#pragma once
#ifndef EveSpotlightSet_h
#define EveSpotlightSet_h


#include "ITr2GeometryProvider.h"
#include "Tr2DeviceResource.h"
#include "EveSpriteSet.h"
#include "EveSpotlightSetItem.h"
#include "TriFrustum.h"
#include "Utilities/ViewDistanceInfo.h"

BLUE_DECLARE( ITriRenderBatchAccumulator );
BLUE_DECLARE( Tr2PerObjectData );
BLUE_DECLARE( EveSpotlightSet );
BLUE_DECLARE_VECTOR( EveSpotlightSet );
BLUE_DECLARE( Tr2Effect );

// --------------------------------------------------------------------------------
// Description:
//   Contains a list of individual spotlight items and renders them efficiently.
// SeeAlso:
//   EveSpriteSet, EveSpaceObject2
// --------------------------------------------------------------------------------
BLUE_CLASS( EveSpotlightSet ):
	public IInitialize,
	public ITr2GeometryProvider,
	public Tr2DeviceResource
{
public:
    EXPOSE_TO_BLUE();

	using IInitialize::Lock;
	using IInitialize::Unlock;

    EveSpotlightSet( IRoot* lockobj = NULL );
	~EveSpotlightSet();

	void GetBatches( ITriRenderBatchAccumulator* accumulator, const Tr2PerObjectData* perObjectData );

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	bool Initialize();

	//////////////////////////////////////////////////////////////////////////////////////
	// ITr2GeometryProvider
	void SubmitGeometry( Tr2RenderContext& renderContext );
	void SubmitSpriteGeometry( Tr2RenderContext& renderContext );

	//////////////////////////////////////////////////////////////////////////////////////////
	// ITriDeviceResource
	void ReleaseResources( TriStorage s );

	void Rebuild();
	void UpdateViewDistanceInfo( const TriFrustum& frustum, ViewDistanceInfo& viewDistance, const Matrix& parentTransform ) const;

	// access effects
	Tr2EffectPtr GetConeEffect() const;
	void SetConeEffect( Tr2EffectPtr effect );
	Tr2EffectPtr GetGlowEffect() const;
	void SetGlowEffect( Tr2EffectPtr effect );

	// access name
	const char* GetName() const;
	void SetName( const char* name );

	// access items
	const EveSpotlightSetItemVector* GetSpotlightItems() const;
	void AddSpotlightItem( EveSpotlightSetItemPtr item );

private:
	bool OnPrepareResources();
	bool m_display;	
	std::string m_name;

	PEveSpotlightSetItemVector m_spotlightItems;

	Tr2EffectPtr m_coneEffect;
	Tr2EffectPtr m_glowEffect;

	unsigned int m_vertexDeclHandle;
	unsigned int m_coneVertexCount;
	Tr2VertexBufferAL m_coneVertexBuffer;

	unsigned int m_spriteVertexCount;
	Tr2VertexBufferAL m_spriteVertexBuffer;
};

TYPEDEF_BLUECLASS( EveSpotlightSet );
#endif //EveSpotlightSet_h
