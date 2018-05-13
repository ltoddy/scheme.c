#ifndef SCHEME_C_EVAL_H
#define SCHEME_C_EVAL_H

#include "object.h"

extern SchemeObject* Eval(SchemeObject* exp, SchemeObject* environ);

extern char IsTaggedList(SchemeObject* exp, SchemeObject* tag);

#endif //SCHEME_C_EVAL_H
