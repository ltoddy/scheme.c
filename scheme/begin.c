#include "begin.h"
#include "predicate.h"

SchemeObject* MakeBegin(SchemeObject* seq)
{
    return Cons(BeginSymbol, seq);
}

char IsBegin(SchemeObject* exp)
{
    return IsTaggedList(exp, BeginSymbol);
}

SchemeObject* BeginAction(SchemeObject* exp)
{
    return Cdr(exp);
}
