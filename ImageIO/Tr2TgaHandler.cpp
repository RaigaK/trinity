////////////////////////////////////////////////////////////
//
//    Created:   May 2012
//    Copyright: CCP 2012
//

#include "StdAfx.h"
#include "Tr2TgaHandler.h"
#include "Tr2HostBitmap.h"

using namespace Tr2RenderContextEnum;

namespace
{

// --------------------------------------------------------------------------------------
// Description:
//   Possible values for Tr2TgaHandler::Header::colorMapType field. 
// --------------------------------------------------------------------------------------
enum ColorMapType
{
	COLOR_TYPE_RGB				= 0,
	COLOR_TYPE_INDEXED			= 1,
	__COLOR_TYPE_UNSUPPORTED,
};

// --------------------------------------------------------------------------------------
// Description:
//   Possible values for Tr2TgaHandler::Header::imageType field. 
// --------------------------------------------------------------------------------------
enum ImageType
{
	IMAGE_TYPE_RAW_INDEXED		= 1,
	IMAGE_TYPE_RAW_RGB			= 2,
	IMAGE_TYPE_RAW_GREYSCALE	= 3,
	IMAGE_TYPE_RLE_INDEXED		= 9,
	IMAGE_TYPE_RLE_RGB			= 10,
	IMAGE_TYPE_RLE_GREYSCALE	= 11,
	__IMAGE_TYPE_UNSUPPORTED,
};

// The only supported TGA palette size (256 * 3 bytes)
const unsigned PALETTE_SIZE = 768;

}

// --------------------------------------------------------------------------------------
// Description:
//   Tr2TgaHandler constructor
// --------------------------------------------------------------------------------------
Tr2TgaHandler::Tr2TgaHandler( const wchar_t* sourceName )
	:Tr2ImageHandler( sourceName )
{
}

