////////////////////////////////////////////////////////////
//
//    Created:   May 2015
//    Copyright: CCP 2015
//

#include "StdAfx.h"
#include "Tr2ToggleCurve.h"

Tr2ToggleKey::Tr2ToggleKey( IRoot* lockobj ) 
{
	m_value = false;
	m_time = 0.0f;
}

// --------------------------------------------------------------------------------------
// Description:
//   Toggle key comparison function.
// Arguments:
//   context - ignored
//   a - First toggle key comparison operand
//   b - Second toggle key comparison operand
// Return Value:
//   true, if key a's time is less that key b's time
//   false, otherwise
// --------------------------------------------------------------------------------------
static bool CompareKeys( IRoot* context, Tr2ScalarKey* a, Tr2ScalarKey* b )
{
	return a->m_time < b->m_time;
}

// --------------------------------------------------------------------------------------
// Description:
//   Default constructor.
// --------------------------------------------------------------------------------------
Tr2ToggleCurve::Tr2ToggleCurve( IRoot* lockobj ): 
	Tr2Curve<Tr2ToggleKey, PTr2ToggleKeyVector, bool>( lockobj )
{
}

bool Tr2ToggleCurve::Initialize()
{
	return true;
}


// --------------------------------------------------------------------------------------
// Description:
//  Sorts the toggle keys into ascending order based on key time.
// --------------------------------------------------------------------------------------
void Tr2ToggleCurve::Sort()
{
	if( !m_keys.empty() )
	{
		if( m_keys.size() > 1 )
		{
			m_keys.Sort( ( IList::CompareFn )CompareKeys, NULL );
		}
		// We might have added a key passed the length of the curve
		if( m_keys.back()->m_time > m_length )
		{
			auto back = m_keys.back();
			float preLength = m_length;
			auto endValue = m_endValue;

			m_length = back->m_time;
			m_endValue = back->m_value;
			if( preLength > 0.0f )
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
//   Private virtual function to add a toggle key at a particular time.
// Arguments:
//   time - The time at which to add the key
//   value - The toggle value for the key
// --------------------------------------------------------------------------------------
void Tr2ToggleCurve::AddKey_( float time, const bool& value )
{
	Tr2ToggleKeyPtr key;
	if( !key.CreateInstance() )
	{
		return;
	}

	key->m_time = time;
	key->m_value = value;
	m_keys.Insert( -1, key );
}

// --------------------------------------------------------------------------------------
// Description:
//	 Returns the lastKey value or the curves startvalue if the curve is playing the first key
// Arguments:
//   out - [output] Current curve value
//   startKey - First toggle key 
//   endKey - Second toggle key (not used)
// Return Value:
//   Current curve value
// --------------------------------------------------------------------------------------
bool* Tr2ToggleCurve::Interpolate( bool* out, Tr2ToggleKey* lastKey, Tr2ToggleKey* nextKey )
{
	if( lastKey )
	{
		*out = lastKey->m_value;
	}
	else
	{
		*out = m_startValue;
	}

	return out;
}