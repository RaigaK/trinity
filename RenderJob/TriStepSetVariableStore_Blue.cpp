#include "StdAfx.h"
#include "TriStepSetVariableStore.h"
#include "Resources/TriTextureRes.h"
#include "Tr2DepthStencil.h"
#include "Tr2RenderTarget.h"

BLUE_DEFINE( TriStepSetVariableStore );

// --------------------------------------------------------------------------------------
// Description:
//   Blue-exposed initializer. 
// --------------------------------------------------------------------------------------
#if BLUE_WITH_PYTHON
void TriStepSetVariableStore::py__init__( Be::Optional<std::string> name, PyObject* value )
{
	if( name.IsAssigned() )
	{
		SetName( name );
	}
	if( value && value != Py_None )
	{
		SetValue( value );
	}
}

PyObject* TriStepSetVariableStore::GetValue()
{
	if( m_type == TRIVARIABLE_TEXTURE_RES )
	{
		return PyOS->WrapBlueObject( m_textureRes->GetRawRoot() );
	}
	else if( m_type == TRIVARIABLE_IROOT )
	{
		return PyOS->WrapBlueObject( m_object );
	}
	else if( m_type == TRIVARIABLE_TEXTURE_AL )
	{
		if( m_depthStencil )
		{
			return PyOS->WrapBlueObject( m_depthStencil->GetRawRoot() );
		}
		if( m_renderTarget )
		{
			return PyOS->WrapBlueObject( m_renderTarget->GetRawRoot() );
		}
		Py_RETURN_NONE;
	}
	else
	{
		// TODO
		Py_RETURN_NONE;
	}
}

void TriStepSetVariableStore::SetValue( PyObject* valueArg )
{
	const unsigned valueArgPosition = 0;

	Tr2DepthStencil* valDepthStencil;
	Tr2RenderTarget* valRenderTarget;
	TriTextureRes* valTextureRes; // TRIVARIABLE_TEXTURE_RES,
	int valInt; // TRIVARIABLE_INT,
	float valFloat; // TRIVARIABLE_FLOAT,
	Vector2 valVector2; // TRIVARIABLE_FLOAT2,
	Vector3 valVector3; // TRIVARIABLE_FLOAT3,
	Vector4 valVector4; // TRIVARIABLE_FLOAT4,
	Matrix valMatrix; // TRIVARIABLE_FLOAT4X4,
	Color valColor; // TRIVARIABLE_COLOR,
	IRoot* valIroot; // TRIVARIABLE_IROOT,

	if( BlueExtractArgument( valueArg, valDepthStencil, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_TEXTURE_AL;
		m_depthStencil = valDepthStencil;		
	}
	else 
	if( BlueExtractArgument( valueArg, valRenderTarget, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_TEXTURE_AL;
		m_renderTarget = valRenderTarget;
	}
	else 
	if( BlueExtractArgument( valueArg, valTextureRes, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_TEXTURE_RES;
		m_textureRes = valTextureRes;
		m_texture.Unlock();
	}
	else if( BlueExtractArgument( valueArg, valInt, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_INT;
		memcpy( m_data, &valInt, sizeof( valInt ) );
	}
	else if( BlueExtractArgument( valueArg, valFloat, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_FLOAT;
		memcpy( m_data, &valFloat, sizeof( valFloat ) );
	}
	else if( BlueExtractArgument( valueArg, valVector2, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_FLOAT2;
		memcpy( m_data, &valVector2, sizeof( valVector2 ) );
	}
	else if( BlueExtractArgument( valueArg, valVector3, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_FLOAT3;
		memcpy( m_data, &valVector3, sizeof( valVector3 ) );
	}
	else if( BlueExtractArgument( valueArg, valVector4, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_FLOAT4;
		memcpy( m_data, &valVector4, sizeof( valVector4 ) );
	}
	else if( BlueExtractArgument( valueArg, valMatrix, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_FLOAT4X4;
		memcpy( m_data, &valMatrix, sizeof( valMatrix ) );
	}
	else if( BlueExtractArgument( valueArg, valColor, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_COLOR;
		memcpy( m_data, &valColor, sizeof( valColor ) );
	}
	else if( BlueExtractArgument( valueArg, valIroot, valueArgPosition ) )
	{
		m_type = TRIVARIABLE_IROOT;
		m_object = valIroot;
	}

	PyErr_Clear();
}
#endif

const Be::ClassInfo* TriStepSetVariableStore::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriStepSetVariableStore, "Render step for setting a variable in variable store" )

		MAP_INTERFACE( TriRenderStep )
		MAP_INTERFACE( TriStepSetVariableStore )

#if BLUE_WITH_PYTHON
		MAP_METHOD_AND_WRAP_OPTIONAL_ARGS
		( 
			"__init__", 
			py__init__,
			2,
			"Create a render step that sets a variable value to the variable store"
			"\n"
			"\nOptional Arguments:"
			"\nname - string name of the variable"
			"\nvalue - a valid python object to set"
		)
#endif
		MAP_ATTRIBUTE( "variableName", m_variableName, "The name of the Tr2VariableStore variable to set", Be::READWRITE | Be::PERSIST )
#if BLUE_WITH_PYTHON
		MAP_PROPERTY( "value", GetValue, SetValue, "Setter for the variable store value" )
#endif

	EXPOSURE_CHAINTO( TriRenderStep )
}