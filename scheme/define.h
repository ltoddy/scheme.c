#ifndef SCHEME_C_DEFINE_H
#define SCHEME_C_DEFINE_H

#include "object.h"

extern SchemeObject* DefineSymbol;

extern char IsDefine(SchemeObject* exp);

extern void DefineVariable(SchemeObject* var, SchemeObject* val, SchemeObject* environ);

extern SchemeObject* DefinitionVariable(SchemeObject* exp);

extern SchemeObject* DefinitionValue(SchemeObject* exp);

#endif //SCHEME_C_DEFINE_H
