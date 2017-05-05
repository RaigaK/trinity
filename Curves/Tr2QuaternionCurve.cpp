#include "StdAfx.h"
#include "Tr2QuaternionCurve.h"

// --------------------------------------------------------------------------------------
// Description:
//   Quaternion key comparison function.
// Arguments:
//   context - ignored
//   a - First quaternion key comparison operand
//   b - Second quaternion key comparison operand
// Return Value:
//   true, if key a's time is less that key b's time
//   false, otherwise
// --------------------------------------------------------------------------------------
static bool CompareKeys( IRoot* context, Tr2QuaternionKey* a, Tr2QuaternionKey* b )
{
	return a->m_time < b->m_time;
}



// --------------------------------------------------------------------------------------
// Description:
//   Default constructor.
// --------------------------------------------------------------------------------------
Tr2QuaternionKey::Tr2QuaternionKey( IRoot* lockobj ) 
{
	m_value = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
	m_time = 0.0f;
	m_interpolation = SPHERICAL_LINEAR;
}



// --------------------------------------------------------------------------------------
// Description:
//   Default constructor.
// --------------------------------------------------------------------------------------
Tr2QuaternionCurve::Tr2QuaternionCurve( IRoot* lockobj ) :
	Tr2Curve<Tr2QuaternionKey, PTr2QuaternionKeyVector, Quaternion>( lockobj )
{
	m_interpolation = SPHERICAL_LINEAR;
	m_startValue = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
	m_endValue = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
	m_currentValue = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
}

// --------------------------------------------------------------------------------------
// Description:
//   Private virtual function to add a quaternion key at a particular time.
// Arguments:
//   time - The time at which to add the key
//   value - The quaternion value for the key
// --------------------------------------------------------------------------------------
void Tr2QuaternionCurve::AddKey_( float time, const Quaternion& value )
{
	Tr2QuaternionKeyPtr key;
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
//  Sorts the quaternion keys into ascending order based on key time.
// --------------------------------------------------------------------------------------
void Tr2QuaternionCurve::Sort()
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
			Tr2QuaternionKey* back = m_keys.back();
			float preLength = m_length;
			Quaternion endValue = m_endValue;

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
//   Interpolates between two quaternion keys using the curve's internal time as the 
//   interpolation control factor.
// Arguments:
//   out - [output] Interpolated quaternion value
//   startKey - First quaternion key from which to interpolate
//   endKey - Second quaternion key from which to interpolate
// Return Value:
//   Interpolated quaternion value
// --------------------------------------------------------------------------------------
Quaternion* Tr2QuaternionCurve::Interpolate( 
	Quaternion* out, 
	Tr2QuaternionKey* startKey, 
	Tr2QuaternionKey* endKey )
{
	*out = m_startValue;
	float time = m_localTime;
	float deltaTime = m_length;
	Quaternion startValue = m_startValue;
	Quaternion endValue = m_endValue;
	unsigned int interp = m_interpolation;
	if ( startKey )
	{
		interp = startKey->m_interpolation;
		time -=  startKey->m_time;
	}

	switch( interp )
	{
	case SPHERICAL_LINEAR:
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
			*out = XMQuaternionSlerp( startValue, endValue, time / deltaTime );
			break;
		}
	default:
		break;
	}

	return out;
}