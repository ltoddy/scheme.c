#ifndef SCHEME_C_ENVIRONMENT_H
#define SCHEME_C_ENVIRONMENT_H

#include "object.h"

extern SchemeObject* TheEmptyEnvironment;
extern SchemeObject* TheGlobalEnvironment;
extern SchemeObject* DefineSymbol;
extern SchemeObject* SetSymbol;
extern SchemeObject* OkSymbol;

extern SchemeObject* LookupVariableValue(SchemeObject* var, SchemeObject* environ);

extern void SetVariableValue(SchemeObject* var, SchemeObject* val, SchemeObject* environ);

extern void DefineVariable(SchemeObject* var, SchemeObject* val, SchemeObject* environ);

extern void InitEnvironment();

#endif //SCHEME_C_ENVIRONMENT_H
