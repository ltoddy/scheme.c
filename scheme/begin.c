#include "begin.h"
#include "predicate.h"

extern SchemeObject*
MakeBegin(SchemeObject* seq)
{
    return Cons(BeginSymbol, seq);
}

extern char
IsBegin(SchemeObject* exp)
{
    return IsTaggedList(exp, BeginSymbol);
}

extern SchemeObject*
BeginAction(SchemeObject* exp)
{
    return Cdr(exp);
}
