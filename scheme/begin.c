#include "begin.h"
#include "predicate.h"

SchemeObject* MakeBegin(SchemeObject* exp)
{
    return Cons(BeginSymbol, exp);
}

char IsBegin(SchemeObject* exp)
{
    return IsTaggedList(exp, BeginSymbol);
}

SchemeObject* BeginAction(SchemeObject* exp)
{
    return Cdr(exp);
}
