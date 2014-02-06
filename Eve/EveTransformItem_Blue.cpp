#include "StdAfx.h"
#include "EveTransformItem.h"

BLUE_DEFINE( EveTransformItem );

Be::VarChooser EveTransformItemModifierChooser[] =
{
	{ 
		"EVE_TOM_NONE", 
		BeCast(EVE_TOM_NONE), 
		"A standard affine transformation" 
	},
	{ 
		"EVE_TOM_CAMERA_ALIGNED", 
		BeCast(EVE_TOM_CAMERA_ALIGNED), 
		"Camera aligned transformation" 
	},
	{
		"EVE_TOM_CAMERA_ALIGNED_WITH_SCALE",
		BeCast(EVE_TOM_CAMERA_ALIGNED_WITH_SCALE),
		"Camera aligned transformation that preserves scale"
	},
	{
		"EVE_TOM_CAMERA_ALIGNED_Z_MODULATED",
		BeCast(EVE_TOM_CAMERA_ALIGNED_Z_MODULATED),
		"Camera aligned transformation that scales by angle between Z and camera direction."
	},
	{ 0 }
};

BLUE_REGISTER_ENUM_EX( "EveTransformItemModifier", EveTransformItemModifier, EveTransformItemModifierChooser, ENUM_REG_ENUM_OBJECT_ON_MODULE );

const Be::ClassInfo* EveTransformItem::ExposeToBlue()
{	
	EXPOSURE_BEGIN(EveTransformItem, "")
		MAP_INTERFACE(EveTransformItem)
		MAP_INTERFACE(ITriReroutable)
		MAP_ATTRIBUTE( "name", m_name, "name of the transform", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE_WITH_CHOOSER( "modifier", m_modifer, "A transformation modifier, allowing it to do things like face the camera", Be::READWRITE | Be::PERSIST | Be::ENUM, EveTransformItemModifierChooser )
		MAP_ATTRIBUTE( "translation", m_translation, "translation of this object", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "scale", m_scale, "scale of this object", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "rotation", m_rotation, "rotation of this object", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "children", m_children, "children", Be::READWRITE | Be::PERSIST )
	EXPOSURE_END()
}