#include "StdAfx.h"
#include "EveTransformArray.h"
#include "EveRenderableMesh.h"
#include "EveTransformItem.h"
#include "Tr2Renderer.h"

// Offsets for vector elements components
enum
{
	OFFSET_TRANSLATION = 0,
	OFFSET_ROTATION = 1,
	OFFSET_SCALE = 2,
};

// --------------------------------------------------------------------------------------
// Description:
//   Builds a standard affine transformation
// --------------------------------------------------------------------------------------
XMMATRIX BuildAffineTransformInput( const XMMATRIX& parent, const XMVECTOR& translation, const XMVECTOR& rotation, const XMVECTOR& scale )
{
	return XMMatrixAffineTransformation( scale, XMVectorZero(), rotation, translation );
}

// --------------------------------------------------------------------------------------
// Description:
//   Performs normal matrix multiplication of a local matrix with a parent matrix
// --------------------------------------------------------------------------------------
XMMATRIX CalculateStandardTransform( const XMMATRIX& local, const XMMATRIX& parent )
{
	return XMMatrixMultiply( local, parent );
}

// --------------------------------------------------------------------------------------
// Description:
//   Builds a camera aligned input matrix. The matrix computes the world translation
//   based on the parent, but does not inherit the scale or rotation from it
//   Requires the world transform to be premultiplied into the parent matrix
// --------------------------------------------------------------------------------------
XMMATRIX BuildCameraAlignedTransformInput( const XMMATRIX& parent, const XMVECTOR& translation, const XMVECTOR& rotation, const XMVECTOR& scale )
{
	const XMVECTOR worldTranslation = XMVector3TransformCoord( translation, parent );
	return XMMatrixAffineTransformation( scale, XMVectorZero(), rotation, worldTranslation );
}


// --------------------------------------------------------------------------------------
// Description:
//   Builds a camera aligned input matrix. The matrix computes the world translation
//   based on the parent, and inherits the scale
//   Requires the world transform to be premultiplied into the parent matrix
// --------------------------------------------------------------------------------------
XMMATRIX BuildCameraAlignedTransformInputWithScale( const XMMATRIX& parent, const XMVECTOR& translation, const XMVECTOR& rotation, const XMVECTOR& scale )
{
	const XMVECTOR worldTranslation = XMVector3TransformCoord( translation, parent );

	// This should be the most efficient way to extract the component-wise scale
	XMMATRIX temp = XMMatrixTranspose(parent);
	temp._14 = 0.0f;
	temp._24 = 0.0f;
	temp._34 = 0.0f;
	temp = XMMatrixMultiply( parent, temp );
	XMVECTOR scaleSq = XMVectorSet( temp._11, temp._22, temp._33, 0.0f );
	
	return XMMatrixAffineTransformation( XMVectorMultiply(scale, XMVectorSqrt(scaleSq)), XMVectorZero(), rotation, worldTranslation );
}


// --------------------------------------------------------------------------------------
// Description:
//   Returns the camera aligned transfomation with Z dependent scaling
// --------------------------------------------------------------------------------------
XMMATRIX CalculateCameraAlignedTransformWithZModulation( const XMMATRIX& local, const XMMATRIX& parent )
{
	XMMATRIX temp = (XMMATRIX)Tr2Renderer::GetInverseViewTransform();
	const XMVECTOR viewDirection = XMVectorSet( temp._31, temp._32, temp._33, 0.0f );
	temp = XMMatrixMultiply( local, temp );
	
	// 
	XMMATRIX transform = XMMatrixMultiply( local, parent );
	XMVECTOR objectZ  = XMVector3Normalize( XMVectorSet( transform._31, transform._32, transform._33, 0.0f ) );
	XMVECTOR scale = XMVector3Dot( viewDirection, objectZ );
	scale *= scale; // Legacy behavior
	XMMATRIX scaleMatrix = XMMatrixScalingFromVector( scale );
	temp = XMMatrixMultiply( scaleMatrix, temp );

	// Don't use the translation from the camera
	temp._41 = local._41;
	temp._42 = local._42;
	temp._43 = local._43;

	return temp;
}

// --------------------------------------------------------------------------------------
// Description:
//   Returns the camera aligned transfomation
// --------------------------------------------------------------------------------------
XMMATRIX CalculateCameraAlignedTransform( const XMMATRIX& local, const XMMATRIX& parent )
{
	XMMATRIX temp = (XMMATRIX)Tr2Renderer::GetInverseViewTransform();
	temp = XMMatrixMultiply( local, temp );

	// Don't use the translation from the camera
	temp._41 = local._41;
	temp._42 = local._42;
	temp._43 = local._43;

	return temp;
}

