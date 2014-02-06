#include "StdAfx.h"
#include "TriUtil.h"

#ifdef _WIN32

#include <dxerr.h>
const char* GetHresultString( HRESULT hr )
{
	return DXGetErrorStringA( hr );
}

void ManualReportHresultError( const char* fileName, int lineNumber, const char* message, HRESULT hr )
{
	const char* msgFormat = "%s(%d) : reported an error %s\n - %s\n";
	const char* errorString = GetHresultString( hr );
	const int bufferSize = 1024;
	char buffer[ bufferSize ] = "";
	_snprintf_s( buffer, bufferSize, _TRUNCATE, msgFormat, fileName, lineNumber, errorString, message );
	OutputDebugString( buffer );
}

void ReportManagedStateError( const char* fileName, int lineNumber, const char* stateName, const char* stateValue, const char* techniqueName )
{
	CCP_LOGERR( "%s(%d) : '%s' did not leave the managed render state %s as %s", fileName, lineNumber, techniqueName, stateName, stateValue );
}

#endif