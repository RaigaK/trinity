#include "StdAfx.h"
#include "Tr2MayaVector3Curve.h"

#if BLUE_WITH_PYTHON

Tr2MayaVector3Curve::Tr2MayaVector3Curve( IRoot* lockobj ):
	m_xIndex(-1),
	m_yIndex(-1),
	m_zIndex(-1),
	m_value(0.0f, 0.0f, 0.0f),
	m_length(0.0f)
{
}

bool Tr2MayaVector3Curve::Initialize(  )
{
	ComputeLength();
	return true;
}

// Accessors
void Tr2MayaVector3Curve::setXIndex( int index )
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


void Tr2MayaVector3Curve::setYIndex( int index )
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


void Tr2MayaVector3Curve::setZIndex( int index )
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

bool Tr2MayaVector3Curve::OnModified( Be::Var* value )
{
	if( IsMatch( value, m_animationEngine ) )
	{		
		ComputeLength();
	}

	return true;
}

void Tr2MayaVector3Curve::UpdateValue( double time )
{
	//CCP_STATS_ZONE( __FUNCTION__ );
	if( m_animationEngine )
	{	
		if( m_xIndex > -1 )
		{
			m_value.x = m_animationEngine->evaluate( m_xIndex, (float)time );
		}	
		if( m_yIndex > -1 )
		{
			if( m_yIndex == m_xIndex )
			{
				m_value.y = m_value.x;
			}
			else
			{
				m_value.y = m_animationEngine->evaluate( m_yIndex, (float)time );
			}
		}	
		if( m_zIndex > -1 )
		{
			if( m_zIndex == m_xIndex )
			{
				m_value.z = m_value.x;
			}
			else if( m_zIndex == m_yIndex )
			{
				m_value.z = m_value.y;
			}
			else
			{
				m_value.z = m_animationEngine->evaluate( m_zIndex, (float)time );
			}
			
		}	
	}
}

Vector3 Tr2MayaVector3Curve::GetValueAt( double time ) const
{
	Vector3 value = m_value;
	if( m_animationEngine )
	{
		if( m_xIndex > -1 )
		{
			value.x = m_animationEngine->evaluate( m_xIndex, (float)time );
		}
		if( m_yIndex > -1 )
		{
			if( m_yIndex == m_xIndex )
			{
				value.y = m_value.x;
			}
			else
			{
				value.y = m_animationEngine->evaluate( m_yIndex, (float)time );
			}
		}
		if( m_zIndex > -1 )
		{
			if( m_zIndex == m_xIndex )
			{
				value.z = m_value.x;
			}
			else if( m_zIndex == m_yIndex )
			{
				value.z = m_value.y;
			}
			else
			{
				value.z = m_animationEngine->evaluate( m_zIndex, (float)time );
			}

		}
	}
	return value;
}

void Tr2MayaVector3Curve::ComputeLength()
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
