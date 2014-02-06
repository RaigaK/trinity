#include "StdAfx.h"
#include "ALResultBlue.h"

#if BLUE_WITH_PYTHON

namespace
{

PyObject* s_ALError = nullptr;
PyObject* s_ALDeviceLostError = nullptr;
PyObject* s_ALDeviceNotAvailable = nullptr;
PyObject* s_ALOutOfMemoryError = nullptr;
PyObject* s_ALInvalidCall = nullptr;

}


// --------------------------------------------------------------------------------------
// Description:
//   Registers Python exception types for ALResult codes.
// Arguments:
//   moduleDict - trinity module __dict__
// --------------------------------------------------------------------------------------
void ALResultRegisterExceptions( PyObject* moduleDict )
{
	s_ALError = PyErr_NewException( const_cast<char*>("trinity.ALError"), PyExc_RuntimeError, nullptr );
	PyDict_SetItemString( moduleDict, "ALError", s_ALError );

	s_ALDeviceLostError = PyErr_NewException( const_cast<char*>("trinity.ALDeviceLostError"), s_ALError, nullptr );
	PyDict_SetItemString( moduleDict, "ALDeviceLostError", s_ALDeviceLostError );

	s_ALDeviceNotAvailable = PyErr_NewException( const_cast<char*>("trinity.ALDeviceNotAvailable"), s_ALError, nullptr );
	PyDict_SetItemString( moduleDict, "ALDeviceNotAvailable", s_ALDeviceNotAvailable );

	s_ALOutOfMemoryError = PyErr_NewException( const_cast<char*>("trinity.ALOutOfMemoryError"), s_ALError, nullptr );
	PyDict_SetItemString( moduleDict, "ALOutOfMemoryError", s_ALOutOfMemoryError );

	s_ALInvalidCall = PyErr_NewException( const_cast<char*>("trinity.ALInvalidCallError"), s_ALError, nullptr );
	PyDict_SetItemString( moduleDict, "ALInvalidCallError", s_ALInvalidCall );
}

// --------------------------------------------------------------------------------------
// Description:
//   Returns Python exception class for the given ALResult code.
// Arguments:
//   result - ALResult code
// Return value:
//   Python exception class appropriate for the given ALResult code
// --------------------------------------------------------------------------------------
PyObject* Be::GetException( const Result<HRESULT>& result )
{
	if( SUCCEEDED( result ) )
	{
		return nullptr;
	}
	else
	{
		switch( result.GetCategory() )
		{
		case Result<HRESULT>::INVALID_CALL:
			return s_ALInvalidCall;
		case Result<HRESULT>::DEVICE_LOST:
			return s_ALDeviceLostError;
		case Result<HRESULT>::DEVICE_NOT_AVAILABLE:
			return s_ALDeviceNotAvailable;
		case Result<HRESULT>::OUT_OF_MEMORY:
			return s_ALOutOfMemoryError;
		default:
			return s_ALError;
		}
	}
}

#endif
