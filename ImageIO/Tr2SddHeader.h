#pragma once

#ifndef Tr2SddHeader_h_
#define Tr2SddHeader_h_

// Forward declarations
class TriTextureRes;

#pragma pack( push )
#pragma pack( 1 )
struct Tr2SddHeader
{
	static const unsigned ms_currentVersion = 1;

	// preserved from original dds
	struct DDS_PIXELFORMAT
	{
		uint32_t dwSize;
		uint32_t dwFlags;
		uint32_t dwFourCC;
		uint32_t dwRGBBitCount;
		uint32_t dwRBitMask;
		uint32_t dwGBitMask;
		uint32_t dwBBitMask;
		uint32_t dwABitMask;
	};

	char		m_magic[4];	// 'SDD '

	static void SetMagic  ( char* dst )       {        dst[0] =  'S';   dst[1] =  'D';   dst[2] =  'D';   dst[3] =  ' '; }
	static bool CheckMagic( const char* dst ) { return dst[0] == 'S' && dst[1] == 'D' && dst[2] == 'D' && dst[3] == ' '; }

	unsigned	m_version;
	unsigned	m_width;
	unsigned	m_height;
	unsigned	m_depth;
	unsigned	m_mipmapCount;
	
	// any cut out rectangles; specified in 0...1 range
	float		m_cutoutX;
	float		m_cutoutY;
	float		m_cutoutWidth;
	float		m_cutoutHeight;

	enum SddCompressionType
	{
		NONE,

		// 8 byte per block:
		DXT1,
		ATI1,
		
		// 16 bytes per block:
		DXT2,
		DXT3,
		DXT4,
		ATI2,
		DXT5
	};

	SddCompressionType	m_compressionType;

	DDS_PIXELFORMAT ddspf;

	bool	m_cubeMap;
	bool	m_reserved1[3];

	unsigned	m_reserved[10];
};
#pragma pack( pop )

#endif
