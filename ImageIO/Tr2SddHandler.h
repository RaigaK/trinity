#pragma once

#ifndef Tr2SddHandler_h_
#define Tr2SddHandler_h_

#include "blue/include/IBluePersist.h"
#include "Tr2ImageHandler.h"
#include "Tr2SddHeader.h"

// Forward declarations
class TriTextureRes;

class Tr2SddHandler : public Tr2ImageHandler
{
public:
	Tr2SddHandler( const wchar_t* sourceName = 0 );
	~Tr2SddHandler();

	// Read header from source stream. Returns true if a valid header was read.
	bool ReadHeader();

	bool IsSaveSupported( const Tr2BitmapDimensions& size );
	virtual bool Save( const Tr2HostBitmap& image, IBlueStream* output );

	// Construct DDS header from the texture's format and parameters
	bool BuildHeader( const Tr2BitmapDimensions& bd );

	// Returns true if the texture format is support by the device (or the loader
	// can convert to a supported format while loading)
	// Assumes that header has been successfully read, and determined to be 
	// valid - only call after ReadHeader returns true.
	bool IsSupported();

	// Returns the format of the texture being loaded.
	// Assumes that header has been successfully read, and determined to be 
	// valid - only call after ReadHeader returns true.
	Tr2RenderContextEnum::PixelFormat GetFormat() const;

	// Reads data from source stream. 
	// Assumes that header has been successfully read, and determined to be 
	// valid - only call after ReadHeader returns true.
	bool ReadImage();

	

	// Call this before loading first texture to determine texture formats supported.
	//static void CacheSupportedFormats();

	unsigned GetBlockByteSize() const;

	bool IsCubeTexture() const;
	bool IsVolumeTexture() const;

	virtual unsigned GetOffset( unsigned mipLevel, unsigned face ) const;

protected:
	virtual bool Convert24BitTo32Bit();
	
private:
	
	Tr2SddHeader	m_header;
	void CopyHeaderValuesToMembers();	// from m_header to the base m_width etc.. members

	//static D3DFORMAT FindD3D9Format( const DDS_PIXELFORMAT& pf );
};

#endif
