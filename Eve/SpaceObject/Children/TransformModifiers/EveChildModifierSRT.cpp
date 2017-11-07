////////////////////////////////////////////////////////////
//
//    Created:   2017
//    Copyright: CCP 2017
//
#include "StdAfx.h"
#include "EveChildModifierSRT.h"

EveChildModifierSRT::EveChildModifierSRT( IRoot* lockobj ):
	m_scaling( 1.f, 1.f, 1.f ),
	m_rotation( 0.f, 0.f, 0.f, 1.f ),
	m_translation( 0.f, 0.f, 0.f )
{
}

EveChildModifierSRT::~EveChildModifierSRT()
{
}

Matrix EveChildModifierSRT::ApplyTransform( const Matrix& transform ) const
{
	Matrix local;	
	return *D3DXMatrixTransformation( &local, nullptr, nullptr, &m_scaling, nullptr, &m_rotation, &m_translation ) * transform;
}