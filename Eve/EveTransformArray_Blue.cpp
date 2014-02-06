#include "StdAfx.h"
#include "EveTransformArray.h"
#include "EveRenderableMesh.h"

BLUE_DEFINE( EveTransformArray );

const Be::ClassInfo* EveTransformArray::ExposeToBlue()
{	
	EXPOSURE_BEGIN( EveTransformArray, "")
		MAP_INTERFACE( EveTransformArray )
		MAP_INTERFACE( IListNotify )
		MAP_INTERFACE( IEveTransform )
		MAP_INTERFACE( IInitialize )

		MAP_ATTRIBUTE( "transformations", m_transforms, "The transformation tree", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "meshes", m_renderableMeshes, "Renderable objects", Be::READWRITE | Be::PERSIST )

		MAP_METHOD_AND_WRAP( "RebuildTransformations", RebuildTransformations, "Rebuilds the transformation heirachy" )

	EXPOSURE_END()
}