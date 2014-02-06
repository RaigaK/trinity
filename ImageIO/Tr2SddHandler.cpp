#include "StdAfx.h"
#include "Tr2SddHandler.h"
#include "Resources/TriTextureRes.h"
#include "Tr2DdsHandler.h"				// go grab MakePixelFormat
#include <blue/include/IBlueResMan.h>
#include <cctype>
#include "Tr2HostBitmap.h"

Tr2SddHandler::Tr2SddHandler( const wchar_t* sourceName ) : 
	Tr2ImageHandler( sourceName )	
{
}

Tr2SddHandler::~Tr2SddHandler()
{
}

bool Tr2SddHandler::ReadHeader()
{
	if( m_source->Read( &m_header, sizeof( m_header ) ) == -1 )
	{
		return false;
	}

	// BeResMan->AddTextureDataRead( sizeof( m_header ) );

	if( !m_header.CheckMagic( m_header.m_magic ) )
	{
		CCP_LOGERR( "Tr2SddHandler: not a valid .sdd file (%S)", m_sourceName.c_str() );
		return false;
	}

	const unsigned currentVersion = 1;
	if( m_header.m_version != currentVersion )
	{
		CCP_LOGERR( "Tr2SddHandler: wrong version, %d instead of %d (%S)", m_header.m_version, currentVersion, m_sourceName.c_str() );
		return false;
	}

	if( !m_header.m_width || !m_header.m_height )
	{
		CCP_LOGERR( "Tr2SddHandler: invalid dimensions %d x %d (%S)", m_header.m_width, m_header.m_height, m_sourceName.c_str() );
		return false;
	}
	
	CopyHeaderValuesToMembers();

	return true;
}

void Tr2SddHandler::CopyHeaderValuesToMembers()
{
	m_width			= m_header.m_width;
	m_height		= m_header.m_height;
	m_bitsPerPixel	= m_header.ddspf.dwRGBBitCount;
	m_mipLevelCount = m_header.m_mipmapCount;

	//TODO do we want this?
	/*
	if( m_header.dwHeaderFlags & DDS_HEADER_FLAGS_VOLUME )
	{
		m_volumeDepth = m_header.dwDepth;
	}
	else*/
	{
		m_volumeDepth = 1;
	}
}

bool Tr2SddHandler::ReadImage()
{
	CCP_STATS_ZONE( __FUNCTION__ );

	unsigned int size = GetTotalDataSize();

	if( size == 0 )
	{
		return false;
	}

	// The format is in reverse, so instead of seeking, we read less
	unsigned int skipCount = 0;
	unsigned int mipCount = m_header.m_mipmapCount;
	GetMipLevelRange( skipCount, mipCount );
	
	if( m_header.m_mipmapCount > mipCount )
	{		
		unsigned int dropBytes = 0;
		CopyHeaderValuesToMembers();
		for( unsigned i = 0; i != skipCount; ++i )
		{
			dropBytes += GetMipLevelSize( i );
		}
		if( IsCubeTexture() )
		{
			dropBytes *= 6;
		}

		size -= dropBytes;

		// We now fudge the header to comply with these mip map adjustments
		m_header.m_mipmapCount	= mipCount;
		m_header.m_width		>>= skipCount;
		m_header.m_height		>>= skipCount;
		CopyHeaderValuesToMembers();

	}

	m_data = (uint8_t*)CCP_MALLOC( "Tr2SddHandler/m_data", size );

    if( !m_data )
    {
		CCP_LOGERR( "Tr2SddHandler couldn't allocate %d bytes (%S)", size, m_sourceName.c_str() );
        return false;
    }

	if( m_source->Read( m_data, size ) == -1 )
	{
		CCP_LOGERR( "Tr2SddHandler couldn't read %d bytes (%S)", size, m_sourceName.c_str() );
		CCP_FREE( m_data );
		m_data = NULL;
		return false;
	}

	// BeResMan->AddTextureDataRead( size );

	if( m_header.ddspf.dwRGBBitCount == 24       &&
		m_header.ddspf.dwRBitMask    == 0xFF0000 &&
		m_header.ddspf.dwGBitMask    == 0xFF00   &&
		m_header.ddspf.dwBBitMask    == 0xFF     &&
		m_header.ddspf.dwABitMask    == 0 )
	{
		Convert24BitTo32Bit();
	}

	return true;
}

