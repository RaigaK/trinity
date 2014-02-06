////////////////////////////////////////////////////////////
//
//    Created:   September 2011
//    Copyright: CCP 2011
//

#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "Tr2InteriorOrientedBoundingBox.h"

BLUE_DEFINE( Tr2InteriorOrientedBoundingBox );

// ------------------------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2InteriorOrientedBoundingBox::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2InteriorOrientedBoundingBox, "" )
		MAP_INTERFACE( INotify )
		MAP_INTERFACE( Tr2InteriorOrientedBoundingBox )

		MAP_ATTRIBUTE( "transform", m_transform, "bounding box transform", Be::READWRITE | Be::PERSIST | Be::NOTIFY )

		MAP_METHOD_AND_WRAP( "GetBoundingBoxInLocalSpace", GetBoundingBoxInLocalSpace, "Gets the bounding box in local space" )
	EXPOSURE_END()
}

#endif
