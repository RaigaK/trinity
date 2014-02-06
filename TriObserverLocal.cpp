#include "StdAfx.h"
#include "TriObserverLocal.h"

TriObserverLocal::TriObserverLocal( IRoot* lockobj ) :
	m_front( 0.0f, 0.0f, 1.0f ),
	m_position( 0.0f, 0.0f, 0.0f )
{}

TriObserverLocal::~TriObserverLocal()
{}

void TriObserverLocal::Update( const Matrix& worldTransform )
{
	if( m_observer )
	{
		Vector3 front, up, position;
		D3DXVec3TransformCoord( &position, &m_position, &worldTransform );
		D3DXVec3TransformNormal( &front, &m_front, &worldTransform );
		Vector3 localUp( 0.0f, 1.0f, 0.0f );
		D3DXVec3TransformNormal( &up, &localUp, &worldTransform );
		m_observer.p->UpdatePlacement( front, up, position );
	}
}

IBluePlacementObserver* TriObserverLocal::GetObserver()
{
	return m_observer;
}

void TriObserverLocal::SetObserver( IBluePlacementObserver* obs )
{
	m_observer = obs;
}