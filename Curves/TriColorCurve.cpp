#include "StdAfx.h"
#include "TriColorCurve.h"
#include <float.h>

TriColorCurve::TriColorCurve(IRoot* lockobj) :
	mStart         ( 0           ), 
	mLength        ( 0.0f        ),
	mExtrapolation ( TRIEXT_NONE ),
	mCurrKey       ( 1           ),
	mValue( 0.0f, 0.0f, 0.0f, 0.0f ),
	PARENTLOCK(mKeys, ITriColorCurve)
{	
	mKeys.SetNotify(this);
	mUseHSV = false;
}


TriColorCurve::~TriColorCurve()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// ITriFunction
/////////////////////////////////////////////////////////////////////////////////////

Color* TriColorCurve::Update(
	Color* in,
	Be::Time t
	)
{	
	GetValueAt(&mValue, t);
	*in = mValue;
	return in;
}

Color* TriColorCurve::Update(
	Color* in,
	double t
	)
{
	GetValueAt(&mValue, t);
	*in = mValue;
	return in;
}


Color* TriColorCurve::GetValueAt(
	Color* in,
	Be::Time now
	)
{
	if(mLength)
	{
		GetValueAt(in, TimeAsDouble(now - mStart));
	}
	else
	{
		*in = mValue;
	}
	return in;
}


Color* TriColorCurve::GetValueAt(
	Color* in,
	double pos
	)
{	
	if(mLength == 0.0f)
	{// there is no curve
		*in = mValue;
		return in;
	}

	// No gradient for Quaternions
	if ( (pos >= mKeys.back()->mTime) )
	{// the curve is over, pos is after the last key
		if (mExtrapolation == TRIEXT_NONE)
		{
			*in = mValue;
			return in;
		}
		else if (mExtrapolation == TRIEXT_CONSTANT)
		{
			*in = mKeys.back()->mValue;
			return in;
		}
		else if (mExtrapolation == TRIEXT_GRADIENT)
		{
			TriColorKey& ck = *mKeys.back();
			*in = ck.mValue + (float)(pos - ck.mTime) * ck.mRight;
			return in;
		}
		else
		{// (mExtrapolation == TRIEXT_CYCLE)
			pos = fmod(pos, (double)mKeys.back()->mTime);
		}
	}
	else if ( (pos < 0.0) || (pos <= (mKeys[0]->mTime)) )
	{// the curve hasn't begun or pos is before or equal to the first key
		if (mExtrapolation == TRIEXT_NONE)
		{
			*in = mValue;
			return in;
		}
		else if (mExtrapolation == TRIEXT_CONSTANT)
		{
			*in = mKeys[0]->mValue;
			return in;
		}
		else if (mExtrapolation == TRIEXT_GRADIENT)
		{
			TriColorKey& ck = *mKeys[0];
			*in = ck.mValue + (float)(pos * mLength - ck.mTime) * ck.mLeft;
			return in;
		}
		else 
		{// (mExtrapolation == TRIEXT_CYCLE)
			*in = mKeys[0]->mValue;
			return in;
		}
	}	

	// sanity check length before accessing
	if( mCurrKey >= (int)mKeys.size() )
	{
		*in = mValue;
		return in;
	}

	TriColorKey* ck_1 = mKeys[mCurrKey - 1];	
	TriColorKey* ck = mKeys[mCurrKey];	
	while((pos >= ck->mTime) || (pos < ck_1->mTime))
	{		
		if (pos < ck_1->mTime)
		{// "cache miss" need to search from the beginning
			mCurrKey = 0;
		}		
		mCurrKey++;
		ck_1 = mKeys[mCurrKey - 1];
		ck = mKeys[mCurrKey];				
	}	

	// Find the normalized time
	float nt = (float)(pos - ck_1->mTime) / float(ck->mTime - ck_1->mTime);
	if (ck_1->mInterpolation == TRIINT_CONSTANT)
	{
		*in = ck_1->mValue;
	}
    else
	{// color works only as linear now
        D3DXColorLerp(in, &ck_1->mValue, &ck->mValue, nt);
	}
	return in;
}

