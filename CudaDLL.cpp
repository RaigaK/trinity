#include "StdAfx.h"
#include "CudaDLL.h"

#if CUDA_ENABLED

#if 0   // delay load the whole thing?
static HINSTANCE hCudaDLL = NULL;
static HINSTANCE hCudaRTDLL = NULL;
static bool loadTried = false;

#define DLL_IMPORT_P1( FUNC, ARG1 )											\
	typedef CUresult (* FUNC ## _t )( ARG1 );								\
	FUNC ## _t FUNC ## _p = NULL;											\
	CUresult CUDAAPI FUNC( ARG1 arg1 )												\
	{																		\
		return FUNC ## _p ? FUNC ## _p ( arg1 ) : CUDA_ERROR_INVALID_DEVICE;		\
	}

#define DLL_IMPORT_P2( FUNC, ARG1, ARG2 )									\
	typedef CUresult (* FUNC ## _t )( ARG1, ARG2 );							\
	FUNC ## _t FUNC ## _p = NULL;											\
	CUresult CUDAAPI FUNC( ARG1 arg1, ARG2 arg2 )									\
	{																		\
		return FUNC ## _p ? FUNC ## _p ( arg1, arg2 ) : CUDA_ERROR_INVALID_DEVICE;	\
	}

#define DLL_IMPORT_P3( FUNC, ARG1, ARG2, ARG3 )								\
	typedef CUresult (* FUNC ## _t )( ARG1, ARG2, ARG3 );					\
	FUNC ## _t FUNC ## _p = NULL;											\
	CUresult CUDAAPI FUNC( ARG1 arg1, ARG2 arg2, ARG3 arg3 )						\
	{																		\
		return FUNC ## _p ? FUNC ## _p ( arg1, arg2, arg3 ) : CUDA_ERROR_INVALID_DEVICE;	\
	}

#define DLL_IMPORT_P4( FUNC, ARG1, ARG2, ARG3, ARG4 )							\
	typedef CUresult (* FUNC ## _t )( ARG1, ARG2, ARG3, ARG4 );					\
	FUNC ## _t FUNC ## _p = NULL;												\
	CUresult CUDAAPI FUNC( ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4 )					\
	{																			\
		return FUNC ## _p ? FUNC ## _p ( arg1, arg2, arg3, arg4 ) : CUDA_ERROR_INVALID_DEVICE;	\
	}

#define DLL_IMPORT_P5( FUNC, ARG1, ARG2, ARG3, ARG4, ARG5 )						\
	typedef CUresult (* FUNC ## _t )( ARG1, ARG2, ARG3, ARG4, ARG5 );			\
	FUNC ## _t FUNC ## _p = NULL;												\
	CUresult CUDAAPI FUNC( ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5 )		\
	{																			\
		return FUNC ## _p ? FUNC ## _p ( arg1, arg2, arg3, arg4, arg5 ) : CUDA_ERROR_INVALID_DEVICE;	\
	}

DLL_IMPORT_P1( cuInit, unsigned );
DLL_IMPORT_P2( cuDeviceGet, CUdevice *, int );
DLL_IMPORT_P3( cuCtxCreate, CUcontext *, unsigned, CUdevice );
DLL_IMPORT_P1( cuCtxDestroy, CUcontext );

typedef const char* (*cudaGetErrorString_t)( cudaError_t );
cudaGetErrorString_t cudaGetErrorString_p = NULL;

typedef cudaError_t (*cudaGetLastError_t)();
cudaGetLastError_t cudaGetLastError_p = NULL;

void InitCudaDLL()
{
	if( loadTried )
	{
		return;
	}

	loadTried = true;

	hCudaDLL = LoadLibraryA( "cuda.dll" );
	if( hCudaDLL == NULL )
	{
		return;
	}

	hCudaRTDLL = LoadLibraryA( "cudart.dll" );
	if( hCudaRTDLL == NULL )
	{
		return;
	}

#define FIND_AND_CAST( FUNC )    FUNC ## _p = ( FUNC ## _t )GetProcAddress( hCudaDLL  , #FUNC ); if( ! FUNC ## _p ) { CCP_LOG( #FUNC " not found in cuda.dll" ); }
#define FIND_AND_CAST_RT( FUNC ) FUNC ## _p = ( FUNC ## _t )GetProcAddress( hCudaRTDLL, #FUNC ); if( ! FUNC ## _p ) { CCP_LOG( #FUNC " not found in cudart.dll" ); }

	FIND_AND_CAST( cuInit );
	FIND_AND_CAST( cuDeviceGet );
	FIND_AND_CAST( cuCtxCreate );
	FIND_AND_CAST( cuCtxDestroy );

	FIND_AND_CAST_RT( cudaGetErrorString );
	FIND_AND_CAST_RT( cudaGetLastError );
}

const char* CUDARTAPI cudaGetErrorString( cudaError_t error )
{
	if( cudaGetErrorString_p )
	{
		return cudaGetErrorString_p( error );
	}
	else
	{
		static const char* message = "No cuda DLL";
		return message;
	}
}

cudaError_t CUDARTAPI cudaGetLastError()
{
	if( cudaGetLastError_p )
	{
		return cudaGetLastError_p();
	}
	else
	{
		return cudaErrorApiFailureBase;
	}
}

#else
void InitCudaDLL() {}
#endif

#endif // #if CUDA_ENABLED
