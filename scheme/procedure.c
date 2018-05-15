#include <stdio.h>
#include "procedure.h"
#include "object.h"
#include "eval.h"
#include "builtin.h"

SchemeObject* MakePrimitiveProc(SchemeObject* (* fn)(SchemeObject* arguments))
{
    SchemeObject* obj = AllocObject();
    obj->type = PRIMITIVE_PROCEDURE;
    obj->data.primitive_poc.fn = fn;
    return obj;
}

char IsPrimitiveProc(SchemeObject* obj)
{
    return obj->type == PRIMITIVE_PROCEDURE;
}

char IsApplication(SchemeObject* exp)
{
    return IsPair(exp);
}

SchemeObject* Operator(SchemeObject* exp)
{
    return Car(exp);
}

SchemeObject* Operands(SchemeObject* exp)
{
    return Cdr(exp);
}

char IsNoOperands(SchemeObject* ops)
{
    return IsTheEmptyList(ops);
}

SchemeObject* FirstOperand(SchemeObject* exp)
{
    return Car(exp);
}

SchemeObject* RestOperands(SchemeObject* exp)
{
    return Cdr(exp);
}
