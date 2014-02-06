#include "StdAfx.h"
#include "Tr2MeshArea.h"

BLUE_DEFINE( Tr2MeshArea );




const Be::ClassInfo* Tr2MeshArea::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2MeshArea, "" )

		MAP_INTERFACE( Tr2MeshArea )

		MAP_ATTRIBUTE( "name", m_name, "na", Be::READWRITE | Be::PERSIST )
		MAPHIDEABLE() // Maps to map_attribute so this is ok. See impl in Tr2HideableMixin.h <andrimar-2010.08.20>

		// meshes should have materials now, no excuses!

		MAP_ATTRIBUTE( "index", m_index, "Start index of the area within the mesh to bind to this effect", Be::READWRITE | Be::PERSIST )
        MAP_ATTRIBUTE( "count", m_count, "Number of areas within the mesh to bind to this effect", Be::READWRITE | Be::PERSIST )
        MAP_ATTRIBUTE( "reversed", m_reversed, "Render mesh triangles in reverse order and with reversed culling order", Be::READWRITE | Be::PERSIST )
        MAP_ATTRIBUTE( "useSHLighting", m_useSHLighting, "Use SH lighting instead of full-forward lighting", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "effect", m_material, "Shader or Material effect", Be::READWRITE | Be::NOTIFY | Be::PERSIST )

	EXPOSURE_END()
}
