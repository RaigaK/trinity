#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "WodLightSourceOverride.h"

WodLightSourceOverride::WodLightSourceOverride( IRoot* lockobj ):
	WodLightSource( lockobj ),
	m_overrideGlow( false ),
	m_overrideReflecting( false ),
	m_overrideRadius( false ),
	m_overrideColor( false ),
	m_overridePointLightProportion( false ),
	m_overrideDirection( false ),
	m_overrideSpotlightConeAngle( false ),
	m_overrideDistanceFalloffKneeRadius( false ),
	m_overrideDistanceFalloffKneeValue( false ),
	m_overrideSpecularRadiusMultiplier( false )
{

}

void WodLightSourceOverride::SetParent( WodLightSource* myParent )
{

	if( !myParent )
	{
		return;
	}

	m_parent = myParent;

	// Update the values on the override to the values from the object

	m_reflecting = myParent->IsReflecting();
	m_glowing = myParent->IsGlowing();

	if( !m_overrideRadius )
	{
		m_radius = myParent->GetRadius();
	}
	
	if( !m_overrideColor )
	{
		m_color = myParent->GetColor();
	}

	if( !m_overridePointLightProportion )
	{
		m_pointLightProportion = myParent->GetPointLightProportion();
	}
	
	if( !m_overrideDirection )
	{	
		m_direction = myParent->GetDirection();
	}
	
	if( !m_overrideSpotlightConeAngle )
	{
		m_spotLightConeAngle =  myParent->GetSpotlightConeAngle();
	}
	
	if( !m_overrideDistanceFalloffKneeRadius )
	{
		m_distanceFalloffKneeRadius = myParent->GetDistanceFalloffKneeRadius();
	}
	
	if( !m_overrideDistanceFalloffKneeValue )
	{
		m_distanceFalloffKneeValue = myParent->GetDistanceFalloffKneeValue();
	}
	
	if( !m_overrideSpecularRadiusMultiplier )
	{
		m_specularRadiusMultiplier = myParent->GetSpecularRadiusMultiplier();
	}

	m_glowConeColor = myParent->GetGlowConeColor();
	m_glowConeEffect = myParent->GetGlowConeEffect();
	m_glowHaloEffect = myParent->GetGlowHaloEffect();
	m_glowHaloScale = myParent->GetGlowHaloScale();
	m_glowHaloColor = myParent->GetGlowHaloColor();
	m_glowHaloZOffset = myParent->GetGlowHaloZOffset();
	m_glowFlareEffect = myParent->GetGlowFlareEffect();
	m_glowFlareColor = myParent->GetGlowFlareColor();
	m_glowFlareScale = myParent->GetGlowFlareScale();
}

void WodLightSourceOverride::PopulateLightData( Tr2PerObjectPerPixelPointLightData* lightdata ) const
{
	m_parent->PopulateLightData( lightdata );

	if( m_overrideColor )
	{
		lightdata->color = Vector3(m_color.r, m_color.g, m_color.b);
	}

	if( m_overrideRadius )
	{
		lightdata->radius = m_radius;
	}

	if( m_overrideDirection )
	{
		lightdata->direction = m_direction;
	}

	if( m_overridePointLightProportion )
	{
		lightdata->pointLightProportion = m_pointLightProportion;
	}

	if( m_overrideSpotlightConeAngle )
	{
		lightdata->spotLightConeAngleCos = cosf( m_spotLightConeAngle );
	}

	if( m_overrideDistanceFalloffKneeRadius )
	{
		lightdata->distanceFalloffKneeRadiusProportion = m_distanceFalloffKneeRadius / lightdata->radius;
	}

	if( m_overrideDistanceFalloffKneeValue )
	{
		lightdata->distanceFalloffKneeValue = m_distanceFalloffKneeValue;
	}

	if( m_overrideSpecularRadiusMultiplier )
	{
		lightdata->specularRadiusMultiplier = m_specularRadiusMultiplier * lightdata->radius;
	}

	if( m_overrideDistanceFalloffKneeRadius || m_overrideDistanceFalloffKneeValue )
	{
		lightdata->distanceFalloffPrecalc1 = lightdata->distanceFalloffKneeValue / ( 1.f - lightdata->distanceFalloffKneeRadiusProportion );
	}
}

#endif
