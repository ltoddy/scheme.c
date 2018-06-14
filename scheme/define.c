#include "define.h"
#include "environment.h"
#include "predicate.h"
#include "builtin.h"
#include "lambda.h"

extern char
IsDefine(SchemeObject* exp)
{
    return IsTaggedList(exp, DefineSymbol);
}

extern void
DefineVariable(SchemeObject* var, SchemeObject* val, SchemeObject* environ)
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

extern SchemeObject*
DefinitionVariable(SchemeObject* exp)
{
    if (IsSymbol(CADR(exp))) {
        return CADR(exp);
    } else {
        return CAADR(exp);
    }
}

extern SchemeObject*
DefinitionValue(SchemeObject* exp)
{
    if (IsSymbol(CADR(exp))) {
        return CADDR(exp);
    } else {
        return MakeLambda(CDADR(exp), CDDR(exp));
    }
}
