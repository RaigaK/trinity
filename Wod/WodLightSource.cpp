#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "WodLightSource.h"
#include "include/TriVector.h"

WodLightSource::WodLightSource( IRoot* lockobj ) :
    PARENTLOCK( m_transform, INotify ),
	m_glowing( true ),
	m_reflecting( false ),
	m_spotLightConeAngle( 3.14159263f / 2.0f ),
	m_pointLightProportion( 0.03f ),
	m_distanceFalloffKneeRadius( 20.0f ),
	m_distanceFalloffKneeValue( 0.5f ),
	m_specularRadiusMultiplier( 0.25f ),
	m_radius( 80.0f ),
	m_direction( 0.0f, -1.0f, 0.0f ),
	m_color( 1.0f, 1.0f, 1.0f, 0.0f ),
	m_glowConeColor( 0.5f, 0.5f, 0.5f, 1.0f ),
	m_glowHaloColor( 0.5f, 0.5f, 0.5f, 1.0f ),
	m_glowHaloScale( 2.0f ),
	m_glowHaloZOffset( 0.0f ),
	m_glowFlareColor( 0.5f, 0.5f, 0.5f, 1.0f ),
	m_glowFlareScale( 10.0f, 1.0f )
{
}

WodLightSource::~WodLightSource()
{

}


bool WodLightSource::Initialize()
{
    return true;
}

void WodLightSource::PopulateLightData( Tr2PerObjectPerPixelPointLightData* lightdata ) const
{
	lightdata->color = Vector3(m_color.r, m_color.g, m_color.b);
	lightdata->radius = m_radius;
	lightdata->direction = m_direction;
	lightdata->pointLightProportion = m_pointLightProportion;
	lightdata->spotLightConeAngleCos = cosf( m_spotLightConeAngle );
	lightdata->distanceFalloffKneeRadiusProportion = m_distanceFalloffKneeRadius / m_radius;
	lightdata->distanceFalloffKneeValue = m_distanceFalloffKneeValue;
	lightdata->specularRadiusMultiplier = m_specularRadiusMultiplier * m_radius;
	lightdata->distanceFalloffPrecalc1 = lightdata->distanceFalloffKneeValue / ( 1.f - lightdata->distanceFalloffKneeRadiusProportion );
}

float WodLightSource::CalculateIntensityAtPoint( const Matrix& lightWorldTransform, const Vector3& point ) const
{

	const float baseIntensity = (m_color.r * 0.2125f) + (m_color.g * 0.7154f) + (m_color.b * 0.0721f);

	const Vector3 worldPosition( lightWorldTransform._41, lightWorldTransform._42, lightWorldTransform._43 );
	Vector3 v = worldPosition - point; 
	const float dist = D3DXVec3Length( &v );
	v /= dist;

	if( dist >= GetRadius() )
	{
		// out of range. Lights always go to 0.0 at their radius.
		// NB: Specular range multiplier complicates this, but we're ignoring that in favour of optimization.
		return 0.0f;
	}

	const float falloffDistanceProportion = min( 1.0f, dist / GetRadius() );
	Vector3 direction = GetDirection();
	D3DXVec3Normalize( &direction, &direction ); // just in case

	const float angleCos = D3DXVec3Dot( &v, &GetDirection() );
	const float cutoffAngleCos = cos( GetSpotlightConeAngle() );

	const float distanceFalloffKneeRadiusProportion = GetDistanceFalloffKneeRadius() / GetRadius();
	float distanceFalloffTerm = 0.0f;
	const float distanceFalloffKneeValue = GetDistanceFalloffKneeValue();

	if( falloffDistanceProportion > distanceFalloffKneeRadiusProportion )
	{
		distanceFalloffTerm = distanceFalloffKneeValue - distanceFalloffKneeValue*((falloffDistanceProportion - distanceFalloffKneeRadiusProportion) / (1.0f - distanceFalloffKneeRadiusProportion));
	} else {
		distanceFalloffTerm = 1.0f - ( 1.0f - distanceFalloffKneeValue ) * (falloffDistanceProportion / distanceFalloffKneeRadiusProportion);
	}
	
	// use direct lighting dot term for indirect lighting so that it can look like a point light with minAngularFalloff = 1
	const float indirectLightingContribution = GetPointLightProportion() *  distanceFalloffTerm;
	// Approximating a smoothstep function with a linear one
	const float directLightingContribution = ( 1.0f - GetPointLightProportion() ) * distanceFalloffTerm * max(0.0f, (cutoffAngleCos - angleCos) / cutoffAngleCos);

	return baseIntensity * (indirectLightingContribution + directLightingContribution);
}

float WodLightSource::CalculateIntensityInBoundingBox( const Matrix& lightWorldTransform, const Vector3& objectBoundingBoxWorldMin, const Vector3& objectBoundingBoxWorldMax ) const
{
	// We require two things, the absolute nearest point in the bounding box,
	// and a value representing the maximum intensity of the spotlight cone on the box
	// We might have to simplify that down

	const Vector3 worldPosition( lightWorldTransform._41, lightWorldTransform._42, lightWorldTransform._43 );

	Vector3 nearestPoint;
    GetNearestPointOnAABB(nearestPoint, worldPosition, objectBoundingBoxWorldMin, objectBoundingBoxWorldMax);

	const float closestPointIntensity = CalculateIntensityAtPoint( lightWorldTransform, nearestPoint );

	float directionIntersectionIntensity = 0.0f;


	return closestPointIntensity;
}

#endif
