////////////////////////////////////////////////////////////////////////////////
//
// Created:		January 2019
// Copyright:	CCP 2019
//

#include "StdAfx.h"
#include "Tr2PostProcessRenderInfo.h"


Tr2PostProcessRenderInfo::Tr2PostProcessRenderInfo( IRoot* lockobj )
{
	m_rt1.CreateInstance();
	m_rt1->m_name = "PostProcess RT1";

	m_rt2.CreateInstance();
	m_rt2->m_name = "PostProcess RT2";

	m_sourceBufferCopy.CreateInstance();
	m_sourceBufferCopy->m_name = "Source Copy";

	m_black.CreateInstance();
	m_black->m_name = "Black";
	m_black->Create( 4, 4, 1, Tr2RenderContextEnum::PIXEL_FORMAT_B8G8R8A8_UNORM );
}


Tr2PostProcessRenderInfo::~Tr2PostProcessRenderInfo()
{
	if( m_rt1->IsValid() )
	{
		m_rt1->Destroy();
	}
	if( m_rt2->IsValid() )
	{
		m_rt2->Destroy();
	}
	if( m_black->IsValid() )
	{
		m_black->Destroy();
	}

	if( m_sourceBufferCopy && m_sourceBufferCopy->IsValid() )
	{
		m_sourceBufferCopy->Destroy();
	}
}


bool Tr2PostProcessRenderInfo::OnModified( Be::Var* value )
{
	if( IsMatch( value, m_sourceBuffer ) )
	{
		SetSourceBuffer( m_sourceBuffer );
	}
	return true;
}

void Tr2PostProcessRenderInfo::SetSourceBuffer( Tr2RenderTarget* sourceBuffer )
{
	m_sourceBuffer = sourceBuffer;
	CopySourceTo( m_rt1, 0.5f );
	CopySourceTo( m_rt2, 0.5f );

	if( m_sourceBufferCopy->IsValid() )
	{
		m_sourceBufferCopy->Destroy();
	}

	m_sourceBufferCopy->Create(
		uint32_t( float( m_sourceBuffer->GetWidth() ) ),
		uint32_t( float( m_sourceBuffer->GetHeight() ) ),
		1,
		m_sourceBuffer->GetFormat(),
		1,
		0 );
}


void Tr2PostProcessRenderInfo::CopySourceTo( Tr2RenderTarget* renderTarget, float sizeScale )
{
	if( renderTarget->IsValid() )
	{
		renderTarget->Destroy();
	}

	if( m_sourceBuffer )
	{
		renderTarget->Create(
			uint32_t( float( m_sourceBuffer->GetWidth() ) * sizeScale ),
			uint32_t( float( m_sourceBuffer->GetHeight() ) * sizeScale ),
			1,
			m_sourceBuffer->GetFormat(),
			1,
			0 );
	}
}

