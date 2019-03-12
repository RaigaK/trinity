////////////////////////////////////////////////////////////
//
//    Created:   February 2019
//    Copyright: CCP 2019
//

#include "StdAfx.h"
#include "Tr2SpotLight.h"
#include "Tr2DebugRenderer.h"

#include "Tr2LightManager.h"
#include "Include/TriMath.h"

Tr2SpotLight::Tr2SpotLight( IRoot* lockobj ):
	Tr2Light( lockobj )
{
	m_type = SPOT_LIGHT;
}

void Tr2SpotLight::RenderDebugInfo( Tr2DebugRenderer& renderer, const Matrix& worldMatrix )
{
	auto baseColor = m_lightData.color * m_lightData.brightness;
	baseColor.a = 0.2;
	auto selectedColor = baseColor + Color( 0.0, 0.0, 0.0, 0.4 );

	Vector3 end = Transform( Vector3( 0.0, 0.0, m_lightData.length ), RotationMatrix( m_lightData.rotation ) ).GetXYZ();
	renderer.DrawCone( this, m_lightData.position + end, m_lightData.position, m_lightData.radius, 10, Tr2DebugRenderer::Solid, Tr2DebugColor( selectedColor, baseColor ) );
	renderer.DrawCone( this, m_lightData.position + end, m_lightData.position, m_lightData.innerRadius, 10, Tr2DebugRenderer::Solid, Tr2DebugColor( selectedColor + Color( 0.0, 0.0, 0.0, 0.2 ), baseColor + Color( 0.0, 0.0, 0.0, 0.2 ) ) );
}

bool Tr2SpotLight::OnModified( Be::Var* value )
{
	if( IsMatch( value, m_lightData.length ) || IsMatch( value, m_lightData.radius ) )
	{
		m_lightData.angle = atan( m_lightData.radius / max( m_lightData.length, 1.0f ) );
	}
	return Tr2Light::OnModified( value );
}