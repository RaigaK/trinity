#include "StdAfx.h"

#include "Tr2InteriorBoundingBox.h"

BLUE_DEFINE( Tr2InteriorBoundingBox );

// ------------------------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2InteriorBoundingBox::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2InteriorBoundingBox, "" )
		MAP_INTERFACE( INotify )
		MAP_INTERFACE( Tr2InteriorBoundingBox )

		MAP_ATTRIBUTE( "minBounds", m_minBounds, "minimum bounds for the subregion", Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( "maxBounds", m_maxBounds, "maximum bounds for the subregion", Be::READWRITE | Be::PERSIST | Be::NOTIFY )

	EXPOSURE_END()
}