unsigned Tr2SddHandler::GetBlockByteSize() const
{
	switch( m_header.m_compressionType )
	{
		case Tr2SddHeader::DXT1:
		case Tr2SddHeader::ATI1:
			return 8;

		case Tr2SddHeader::DXT2:
		case Tr2SddHeader::DXT3:
		case Tr2SddHeader::DXT4:
		//case m_header.RXGB:
		case Tr2SddHeader::ATI2:
		case Tr2SddHeader::DXT5:
			return 16;

		case Tr2SddHeader::NONE:
			return 0;
	};

	CCP_ASSERT( false && "Unknown compression type in GetBlockByteSize" );	// forgot to increment a version number?
	return 0;
}

bool Tr2SddHandler::IsCubeTexture() const
{
	return m_header.m_cubeMap;
}

bool Tr2SddHandler::IsVolumeTexture() const
{
	//return m_header.dwHeaderFlags & DDS_HEADER_FLAGS_VOLUME ? true : false;
	return false;	//TODO want this?
}

bool Tr2SddHandler::IsSupported()
{
	/*
	D3DFORMAT fmt = FindD3D9Format( m_header.ddspf );
	if( s_supportedFormats.find( fmt ) != s_supportedFormats.end() )
	{
		return true;
	}
	else
	{
		const char* fmtName = "<unknown>";
		FormatNameMap::iterator it = s_formatNames.find( fmt );
		if( it != s_formatNames.end() )
		{
			fmtName = it->second;
		}
		CCP_LOGWARN( "Tr2SddHandler: '%s' in unsupported format (%s)\n", GetSourceNameA(), fmtName );
		return false;
	}
*/
	return true;	// We're not supposed to preprocess anything funky
}

Tr2RenderContextEnum::PixelFormat Tr2SddHandler::GetFormat() const
{
	// http://msdn.microsoft.com/en-us/library/windows/desktop/cc308051%28v=vs.85%29.aspx

	using namespace Tr2RenderContextEnum;

	switch( m_header.m_compressionType )
	{
		case Tr2SddHeader::DXT1:
		case Tr2SddHeader::ATI1:
			return PIXEL_FORMAT_BC1_UNORM;

		case Tr2SddHeader::DXT2:
		case Tr2SddHeader::DXT3:
			return PIXEL_FORMAT_BC2_UNORM;

		case Tr2SddHeader::DXT4:
		//case m_header.RXGB:
		case Tr2SddHeader::ATI2:
		case Tr2SddHeader::DXT5:
			return PIXEL_FORMAT_BC3_UNORM;

		case Tr2SddHeader::NONE:
			{
				if( m_header.ddspf.dwRGBBitCount == 8 )
				{
					if( m_header.ddspf.dwRBitMask == 8 )
					{
						return PIXEL_FORMAT_R8_UNORM;
					}
					if( m_header.ddspf.dwABitMask == 8 )
					{
						return PIXEL_FORMAT_A8_UNORM;
					}
				}
			}
			return PIXEL_FORMAT_B8G8R8A8_UNORM;
	}
	CCP_ASSERT( false && "Unknown compression type in GetFormat" );	// forgot to increment a version number?
	return PIXEL_FORMAT_B8G8R8A8_UNORM;
}

bool Tr2SddHandler::Convert24BitTo32Bit()
{
	//TODO convert in the tool and avoid this altogether?  ...larger files though.
	if( !Tr2ImageHandler::Convert24BitTo32Bit() )
	{
		return false;
	}
			
	m_header.ddspf.dwRGBBitCount = 32;
	return true;
}

unsigned Tr2SddHandler::GetOffset( unsigned mipLevel, unsigned face ) const
{
	CCP_ASSERT( !m_header.m_mipmapCount || mipLevel < m_header.m_mipmapCount );
	if( m_header.m_mipmapCount && mipLevel >= m_header.m_mipmapCount )
	{
		return 0;
	}

	unsigned offset = 0;
	if( m_header.m_mipmapCount )
	{
		const unsigned numFaces = m_header.m_cubeMap ? 6 : 1;
		for( unsigned int i = m_header.m_mipmapCount; i != mipLevel+1 ; --i )
		{
			offset += GetMipLevelSize( i - 1 ) * numFaces;
		}
	}
	if( face )
	{
		offset += GetMipLevelSize( mipLevel ) * face;
	}
	return offset;
}

