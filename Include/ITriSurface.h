/* 
	*************************************************************************

	ITriSurface.h

	Author:    Hilmar Veigar Pétursson
	Created:   November 2001
	OS:        Win32
	Project:   Trinity

	Description:   

		Hemm...


	Dependencies:

		Blue, Trinity

	(c) CCP 2000

	*************************************************************************
*/

#ifndef _ITRISURFACE_H_
#define _ITRISURFACE_H_

#include <d3d9.h>
#include <d3dx9tex.h>

BLUE_INTERFACE(ITriSurface) : public IRoot
{
	virtual IDirect3DSurface9* GetSurface(
		) = 0;

	virtual bool SetSurface(
		IDirect3DSurface9*
		) = 0;

	virtual void SetSharedHandle(
		HANDLE
		) = 0;

	virtual bool CopySurfaceTo(
		IDirect3DSurface9* in
		) = 0;

	virtual const D3DSURFACE_DESC* GetDesc(		
		) = 0;

	virtual bool LockBuffer(			
		) = 0;	

	virtual bool SetPixel(
		int width,
		int height, 
		void* val
		) = 0;

	virtual bool GetPixel(
		int width,
		int height, 
		void* val
		) = 0;

	virtual bool FlushBuffer(
		) = 0;

	virtual D3DLOCKED_RECT* GetLockedRect(
		) = 0;

	virtual bool ChangeFormat(
		D3DFORMAT fmat
		) = 0;
	
	virtual bool SaveSurfaceToFile(
		LPCWSTR                  pDestFile,
		D3DXIMAGE_FILEFORMAT     DestFormat,
		CONST PALETTEENTRY*      pSrcPalette,
		CONST RECT*              pSrcRect
		) = 0;

	virtual bool SaveSurfaceToFileInMemory(
		LPD3DXBUFFER			 *ppDestBuffer,
		D3DXIMAGE_FILEFORMAT     DestFormat,
		CONST PALETTEENTRY*      pSrcPalette,
		CONST RECT*              pSrcRect
		) = 0;

	//the D3DXLoadSurfaceFromFile() function
	virtual bool LoadSurfaceFromFile(
		CONST PALETTEENTRY		 *pDestPalette,
		CONST RECT				 *pDestRect,
		LPCWSTR					 pSrcFile,
		CONST RECT				 *pSrcRect,
		uint32_t				 Filter,
		D3DCOLOR				 ColorKey,
		D3DXIMAGE_INFO			 *pSrcInfo
		) = 0;

	virtual bool LoadSurfaceFromFileInMemory(
		CONST PALETTEENTRY		 *pDestPalette,
		CONST RECT				 *pDestRect,
		LPCVOID					 pSrcData,
		UINT					 SrcData,
		CONST RECT				 *pSrcRect,
		uint32_t				 Filter,
		D3DCOLOR				 ColorKey,
		D3DXIMAGE_INFO			 *pSrcInfo
		) = 0;
};


#endif