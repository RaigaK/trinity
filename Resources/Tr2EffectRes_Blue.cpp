#include "StdAfx.h"
#include "Tr2EffectRes.h"

BLUE_DEFINE( Tr2EffectRes );

#if BLUE_WITH_PYTHON
PyObject* PyGetShaderInputDefinition( PyObject* self, PyObject* args )
{
	Tr2EffectRes* pThis = BluePythonCast<Tr2EffectRes*>( self );
	if( !pThis || !pThis->IsGood() )
	{
		PyErr_SetString(PyExc_RuntimeError, "Tr2EffectRes.GetShaderInputDefinition: invalid effect resource");
		return NULL;
	}
	int pass, shaderType;
	if( !PyArg_ParseTuple( args, "ii", &pass, &shaderType ) )
	{
		PyErr_SetString(PyExc_RuntimeError, "Tr2EffectRes.GetShaderInputDefinition: expects to integer parameters");
		return NULL;
	}
	const Tr2ShaderInputDefinition* definition = pThis->GetShaderInputDefinition( pass, Tr2RenderContextEnum::ShaderType( shaderType ) );
	if( !definition )
	{
		PyErr_SetString(PyExc_RuntimeError, "Tr2EffectRes.GetShaderInputDefinition: failed to get shader input definition");
		return NULL;
	}

	PyObject *result =  PyTuple_New( definition->elements.size() );
	for( unsigned i = 0; i < definition->elements.size(); ++i )
	{
		const Tr2ShaderInputDefinitionElement& element = definition->elements[i];
		PyTuple_SET_ITEM(result, i, Py_BuildValue("(iiii)", element.usage, element.usageIndex, element.registerIndex, element.usedMask ) ); 
	}
	return result;
}
#endif

const Be::ClassInfo* Tr2EffectRes::ExposeToBlue()
{
	EXPOSURE_BEGIN( Tr2EffectRes, "" )

		MAP_INTERFACE( Tr2EffectRes )
		MAP_INTERFACE( IBlueResource )
		MAP_INTERFACE( ICacheable )
		MAP_ICACHEABLE_METHODS()

		MAP_PROPERTY_READONLY( "passCount", GetPassCount, "Number of passes used in the effect.")
		MAP_PROPERTY_READONLY( "sortValue", GetSortValue, "Sort value used when rendering sorted by effect.")

		MAP_METHOD( 
			"GetShaderInputDefinition", 
			PyGetShaderInputDefinition, 
			"Returns shader input definition (inputs from graphics pipeline).\n"
			"Result is an n-tuple of tuples (usage, usageIndex, inputRegisterIndex, usageMask).\n" 
			"\nArguments:"
			"\npass : Pass index"
			"\nshader : Shader type" 
			);

	EXPOSURE_CHAINTO( BlueAsyncRes )
}
