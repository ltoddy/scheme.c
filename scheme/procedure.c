#include <stdio.h>
#include "procedure.h"
#include "object.h"
#include "eval.h"
#include "builtin.h"

extern SchemeObject*
MakePrimitiveProc(SchemeObject* (* fn)(SchemeObject* arguments))
{
    SchemeObject* obj = AllocObject();
    obj->type = PRIMITIVE_PROCEDURE;
    obj->data.primitive_proc.fn = fn;
    return obj;
}

extern char
IsPrimitiveProc(SchemeObject* obj)
{
    return obj->type == PRIMITIVE_PROCEDURE;
}

extern SchemeObject*
MakeApplication(SchemeObject* operator, SchemeObject* operands)
{
    return Cons(operator, operands);
}

extern char
IsApplication(SchemeObject* exp)
{
    return IsPair(exp);
}

extern SchemeObject*
Operator(SchemeObject* exp)
{
    return Car(exp);
}

extern SchemeObject*
Operands(SchemeObject* exp)
{
    return Cdr(exp);
}

extern char
IsNoOperands(SchemeObject* ops)
{
    return IsTheEmptyList(ops);
}

extern SchemeObject*
FirstOperand(SchemeObject* exp)
{
    return Car(exp);
}

extern SchemeObject*
RestOperands(SchemeObject* exp)
{
    return Cdr(exp);
}
