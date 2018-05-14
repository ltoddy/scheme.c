#ifndef SCHEME_C_PREDICATE_H
#define SCHEME_C_PREDICATE_H

#include "object.h"

extern char IsTaggedList(SchemeObject* exp, SchemeObject* tag);

extern char IsSelfEvaluating(SchemeObject* exp);

extern char IsVariable(SchemeObject* exp);

#endif //SCHEME_C_PREDICATE_H
