#include "StdAfx.h"
#include "Tr2ImageRes.h"
#include "blue/include/IBlueResMan.h"
#include "ImageIO/Tr2ImageHandler.h"

Tr2ImageRes::Tr2ImageRes( IRoot* lockobj ) :
	m_imageHandler( nullptr )
{
}

Tr2ImageRes::~Tr2ImageRes()
{
	CCP_DELETE m_imageHandler;
	m_imageHandler = NULL;
}

bool Tr2ImageRes::IsMemoryUsageKnown()
{
	return !IsLoading();
}

size_t Tr2ImageRes::GetMemoryUsage()
{
	if( m_imageHandler )
	{
		return m_imageHandler->GetTotalDataSize();
	}
	else
	{
		return 1024;
	}
}

bool Tr2ImageRes::DoOpenStream()
{
	m_reservedMemory = 0;

	// make sure the path string is not empty
	if( !GetPath()[0] )
	{
		return false;
	}

	if( BePaths->GetStreamFromPathW( GetPath(), &m_dataStream ) )
	{
		m_reservedMemory = m_dataStream->GetSize();
		BeResMan->ReserveBackgroundLoadMemory( m_reservedMemory );
		return true;
	}

	return false;
}

void Tr2ImageRes::DoCloseStream()
{
	if( m_dataStream )
	{
		m_dataStream->UnlockData();
		m_dataSize = 0;
		m_dataStream = 0;
	}

	BeResMan->ReleaseBackgroundLoadMemory( m_reservedMemory );
	m_reservedMemory = 0;
}

BlueAsyncRes::LoadingResult Tr2ImageRes::DoLoad()
{
	CCP_STATS_ZONE( __FUNCTION__ );

	if( !m_dataStream )
	{
		return LR_FAILED;
	}

	bool isOK = true;

	m_imageHandler = CreateImageHandler( m_path );
	CCP_ASSERT( m_imageHandler != NULL );

	m_imageHandler->SetStream( m_dataStream );
	isOK = m_imageHandler->ReadHeader();
	if(isOK)
	{
		isOK = m_imageHandler->IsSupported();
		if( isOK )
		{
			isOK = m_imageHandler->ReadImage();
		}
		else
		{
			CCP_LOGWARN( "Texture '%S' needs format conversion", GetPath() );
		}
	}
	else
	{
		CCP_LOGWARN( "Texture '%S' - couldn't read header", GetPath() );
	}

	return isOK ? LR_SUCCESS : LR_FAILED;
}

bool Tr2ImageRes::DoPrepare()
{
	return true;
}

int Tr2ImageRes::GetWidth() const
{
	if( m_imageHandler )
	{
		return m_imageHandler->GetWidth();
	}

	return 0;
}

int Tr2ImageRes::GetHeight() const
{
	if( m_imageHandler )
	{
		return m_imageHandler->GetHeight();
	}

	return 0;
}

bool Tr2ImageRes::IsPixelOpaque( int x, int y ) const
{
	if( m_imageHandler )
	{
		return m_imageHandler->IsPixelOpaque( x, y );
	}

	return false;
}

Color Tr2ImageRes::GetPixelColor( int x, int y ) const
{
	if( m_imageHandler )
	{
		return m_imageHandler->GetPixelColor( x, y );
	}

	return Color( 0.0f, 0.0f, 0.0f, 0.0f );
}
