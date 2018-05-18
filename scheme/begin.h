#ifndef SCHEME_C_BEGIN_H
#define SCHEME_C_BEGIN_H

#include "object.h"

extern SchemeObject* BeginSymbol;

extern SchemeObject* MakeBegin(SchemeObject* seq);

extern char IsBegin(SchemeObject* exp);

extern SchemeObject* BeginAction(SchemeObject* exp);

#endif //SCHEME_C_BEGIN_H