struct TransformModifierData
{
	enum ModifierFlags
	{
		DEFAULT = 0,
		MODIFIER_INPUT_IS_PARENT_DEPENDENT,
		MODIFIER_IS_VIEW_DEPENDENT,
	};

	BuildInputMatrixType constructInputMatrixFuncPtr;
	CalculateTransformType calculateTransformFuncPtr;
	unsigned modifierFlags;
};

// Functions used to calculate the new matrices for each of the modifiers
static TransformModifierData s_transformModifierInfo[TR2_TOM_MODIFIER_COUNT] = {
	// TR2_TOM_NONE,
	{ 
		BuildAffineTransformInput,	
		CalculateStandardTransform,
		TransformModifierData::DEFAULT
	},
	// TR2_TOM_CAMERA_ALIGNED
	{ 
		BuildCameraAlignedTransformInput,	//
		CalculateCameraAlignedTransform,	// 
		TransformModifierData::MODIFIER_INPUT_IS_PARENT_DEPENDENT | TransformModifierData::MODIFIER_IS_VIEW_DEPENDENT
	}, 
	// TR2_TOM_CAMERA_ALIGNED_WITH_SCALE
	{ 
		BuildCameraAlignedTransformInputWithScale,	//
		CalculateCameraAlignedTransform,	// 
		TransformModifierData::MODIFIER_INPUT_IS_PARENT_DEPENDENT | TransformModifierData::MODIFIER_IS_VIEW_DEPENDENT
	},
	// EVE_TOM_CAMERA_ALIGNED_Z_MODULATED
	{ 
		BuildCameraAlignedTransformInputWithScale, //BuildCameraAlignedTransformInputWithYModulation,	//
		CalculateCameraAlignedTransformWithZModulation,	// 
		TransformModifierData::MODIFIER_INPUT_IS_PARENT_DEPENDENT | TransformModifierData::MODIFIER_IS_VIEW_DEPENDENT
	}
};

// This structure is used to hold temporary data about the
// command list that we are constructing
// since we're pushing back into a vector, use offsets, not pointers
struct MatrixResolutionOrderOffsets
{
	EveTransformItemModifier modifier;
	EveTransformItem* tf;
	unsigned input_matrix_offset;
	unsigned parent_matrix_offset;
	unsigned output_matrix_offset;
	unsigned components_offset;
	EveTransformArray::TransformState tfState;
};

// Temporary structure used to track the input and output matrices for a
// given EveTransformItem
struct TransformLookupInfo
{
	unsigned inputMatrixOffset;
	unsigned outputMatrixOffset;
	bool preMultipliedWithWorldTransform;
};

EveTransformArray::EveTransformArray( IRoot* lockobj /*= NULL */ ):
	PARENTLOCK( m_renderableMeshes ),
	PARENTLOCK( m_transforms ),
	m_alignedTransformMatrices( nullptr ),
	m_alignedTransformComponents( nullptr )
{
	m_renderableMeshes.SetNotify( this );
}

EveTransformArray::~EveTransformArray()
{
	if( m_alignedTransformMatrices )
	{
		CCP_ALIGNED_FREE( m_alignedTransformMatrices );
	}
	if( m_alignedTransformComponents )
	{
		CCP_ALIGNED_FREE( m_alignedTransformComponents );
	}
}

// -------------------------------------------------------------
// Description:
//   Updates transformation information per-frame. Is not based on
//   the parent transformation, since this is not passed in at this point.
//   Additionally, since the top level transform is fairly consistently changing
//   it is more optimal to not multiply that in until the last moment, allowing
//   us to not recompute internal matrix compositions.
// -------------------------------------------------------------
void EveTransformArray::Update( EveUpdateContext& updateContext )
{
	// Do any non-view dependent curve-based updates here
	if( !m_perFrameUpdateList.empty() )
	{
		for( auto i = m_perFrameUpdateList.cbegin(); i != m_perFrameUpdateList.cend(); ++i )
		{
			const TransformUpdateCommand& command = *i;

			XMMATRIX input_matrix = *command.localMatrix;
			const XMMATRIX& parent_matrix = *command.parentMatrix;
			XMMATRIX& output_matrix = *command.outputMatrix;

			if( command.constructInputMatrixFuncPtr != nullptr )
			{
				const XMVECTOR& translation = m_alignedTransformComponents[command.componentsOffset + OFFSET_TRANSLATION];
				const XMVECTOR& rotation = m_alignedTransformComponents[command.componentsOffset + OFFSET_ROTATION];
				const XMVECTOR& scale = m_alignedTransformComponents[command.componentsOffset + OFFSET_SCALE];

				input_matrix = command.constructInputMatrixFuncPtr( 
					parent_matrix, 
					translation,
					rotation,
					scale);	
			}

			output_matrix = command.calculateTransformFuncPtr( input_matrix, parent_matrix );
		}
	}
}

