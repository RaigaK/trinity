#include "StdAfx.h"
#include "EveRenderableMesh.h"
#include "Tr2Mesh.h"
#include "Tr2Renderer.h"
// Needed for the Per Object Data
#include "EveTransform.h"

EveRenderableMesh::EveRenderableMesh( IRoot* lockobj /*= NULL */ )
{

}

EveRenderableMesh::~EveRenderableMesh()
{

}

void EveRenderableMesh::GetBatches( ITriRenderBatchAccumulator* batches, TriBatchType batchType, const Tr2PerObjectData* perObjectData )
{
	if( m_mesh)
	{
		m_mesh->GetBatches( batches, m_mesh->GetAreas( batchType ), perObjectData );
	}
}

bool EveRenderableMesh::HasTransparentBatches()
{
	if( m_mesh )
	{
		return !(m_mesh->GetAreas( TRIBATCHTYPE_TRANSPARENT )->empty());
	}

	return false;
}

float EveRenderableMesh::GetSortValue()
{
	Vector3 d = Tr2Renderer::GetViewPosition() - m_transform.GetTranslation();
	return D3DXVec3Length( &d );
}

Tr2PerObjectData* EveRenderableMesh::GetPerObjectData( ITriRenderBatchAccumulator* accumulator )
{
	EveBasicPerObjectData* data = accumulator->Allocate<EveBasicPerObjectData>();

	if( !data )
	{
		return NULL;
	}

	// column_major for shaders
	D3DXMatrixTranspose( &data->m_world, &m_transform );
	// attention: need the transposed, but shader also needs column_major, so it is transpose(transpose(m)) == m
	if( D3DXMatrixInverse( &data->m_worldInverseTranspose, NULL, &m_transform ) == NULL)
	{
		// ok, so a complete row is 0.f -> find it and "fix" it
		Matrix wm = m_transform;
		if( wm._11 == 0.f && wm._12 == 0.f && wm._13 == 0.f )
			wm._11 = 0.1f;
		else if( wm._21 == 0.f && wm._22 == 0.f && wm._23 == 0.f )
			wm._22 = 0.1f;
		else if( wm._31 == 0.f && wm._32 == 0.f && wm._33 == 0.f )
			wm._33 = 0.1f;
		D3DXMatrixInverse( &data->m_worldInverseTranspose, NULL, &wm );
	}

	return data;
}

void EveRenderableMesh::UpdateTransform( const Matrix& worldMatrix )
{
	m_transform = worldMatrix;
}

EveTransformItem* EveRenderableMesh::GetTransformObject()
{
	return m_transformItem;
}

