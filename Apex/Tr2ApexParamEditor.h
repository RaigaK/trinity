#ifndef APEX_PARAM_EDITOR_H

#define APEX_PARAM_EDITOR_H

#include "Apex.h"

#if USE_APEX_PARAM_EDITOR

class Tr2ApexParamEditor
{
public:
	virtual void edit(class Tr2ApexEmitterActor *emitter) = 0;
	virtual void release(void) = 0;
protected:
	virtual ~Tr2ApexParamEditor(void) { };
};

Tr2ApexParamEditor * createApexParamEditor(void);

#endif

#endif
