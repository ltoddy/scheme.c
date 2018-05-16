#ifndef SCHEME_C_COMPOUND_H
#define SCHEME_C_COMPOUND_H

#include "object.h"

extern SchemeObject* LambdaSymbol;

extern SchemeObject* MakeLambda(SchemeObject* parameters, SchemeObject* body);

extern char IsLambda(SchemeObject* exp);

extern SchemeObject* LambdaParameters(SchemeObject* exp);

extern SchemeObject* LambdaBody(SchemeObject* exp);

extern char IsLastExp(SchemeObject* exp);

extern SchemeObject* FirstExp(SchemeObject* exp);

extern SchemeObject* RestExps(SchemeObject* exp);

#endif //SCHEME_C_COMPOUND_H
