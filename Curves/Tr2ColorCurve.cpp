#include "StdAfx.h"
#include "Tr2ColorCurve.h"

// --------------------------------------------------------------------------------------
// Description:
//   Color key comparison function.
// Arguments:
//   context - ignored
//   a - First color key comparison operand
//   b - Second color key comparison operand
// Return Value:
//   true, if key a's time is less that key b's time
//   false, otherwise
// --------------------------------------------------------------------------------------
static bool CompareKeys( IRoot* context, Tr2ColorKey* a, Tr2ColorKey* b )
{
	return a->m_time < b->m_time;
}



// --------------------------------------------------------------------------------------
// Description:
//   Default constructor.
// --------------------------------------------------------------------------------------
Tr2ColorKey::Tr2ColorKey( IRoot* lockobj )
{
	m_value = Color( 0.0f, 0.0f, 0.0f, 1.0f );
	m_time = 0.0f;
	m_interpolation = LINEAR;
}



// --------------------------------------------------------------------------------------
// Description:
//   Default constructor.
// --------------------------------------------------------------------------------------
Tr2ColorCurve::Tr2ColorCurve( IRoot* lockobj ) :
	Tr2Curve<Tr2ColorKey, PTr2ColorKeyVector, Color>( lockobj )
{
	m_startValue = Color(0.0f, 0.0f, 0.0f, 1.0f);
	m_endValue = Color(0.0f, 0.0f, 0.0f, 1.0f);
	m_currentValue = Color(0.0f, 0.0f, 0.0f, 1.0f);
}

// --------------------------------------------------------------------------------------
// Description:
//   Private virtual function to add a color key at a particular time.
// Arguments:
//   time - The time at which to add the key
//   value - The color value for the key
// --------------------------------------------------------------------------------------
void Tr2ColorCurve::AddKey_( float time, const Color& value )
{
	Tr2ColorKeyPtr key;
	if( !key.CreateInstance() )
	{
		return;
	}

	key->m_time = time;
	key->m_value = value;
	key->m_interpolation = (Interpolation)m_interpolation;
	m_keys.Insert( -1, key );
}

// --------------------------------------------------------------------------------------
// Description:
//  Sorts the color keys into ascending order based on key time.
// --------------------------------------------------------------------------------------
void Tr2ColorCurve::Sort()
{
	if( !m_keys.empty() )
	{
		if( m_keys.size() > 1 )
		{
			m_keys.Sort( ( IList::CompareFn )CompareKeys, NULL );
		}
		// We might have added a key passed the length of the curve
		if ( m_keys.back()->m_time > m_length )
		{
			Tr2ColorKey* back = m_keys.back();
			float preLength = m_length;
			Color endValue = m_endValue;

			m_length = back->m_time;
			m_endValue = back->m_value;
			if ( preLength > 0.0f )
			{	
				back->m_time = preLength;
				back->m_value = endValue;
			}
		}
	}
	m_lastKey = nullptr;
	m_nextKey = nullptr;
}

// --------------------------------------------------------------------------------------
// Description:
//   Interpolates between two color keys using the curve's internal time as the 
//   interpolation control factor.
// Arguments:
//   out - [output] Interpolated color value
//   startKey - First color key from which to interpolate
//   endKey - Second color key from which to interpolate
// Return Value:
//   Interpolated color value
// --------------------------------------------------------------------------------------
Color* Tr2ColorCurve::Interpolate( Color* out, Tr2ColorKey* startKey, Tr2ColorKey* endKey )
{
	*out = m_startValue;
	float time = (float)m_localTime;
	float deltaTime = m_length;
	Color startValue = m_startValue;
	Color endValue = m_endValue;
	unsigned int interp = m_interpolation;
	
	if ( startKey )
	{
		time -=  startKey->m_time;
		interp = startKey->m_interpolation;
	}

	switch( interp )
	{
	case LINEAR:
		{
			if ( startKey && endKey  )
			{
				startValue = startKey->m_value;
				endValue = endKey->m_value;			
				deltaTime = endKey->m_time - startKey->m_time;
			}
			else if ( startKey == NULL && endKey != NULL )
			{
				endValue = endKey->m_value;
				deltaTime = endKey->m_time;
			}
			else if ( startKey != NULL && endKey == NULL )
			{				
				startValue = startKey->m_value;
				deltaTime = m_length - startKey->m_time;
			}
			// TODO: convert Color to an XNAMath/DirectXMath compliant type.  Once done,
			// clean this silly shit up & use a single XMVectorLerp statement.
			XMVECTOR v1 = XMVectorSet( startValue.r, startValue.g, startValue.b, startValue.a );
			XMVECTOR v2 = XMVectorSet( endValue.r, endValue.g, endValue.b, endValue.a );
			XMVECTOR o = XMVectorLerp( v1, v2, time / deltaTime );
			out->r = XMVectorGetX( o );
			out->g = XMVectorGetY( o );
			out->b = XMVectorGetZ( o );
			out->a = XMVectorGetW( o );

			break;
		}
	default:
		break;
	}

	return out;
}