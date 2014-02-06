#pragma once
#ifndef EveRenderableMesh_H
#define EveRenderableMesh_H

#include "ITr2Renderable.h"

BLUE_DECLARE( Tr2Mesh );
BLUE_DECLARE( EveRenderableMesh );
BLUE_DECLARE( EveTransformItem );

class EveRenderableMesh:
	public ITr2Renderable
{
public:
	EXPOSE_TO_BLUE();

	EveRenderableMesh( IRoot* lockobj = NULL );
	~EveRenderableMesh();

	// ITr2Renderable
	void GetBatches( ITriRenderBatchAccumulator* batches, 
		TriBatchType batchType, 
		const Tr2PerObjectData* perObjectData );

	bool HasTransparentBatches();
	float GetSortValue();

	Tr2PerObjectData* GetPerObjectData( ITriRenderBatchAccumulator* accumulator );

	// Setter for EveTransformArray
	void UpdateTransform( const Matrix& worldMatrix );

	// Accessor for EveTransformArray
	EveTransformItem* GetTransformObject();

private:

	std::string m_name;

	// The temporary world transform
	// not exposed!
	Matrix m_transform;

	// The mesh to render
	Tr2MeshPtr m_mesh;

	// The Transform with which this renderable is associated
	EveTransformItemPtr m_transformItem;

};

TYPEDEF_BLUECLASS( EveRenderableMesh );

#endif