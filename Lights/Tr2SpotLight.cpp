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

void Tr2SpotLight::RenderDebugInfo( ITr2DebugRenderer2& renderer, const Matrix& worldMatrix, const granny_matrix_3x4* bones, size_t boneCount  )
{
	auto baseColor = m_lightData.color * m_lightData.brightness;
	baseColor.a = 0.1;
	auto selectedColor = baseColor + Color( 0.0, 0.0, 0.0, 0.1 );
	
	Matrix boneMatrix = m_boneTransform;
	if( m_lightData.boneIndex >= 0 && m_lightData.boneIndex < boneCount ) {
		TriMatrixCopyFrom3x4( &boneMatrix, &bones[m_lightData.boneIndex] );
	}

	Matrix lightOffsetMatrix = boneMatrix * worldMatrix;	
	Matrix lightMatrixWithRotation = RotationMatrix( Normalize( m_lightData.rotation ) ) * lightOffsetMatrix;
	lightMatrixWithRotation.GetTranslation() = Vector3( 0, 0, 0 );
	
	float scaling = XMVectorGetX( XMVectorAdd( XMVector3LengthEst( lightOffsetMatrix.GetX() ),
		XMVectorAdd( XMVector3LengthEst( lightOffsetMatrix.GetY() ), XMVector3LengthEst( lightOffsetMatrix.GetZ() ) ) ) ) / 3.f;

	Vector3 start = TransformCoord( m_lightData.position, lightOffsetMatrix );
	Vector3 outerEnd = start + TransformCoord( Vector3( 0.0, 0.0, m_lightData.radius * scaling ), lightMatrixWithRotation );
	Vector3 innerEnd = start + TransformCoord( Vector3( 0.0, 0.0, m_lightData.innerRadius * scaling ), lightMatrixWithRotation );

	float outerConeRadius = tan( TRI_2PI * m_lightData.outerAngle / 360.f ) * m_lightData.radius * scaling;
	float innerConeRadius = tan( TRI_2PI * m_lightData.innerAngle / 360.f ) * m_lightData.innerRadius * scaling;
	renderer.DrawCone( this, outerEnd, start, outerConeRadius, 10, Tr2DebugRenderer::Solid, Tr2DebugColor( selectedColor, baseColor ) );
	renderer.DrawCone( this, innerEnd, start, innerConeRadius, 10, Tr2DebugRenderer::Solid, Tr2DebugColor( selectedColor, baseColor ) );
}