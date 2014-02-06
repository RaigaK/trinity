#include "StdAfx.h"
#include "TriRenderStep.h"

BLUE_DEFINE_ABSTRACT( TriRenderStep );

const Be::VarChooser TriRenderStepResultChooser[] =
{
	// Name					Value						Docstring
	{ "RS_OK",			BeCast( RS_OK ),			"Render step succeeded" }, 
	{ "RS_FAILED",		BeCast( RS_FAILED ),		"Render failed" },
	{ "RS_IN_PROGRESS",	BeCast( RS_IN_PROGRESS ),	"Render is still in progress" },
	{0}
};

BLUE_REGISTER_ENUM( "RENDERSTEP_RESULT", TriStepResult, TriRenderStepResultChooser );


const Be::ClassInfo* TriRenderStep::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriRenderStep, "" )

		MAP_INTERFACE( TriRenderStep )

		MAP_ATTRIBUTE
		(
			"name", 
			m_name, 
			"Name of this step (for the benefit of the user)", 
			Be::READWRITE | Be::PERSIST
		)

		MAP_ATTRIBUTE
		(
			"enabled", 
			m_enabled, 
			"Enabled/disabled flag: disabled steps are not executed", 
			Be::READWRITE
		)

	EXPOSURE_END()
}