#pragma once
#ifndef WodLightSource_H
#define WodLightSource_H

#include "include/TriMatrix.h"

#include "Tr2ConstantBufferFormats.h"

namespace Umbra
{
	class Cell;
}

BLUE_DECLARE( Tr2Effect );

BLUE_CLASS( WodLightSource ) :  public IInitialize
{
public:
    EXPOSE_TO_BLUE();

    WodLightSource( IRoot* lockobj = 0 );

    ~WodLightSource();

    using IInitialize::Lock;
    using IInitialize::Unlock;

    bool Initialize();

    void Update( Be::Time time );

	virtual void PopulateLightData( Tr2PerObjectPerPixelPointLightData* lightdata ) const;

    bool IsGlowing() const { return m_glowing; }
    bool IsReflecting() const { return m_reflecting; }
    const Matrix& GetTransform() const { return *m_transform.GetMatrix(); }
	const Vector3& GetPosition() const { return *(Vector3*)&m_transform._41; }
	const Color& GetColor() const { return m_color; }
	float GetRadius() const { return m_radius; }

	float  GetPointLightProportion() const { return m_pointLightProportion; }
	float GetSpotlightConeAngle() const { return m_spotLightConeAngle; }
	const Vector3& GetDirection() const { return m_direction; }
	float GetDistanceFalloffKneeRadius() const { return m_distanceFalloffKneeRadius; }
	float GetDistanceFalloffKneeValue() const { return m_distanceFalloffKneeValue; }
	float GetSpecularRadiusMultiplier() const { return m_specularRadiusMultiplier; }

	const Color& GetGlowConeColor() const { return m_glowConeColor; }

	const Color& GetGlowHaloColor() const { return m_glowHaloColor; }
	float GetGlowHaloScale() const { return m_glowHaloScale; }
	float GetGlowHaloZOffset() const { return m_glowHaloZOffset; }

	const Color& GetGlowFlareColor() { return m_glowFlareColor; }
	const Vector2& GetGlowFlareScale() { return m_glowFlareScale; }

	Tr2Effect* GetGlowConeEffect() const { return m_glowConeEffect; }
	void SetGlowConeEffect( Tr2Effect* val) { m_glowConeEffect = val; }

	Tr2Effect* GetGlowHaloEffect() const { return m_glowHaloEffect; }
	void SetGlowHaloEffect( Tr2Effect* val) { m_glowHaloEffect = val; }

	Tr2Effect* GetGlowFlareEffect() const { return m_glowFlareEffect; }
	void SetGlowFlareEffect( Tr2Effect* val) { m_glowFlareEffect = val; }

	float CalculateIntensityAtPoint( const Matrix& lightWorldTransform, const Vector3& point ) const;
	float CalculateIntensityInBoundingBox( const Matrix& lightWorldTransform, const Vector3& worldBoundingBoxMin, const Vector3& worldBoundingBoxMax ) const;
protected:
	bool m_glowing;
	bool m_reflecting;
	PTriMatrix m_transform;
	float	m_radius;
	Color	m_color;
	float	m_pointLightProportion;
	Vector3 m_direction;
	float	m_spotLightConeAngle;
	float m_distanceFalloffKneeRadius;
	float m_distanceFalloffKneeValue;
	float m_specularRadiusMultiplier;

	Color m_glowConeColor;

	Color m_glowHaloColor;
	float m_glowHaloScale;
	float m_glowHaloZOffset;

	Color m_glowFlareColor;
	Vector2 m_glowFlareScale;

	Tr2EffectPtr m_glowConeEffect;
	Tr2EffectPtr m_glowHaloEffect;
	Tr2EffectPtr m_glowFlareEffect;
};

TYPEDEF_BLUECLASS( WodLightSource );

BLUE_DECLARE_VECTOR( WodLightSource );

#endif // WodLightSource_H
