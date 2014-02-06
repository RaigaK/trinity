#pragma once
#ifndef EveTransformObject_H
#define EveTransformObject_H

#include "ITriReroutable.h"

BLUE_DECLARE( EveTransformItem );
BLUE_DECLARE_VECTOR( EveTransformItem );
BLUE_DECLARE( EveTransformArray );

// Modifiers for how the transforms work
// If you add things to this enum (try not to!) then you need to update
// the chooser in ..._Blue, and the lookup functions in EveTransformArray.cpp
enum EveTransformItemModifier
{
	// The standard transformation
	EVE_TOM_NONE,

	// Camera Aligned. Translated, but rotated to point Z at camera.
	// Rotation and Scale are not inherited
	EVE_TOM_CAMERA_ALIGNED,

	// Camera Aligned. Translated, but rotated to point Z at camera.
	// Scale is preserved
	EVE_TOM_CAMERA_ALIGNED_WITH_SCALE,

	// Camera Aligned. Translated, but rotated to point Z at camera.
	// Scale is preserved, but modified by the angle between the 
	// object's previous Z axis and camera direction.
	EVE_TOM_CAMERA_ALIGNED_Z_MODULATED,

	// ....
	TR2_TOM_MODIFIER_COUNT,
	TR2_TOM_FORCE_DWORD = 0xffffffff
};

//////////////////////////////////////////////////////////////////////////
// Description:
//   EveTransformItem is a simplified EveTransform. It is used only to
//   store a description of the transformation hierarchy for the
//   EveTransformArray, and to track bindings to those transformations.
//   It is not dynamically updated at runtime, and users will need to 
//   rebuild the TransformArray to see changes.
//
// TODO:
//   The magic behind rerouting multiple bindings on different variables
//   does not work perfectly with the ITriReroutable interface, which
//   assumes that there is only a single value per object that is rerouted
//   (see GetDestination/SetDestination). If we knew which variable it was
//   bound against, then we could do a better job here.
//   GetDestination is used by TriVariableBinding. The most consistent thing
//   there would be to pass in a Be::Var pointer for the variable as an argument.
//   SetDestination is used by EveTransformArray and Tr2Effect etc, so
//   those systems don't nessecarily want to know about the exposure of
//   the EveTransformItem though.
//////////////////////////////////////////////////////////////////////////
class EveTransformItem:
	public ITriReroutable,
	public IListNotify
{
public:
	EXPOSE_TO_BLUE();

	EveTransformItem( IRoot* lockobj = NULL );
	~EveTransformItem();

	//////////////////////////////////////////////////////////////////////////
	// IListNotify
	//////////////////////////////////////////////////////////////////////////
	// Used to maintain a correct 'parent' EveTransformArray for all the
	// EveTransformObjects

	void OnListModified(
		long event,		// BLUELISTEVENT values
		ssize_t key,
		ssize_t key2,
		IRoot* value,
		const IList* theList
		);

	//////////////////////////////////////////////////////////////////////////
	// ITriReroutable
	//////////////////////////////////////////////////////////////////////////
	// This allows us to capture curveset bindings to the
	// translation, scale and rotation, and send them to the Tr2TransformArray
	// it also allows us to detect that there are bindings when we build it

	// Not implemented, each parameter must be routed to a different location
	void SetDestination( void* dest, size_t size ) {}

	// This doesn't make sense without a binding as an argument
	// because we don't have the same destination for every binding
	// Make sure it returns an invalid result (size = 0)
	void GetDestination( void*& dest, size_t& size )
	{
		size = 0;
	}

	// Called by TriValueBinding when it attaches to a value
	void RegisterBinding( TriValueBinding* vb );

	// Called by TriValueBinding when it unattaches
	void UnregisterBinding( TriValueBinding* vb );

	// Nothing really cares about this
	bool IsRerouted() const
	{
		return true;
	}

	// For routing curve-set updated changes to the TransformArray
	void SetTransformArray( EveTransformArray* parent );
	
	// Allows EveTransformArray to check if it needs to treat this transform dynamically
	bool HasBindings() const;

	// Makes the assumption that there's only a single binding to the translation
	// Allows EveTransformArray to point any binding to the aligned memory that is
	// reserved for animated parameters
	void SetTranslationBindingDestination( float* destination );
	void SetRotationBindingDestination( float* destination );
	void SetScaleBindingDestination( float* destination );

	// Rotation accessor
	const Quaternion& GetRotation() const
	{
		return m_rotation;
	}

	// Scale Accessor
	const Vector3& GetScale() const
	{
		return m_scale;
	}

	// Translation Accessor
	const Vector3& GetTranslation() const
	{
		return m_translation;
	}

	// Modifier Accessor (EveTransformItemModifier)
	unsigned GetTransformModifier() const
	{
		return m_modifer;
	}

	// Children Accessor
	PEveTransformItemVector& GetChildren()
	{
		return m_children;
	}

private:

	std::string m_name;

	// EveTransformItemModifier
	unsigned m_modifer;

	// The rotation
	Quaternion m_rotation;

	// The Scale
	Vector3 m_scale;

	// The Translation
	Vector3 m_translation;

	// Child transforms
	PEveTransformItemVector m_children;

	// Bindings Weakref
	TriValueBinding* m_translationBinding;
	TriValueBinding* m_rotationBinding;
	TriValueBinding* m_scaleBinding;

	// The array that this transform is under
	EveTransformArray* m_parentArray;
};

TYPEDEF_BLUECLASS( EveTransformItem );

#endif