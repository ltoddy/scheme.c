#ifndef SCHEME_C_ENVIRONMENT_H
#define SCHEME_C_ENVIRONMENT_H

#include "object.h"

extern SchemeObject* TheEmptyEnvironment;
extern SchemeObject* TheGlobalEnvironment;

extern SchemeObject* FirstFrame(SchemeObject* environ);

extern SchemeObject* FrameVariables(SchemeObject* frame);

extern SchemeObject* FrameValues(SchemeObject* frame);

extern void AddBindingToFrame(SchemeObject* var, SchemeObject* val, SchemeObject* frame);

extern SchemeObject* ExtendEnvironment(SchemeObject* var, SchemeObject* val, SchemeObject* base_environ);

extern SchemeObject* LookupVariableValue(SchemeObject* var, SchemeObject* environ);

extern void SetVariableValue(SchemeObject* var, SchemeObject* val, SchemeObject* environ);

extern SchemeObject* SetupEnvironment();

extern SchemeObject* InteractionEnvironmentProc(SchemeObject* arguments);

extern SchemeObject* NullEnvironmentProc(SchemeObject* arguments);

extern SchemeObject* EnvironemntProc(SchemeObject* arguments);

extern SchemeObject* MakeEnvironment();

extern SchemeObject* EvalProc(SchemeObject* arguments);

#endif //SCHEME_C_ENVIRONMENT_H