/////////////////////////////////////////////////////////////////////////////////////////
// compare function
/////////////////////////////////////////////////////////////////////////////////////////
static bool CompareKeys(IRoot* context, TriQuaternionKey* a, TriQuaternionKey* b)
{
	return a->mTime < b->mTime;
}

void TriColorCurve::AddKey(
	float t,
	const Color& v, 
	const Color& l, 
	const Color& r, 
	TRIINTERPOLATION i
	)
{	
	TriColorKeyPtr k;
	k.CreateInstance();

	k->mTime = t;
	k->mValue = v;
	k->mLeft = l;
	k->mRight = r;
	k->mInterpolation = i;

	mKeys.Insert( -1, k );
	Sort();
}

void TriColorCurve::Sort(
	)
{
	if( mKeys.empty() )
	{
		mLength = 0.0f;
	}
	else
	{
		mKeys.Sort((IList::CompareFn)CompareKeys, NULL);
		mLength = (float) (mKeys.back()->mTime - mKeys[0]->mTime);
	}
}


void TriColorCurve::ScaleTime(
	float s
	)
{
	if(mKeys.GetSize() >= 2)
	{
		for(int i=0; i< mKeys.GetSize();i++)
		{
			mKeys[i]->mTime *= s;
		}
		mLength = (float) (mKeys.back()->mTime - mKeys[0]->mTime);
	}
}

void TriColorCurve::Reverse(
	)
{
	if(mKeys.GetSize() >= 2)
	{
		for(int i=0; i< mKeys.GetSize();i++)
		{
			mKeys[i]->mTime = mLength - mKeys[i]->mTime;
		}
	}
	Sort();
}

void TriColorCurve::ScaleValue(
	float s
	)
{
	for(int i=0; i< mKeys.GetSize();i++)
	{
		mKeys[i]->mValue *= s;
	}
}

float TriColorCurve::Length(
	)
{
	return mLength;
}

Be::Time TriColorCurve::Start(
	)
{
	return mStart;
}

void TriColorCurve::SetStartTime(
	Be::Time startTime
	)
{
	mStart = startTime;
}

TRIEXTRAPOLATION TriColorCurve::Extrapolation()
{
	return mExtrapolation;
}

void TriColorCurve::OnListModified(
	long event,
	ssize_t key,
	ssize_t key2,
	IRoot* currvalue,
	const IList* theList
	)
{
	//TriScalarKey* skey = (TriScalarKey*)currvalue;

	switch(event & BELIST_EVENTMASK)
	{

	case BELIST_REMOVED:
		if(event & BELIST_LOADING)
		{
			return;
		}
		else
		{
			if( mKeys.GetSize() > 1 )
			{				
				if ( key == 0 )
				{
					mKeys[1]->mTime = 0.0f;
					Sort();
				}
				else
				{
					mLength = (float) (mKeys.back()->mTime - mKeys[0]->mTime);
				}
			}
			else
			{
				// Although one would think that the code here below would make sense
				// it fucks with the loading of the curve as the length is messed up
				// the reader/writer is redundantly calling clear key == -1 when loading a 
				// curve and not flagging with BELIST_LOADING :-(
				//else
				//{
				//	mLength = 0.0f;
				//}
				if ( key == 0 )
				{
					mLength = 0.0f;
				}	
				mCurrKey = 1;
			}	
		}
		break;

	case BELIST_LOADFINISHED:
		if( mKeys.empty() )
		{
			mLength = 0.f;
		}
		else if( fabs( mLength - ( mKeys.back()->mTime - mKeys[0]->mTime ) ) > FLT_EPSILON )
		{
			CCP_LOGWARN(
				"The curve %S length (%f) does not match the key length (%f), this has been fixed",
				mName.c_str(), mLength, (mKeys.back()->mTime - mKeys[0]->mTime)
				);		
			Sort();
		}
		break;

	case BELIST_UNLOADSTART:
		mLength = 0.0;
		mCurrKey = 1;
		break;
	}
}



