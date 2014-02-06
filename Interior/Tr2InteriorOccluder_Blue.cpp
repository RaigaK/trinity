#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "Tr2InteriorOccluder.h"

BLUE_DEFINE( Tr2InteriorOccluder );


const Be::ClassInfo* Tr2InteriorOccluder::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2InteriorOccluder, "" )

		MAP_INTERFACE( Tr2InteriorOccluder )
		MAP_INTERFACE( INotify )

		MAP_PROPERTY_READONLY( "parentTransform", GetParentTransform, "Matrix specifying the position and rotation of the parent cell in the world" )
		MAP_ATTRIBUTE( "transform", m_transform, "Local to cell transform matrix", Be::READWRITE | Be::PERSIST | Be::NOTIFY )

	EXPOSURE_END()
}

#endif
