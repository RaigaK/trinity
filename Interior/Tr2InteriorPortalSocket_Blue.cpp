////////////////////////////////////////////////////////////
//
//    Created:   May 2010
//    Copyright: CCP 2010
//

#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "Tr2InteriorPortalSocket.h"

BLUE_DEFINE( Tr2InteriorPortalSocket );

// ------------------------------------------------------------------------------------------------------
const Be::ClassInfo* Tr2InteriorPortalSocket::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2InteriorPortalSocket, "" )
        MAP_INTERFACE( Tr2InteriorPortalSocket )
		MAP_INTERFACE( INotify )
		MAP_INTERFACE( IInitialize )

		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST )

		MAP_PROPERTY_READONLY( "parentTransform", GetParentTransform, "Matrix specifying the position and rotation of the parent cell in the world" )
		MAP_ATTRIBUTE( "transform", m_transform, "Matrix specifying the position and rotation of the portal socket in parent cell coordinates", Be::READWRITE | Be::NOTIFY | Be::PERSIST )
		MAP_ATTRIBUTE( "minBounds", m_minBounds, "Minimum bounds of the bounding box defining the portal socket", Be::READWRITE | Be::PERSIST | Be::NOTIFY );
		MAP_ATTRIBUTE( "maxBounds", m_maxBounds, "Maximum bounds of the bounding box defining the portal socket", Be::READWRITE | Be::PERSIST | Be::NOTIFY );

		MAP_ATTRIBUTE( "outputScale", m_scale, "Scale factor for output lighting intensity", Be::READWRITE | Be::PERSIST | Be::NOTIFY );
		MAP_ATTRIBUTE( "probeOffset", m_probeOffset, "SH probe offset along socket's normal from its center", Be::READWRITE | Be::PERSIST | Be::NOTIFY );
		MAP_ATTRIBUTE( "validProbe", m_validProbe, "This socket has valid computed SH probe", Be::READ );
		MAP_ATTRIBUTE( "geometryGuid", m_geometryGuid, "Unique identifier for socket's geometry", Be::READWRITE | Be::PERSIST );
		MAP_ATTRIBUTE( "instanceInSystemIdx", m_instanceInSystemIdx, "Index of geometry in portal socket Enlighten system", Be::PERSISTONLY );
		MAP_ATTRIBUTE( "texturePosition", m_texturePosition, "Position of portal geometry in Enlighten albedo texture", Be::PERSISTONLY );
		MAP_PROPERTY_READONLY( "normal", GetNormalCell, "Vector specifying the direction towards the containing cell (in cell coordinate system)" )
	EXPOSURE_END()
}

#endif