#if BLUE_WITH_PYTHON
PyObject* TriColorCurve::PyAddKey(PyObject* args)
{	

	float t; 
	PyObject* v; 
	PyObject* l; 
	PyObject* r; 
	TRIINTERPOLATION i;

	if (!PyArg_ParseTuple(args, "fOOOi", 
		&t, &v, &l, &r, &i))
		return NULL;

	Color colorVal;
	Color colorLeft;
	Color colorRight;


	if( !BlueExtractVector( v, (float*)&colorVal, 4 ) )
	{
		ITriColorPtr iv( v );
		if( iv )
		{
			colorVal = *iv->GetColor();
		}
		else
		{
			PyErr_SetString( PyExc_TypeError, "Color value must be a 4-tuple or a TriColor" );
			return NULL;
		}
	}

	if( !BlueExtractVector( l, (float*)&colorLeft, 4 ) )
	{
		ITriColorPtr il( l );
		if( il )
		{
			colorLeft = *il->GetColor();
		}
		else
		{
			PyErr_SetString( PyExc_TypeError, "Color left must be a 4-tuple or a TriColor" );
			return NULL;
		}
	}

	if( !BlueExtractVector( r, (float*)&colorRight, 4 ) )
	{
		ITriColorPtr ir( r );
		if( ir )
		{
			colorRight = *ir->GetColor();
		}
		else
		{
			PyErr_SetString( PyExc_TypeError, "Color right must be a 4-tuple or a TriColor" );
			return NULL;
		}
	}

    AddKey( t, colorVal, colorLeft,	colorRight,	i );
	
	Py_INCREF(Py_None);
	return Py_None;
}

PyObject* TriColorCurve::PyGetKey(PyObject* args)
{	
	int index;
	if (!PyArg_ParseTuple(args, "i", &index))
		return NULL;

	// Check the length of the keys list
	if ( index < 0 || index >= (int)mKeys.size())
	{
		PyErr_SetString( PyExc_TypeError, "Index out of range");
		return NULL;
	}

	// Wrap the key and return		
	TriColorKey* key = new OTriColorKey;
	TriColorKey* src = mKeys[index];
	*key = *src;

	PyObject* pyKey = PyOS->WrapBlueObject(key);
	key->Unlock();

	return pyKey;
}

PyObject* TriColorCurve::PySetKey(PyObject* args)
{	
	//ITriQuaternionKey
	int index;
	PyObject* pyKey = NULL;
	if (!PyArg_ParseTuple(args, "iO", &index, &pyKey))
		return NULL;

	// Check the length of the keys list
	if ( index < 0 || index >= (int)mKeys.size())
	{
		PyErr_SetString( PyExc_TypeError, "Index out of range");
		return NULL;
	}

	TriColorKey* src = BluePythonCast<TriColorKey*>( pyKey );
	TriColorKey* t = mKeys[index];
	*t = *src;

	Sort();	

	Py_INCREF(Py_None);
	return Py_None;
}

PyObject* TriColorCurve::PyRemoveKey(PyObject* args)
{	
	int index;
	if (!PyArg_ParseTuple( args, "i", &index ))
		return NULL;

	// Check the length of the keys list
	if ( index < 0 || index >= (int)mKeys.size())
	{
		PyErr_SetString( PyExc_TypeError, "Index out of range");
		return NULL;
	}

	mKeys.Remove(index);	

	// If we removed the start key
	if ( mKeys.size() > 0 && index == 0 )
	{
		mKeys[0]->mTime = 0.0f;
	}

	Sort();


	Py_INCREF(Py_None);
	return Py_None;
}
#endif

double TriColorCurve::GetCurrentPos( Be::Time time )
{	
	double t = TimeAsDouble( time - mStart );
	t = fmod( t, (double)mLength );
	return t;
}




