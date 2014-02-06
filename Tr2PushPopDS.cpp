#include "StdAfx.h"
#include "Tr2PushPopDS.h"
#include "Tr2Renderer.h"

Tr2PushPopDS::Tr2PushPopDS()
: m_renderContext( nullptr )
{
	USE_MAIN_THREAD_RENDER_CONTEXT();
	Tr2Renderer::PushDepthStencilBuffer( renderContext );
}

Tr2PushPopDS::Tr2PushPopDS( const Tr2DepthStencilAL& ds )
: m_renderContext( nullptr )
{
	USE_MAIN_THREAD_RENDER_CONTEXT();
	Tr2Renderer::PushDepthStencilBuffer( ds, renderContext );
}

Tr2PushPopDS::Tr2PushPopDS( Tr2RenderContext& renderContext )
: m_renderContext( &renderContext )
{
	Tr2Renderer::PushDepthStencilBuffer( renderContext );
}

Tr2PushPopDS::Tr2PushPopDS( const Tr2DepthStencilAL& ds, Tr2RenderContext& renderContext )
: m_renderContext( &renderContext )
{
	Tr2Renderer::PushDepthStencilBuffer( ds, renderContext );
}

Tr2PushPopDS::~Tr2PushPopDS()
{
	if( m_renderContext )
	{
		Tr2Renderer::PopDepthStencilBuffer( *m_renderContext );
	}
	else
	{
		USE_MAIN_THREAD_RENDER_CONTEXT();
		Tr2Renderer::PopDepthStencilBuffer( renderContext );
	}
}
