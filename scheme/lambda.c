#include "lambda.h"
#include "object.h"
#include "predicate.h"
#include "builtin.h"

extern SchemeObject*
MakeLambda(SchemeObject* parameters, SchemeObject* body)
{
    return Cons(LambdaSymbol, Cons(parameters, body));
}

extern char
IsLambda(SchemeObject* exp)
{
    return IsTaggedList(exp, LambdaSymbol);
}

extern SchemeObject*
LambdaParameters(SchemeObject* exp)
{
    return CADR(exp);
}

extern SchemeObject*
LambdaBody(SchemeObject* exp)
{
    return CDDR(exp);
}

extern char
IsLastExp(SchemeObject* exp)
{
    return IsTheEmptyList(Cdr(exp));
}

extern SchemeObject*
FirstExp(SchemeObject* exp)
{
    return Car(exp);
}

extern SchemeObject*
RestExps(SchemeObject* exp)
{
    return Cdr(exp);
}
