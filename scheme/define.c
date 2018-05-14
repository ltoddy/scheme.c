#include "define.h"
#include "environment.h"
#include "predicate.h"
#include "builtin.h"

char IsDefine(SchemeObject* exp)
{
    return IsTaggedList(exp, DefineSymbol);
}

void DefineVariable(SchemeObject* var, SchemeObject* val, SchemeObject* environ)
{
    SchemeObject* frame = FirstFrame(environ);
    SchemeObject* vars = FrameVariables(frame);
    SchemeObject* vals = FrameValues(frame);

    while (!IsTheEmptyList(vals)) {
        if (var == Car(vars)) {
            SetCar(vals, val);
            return;
        }
        vars = Cdr(vars);
        vals = Cdr(vals);
    }
    AddBindingToFrame(var, val, frame);
}

SchemeObject* DefinitionVariable(SchemeObject* exp)
{
    return CADR(exp);
}

SchemeObject* DefinitionValue(SchemeObject* exp)
{
    return CADDR(exp);
}
