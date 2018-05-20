#ifndef SCHEME_C_PREDICATE_H
#define SCHEME_C_PREDICATE_H

#include "object.h"

extern SchemeObject* AndSymbol;
extern SchemeObject* OrSymbol;

extern char IsAnd(SchemeObject* exp);

extern SchemeObject* AndTests(SchemeObject* exp);

extern char IsOr(SchemeObject* exp);

extern SchemeObject* OrTests(SchemeObject* exp);

extern char IsTaggedList(SchemeObject* exp, SchemeObject* tag);

extern char IsSelfEvaluating(SchemeObject* exp);

extern char IsVariable(SchemeObject* exp);

#endif //SCHEME_C_PREDICATE_H
