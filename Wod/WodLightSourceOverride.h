#pragma once
#ifndef WodLightSourceOverride_H
#define WodLightSourceOverride_H

#include "WodLightSource.h"

BLUE_CLASS( WodLightSourceOverride ) : public WodLightSource
{
public:
	EXPOSE_TO_BLUE();

	WodLightSourceOverride( IRoot* lockobj = NULL );

	void SetParent( WodLightSource* myParent );
	virtual void PopulateLightData( Tr2PerObjectPerPixelPointLightData* lightdata ) const;

	void SetWorldTransform( const Matrix& m )
	{
		m_transform.SetMatrix( &m );
	}

	const Matrix& GetWorldTransform()
	{
		return *m_transform.GetMatrix();
	}

	const Matrix& GetTransform() const 
	{
		CCP_ASSERT( m_parent );
		return m_parent->GetTransform(); 
	}

	const Vector3& GetPosition() 
	{ 
		CCP_ASSERT( m_parent );
		return m_parent->GetPosition(); 
	}

	bool IsGlowing() const 
	{ 
		CCP_ASSERT( m_parent );
		return m_parent->IsGlowing(); 
	}

	bool IsReflecting() const 
	{ 
		CCP_ASSERT( m_parent );
		return m_parent->IsReflecting(); 
	}

	float GetRadius() const
	{
		CCP_ASSERT( m_parent );
		if( !m_overrideRadius )
		{
			return m_parent->GetRadius(); 
		} else {
			return m_radius;
		}
	}

	float GetSpotlightConeAngle() const
	{
		CCP_ASSERT( m_parent );
		if( !m_overrideSpotlightConeAngle )
		{
			return m_parent->GetSpotlightConeAngle(); 
		} else {
			return m_spotLightConeAngle;
		}
		
	}

	float GetDistanceFalloffKneeRadius() const
	{
		CCP_ASSERT( m_parent );
		if( !m_overrideDistanceFalloffKneeRadius )
		{
			return m_parent->GetDistanceFalloffKneeRadius(); 
		} else {
			return m_distanceFalloffKneeRadius;
		}
	}

	float GetDistanceFalloffKneeValue() const
	{
		CCP_ASSERT( m_parent );
		if( !m_overrideDistanceFalloffKneeValue )
		{
			return m_parent->GetDistanceFalloffKneeValue(); 
		} else {
			return m_distanceFalloffKneeValue;
		}
	}

	float GetPointLightProportion() const
	{
		CCP_ASSERT( m_parent );
		if( !m_overridePointLightProportion )
		{
			return m_parent->GetPointLightProportion(); 
		} else {
			return m_pointLightProportion;
		}
	}

	const Vector3& GetDirection()
	{
		CCP_ASSERT( m_parent );
		return m_parent->GetDirection(); 
	}
private:

	WodLightSourcePtr m_parent;

	bool m_overrideGlow;
	bool m_overrideReflecting;
	bool m_overrideRadius;
	bool m_overrideColor;
	bool m_overridePointLightProportion;
	bool m_overrideDirection;
	bool m_overrideSpotlightConeAngle;
	bool m_overrideDistanceFalloffKneeRadius;
	bool m_overrideDistanceFalloffKneeValue;
	bool m_overrideSpecularRadiusMultiplier;
};

TYPEDEF_BLUECLASS( WodLightSourceOverride );
BLUE_DECLARE_VECTOR( WodLightSourceOverride );

BLUE_INTERFACE( IWodHaveLightSources ) : public IRoot
{
	virtual const Matrix& GetTransform() = 0;
	virtual WodLightSourceOverrideVector* GetLightSources() = 0;
};

#endif