#include "object.h"

#ifndef SCHEME_C_IF_H
#define SCHEME_C_IF_H

extern SchemeObject* IfSymbol;

extern char IsIf(SchemeObject* exp);

extern SchemeObject* MakeIf(SchemeObject* predicate, SchemeObject* consequent, SchemeObject* alternative);

extern SchemeObject* IfPredicate(SchemeObject* exp);

extern SchemeObject* IfConsequent(SchemeObject* exp);

extern SchemeObject* IfAlternative(SchemeObject* exp);

#endif //SCHEME_C_IF_H
