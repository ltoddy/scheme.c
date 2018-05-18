#include "if.h"
#include "builtin.h"
#include "eval.h"
#include "predicate.h"

/*
(if (predicate) (consequent) (alternative))
*/

char IsIf(SchemeObject* exp)
{
    return IsTaggedList(exp, IfSymbol);
}

SchemeObject* MakeIf(SchemeObject* predicate, SchemeObject* consequent, SchemeObject* alternative)
{
    return Cons(IfSymbol,
                Cons(predicate,
                     Cons(consequent,
                          Cons(alternative, TheEmptyList))));
}

SchemeObject* IfPredicate(SchemeObject* exp)
{
    return CADR(exp);
}

SchemeObject* IfConsequent(SchemeObject* exp)
{
    return CADDR(exp);
}

SchemeObject* IfAlternative(SchemeObject* exp)
{
    if (IsTheEmptyList(CDDDR(exp))) {
        return False;
    } else {
        return CADDDR(exp);
    }
}
