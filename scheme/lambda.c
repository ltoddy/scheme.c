#include "lambda.h"
#include "object.h"
#include "predicate.h"
#include "builtin.h"

SchemeObject* MakeLambda(SchemeObject* parameters, SchemeObject* body)
{
    return Cons(LambdaSymbol, Cons(parameters, body));
}

char IsLambda(SchemeObject* exp)
{
    return IsTaggedList(exp, LambdaSymbol);
}

SchemeObject* LambdaParameters(SchemeObject* exp)
{
    return CADR(exp);
}

SchemeObject* LambdaBody(SchemeObject* exp)
{
    return CDDR(exp);
}

char IsLastExp(SchemeObject* exp)
{
    return IsTheEmptyList(Cdr(exp));
}

SchemeObject* FirstExp(SchemeObject* exp)
{
    return Car(exp);
}

SchemeObject* RestExps(SchemeObject* exp)
{
    return Cdr(exp);
}

