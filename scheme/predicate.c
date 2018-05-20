#include "predicate.h"
#include "assignment.h"

char IsAnd(SchemeObject* exp)
{
    return IsTaggedList(exp, AndSymbol);
}

SchemeObject* AndTests(SchemeObject* exp)
{
    return Cdr(exp);
}

char IsOr(SchemeObject* exp)
{
    return IsTaggedList(exp, OrSymbol);
}

SchemeObject* OrTests(SchemeObject* exp)
{
    return Cdr(exp);
}

char IsTaggedList(SchemeObject* exp, SchemeObject* tag)
{
    SchemeObject* car;
    if (IsPair(exp)) {
        car = Car(exp);
        return IsSymbol(car) && (car == tag);
    }
    return 0;
}

char IsSelfEvaluating(SchemeObject* exp)
{
    return IsBoolean(exp) ||
           IsFixnum(exp) ||
           IsCharacter(exp) ||
           IsString(exp);
}

char IsVariable(SchemeObject* exp)
{
    return IsSymbol(exp);
}
