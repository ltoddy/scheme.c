#ifndef SCHEME_C_PROCEDURE_H
#define SCHEME_C_PROCEDURE_H

#include "object.h"

extern SchemeObject* MakePrimitiveProc(SchemeObject* (* fn)(SchemeObject* arguments));

extern char IsPrimitiveProc(SchemeObject* obj);

extern SchemeObject* MakeApplication(SchemeObject* operator, SchemeObject* operands);

extern char IsApplication(SchemeObject* exp);

extern SchemeObject* Operator(SchemeObject* exp);

extern SchemeObject* Operands(SchemeObject* exp);

extern char IsNoOperands(SchemeObject* ops);

extern SchemeObject* FirstOperand(SchemeObject* exp);

extern SchemeObject* RestOperands(SchemeObject* exp);

#endif //SCHEME_C_PROCEDURE_H
