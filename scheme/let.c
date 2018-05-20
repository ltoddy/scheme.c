#include "let.h"
#include "predicate.h"
#include "builtin.h"
#include "procedure.h"
#include "lambda.h"

char IsLet(SchemeObject* exp)
{
    return IsTaggedList(exp, LetSymbol);
}

static SchemeObject* LetBindings(SchemeObject* exp)
{
    return CADR(exp);
}

static SchemeObject* LetBody(SchemeObject* exp)
{
    return CDDR(exp);
}

static SchemeObject* BindingParameter(SchemeObject* binding)
{
    return Car(binding);
}

static SchemeObject* BindingArgument(SchemeObject* binding)
{
    return CADR(binding);
}

static SchemeObject* BindingParameters(SchemeObject* bindings)
{
    return IsTheEmptyList(bindings) ?
           TheEmptyList :
           Cons(BindingParameter(Car(bindings)), BindingParameters(Cdr(bindings)));
}

static SchemeObject* BindingArguments(SchemeObject* bindings)
{
    return IsTheEmptyList(bindings) ?
           TheEmptyList :
           Cons(BindingArgument(Car(bindings)), BindingArguments(Cdr(bindings)));
}

static SchemeObject* LetParameters(SchemeObject* exp)
{
    return BindingParameters(LetBindings(exp));
}

static SchemeObject* LetArguments(SchemeObject* exp)
{
    return BindingArguments(LetBindings(exp));
}

SchemeObject* LetToApplication(SchemeObject* exp)
{
    return MakeApplication(MakeLambda(LetParameters(exp), LetBody(exp)), LetArguments(exp));
}