// --------------------------------------------------------------------------------------
// Description:
//   Reads TGA header from the stream and initializes basic variables (width, height, 
//   etc.).
// Return Value:
//   true If the header was suscessfully read
//   false If there was an error reading the header or the format is unsupported
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::ReadHeader()
{
	m_fileSize = m_source->GetSize();

	if( m_source->Read( &m_header, sizeof( Header ) ) != sizeof( Header ) )
	{
		return false;
	}
	if( m_header.colorMapType >= __COLOR_TYPE_UNSUPPORTED )
	{
		return false;
	}
	if( m_header.imageType >= __IMAGE_TYPE_UNSUPPORTED )
	{
		return false;
	}
	if( m_header.colorMapType == COLOR_TYPE_INDEXED )
	{
		if( m_header.colorMapStart != 0 || m_header.colorMapLength != 256 || m_header.colorMapBpp != 24 )
		{
			return false;
		}
	}
	if( m_header.right - m_header.left < 1 || m_header.bottom - m_header.top < 1 )
	{
		return false;
	}
	if( m_header.imageDescriptor > 32 )
	{
		return false;
	}
	
	m_width = unsigned( m_header.right - m_header.left );
	m_height = unsigned( m_header.bottom - m_header.top );
	if( m_header.imageType == IMAGE_TYPE_RAW_GREYSCALE ||
		m_header.imageType == IMAGE_TYPE_RLE_GREYSCALE )
	{
		m_bitsPerPixel = 8;
	}
	else
	{
		m_bitsPerPixel = 32;
	}

	m_mipLevelCount = 1;
	
	m_imageSize = m_width * m_height * size_t( m_header.bpp / 8 );

	m_source->Seek( m_header.idLength, BS_CURRENT );

	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Returns true if the texture format is support by the device (or the loader
//   can convert to a supported format while loading).
// Return Value:
//   true Always
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::IsSupported()
{
	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Returns the format of the texture being loaded.
//   Assumes that header has been successfully read, and determined to be 
//   valid - only call after ReadHeader returns true.
// Return Value:
//   Pixel format for TGA image
// --------------------------------------------------------------------------------------
Tr2RenderContextEnum::PixelFormat Tr2TgaHandler::GetFormat() const 
{
	if( m_header.imageType == IMAGE_TYPE_RAW_INDEXED || m_header.imageType == IMAGE_TYPE_RLE_INDEXED )
	{
		return Tr2RenderContextEnum::PIXEL_FORMAT_B8G8R8X8_UNORM;
	}
	else if( m_header.bpp == 8 )
	{
		return Tr2RenderContextEnum::PIXEL_FORMAT_R8_UNORM;
	}
	else if( m_header.bpp < 32 )
	{
		return Tr2RenderContextEnum::PIXEL_FORMAT_B8G8R8X8_UNORM;
	}
	else
	{
		return Tr2RenderContextEnum::PIXEL_FORMAT_B8G8R8A8_UNORM;
	}
}

// --------------------------------------------------------------------------------------
// Description:
//   Reads image data from the stream. Generates mip levels.
// Return Value:
//   true If the image was suscessfully read
//   false If there was an error loading the image
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::ReadImage()
{
	CCP_STATS_ZONE( __FUNCTION__ );

	if( m_height > 4096 || m_width > 4096 ) 
	{
		CCP_LOGWARN( "Very large tga image being loaded: %d x %d", m_width, m_height );
	}

	unsigned char *palette = nullptr;
	ON_BLOCK_EXIT( [&] { delete[] palette; } );

	switch( m_header.imageType )
	{
	case IMAGE_TYPE_RAW_INDEXED:
		if( m_imageSize + sizeof( Header ) + m_header.idLength + PALETTE_SIZE > m_fileSize )
		{
			return false;
		}
		if( !ReadPalette( palette ) )
		{
			return false;
		}
		if( !ReadRawData( palette ) )
		{
			return false;
		}
		break;
	case IMAGE_TYPE_RAW_RGB:
	case IMAGE_TYPE_RAW_GREYSCALE:
		if( m_imageSize + sizeof( Header ) + m_header.idLength > m_fileSize )
		{
			return false;
		}
		if( !ReadRawData( palette ) )
		{
			return false;
		}
		break;
	case IMAGE_TYPE_RLE_INDEXED:
		if( !ReadPalette( palette ) )
		{
			return false;
		}
		if( !ReadRLEData( palette ) )
		{
			return false;
		}
		break;
	case IMAGE_TYPE_RLE_RGB:
	case IMAGE_TYPE_RLE_GREYSCALE:
		if( !ReadRLEData( palette ) )
		{
			return false;
		}
		break;
	default:
		return false;
	}	
	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Return the dds block size, or 0 if there's no compression
// Return Value:
//   0 always
// --------------------------------------------------------------------------------------
unsigned Tr2TgaHandler::GetBlockByteSize() const
{
	return 0;
}

// --------------------------------------------------------------------------------------
// Description:
//   Return the offset where this face and miplevel would be, relative to the start of m_data.
//   This does not include the size of the header, ie. we're dealing strictly with texels.
// Arguments:
//   mipLevel - Mip level
//   face - Cubemap face (unused: TGAs don't support cube maps)
// Return Value:
//   Offset of specified mip level.
// --------------------------------------------------------------------------------------
unsigned Tr2TgaHandler::GetOffset( unsigned mipLevel, unsigned face ) const
{
	unsigned offset = 0;
	for( unsigned int i = 0; i != mipLevel ; ++i )
	{
		offset += GetMipLevelSize( i );
	}
	return offset;
}

// --------------------------------------------------------------------------------------
// Description:
//   Checks if saving for an image is supported.
// Arguments:
//   bd - Image information
// Return Value:
//   true If saving is supported for the image
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::IsSaveSupported( const Tr2BitmapDimensions& bd )
{
	return bd.GetType() == TEX_TYPE_2D && IsSaveSupported( bd.GetFormat() );
}

// --------------------------------------------------------------------------------------
// Description:
//   Checks if image format matches one of the formats for which saving supported.
// Arguments:
//   format - Pixel format
// Return Value:
//   true If saving is supported for the format
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::IsSaveSupported( Tr2RenderContextEnum::PixelFormat format )
{
	return format == PIXEL_FORMAT_B8G8R8X8_UNORM ||
		format != PIXEL_FORMAT_B8G8R8A8_UNORM ||
		format != PIXEL_FORMAT_R8_UNORM;
}

// --------------------------------------------------------------------------------------
// Description:
//   Saves TGA header to the stream.
// Arguments:
//   width - Image width
//   height - Image height
//   format - Image pixel format
//   output - Stream to save image to
// Return Value:
//   true If the image header was saved
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::SaveHeader( 
	uint32_t width, 
	uint32_t height, 
	Tr2RenderContextEnum::PixelFormat format, 
	IBlueStream* output )
{
	if( !IsSaveSupported( format ) )
	{
		CCP_LOGWARN( "Tr2TgaHandler::SaveHeader does not support this image format" );
		return false;
	}

	Header header;
	header.idLength = 0;
	header.colorMapType = COLOR_TYPE_RGB;
	header.colorMapStart = 0;
	header.colorMapLength = 0;
	header.colorMapBpp = 0;
	header.left = 0;
	header.top = 0;
	header.right = width;
	header.bottom = height;
	header.imageDescriptor = 0;

	switch( format )
	{
	case PIXEL_FORMAT_B8G8R8X8_UNORM:
		header.imageType = IMAGE_TYPE_RAW_RGB;
		header.bpp = 24;
		break;
	case PIXEL_FORMAT_B8G8R8A8_UNORM:
		header.imageType = IMAGE_TYPE_RAW_RGB;
		header.bpp = 32;
		break;
	case PIXEL_FORMAT_R8_UNORM:
		header.imageType = IMAGE_TYPE_RAW_GREYSCALE;
		header.bpp = 8;
		break;
    default:
        return false;
	}

	if( output->Write( &header, sizeof( Header ) ) != sizeof( Header ) )
	{
		CCP_LOGWARN( "Tr2TgaHandler::SaveHeader failed to write the header" );
		return false;
	}

	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Saves several rows of image data into a TGA stream.
// Arguments:
//   width - Image width
//   height - Image part height
//   format - Image pixel format
//   data - Image pixel data
//   output - Stream to save image to
// Return Value:
//   true If the image was saved
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::SaveRows( 
	uint32_t width, 
	uint32_t height, 
	Tr2RenderContextEnum::PixelFormat format, 
	const void* data, 
	IBlueStream* output )
{
	unsigned srcBitesPerPixel;
	unsigned destBitesPerPixel;
	switch( format )
	{
	case PIXEL_FORMAT_B8G8R8X8_UNORM:
		srcBitesPerPixel = 4;
		destBitesPerPixel = 3;
		break;
	case PIXEL_FORMAT_B8G8R8A8_UNORM:
		srcBitesPerPixel = 4;
		destBitesPerPixel = 4;
		break;
	case PIXEL_FORMAT_R8_UNORM:
		srcBitesPerPixel = 1;
		destBitesPerPixel = 1;
		break;
    default:
        return false;
	}

	unsigned srcStride = width * srcBitesPerPixel;
	const char* row = reinterpret_cast<const char*>( data ) + ( height - 1 ) * srcStride;
	if( srcBitesPerPixel == destBitesPerPixel )
	{
		for( unsigned j = 0; j < height; ++j )
		{
			if( output->Write( row, srcStride ) != srcStride )
			{
				CCP_LOGWARN( "Tr2TgaHandler::SaveRows failed to write datachunk(1)" );
				return false;
			}
			row -= srcStride;
		}
	}
	else
	{
		CCP_ASSERT( srcBitesPerPixel == 4 && destBitesPerPixel == 3 );

		unsigned destStride = destBitesPerPixel * width;
		char* rowData = new char[destStride];
		ON_BLOCK_EXIT( [&] { delete[] rowData; } );

		for( unsigned j = 0; j < height; ++j )
		{
			const char* current = row;
			char* destRow = rowData;
			for( unsigned j = 0; j < width; ++j )
			{
				*destRow++ = *current++;
				*destRow++ = *current++;
				*destRow++ = *current++;
				current++;
			}

			if( output->Write( rowData, destStride ) != destStride )
			{
				CCP_LOGWARN( "Tr2TgaHandler::SaveRows failed to write datachunk(2)" );
				return false;
			}
			row -= srcStride;
		}
	}

	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Saves a bitmap to TGA file.
// Arguments:
//   image - Bitmap to save
//   output - Stream to save image to
// Return Value:
//   true If the image was saved
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::Save( const Tr2HostBitmap& image, IBlueStream* output )
{
	if( !image.IsValid() )
	{
		CCP_LOGWARN( "Tr2TgaHandler::Save input image isn't valid" );
		return false;
	}

	if( !IsSaveSupported( image ) )
	{
		CCP_LOGWARN( "Tr2TgaHandler::Save does not support this image format" );
		return false;
	}

	if( !SaveHeader( image.GetWidth(), image.GetHeight(), image.GetFormat(), output ) )
	{
		return false;
	}

	return SaveRows( image.GetWidth(), image.GetHeight(), image.GetFormat(), image.GetRawData(), output );
}

// --------------------------------------------------------------------------------------
// Description:
//   Reads palette data from the steam.
// Arguments:
//   palette - (out) Color values of palette entries
// Return Value:
//   true If the palette was loaded
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::ReadPalette( unsigned char*& palette )
{
	palette = new unsigned char[PALETTE_SIZE];
	if( palette == nullptr )
	{
		return false;
	}
	if( m_source->Read( palette, PALETTE_SIZE ) != PALETTE_SIZE )
	{
		return false;
	}
	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Reads uncompressed image data from the steam. When reading the function also 
//   performs flipping the image and converting 24bpp images to 32bpp.
// Arguments:
//   palette - Color values of palette entries (or null for non-indexed formats)
// Return Value:
//   true If the image was loaded
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::ReadRawData( unsigned char* palette )
{
	CCP_FREE( m_data );
	m_dataSize = GetTotalDataSize();

	m_data = (uint8_t*)CCP_MALLOC( "Tr2TgaHandler/m_data", GetTotalDataSize() );	
	if( !m_data )
	{
		CCP_LOGERR( "Tr2TgaHandler couldn't allocate %d bytes (%S)", GetTotalDataSize(), m_sourceName.c_str() );
		m_dataSize = 0;
		return false;
	}

	if( palette )
	{
		uint8_t *indexes = new uint8_t[m_imageSize];
		ON_BLOCK_EXIT( [&] { delete[] indexes; } );
		if( !indexes || m_source->Read( indexes, m_imageSize ) != m_imageSize )
		{
			return false;
		}
		unsigned index = 0;
		unsigned stride = m_width * ( m_bitsPerPixel / 8 );
		uint8_t* data = m_data + stride * ( m_height - 1 );
		for( unsigned j = 0; j < m_height; ++j )
		{
			unsigned rowIndex = 0;
			for( unsigned i = 0; i < m_width; ++i )
			{
				unsigned paletteIndex = indexes[index++] * 3;
				data[rowIndex++] = palette[paletteIndex];
				data[rowIndex++] = palette[paletteIndex + 1];
				data[rowIndex++] = palette[paletteIndex + 2];
				data[rowIndex++] = 255;
			}
			data -= stride;
		}
	}
	else
	{
		unsigned bpp = ( m_header.colorMapType == COLOR_TYPE_INDEXED ? m_header.colorMapBpp : m_header.bpp ) / 8;
		unsigned stride = m_width * bpp;
		if( bpp != 3 )
		{
			uint8_t* data = m_data + stride * ( m_height - 1 );
			for( unsigned i = 0; i < m_height; ++i )
			{
				if( m_source->Read( data, stride ) != stride )
				{
					return false;
				}
				data -= stride;
			}
		}
		else
		{
			uint8_t* row = new uint8_t[stride];
			ON_BLOCK_EXIT( [&] { delete[] row; } );

			unsigned outputStride = m_width * ( m_bitsPerPixel / 8 );
			uint8_t* data = m_data + outputStride * ( m_height - 1 );
			for( unsigned i = 0; i < m_height; ++i )
			{
				if( m_source->Read( row, stride ) != stride )
				{
					return false;
				}
				unsigned inputIndex = 0;
				unsigned outputIndex = 0;
				for( unsigned j = 0; j < m_width; ++j )
				{
					data[outputIndex++] = row[inputIndex++];
					data[outputIndex++] = row[inputIndex++];
					data[outputIndex++] = row[inputIndex++];
					data[outputIndex++] = 255;
				}
				data -= outputStride;
			}
		}
	}
	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Reads RLE compressed image data from the steam. When reading the function also 
//   performs flipping the image and converting 24bpp images to 32bpp.
// Arguments:
//   palette - Color values of palette entries (or null for non-indexed formats)
// Return Value:
//   true If the image was loaded
//   false Otherwise
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::ReadRLEData( unsigned char* palette )
{
	CCP_FREE( m_data );
	m_dataSize = GetTotalDataSize();

	m_data = (uint8_t*)CCP_MALLOC( "Tr2TgaHandler/m_data", m_dataSize );
	if( !m_data )
	{
		CCP_LOGERR( "Tr2TgaHandler couldn't allocate %d bytes (%S)", GetTotalDataSize(), m_sourceName.c_str() );
		m_dataSize = 0;
		return false;
	}

	uint8_t* compressedData = new uint8_t[m_imageSize];
	ON_BLOCK_EXIT( [&] { delete[] compressedData; } );

	size_t size = m_source->GetSize() - m_source->GetPosition();
	if( !compressedData || m_source->Read( compressedData, size ) != size )
	{
		return false;
	}

	uint8_t* current = compressedData;
	unsigned index = 0;
	unsigned pixelSize = m_bitsPerPixel / 8;
	unsigned inputPixelSize = ( m_header.colorMapType == COLOR_TYPE_INDEXED ? m_header.colorMapBpp : m_header.bpp ) / 8;
	unsigned outputSize = m_width * m_height * pixelSize;

	auto Decode = [&]( uint8_t* destination, const uint8_t* source, unsigned bpp )
	{
		if( palette )
		{
			unsigned paletteIndex = *source * 3;
			destination[0] = palette[paletteIndex];
			destination[1] = palette[paletteIndex + 1];
			destination[2] = palette[paletteIndex + 2];
		}
		else
		{
			memcpy( destination, source, bpp );
		}
	};

	// Decode
	while( index < outputSize ) 
	{
		if( *current & 0x80 ) // Run length chunk (High bit = 1)
		{
			int length = *current - 127;
			current++;
			// Repeat the next pixel length times
			for( int loop=0; loop != length; ++loop )
			{
				Decode( m_data + index, current, pixelSize );
				index += pixelSize;
			}

			current += inputPixelSize; // Move to the next descriptor chunk
		}
		else // Raw chunk
		{
			int length = *current + 1;
			current++;
			// Write the next length pixels directly
			for( int loop = 0; loop != length; ++loop )
			{
				Decode( m_data + index, current, pixelSize );
				index += pixelSize;
				current += inputPixelSize;
			}
		}
	}

	// Flip the image
	unsigned stride = m_width * ( m_bitsPerPixel / 8 );
	uint8_t* row0 = m_data;
	uint8_t* row1 = m_data + stride * ( m_height - 1 );
	for( unsigned i = 0; i < m_height / 2; ++i )
	{
		for( unsigned j = 0; j < stride; ++j )
		{
			std::swap( row0[j], row1[j] );
		}
		row0 += stride;
		row1 -= stride;
	}
	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Generates entire mip chain for the loaded image.
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::GenerateMips()
{
	if( m_mipLevelCount != 1 )
	{
		return true;
	}

	uint8_t* oldData = m_data;
	unsigned oldDataSize = m_dataSize;

	unsigned srcOffset = 0;
	unsigned width = m_width;
	unsigned height = m_height;

	const unsigned oldMipLevelCount = m_mipLevelCount;

	unsigned maxSize = std::max( m_height, m_width );
	m_mipLevelCount = 0;
	while( maxSize )
	{
		maxSize >>= 1;
		m_mipLevelCount++;
	}

	m_dataSize = GetTotalDataSize();
	m_data = (uint8_t*)CCP_MALLOC( "Tr2TgaHandler/m_data", m_dataSize );
	if( !m_data )
	{
		CCP_LOGERR( "Tr2TgaHandler::GenerateMips couldn't allocate %d bytes", m_dataSize );
		m_mipLevelCount = oldMipLevelCount;
		m_dataSize = GetTotalDataSize();
		m_data = oldData;
		return false;
	}

	memcpy( m_data, oldData, oldDataSize );
	CCP_FREE( oldData );

	for( unsigned i = 0; i + 1 < m_mipLevelCount; ++i )
	{
		unsigned destOffset = GetOffset( i + 1, 0 );
		if( !GenerateMipLevel( m_data + srcOffset, width, height, m_data + destOffset ) )
		{
			return false;
		}
		srcOffset = destOffset;
		width = max( width / 2, 1u );
		height = max( height / 2, 1u );
	}
	return true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Generates mip level given previous mip level data.
// Arguments:
//   source - Data of the previous (larger) mip level
//   width - Width of the previous mip level
//   height - Height of the previous mip level
//   destination - Data of the mip level to generate
// --------------------------------------------------------------------------------------
bool Tr2TgaHandler::GenerateMipLevel( uint8_t* source, unsigned width, unsigned height, uint8_t* destination )
{
	unsigned bpp = m_bitsPerPixel / 8;
	unsigned dstWidth = max( width / 2, 1u );
	unsigned dstHeight = max( height / 2, 1u );
	unsigned srcStride = width * bpp;

	unsigned vertStep = height > 1 ? srcStride : 0;
	unsigned horizStep = width > 1 ? bpp : 0;

	uint8_t* src00 = source;
	uint8_t* src01 = source + vertStep;

	uint8_t* bottom = source + ( height - 1 ) * srcStride;

	for( unsigned i = 0; i < dstHeight; ++i )
	{
		uint8_t* right0 = src00 + ( width - 1 ) * bpp;
		uint8_t* right1 = src01 + ( width - 1 ) * bpp;
		for( unsigned j = 0; j < dstWidth; ++j )
		{
			uint8_t* src10 = min( src00 + horizStep, right0 );
			uint8_t* src11 = min( src01 + horizStep, right1 );
			for( unsigned k = 0; k < bpp; ++k )
			{
				*destination++ = ( unsigned( *src00++ ) + unsigned( *src01++ ) + unsigned( *src10++ ) + unsigned( *src11++ ) ) >> 2;
			}
			src00 += horizStep;
			src01 += horizStep;
		}
		src00 = min( right0 + bpp + vertStep, bottom );
		src01 = min( right1 + bpp + vertStep, bottom );
	}

	return true;
}