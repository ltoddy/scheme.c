#ifndef SCHEME_C_COND_H
#define SCHEME_C_COND_H

#include "object.h"

extern SchemeObject* CondSymbol;
extern SchemeObject* ElseSymbol;

extern char IsCond(SchemeObject* exp);

extern SchemeObject* CondToIf(SchemeObject* exp);

#endif //SCHEME_C_COND_H
