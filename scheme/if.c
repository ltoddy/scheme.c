#include "if.h"
#include "builtin.h"
#include "eval.h"

/*
(if (predicate) (consequent) (alternative))
*/

char IsIf(SchemeObject* exp)
{
    return IsTaggedList(exp, IfSymbol);
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