// -------------------------------------------------------------
// Description:
//   Gets the renderable sub-objects, as well as providing the correct point
//   in execution to update any view-dependent information.
//
//   Any transformations that require the world matrix are computed at this point.
//   EveRenderableMesh is updated with the current transform.
// -------------------------------------------------------------
void EveTransformArray::GetRenderables( const TriFrustum& frustum, std::vector<ITr2Renderable*>& renderables, const Matrix& parentTransform )
{
	if( !m_viewDependentUpdateList.empty() )
	{
		UpdateViewDependentData( parentTransform );
	}

	for( auto i = m_internalMeshVector.begin(); i != m_internalMeshVector.end(); ++i )
	{
		PerMeshData& data = *i;
		EveRenderableMesh* mesh = data.mesh;

		// Assuming that the renderable is attached to a valid, resolved transform
		if( data.transform )
		{
			if( data.isPreMultipliedWithWorldTransform )
			{
				mesh->UpdateTransform( (const Matrix)*data.transform );
			}
			else
			{
				const XMMATRIX finalTransform = XMMatrixMultiply( *(data.transform), parentTransform );
				mesh->UpdateTransform( (const Matrix)finalTransform );
			}
		}
		else
		{
			mesh->UpdateTransform( parentTransform );
		}

		renderables.push_back( mesh );
	}
}

