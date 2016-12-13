#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2ClothingActor.h"
#include "Resources/TriGrannyRes.h"

BLUE_DEFINE( Tr2ClothingActor );

#if BLUE_WITH_PYTHON

static PyObject* PySetMorphResWeights( PyObject* self, PyObject* args )
{
	Tr2ClothingActor* pThis = BluePythonCast<Tr2ClothingActor*>( self );
	if( !pThis )
	{
		Py_RETURN_FALSE;
	}

	PyObject* pWeights = NULL;
	if( !PyArg_ParseTuple( args, "O", &pWeights ) )
	{
		Py_RETURN_FALSE;
	}

	if( !PyList_Check( pWeights ) )
	{
		Py_RETURN_FALSE;
	}

	unsigned int n = (unsigned int)PyList_Size( pWeights );
	std::vector<float> &weights = pThis->m_morphResWeights;
	weights.resize( n );

	for( unsigned int i = 0; i < n; ++i )
	{
		float item = (float)PyFloat_AsDouble( PyList_GetItem( pWeights, i ) );
		weights[i] = item;
	}

	Py_RETURN_NONE;
}

#endif

const Be::ClassInfo* Tr2ClothingActor::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2ClothingActor, "" )
#if APEX_ENABLED
        MAP_INTERFACE( Tr2ClothingActor )
		MAP_INTERFACE( IInitialize )

		MAP_ATTRIBUTE( "name", m_name, "", Be::READWRITE | Be::PERSIST )
		MAP_PROPERTY( "resPath", GetResPath, SetResPath, "Resource path to clothing asset file" )
		MAP_ATTRIBUTE( "resPath", m_resPath, "", Be::PERSISTONLY )
		MAP_ATTRIBUTE( "clothingRes", m_clothingRes, "Resource loaded from resPath", Be::READ )

		MAP_ATTRIBUTE( "effect", m_effect, "Effect used to render the cloth asset", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "depthEffect", m_depthEffect, "Effect used to render the cloth asset into shadow map", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "depthNormalEffect", m_depthNormalEffect, "Effect used to render the cloth asset during pre pass", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "effectReversed", m_effectReversed, "Effect used to render the cloth asset with triangles in reversed order", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "depthEffectReversed", m_depthEffectReversed, "Effect used to render the cloth asset into shadow map with triangles in reversed order", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "depthNormalEffectReversed", m_depthNormalEffectReversed, "Effect used to render the cloth asset during pre pass with triangles in reversed order", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "morphRes", m_morphRes, "TriGrannyRes to be used for morph targets", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "morphResMeshIndex", m_morphResMeshIndex, "MeshIndex in morphRes to be used for morph targets", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "morphResEpsilon", m_morphResEpsilon, "Tolerance for mapping morphRes vertices to cloth vertices", Be::READWRITE | Be::PERSIST )
		MAP_METHOD( 
			"SetMorphResWeights", 
			PySetMorphResWeights, 
			"Sets the list of floats with the blend weights; the length should match the number of morph targets\n"
			":param weights: list of weights\n"
			":type weights: list[float]\n"
			":rtype: bool | None"
			)
		MAP_METHOD_AND_WRAP( "GetWorldBoundingBox", GetWorldBoundingBox, "Returns two vec3s with the bounding box of this actor." )

		MAP_PROPERTY
		( 
			"visualize", 
			GetVisualize, 
			SetVisualize, 
			"Enable PhysX debug visualization for this particular actor."
		)

		MAP_ATTRIBUTE( "isInScene", m_isInScene, "Has the actor been added to a scene.", Be::READ )

		MAP_ATTRIBUTE( "windStrength", m_windStrength, "Strength of wind affecting this cloth.", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "windDirection", m_windDirection, "Direction of wind affecting this cloth.", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "blendVelocity", m_blendVelocity, "Factor to determine how fast blending between different physics lod's occur.", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "resetCloth", m_resetCloth, "If true, the next update will force the cloth to be skinned, and then reset this flag to false.", Be::READWRITE )

		MAP_ATTRIBUTE( "maxDistance", m_maxDistance, "The benefit of an actor should fall off linearly with eye-distance from zero to this maxDistance.", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "distanceWeight", m_distanceWeight, "The weight of the distance-benefit in the benefit function", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "bias", m_bias, "Bias of the distance formula", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "benefitBias", m_benefitBias, "Bias of the overall benefit", Be::READWRITE | Be::PERSIST )

		MAP_PROPERTY
		( 
			"stretchingStiffness", 
			GetStretchingStiffness,
			SetStretchingStiffness,
			"The stretching stiffness of a cloth/softbody. See also 'hardStretchLimitation'."
		)

		MAP_ATTRIBUTE
		(
			"_stretchingStiffness",
			m_stretchingStiffness,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"bendingStiffness", 
			GetBendingStiffness,
			SetBendingStiffness,
			"The bending stiffness of a cloth/softbody."
		)

		MAP_ATTRIBUTE
		(
			"_bendingStiffness",
			m_bendingStiffness,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"orthoBending", 
			GetOrthoBending,
			SetOrthoBending,
			"A more accurate bending force, comes with a performance penalty."
		)

		MAP_ATTRIBUTE
		(
			"_orthoBending",
			m_orthoBending,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"damping", 
			GetDamping,
			SetDamping,
			"The amount of damping per constraint."
		)

		MAP_ATTRIBUTE
		(
			"_damping",
			m_damping,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"comDamping", 
			GetComDamping,
			SetComDamping,
			"Damping around the COM of the Cloth instead of on each constraint. Only of limited use for clothing."
		)

		MAP_ATTRIBUTE
		(
			"_comDamping",
			m_comDamping,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"friction", 
			GetFriction,
			SetFriction,
			"The friction between cloth/softbody and rigid bodies."
		)

		MAP_ATTRIBUTE
		(
			"_friction",
			m_friction,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"solverIterations", 
			GetSolverIterations,
			SetSolverIterations,
			"Maximum number of solver iterations permitted, lower physical LoDs will only have a fraction of this value."
		)

		MAP_ATTRIBUTE
		(
			"_solverIterations",
			m_solverIterations,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"gravityScale", 
			GetGravityScale,
			SetGravityScale,
			"Modifies the amount of gravity that is applied to this piece of clothing."
			"\n	Values higher than 1.0 will generate accelerations higher than gravity."
			"\nValues between 0.0 and 1.0 will generate moon gravity."
		)

		MAP_ATTRIBUTE
		(
			"_gravityScale",
			m_gravityScale,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"hardStretchLimitation", 
			GetHardStretchLimitation,
			SetHardStretchLimitation,
			"Project some constraints to enforce stretch limitations. Must be in [1, inf) or 0 to disable."
		)

		MAP_ATTRIBUTE
		(
			"_hardStretchLimitation",
			m_hardStretchLimitation,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"maxDistanceBias", 
			GetMaxDistanceBias,
			SetMaxDistanceBias,
			"Deformation factor of the max distance sphere, must be in [-1, 1] range, 0 to turn off."
			"\nThe sphere will transform into the normal of a vertex the more this value goes towards -1."
			"\nThe sphere will transform into a disc perpendicular to the normal the more this value goes towards 1."
		)

		MAP_ATTRIBUTE
		(
			"_maxDistanceBias",
			m_maxDistanceBias,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"maxDistanceScale", 
			GetMaxDistanceScale,
			SetMaxDistanceScale,
			"Scale factor on the max distance, range 0...1 (multiplier)."			
		)

		MAP_ATTRIBUTE
		(
			"_maxDistanceScale",
			m_maxDistanceScale,
			"",
			Be::PERSISTONLY
		)

		MAP_PROPERTY
		( 
			"hierarchicalSolverIterations", 
			GetHierarchicalSolverIterations,
			SetHierarchicalSolverIterations,
			"Number of hierarchical solver iterations, 0 to turn off."
			"\nIf either the hierarchical solver iterations or the hierarchical levels are set to 0, this feature is turned off"
		)

		MAP_ATTRIBUTE
		(
			"_hierarchicalSolverIterations",
			m_hierarchicalSolverIterations,
			"",
			Be::PERSISTONLY
		)

		MAP_ATTRIBUTE
		(
			"useTransparentBatches",
			m_useTransparentBatches,
			"Emit this apex mesh as transparent batches? False by default, making it Decal.",
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"useSHLighting",
			m_useSHLighting,
			"Use SH lighting instead of direct (for transparent meshes only). False by default.",
			Be::READWRITE | Be::PERSIST
		)
#endif // APEX_ENABLED
	EXPOSURE_END()
}

#endif
