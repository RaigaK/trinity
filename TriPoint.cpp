#include "StdAfx.h"
#include "TriPoint.h"

/////////////////////////////////////////////////////////////////////////////////////////
// IPythonMethods Impl
/////////////////////////////////////////////////////////////////////////////////////////

#if BLUE_WITH_PYTHON
void TriPoint::Destroy(
	)
{
	//delete this;
}


PyObject* TriPoint::GetAttr( 
	const char* name, 
	bool* handled
	)
{
	return 0;
}


bool TriPoint::SetAttr(
	const char* name, 
	PyObject* v, 
	bool* handled 
	)
{
	return true;
}


PyObject* TriPoint::Repr(
	bool* handled
	)
{
	*handled = true;
	char buf[120];
	sprintf_s(buf, "<Instance of 'TriPoint' (x=%d y=%d)>", x, y);
	return PyString_FromString(buf);
}


/////////////////////////////////////////////////////////////////////////////////////////
// TriColor
/////////////////////////////////////////////////////////////////////////////////////////

TriPoint::TriPoint(IRoot* lockobj)	
{
	SetXY(0,0);
}


TriPoint::~TriPoint()
{
}


/////////////////////////////////////////////////////////////////////////////////////////
// ITriColor Impl
/////////////////////////////////////////////////////////////////////////////////////////

void TriPoint::SetXY(
	int32_t _x,
	int32_t _y
	)
{
	x = _x;
	y = _y;
}

void TriPoint::SetPoint(
    const ::Point* c
	)
{
	x = c->x;
	y = c->y;
}


const ::Point* TriPoint::GetPoint(
	) const
{
	return this; 
}

::Point* TriPoint::CopyPoint(
    ::Point* in
	) const
{
	// would this work?
	//return &(*in = *this);
	*in = *this;
	return in;
}

::Point* TriPoint::Point(
	)
{
	return this;
}

void TriPoint::PySetPoint( Be::Optional<int32_t> _x, Be::Optional<int32_t> _y )
{		
	if( _x.IsAssigned() )
	{
		x = _x;
	}
	if( _y.IsAssigned() )
	{
		y = _y;
	}
}

#endif