// -------------------------------------------------------------
// Description:
//   Provides a way to try and get some transform information out in python
//   Not used (was planned for a utility function to extract sprite-sets)
// -------------------------------------------------------------
Vector3 EveTransformArray::GetWorldPositionLastFrame( EveRenderableMesh* x, Matrix parentTransform ) const
{
	for( auto i = m_internalMeshVector.cbegin(); i != m_internalMeshVector.cend(); ++i )
	{
		const PerMeshData& data = *i;
		if( data.mesh == x )
		{
			// Assuming that the renderable is attached to a valid, resolved transform
			if( data.transform )
			{
				if( data.isPreMultipliedWithWorldTransform )
				{
					return Vector3( data.transform->_41, data.transform->_42, data.transform->_43 );
				}
				else
				{
					const XMMATRIX finalTransform = XMMatrixMultiply( *(data.transform), parentTransform );
					return Vector3( finalTransform._41, finalTransform._42, finalTransform._43 );
				}
			}
			else
			{
				return Vector3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	return Vector3(0.0f, 0.0f, 0.0f);
}

// -------------------------------------------------------------
// Description:
//   Updates the view dependent data. The PREMULTIPLY_WORLD_TRANSFORM
//   state is one of the few remaining states that is needed at runtime
//   Some refactoring might allow us to remove this.
// -------------------------------------------------------------
void EveTransformArray::UpdateViewDependentData( const Matrix& worldTransform )
{
	for( auto i = m_viewDependentUpdateList.cbegin(); i != m_viewDependentUpdateList.cend(); ++i )
	{
		const TransformUpdateCommand& command = *i;

		// Input and parent matrices are local copies, we may need to modify them
		XMMATRIX input_matrix = *command.localMatrix;
		XMMATRIX parent_matrix = *command.parentMatrix;
		XMMATRIX& output_matrix = *command.outputMatrix;

		// If the transform is dependent on its parent, we need to resolve the world transform now
		if( command.tfState & PREMULTIPLY_WORLD_TRANSFORM )
		{
			parent_matrix = XMMatrixMultiply( parent_matrix, worldTransform );
		}

		// Either animated transforms or ones where the input matrix depends on the parent
		if( command.constructInputMatrixFuncPtr != nullptr )
		{
			const XMVECTOR& translation = m_alignedTransformComponents[command.componentsOffset + OFFSET_TRANSLATION];
			const XMVECTOR& rotation = m_alignedTransformComponents[command.componentsOffset + OFFSET_ROTATION];
			const XMVECTOR& scale = m_alignedTransformComponents[command.componentsOffset + OFFSET_SCALE];

			input_matrix = command.constructInputMatrixFuncPtr( 
				parent_matrix, 
				translation,
				rotation,
				scale );
		}

		output_matrix = command.calculateTransformFuncPtr( input_matrix, parent_matrix );
	}
}

// -------------------------------------------------------------
// Description:
//   Allows us to respond to item addition and removal from child lists.
//   We set weak pointers back to ourselves, although this functionality
//   is not really used currently.
//
//   This would allow changes to the transform tree, or the addition / removal
//   of bindings to cause a dynamic rebuild of the transforms.
// -------------------------------------------------------------
void EveTransformArray::OnListModified( long event, ssize_t key, ssize_t key2, IRoot* value, const IList* theList )
{
	// Make sure all the elements of the EveTransformItem have this transform array set as a parent
	// This is so that they can route binding changes directly to us
	if( (event & BELIST_LOADING) == 0  )
	{
		switch( event & BELIST_EVENTMASK )
		{
		case BELIST_INSERTED:
			{
				EveTransformItemPtr object( BlueCastPtr( value ) );
				if( object )
				{
					object->SetTransformArray( this );
				}
			}
			break;
		case BELIST_REMOVED:
			{
				//	If an entry is being removed from the statics list, ensure that it has its parent system cleared
				EveTransformItemPtr object( BlueCastPtr( value ) );
				if( object )
				{
					object->SetTransformArray( nullptr );
				}
			}
			break;
		case BELIST_SWAPPED:
		case BELIST_MOVED:
			break;
		}
	}
	
	RebuildTransformations();
}

void EveTransformArray::RenderDebugInfo( Tr2RenderContext& renderContext )
{
}

void EveTransformArray::SetLowDetail( bool b )
{
}

// --------------------------------------------------------------------------------------
// Description:
//   Helper function that's called recursively for the transform tree, which builds
//   up a vector of input and output matrices and a temporary command list 
//   with information on what needs to be recalculated per-view and per frame.
//
//   It will pre-multiply and collapse what it can, attempting to achieve the fewest matrix 
//   operations. It does not currently collapse constant matrix operations that are below
//   an animated transform.
// --------------------------------------------------------------------------------------
void BuildMatrixHeirachyImpl( 
	PEveTransformItemVector& currentChildren, 
	const Matrix& parentTransform, 
	std::vector<Matrix>& matrices,
	std::vector<Vector4>& components,
	std::map<EveTransformItem*, TransformLookupInfo>& input_output_matrix_lookup, 
	unsigned parentMatrixIndex, 
	std::vector<MatrixResolutionOrderOffsets>& matrixOperationsOffsets,
	unsigned inheritedTransformState )
{

	for( auto i = currentChildren.begin(); i != currentChildren.end(); ++i )
	{
		EveTransformItem& t = **i;
		Matrix input_matrix;
		Matrix output_matrix;

		const unsigned transformModifier = t.GetTransformModifier();

		input_matrix = (Matrix)s_transformModifierInfo[transformModifier].constructInputMatrixFuncPtr( parentTransform, t.GetTranslation(), t.GetRotation(), t.GetScale() );
		output_matrix = (Matrix)s_transformModifierInfo[transformModifier].calculateTransformFuncPtr( input_matrix, parentTransform );
		
		// Reserve the matrix slots
		const unsigned input_matrix_offset = (unsigned int)matrices.size();
		const unsigned output_matrix_offset = input_matrix_offset + 1;

		matrices.push_back( input_matrix );
		matrices.push_back( output_matrix );

		// We inherit our state from the parent
		unsigned localTransformState = inheritedTransformState;
		unsigned modifierFlags = s_transformModifierInfo[transformModifier].modifierFlags;

		// A given transform is view dependent either because of its parent is
		// or because it is itself
		if( TransformModifierData::MODIFIER_IS_VIEW_DEPENDENT & modifierFlags )
		{
			localTransformState |= EveTransformArray::VIEW_DEPENDENT;
		}
		
		const bool transformIsAnimated = t.HasBindings();
		if( transformIsAnimated )
		{
			localTransformState |= EveTransformArray::ANIMATED_TRANSFORM;
		}

		// if the function for the input matrix is parent dependent, then we need to multiply the world-matrix in at the start
		const bool inputMatrixIsParentDependent = TransformModifierData::MODIFIER_INPUT_IS_PARENT_DEPENDENT & modifierFlags;
		
		// Make sure that our child transforms know that they're dealing with a world-transform
		const unsigned components_offset = (unsigned int)components.size();
		const bool store_components = transformIsAnimated || inputMatrixIsParentDependent;

		if( store_components )
		{
			// Same order as OFFSET_TRANSLATION
			components.push_back( Vector4( t.GetTranslation(), 0.0f ) );
			components.push_back( Vector4( (float*)&t.GetRotation() ) );
			components.push_back( Vector4( t.GetScale(), 0.0f ) );

			if( inputMatrixIsParentDependent && !(localTransformState & EveTransformArray::PREMULTIPLIED_WORLD_TRANSFORM_IN_PARENT) )
			{
				// This is the first
				localTransformState |= EveTransformArray::PREMULTIPLY_WORLD_TRANSFORM;
			}
		}

		// When we look up this matrix for the renderables, we need to know not to multiply the world-matrix in
		TransformLookupInfo tfInfo = { input_matrix_offset, 
									   output_matrix_offset, 
									   (bool)(localTransformState & EveTransformArray::IN_WORLD_COORDINATES) };

		auto keyVal = std::make_pair( &t, tfInfo );
		input_output_matrix_lookup.insert( keyVal );

		MatrixResolutionOrderOffsets usage = {
			(EveTransformItemModifier)(transformModifier),
			&t,
			input_matrix_offset, 
			parentMatrixIndex, 
			output_matrix_offset,
			components_offset,
			(EveTransformArray::TransformState)localTransformState };

		matrixOperationsOffsets.push_back( usage );

		// If we pre-multiply the world-matrix, we don't want children to do the same
		unsigned transformStateForChildren = localTransformState;
		if( transformStateForChildren & EveTransformArray::PREMULTIPLY_WORLD_TRANSFORM )
		{
			// Remove the pre-multiply flag, we only want this to be done once
			transformStateForChildren ^= EveTransformArray::PREMULTIPLY_WORLD_TRANSFORM;
			transformStateForChildren |= EveTransformArray::PREMULTIPLIED_WORLD_TRANSFORM_IN_PARENT;
		}
		// If we are animated, our children have an animated parent
		if( transformStateForChildren & EveTransformArray::ANIMATED_TRANSFORM )
		{
			// Remove the animated flag
			transformStateForChildren ^= EveTransformArray::ANIMATED_TRANSFORM;
			transformStateForChildren |= EveTransformArray::ANIMATED_PARENT;
		}

		BuildMatrixHeirachyImpl( 
			t.GetChildren(),
			output_matrix,
			matrices,
			components,
			input_output_matrix_lookup,
			output_matrix_offset,
			matrixOperationsOffsets,
			transformStateForChildren );
	}
}

// --------------------------------------------------------------------------------------
// Description:
//   Cause a rebuild of the transform heirachy and a re-evaluation of transforms.
//   This is needed when:
//     Bindings are added to EveTransformObects
//     Transformations are changed (added, deleted, modified)
// --------------------------------------------------------------------------------------
void EveTransformArray::RebuildTransformations()
{
	if( m_alignedTransformMatrices )
	{
		CCP_ALIGNED_FREE( m_alignedTransformMatrices );
		m_alignedTransformMatrices = nullptr;
		m_alignedTransformMatrixCount = 0;
	}

	if( m_alignedTransformComponents )
	{
		CCP_ALIGNED_FREE( m_alignedTransformComponents );
		m_alignedTransformComponents = nullptr;
		m_alignedTransformComponentCount = 0;
	}

	m_internalMeshVector.clear();
	m_transformUpdateList.clear();
	m_perFrameUpdateList.clear();
	m_viewDependentUpdateList.clear();

	std::map<EveTransformItem*, TransformLookupInfo> input_output_matrix_lookup;

	// Use standard matrices for this as temporaries, since they don't have to be aligned
	std::vector<Matrix> matrices;
	std::vector<MatrixResolutionOrderOffsets> matrixOperationsOffsets;
	std::vector<Vector4> components;

	Matrix identityMatrix = (Matrix)XMMatrixIdentity();
	auto& parentTransform = identityMatrix;

	// position 0 is reserved for the identity
	matrices.push_back( identityMatrix );
	unsigned parentMatrixIndex = 0;

	auto& currentChildren = m_transforms;

	BuildMatrixHeirachyImpl(
		currentChildren, 
		parentTransform, 
		matrices,
		components,
		input_output_matrix_lookup, 
		parentMatrixIndex, 
		matrixOperationsOffsets,
		NO_INHERITED_TRANSFORM_STATE 
		);

	// Build the allocated XMMatrix structures, which are aligned
	m_alignedTransformMatrices = (XMMATRIX*)CCP_ALIGNED_MALLOC( "EveTransformArray/Matrices", sizeof(XMMATRIX)*matrices.size(), 16 );
	m_alignedTransformMatrixCount = (unsigned int)matrices.size();

	for( size_t i = 0; i < matrices.size();  ++i )
	{
		m_alignedTransformMatrices[i] = matrices[i];
	}
	
	m_alignedTransformComponents = (XMVECTOR*)CCP_ALIGNED_MALLOC( "EveTransformArray/Components", sizeof(XMVECTOR)*components.size(), 16 );
	m_alignedTransformComponentCount = (unsigned int)components.size();
	
	for( unsigned i = 0; i < components.size(); ++i )
	{
		m_alignedTransformComponents[i] = components[i];
	}

	m_transformUpdateList.reserve( matrixOperationsOffsets.size() ); 
	for( auto i = matrixOperationsOffsets.begin(); i != matrixOperationsOffsets.end(); ++i )
	{
		TransformUpdateCommand o = { 
			i->modifier,
			i->tfState,
			nullptr,
			s_transformModifierInfo[i->modifier].calculateTransformFuncPtr,
			i->components_offset,
			&m_alignedTransformMatrices[i->parent_matrix_offset], 
			&m_alignedTransformMatrices[i->input_matrix_offset], 
			&m_alignedTransformMatrices[i->output_matrix_offset] };

		// Only set this function if the input matrix needs rebuilding
		if( (TransformModifierData::MODIFIER_INPUT_IS_PARENT_DEPENDENT & s_transformModifierInfo[i->modifier].modifierFlags) 
				|| (i->tfState & ANIMATED_TRANSFORM) )
		{
			// Set the function pointer on the resolution order
			o.constructInputMatrixFuncPtr = s_transformModifierInfo[i->modifier].constructInputMatrixFuncPtr;
		}

		// Animated transforms will have stored components
		// We need to point the TriValueBindings at our allocated memory
		if( i->tfState & ANIMATED_TRANSFORM )
		{
			EveTransformItem* tf = i->tf;
			// Route the bindings to the aligned vectors
			XMVECTOR* baseComponent = &m_alignedTransformComponents[i->components_offset];
			tf->SetTranslationBindingDestination(	(float*)&baseComponent[ OFFSET_TRANSLATION ] );
			tf->SetRotationBindingDestination(		(float*)&baseComponent[ OFFSET_ROTATION ] );
			tf->SetScaleBindingDestination(			(float*)&baseComponent[ OFFSET_SCALE ] );	
		}

		if( !(i->tfState & VIEW_DEPENDENT) )
		{
			// view independent
			if( i->tfState & (ANIMATED_PARENT | ANIMATED_TRANSFORM) )
			{
				// Updated in Update
				m_perFrameUpdateList.push_back( o );
			}
			else
			{
				// Not updated
				m_transformUpdateList.push_back( o );
			}
		}
		else
		{
			// Updated in UpdateViewDependentData
			// This happens at least as frequently as Update() and possibly more
			m_viewDependentUpdateList.push_back( o );
		}
	}

	// Associate the renderable meshes with an output matrix
	for( auto i = m_renderableMeshes.begin(); i != m_renderableMeshes.end(); ++i )
	{
		EveRenderableMesh* mesh = *i;
		EveTransformItem* transform_for_mesh = mesh->GetTransformObject();

		auto matrices_for_transform = input_output_matrix_lookup.find( transform_for_mesh );

		if( matrices_for_transform != input_output_matrix_lookup.end() )
		{
			TransformLookupInfo& tfInfo = matrices_for_transform->second;
			PerMeshData d = { mesh, tfInfo.preMultipliedWithWorldTransform, &m_alignedTransformMatrices[ tfInfo.outputMatrixOffset ] };
			m_internalMeshVector.push_back( d );
		}
		else
		{
			PerMeshData d = { mesh, false, nullptr };
			m_internalMeshVector.push_back( d );
		}
	}
}

bool EveTransformArray::Initialize()
{
	for (auto i = m_transforms.begin(); i != m_transforms.end(); ++i )
	{
		(*i)->SetTransformArray( this );
	}
	RebuildTransformations();

	return true;
}


