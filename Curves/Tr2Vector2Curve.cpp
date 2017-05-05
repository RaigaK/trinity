#include "StdAfx.h"
#include "Tr2Vector2Curve.h"

static bool CompareKeys( IRoot* context, Tr2Vector2Key* a, Tr2Vector2Key* b )
{
	return a->m_time < b->m_time;
}

Tr2Vector2Key::Tr2Vector2Key( IRoot* lockobj ) 
{
	m_time = 0.0f;
	m_value = Vector2( 0.0f, 0.0f);
	m_interpolation = LINEAR;
	m_leftTangent = Vector2( 0.0f, 0.0f );
	m_rightTangent = Vector2( 0.0f, 0.0f );
}

Tr2Vector2Curve::Tr2Vector2Curve( IRoot* lockobj ):
Tr2Curve<Tr2Vector2Key, PTr2Vector2KeyVector, Vector2>( lockobj )
{
	m_startValue = Vector2( 0.0f, 0.0f);
	m_endValue = Vector2( 0.0f, 0.0f);
	m_startTangent = Vector2( 0.0f, 0.0f );
	m_endTangent = Vector2( 0.0f, 0.0f );
	m_currentValue = Vector2( 0.0f, 0.0f );
}

void Tr2Vector2Curve::AddKey_( float time, const Vector2& value )
{
	Tr2Vector2KeyPtr key;
	if( !key.CreateInstance() )
	{
		return;
	}

	key->m_time = time;
	key->m_value = value;
	key->m_leftTangent = Vector2( 0.0f, 0.0f );
	key->m_rightTangent = Vector2( 0.0f, 0.0f );
	key->m_interpolation = (Interpolation)m_interpolation;
	m_keys.Insert( -1, key );
}

void Tr2Vector2Curve::Sort( )
{
	if( !m_keys.empty() )
	{
		if( m_keys.size() > 1 )
		{
			m_keys.Sort( ( IList::CompareFn )CompareKeys, NULL );
		}

		if ( m_keys.back()->m_time > m_length )
		{
			Tr2Vector2Key* back = m_keys.back();
			float preLength = m_length;
			Vector2 endValue = m_endValue;
			Vector2 endTangent = m_endTangent;

			m_length = back->m_time;
			m_endValue = back->m_value;
			m_endTangent = back->m_leftTangent;
			if ( preLength > 0.0f )
			{	
				back->m_time = preLength;
				back->m_value = endValue;
				back->m_leftTangent = endTangent;
			}
		}
	}
	m_lastKey = nullptr;
	m_nextKey = nullptr;
}

Vector2 Tr2Vector2Curve::GetKeyLeftTangent( unsigned int idx )
{
	if ( idx < m_keys.size() )
	{
		return m_keys[idx]->m_leftTangent;
	}
	return m_startTangent;
}

void Tr2Vector2Curve::SetKeyLeftTangent( unsigned int idx, Vector2 tangent )
{
	if ( idx < m_keys.size() )
	{
		m_keys[idx]->m_leftTangent = tangent;
	}
}

Vector2 Tr2Vector2Curve::GetKeyRightTangent( unsigned int idx )
{
	if ( idx < m_keys.size() )
	{
		return m_keys[idx]->m_rightTangent;
	}
	return m_endTangent;
}

void Tr2Vector2Curve::SetKeyRightTangent( unsigned int idx, Vector2 tangent )
{
	if ( idx < m_keys.size() )
	{
		m_keys[idx]->m_rightTangent = tangent;
	}
}

Vector2* Tr2Vector2Curve::Interpolate( Vector2* out, Tr2Vector2Key* lastKey, Tr2Vector2Key* nextKey )
{
	*out = m_startValue;

	float time = (float)m_localTime;
	float deltaTime = m_length;
	Vector2 startValue = m_startValue;
	Vector2 endValue = m_endValue;
	unsigned int interp = m_interpolation;

	if ( lastKey )
	{
		interp = lastKey->m_interpolation;
		time -=  lastKey->m_time;
	}

	// The tr2 curves have by default a start and end point
	if ( interp != CONSTANT )
	{

		if( interp == LINEAR )
		{
			// We are in between two keys start------x---0----x------end
			if ( lastKey && nextKey  )
			{
				startValue = lastKey->m_value;
				endValue = nextKey->m_value;					
				deltaTime = nextKey->m_time - lastKey->m_time;
			}
			// We are in between the start of the curve and the next key 
			// start--0---x-------x------end
			else if ( lastKey == NULL && nextKey != NULL )
			{
				endValue = nextKey->m_value;
				deltaTime = nextKey->m_time;
			}
			// We are in between the end of the curve and the last key 
			// start------x-------x--0---end
			else if ( lastKey != NULL && nextKey == NULL )
			{
				startValue = lastKey->m_value;
				deltaTime = m_length - lastKey->m_time;
			}// else there are no keys, just the start and end point . start---0---end
			*out = XMVectorLerp( startValue, endValue, time / deltaTime );
		}
		else
		{
			Vector2 inTangent = m_startTangent;
			Vector2 outTangent = m_endTangent;

			// The tr2 curves have by default a start and end point
			// We are in between two keys start------x---0----x------end
			if ( lastKey && nextKey  )
			{
				startValue = lastKey->m_value;
				inTangent = lastKey->m_rightTangent;
				endValue = nextKey->m_value;
				outTangent = nextKey->m_leftTangent;
				deltaTime = nextKey->m_time - lastKey->m_time;
			}
			// We are in between the start of the curve and the next key 
			// start--0---x-------x------end
			else if ( lastKey == NULL && nextKey != NULL )
			{
				endValue = nextKey->m_value;
				outTangent = nextKey->m_leftTangent;				
				deltaTime = nextKey->m_time;
			}
			// We are in between the end of the curve and the last key 
			// start------x-------x--0---end
			else if ( lastKey != NULL && nextKey == NULL )
			{
				startValue = lastKey->m_value;
				inTangent = lastKey->m_rightTangent;
				deltaTime = m_length - lastKey->m_time;				
			}// else there are no keys, just the start and end point . start---0---end
			
			if ( interp == HERMITE )
			{
				*out = XMVectorHermite( startValue, inTangent, endValue, outTangent, time / deltaTime );
			}
		}
	}
	return out;
}