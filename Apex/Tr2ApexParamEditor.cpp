#include "StdAfx.h"

#if APEX_ENABLED

#include "Tr2ApexParamEditor.h"
//#include "ApexParamEditor.h"

#if USE_APEX_PARAM_EDITOR

class ApexParamEditor : public Tr2ApexParamEditor
{
public:
	ApexParamEditor(void)
	{
	}

	virtual void edit(class Tr2ApexEmitterActor *emitter)
	{

	}

	virtual void release(void)
	{
		CCP_DELETE(this);
	}

	virtual ~ApexParamEditor(void)
	{
	};

};

Tr2ApexParamEditor * createApexParamEditor(void)
{
  ApexParamEditor *ret = CCP_NEW("ApexParamEditor")ApexParamEditor;
  return static_cast< Tr2ApexParamEditor * >(ret);
}

#endif

#endif