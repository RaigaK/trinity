#pragma once
#ifndef CudaDLL_h
#define CudaDLL_h

#if EVALUATION_SDKS_ENABLED
#	define CUDA_ENABLED	1
#endif

#if CUDA_ENABLED

void InitCudaDLL();

//#define RTAPI
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cudad3d9.h>
#include <cuda_d3d9_interop.h>


#endif // CUDA_ENABLED

#endif	// CudaDLL_h
