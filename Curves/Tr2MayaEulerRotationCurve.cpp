#include "StdAfx.h"
#include "Tr2MayaEulerRotationCurve.h"

#if BLUE_WITH_PYTHON

Tr2MayaEulerRotationCurve::Tr2MayaEulerRotationCurve( IRoot* lockobj ):
	m_xIndex(-1),
	m_yIndex(-1),
	m_zIndex(-1),
	m_quatValue(0.0f, 0.0f, 0.0f, 1.0f),
	m_eulerValue(0.0f, 0.0f, 0.0f),
	m_length(0.0f),
	m_updateQuaternion(false)
{
}

bool Tr2MayaEulerRotationCurve::Initialize(  )
{
	ComputeLength();
	return true;
}

// Accessors
void Tr2MayaEulerRotationCurve::setXIndex( int index )
{
	if( m_animationEngine && ( (int)m_animationEngine->getNumberOfCurves() > index ) && index > -2 )
	{
		if( index != m_xIndex )
		{
			m_xIndex = index;
			ComputeLength();
		}
	}
}


void Tr2MayaEulerRotationCurve::setYIndex( int index )
{
	if( m_animationEngine && ( (int)m_animationEngine->getNumberOfCurves() > index ) && index > -2 )
	{
		if( index != m_yIndex )
		{			
			m_yIndex = index;
			ComputeLength();
		}
	}
}


void Tr2MayaEulerRotationCurve::setZIndex( int index )
{
	if( m_animationEngine && ( (int)m_animationEngine->getNumberOfCurves() > index ) && index > -2 )
	{
		if( index != m_zIndex )
		{			
			m_zIndex = index;
			ComputeLength();
		}
	}
}

bool Tr2MayaEulerRotationCurve::OnModified( Be::Var* value )
{
	if( IsMatch( value, m_animationEngine ) )
	{		
		ComputeLength();
	}

	return true;
}

void Tr2MayaEulerRotationCurve::UpdateValue( double time )
{
	//CCP_STATS_ZONE( __FUNCTION__ );
	if( m_animationEngine )
	{	
		if( m_xIndex > -1 )
		{
			m_eulerValue.x = m_animationEngine->evaluate( m_xIndex, (float)time );
		}
		if( m_yIndex > -1 )
		{
			if( m_yIndex == m_xIndex )
			{
				m_eulerValue.y = m_eulerValue.x;
			}
			else
			{
				m_eulerValue.y = m_animationEngine->evaluate( m_yIndex, (float)time );
			}			
		}
		if( m_zIndex > -1 )
		{
			if( m_zIndex == m_xIndex )
			{
				m_eulerValue.z = m_eulerValue.x;
			}
			else if( m_zIndex == m_yIndex )
			{
				m_eulerValue.z = m_eulerValue.y;
			}
			else
			{
				m_eulerValue.z = m_animationEngine->evaluate( m_zIndex, (float)time );
			}				
		}

		if( m_updateQuaternion )
		{
			m_quatValue = Quaternion( XMQuaternionRotationRollPitchYaw( m_eulerValue.x, m_eulerValue.y, m_eulerValue.z ) );
		}		
	}
}

void Tr2MayaEulerRotationCurve::ComputeLength()
{
	float duration = 0.0f;
	float diff = 0.0f;

	if( m_animationEngine == NULL )
	{
		return;
	}

	if( m_animationEngine->getNumberOfCurves() == 0 )
	{
		return;
	}

	if( m_xIndex > -1  )
	{
		duration = m_animationEngine->getLength(m_xIndex);
	}	

	if( m_yIndex > -1 )
	{		
		diff = m_animationEngine->getLength(m_yIndex);
		if( diff > duration )
		{
			duration = diff;
		}
	}	

	if( m_zIndex > -1 )
	{
		diff = m_animationEngine->getLength(m_zIndex);
		if( diff > duration )
		{
			duration = diff;
		}
	}	
	m_length = duration;
}

#endif
