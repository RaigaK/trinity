#include "StdAfx.h"
#include "Tr2Vector3Curve.h"

static bool CompareKeys( IRoot* context, Tr2Vector3Key* a, Tr2Vector3Key* b )
{
	return a->m_time < b->m_time;
}

Tr2Vector3Key::Tr2Vector3Key( IRoot* lockobj ) 
{
	m_time = 0.0f;
	m_value = Vector3(0.0f, 0.0f, 0.0f);
	m_interpolation = LINEAR;
	m_leftTangent = Vector3(0.0f, 0.0f, 0.0f);
	m_rightTangent = Vector3(0.0f, 0.0f, 0.0f);
}

Tr2Vector3Curve::Tr2Vector3Curve( IRoot* lockobj ):
Tr2Curve<Tr2Vector3Key, PTr2Vector3KeyVector, Vector3>( lockobj )
{
	m_startValue = Vector3(0.0f, 0.0f, 0.0f);
	m_endValue = Vector3(0.0f, 0.0f, 0.0f);
	m_startTangent = Vector3(0.0f, 0.0f, 0.0f);
	m_endTangent = Vector3(0.0f, 0.0f, 0.0f);
	m_currentValue = Vector3(0.0f, 0.0f, 0.0f);
}

void Tr2Vector3Curve::AddKey_( float time, const Vector3& value )
{
	Tr2Vector3KeyPtr key;
	if( !key.CreateInstance() )
	{
		return;
	}

	key->m_time = time;
	key->m_value = value;
	key->m_leftTangent = Vector3(0.0f, 0.0f, 0.0f);
	key->m_rightTangent = Vector3(0.0f, 0.0f, 0.0f);
	key->m_interpolation = (Interpolation)m_interpolation;
	m_keys.Insert( -1, key );
}

void Tr2Vector3Curve::Sort( )
{
	if( !m_keys.empty() )
	{
		if( m_keys.size() > 1 )
		{
			m_keys.Sort( ( IList::CompareFn )CompareKeys, NULL );
		}
		if ( m_keys.back()->m_time > m_length )
		{
			Tr2Vector3Key* back = m_keys.back();
			float preLength = m_length;
			Vector3 endValue = m_endValue;
			Vector3 endTangent = m_endTangent;

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

Vector3 Tr2Vector3Curve::GetKeyLeftTangent( unsigned int idx )
{
	if ( idx < m_keys.size() )
	{
		return m_keys[idx]->m_leftTangent;
	}
	return m_startTangent;
}

void Tr2Vector3Curve::SetKeyLeftTangent( unsigned int idx, Vector3 tangent )
{
	if ( idx < m_keys.size() )
	{
		m_keys[idx]->m_leftTangent = tangent;
	}
}

Vector3 Tr2Vector3Curve::GetKeyRightTangent( unsigned int idx )
{
	if ( idx < m_keys.size() )
	{
		return m_keys[idx]->m_rightTangent;
	}
	return m_endTangent;
}

void Tr2Vector3Curve::SetKeyRightTangent( unsigned int idx, Vector3 tangent )
{
	if ( idx < m_keys.size() )
	{
		m_keys[idx]->m_rightTangent = tangent;
	}
}

Vector3* Tr2Vector3Curve::Interpolate( Vector3* out, Tr2Vector3Key* lastKey, Tr2Vector3Key* nextKey )
{
	*out = m_startValue;

	float time = (float)m_localTime;
	float deltaTime = m_length;
	Vector3 startValue = m_startValue;
	Vector3 endValue = m_endValue;
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
			Vector3 inTangent = m_startTangent;
			Vector3 outTangent = m_endTangent;

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