bool Tr2SddHandler::IsSaveSupported( const Tr2BitmapDimensions& bd )
{
	if( bd.GetType() == Tr2RenderContextEnum::TEX_TYPE_3D )
	{
		return false;
	}

	Tr2DdsHandler::DDS_PIXELFORMAT ddspf;
	if( !Tr2DdsHandler::MakePixelFormat( ddspf, bd ) )
	{
		CCP_LOGERR( "Texture has a unsupported pixelformat %d", bd.GetFormat() );
		return false;
	}

	return true;
}

bool Tr2SddHandler::BuildHeader( const Tr2BitmapDimensions& bd )
{
	memset( &m_header, 0, sizeof( m_header ) );

	m_header.SetMagic( m_header.m_magic );
	m_header.m_version = m_header.ms_currentVersion;

	m_header.m_width  = bd.GetWidth();
	m_header.m_height = bd.GetHeight();
	m_header.m_depth  = 0;
	m_header.m_mipmapCount = bd.GetMipCount();

	if( !Tr2DdsHandler::MakePixelFormat( reinterpret_cast<Tr2DdsHandler::DDS_PIXELFORMAT&>( m_header.ddspf ), bd ) )
	{
		CCP_LOGERR( "Texture has a unsupported pixelformat %d", bd.GetFormat() );
		return false;
	}

	#define DDS_FOURCC 0x00000004
	if( m_header.ddspf.dwFlags & DDS_FOURCC )
	{
		// Note: bit of copy paste here with the sddtool. Not the end of the world as these are practically carved in stone.
		const std::pair<unsigned, Tr2SddHeader::SddCompressionType> supported[] =
		{
			std::make_pair( MAKEFOURCC('D', 'X', 'T', '1'), Tr2SddHeader::DXT1 ) ,
			std::make_pair( MAKEFOURCC('A', 'T', 'I', '1'), Tr2SddHeader::ATI1 ) ,
			std::make_pair( MAKEFOURCC('D', 'X', 'T', '2'), Tr2SddHeader::DXT2 ) ,
			std::make_pair( MAKEFOURCC('D', 'X', 'T', '3'), Tr2SddHeader::DXT3 ) ,
			std::make_pair( MAKEFOURCC('D', 'X', 'T', '4'), Tr2SddHeader::DXT4 ) ,
			std::make_pair( MAKEFOURCC('A', 'T', 'I', '2'), Tr2SddHeader::ATI2 ) ,
			std::make_pair( MAKEFOURCC('D', 'X', 'T', '5'), Tr2SddHeader::DXT5 ) 
		};

		bool found = false;
		for( unsigned i = 0; !found && i != sizeof( supported ) / sizeof( supported[0] ); ++i)
		{
			if( m_header.ddspf.dwFourCC == supported[i].first )
			{
				m_header.m_compressionType = supported[i].second;
				found = true;
			}
		}

		if( !found )
		{
			CCP_LOGERR( "Texture has a FourCC code that SDD doesn't support %d", bd.GetFormat() );
			return false;
		}
	}
	else
	{
		if( m_header.ddspf.dwRGBBitCount == 0 )	// messes up our math below
		{
			CCP_LOGERR( "Texture has a unsupported pixelformat/zero bitcount %d", bd.GetFormat() );
			return false;
		}

		// no need to worry about support: we have it, so it's supported.
		m_header.m_compressionType = m_header.NONE;
	}


	m_header.m_cubeMap = bd.GetType() == Tr2RenderContextEnum::TEX_TYPE_CUBE;
	
	CopyHeaderValuesToMembers();
	return true;
}

bool Tr2SddHandler::Save( const Tr2HostBitmap& image, IBlueStream* output )
{
	CCP_ASSERT( output );
	CCP_ASSERT( image.IsValid() );

	if( !BuildHeader( image ) )
	{
		return false;
	}
	
	output->Write( &m_header, sizeof( m_header ) );
	const unsigned faces = image.GetType() == Tr2RenderContextEnum::TEX_TYPE_CUBE ? 6 : 1;
	for( unsigned i = image.GetTrueMipCount(); i != 0; --i )
	{
		for( unsigned face = 0; face < faces; ++face )
		{
			output->Write( image.GetMipRawData( i - 1, Tr2RenderContextEnum::CubemapFace( face ) ), 
						   image.GetMipSize( i - 1 ) );
		}
	}
	return true;
}
