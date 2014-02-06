#pragma once
#ifndef EveTransformArray_H
#define EveTransformArray_H

#include "IEveTransform.h"
#include "ITr2Renderable.h"
#include "EveTransformItem.h"

BLUE_DECLARE( EveRenderableMesh );
BLUE_DECLARE_VECTOR( EveRenderableMesh );

BLUE_DECLARE( EveTransformItem );
BLUE_DECLARE_VECTOR( EveTransformItem );

BLUE_DECLARE( EveTransformArray );

// The function type for a function that builds an input matrix
// static, normal transformations do not need to rebuild their input every frame unless animated
typedef XMMATRIX (*BuildInputMatrixType)( const XMMATRIX& parent, const XMVECTOR& translation, const XMVECTOR& rotation, const XMVECTOR& scale );

// The function type for a function that returns the output matrix
// camera aligned transformations (for example) modify beyond a standard XMMatrixMultiply
typedef XMMATRIX (*CalculateTransformType)( const XMMATRIX& local, const XMMATRIX& parent );

//////////////////////////////////////////////////////////////////////////
// Description:
//   EveTransformArray attempts to coalesce transformations in order to 
//   perform the minimum possible runtime matrix math. It is designed not for authoring
//   but with a focus on the runtime efficiency.
//   Transformations are classified into three different TransformUpdateCommand vectors,
//   one for view-dependent updates, one for per-frame (animated) updates, and one that
//   isn't needed (static transforms) but is handy to keep around for debugging.
//
//   Internally, EveTransformArray builds a command list with function pointers
//   which correspond to to the steps needed to rebuild the matrices.
//   We build the transformations locally and only add in the world transform when we
//   get the renderables.
//
// TODO:
//   Support particle systems
//////////////////////////////////////////////////////////////////////////
class EveTransformArray:
	public IEveTransform, // Allows this to live in the children list of a spaceobject
	public IListNotify,	  // Try and track all additions and removals from the lists (because of the raw pointer caching)
	public IInitialize	  // Rebuilds the transform stack when loaded
{
public:
	EXPOSE_TO_BLUE();

	EveTransformArray( IRoot* lockobj = NULL );
	~EveTransformArray();

	//////////////////////////////////////////////////////////////////////////
	// IEveTransform
	//////////////////////////////////////////////////////////////////////////

	// Update and resolve all non-view dependent changes
	void Update( EveUpdateContext& updateContext );

	void RenderDebugInfo( Tr2RenderContext& renderContext );

	// Get the renderable sub-objects
	void GetRenderables( const TriFrustum& frustum, std::vector<ITr2Renderable*>& renderables, const Matrix& parentTransform );

	// View dependent update. You may query the camera state within this!
	void UpdateViewDependentData( const Matrix& parentTransform );
	
	virtual void UpdateViewDistanceInfo( const TriFrustum& frustum, ViewDistanceInfo& viewDistance ) const {}

	void SetLowDetail( bool b );

	LodLevel GetLODLevel() const { return LOD_HIGH; }
	virtual bool GetBoundingSphere( Vector4& sphere, BoundingSphereQuery query=EVE_BOUNDS_NORMAL ) const { return false; }

	//////////////////////////////////////////////////////////////////////////
	// IListNotify
	//////////////////////////////////////////////////////////////////////////

	void OnListModified(
		long event,		// BLUELISTEVENT values
		ssize_t key,
		ssize_t key2,
		IRoot* value,
		const IList* theList
		);

	//////////////////////////////////////////////////////////////////////////
	// IInitialize
	//////////////////////////////////////////////////////////////////////////
	bool Initialize();
	
	enum TransformState
	{
		NO_INHERITED_TRANSFORM_STATE = 0,

		// Transform is view dependent, or a parent is
		// Recalculate the transform in UpdateViewDependentData
		VIEW_DEPENDENT = 1,

		// Transform is animated
		// Recalculate the input matrix every frame
		ANIMATED_TRANSFORM = 2,

		// A parent matrix is animated.
		// We have to recalculate the output matrix, but not the input matrix
		ANIMATED_PARENT = 4,

		// Multiply this matrix by the world transform
		PREMULTIPLY_WORLD_TRANSFORM = 8,

		// Parent matrix is pre-multiplied with the world matrix
		// every frame. Make sure you don't multiply by the world-matrix again
		// at the end.
		PREMULTIPLIED_WORLD_TRANSFORM_IN_PARENT = 16,

		IN_WORLD_COORDINATES = PREMULTIPLY_WORLD_TRANSFORM | PREMULTIPLIED_WORLD_TRANSFORM_IN_PARENT,
	};
	
private:

	Vector3 GetWorldPositionLastFrame( EveRenderableMesh* i, Matrix parentTransform ) const;

	// Rebuild the transformation information for the given renderables and
	// transformations
	void RebuildTransformations();

	// Renderable objects. This vector is not used directly during rendering.
	// it is just there for persistence and user-editing
	PEveRenderableMeshVector m_renderableMeshes;

	// A tree of transformations
	// Renderable meshes reference into this tree
	PEveTransformItemVector m_transforms;

	// Per EveRenderableMesh we store an entry
	// that contains information about the transform
	// and if it already contains the worldtransform
	// (this can be the case with view-dependent
	// modifiers)
	struct PerMeshData
	{
		EveRenderableMesh* mesh;
		bool isPreMultipliedWithWorldTransform;
		const XMMATRIX* transform;
	};

	// This data structure is the one used internally
	std::vector<PerMeshData> m_internalMeshVector;

	// Contains all pertinent data for updating our matrix list
	// The most major components are the function pointers and matrix pointers
	// The modifiers and transform state may be mostly irrelevant now
	struct TransformUpdateCommand
	{
		EveTransformItemModifier modifier;
		TransformState tfState;
		BuildInputMatrixType constructInputMatrixFuncPtr;
		CalculateTransformType calculateTransformFuncPtr;
		unsigned componentsOffset;
		const XMMATRIX* parentMatrix;
		const XMMATRIX* localMatrix;
		XMMATRIX* outputMatrix;
	};

	// A list of operations in the correct order needed to update the transformations
	std::vector<TransformUpdateCommand> m_transformUpdateList;

	// A list of the operations that need to be done per frame, due to animated curves
	std::vector<TransformUpdateCommand> m_perFrameUpdateList;

	// A list of view-dependent matrix operations needed, with any children
	std::vector<TransformUpdateCommand> m_viewDependentUpdateList;

	// A buffer of accumulated transformations that are used
	// with the parent matrix to resolve a renderable in a single pass
	XMMATRIX* m_alignedTransformMatrices;
	unsigned m_alignedTransformMatrixCount;

	// An aligned buffer of transform components (translation...)
	// Curve binding updates are piped directly into this memory
	XMVECTOR* m_alignedTransformComponents;
	unsigned m_alignedTransformComponentCount;
};

TYPEDEF_BLUECLASS( EveTransformArray );

#endif