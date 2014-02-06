#pragma once
#ifndef EveSpriteSet_H
#define EveSpriteSet_H


#include "Tr2DeviceResource.h"
#include "ITr2GeometryProvider.h"
#include "EveSpriteSetItem.h"

BLUE_DECLARE( EveSpriteSet );
BLUE_DECLARE_VECTOR( EveSpriteSet );
BLUE_DECLARE( Tr2Effect );

class ITriRenderBatchAccumulator;
class Tr2PerObjectData;

BLUE_CLASS( EveSpriteSet ):
	public IInitialize,
	public ITr2GeometryProvider,
	public Tr2DeviceResource
{
public:
	EXPOSE_TO_BLUE();

	using IInitialize::Lock;
	using IInitialize::Unlock;

	EveSpriteSet( IRoot* lockobj = NULL );
	~EveSpriteSet();

	// Note: Call Clear, Add (as many times as needed), then PrepareResources
	void Clear();
	void Add( const Vector3& pos, float blinkRate, float blinkPhase, float minScale, float maxScale, float falloff, Color color );
	void Add( const Vector3& pos, float scale, Color color );
	void Add( EveSpriteSetItemPtr newItem );
	
	// Rebuild resources
	void Rebuild();

	void GetBatches( ITriRenderBatchAccumulator* accumulator, const Tr2PerObjectData* perObjectData );

	EveSpriteSetItemVector* GetSprites();
	const char* GetName();
	void SetName( const char* name );

	Tr2EffectPtr GetEffect();
	void SetEffect( Tr2EffectPtr effect );

	//////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	bool Initialize();
	
	//////////////////////////////////////////////////////////////////////////////////////
	// ITr2GeometryProvider
	void SubmitGeometry( Tr2RenderContext& renderContext );

	//////////////////////////////////////////////////////////////////////////////////////
	// ITriDeviceResource
	void ReleaseResources( TriStorage s );
private:
	bool OnPrepareResources();
private:
	// Persisted members
	bool m_display;
	std::string m_name;

	PEveSpriteSetItemVector m_sprites;
	Tr2EffectPtr m_effect;

	// Member variables for runtime state
	unsigned int m_vertexDeclHandle;
	unsigned int m_bytesPerVertex;
	unsigned int m_vertexCount;
	Tr2VertexBufferAL m_vertexBuffer;

};

TYPEDEF_BLUECLASS( EveSpriteSet );

#endif // EveSpriteSet_H