#include "StdAfx.h"
#include "EveRenderableMesh.h"
#include "EveTransformItem.h"

BLUE_DEFINE( EveRenderableMesh );

const Be::ClassInfo* EveRenderableMesh::ExposeToBlue()
{	
	EXPOSURE_BEGIN(EveRenderableMesh, "")
		MAP_INTERFACE(EveRenderableMesh)
		MAP_INTERFACE(ITr2Renderable)

		MAP_ATTRIBUTE( "name", m_name, "name of the transform", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "mesh", m_mesh, "The mesh to render", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "transform", m_transformItem, "The transform object with which this mesh is associated", Be::READWRITE | Be::PERSIST )
	EXPOSURE_END()
}