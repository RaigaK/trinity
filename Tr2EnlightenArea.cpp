#include "StdAfx.h"
#include "Tr2EnlightenArea.h"

Tr2EnlightenArea::Tr2EnlightenArea( IRoot* lockobj /*= 0 */ ):
	m_albedoColor( 0.7f, 0.7f, 0.7f, 0.0f ),
	m_emissiveColor( 0.0f, 0.0f, 0.0f, 0.0f ),
	m_isEmissive( false ),
	m_isDirty( false )
{

}

Tr2EnlightenArea::~Tr2EnlightenArea()
{

}