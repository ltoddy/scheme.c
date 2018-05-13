#ifndef SCHEME_C_ENVIRONMENT_H
#define SCHEME_C_ENVIRONMENT_H

#include "object.h"

extern SchemeObject* FirstFrame(SchemeObject* environ);

extern SchemeObject* FrameVariables(SchemeObject* frame);

extern SchemeObject* FrameValues(SchemeObject* frame);

extern void AddBindingToFrame(SchemeObject* var, SchemeObject* val, SchemeObject* frame);

extern SchemeObject* LookupVariableValue(SchemeObject* var, SchemeObject* environ);

extern void SetVariableValue(SchemeObject* var, SchemeObject* val, SchemeObject* environ);

extern SchemeObject* SetupEnvironment();

#endif //SCHEME_C_ENVIRONMENT_H
