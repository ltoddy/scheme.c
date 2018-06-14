#include "predicate.h"
#include "assignment.h"

extern char
IsAnd(SchemeObject* exp)
{
    return IsTaggedList(exp, AndSymbol);
}

extern SchemeObject*
AndTests(SchemeObject* exp)
{
    return Cdr(exp);
}

extern char
IsOr(SchemeObject* exp)
{
    return IsTaggedList(exp, OrSymbol);
}

extern SchemeObject*
OrTests(SchemeObject* exp)
{
    return Cdr(exp);
}

extern char
IsTaggedList(SchemeObject* exp, SchemeObject* tag)
{
    SchemeObject* car;
    if (IsPair(exp)) {
        car = Car(exp);
        return IsSymbol(car) && (car == tag);
    }
    return 0;
}

extern char
IsSelfEvaluating(SchemeObject* exp)
{
    return IsBoolean(exp) ||
           IsFixnum(exp) ||
           IsCharacter(exp) ||
           IsString(exp);
}

extern char
IsVariable(SchemeObject* exp)
{
    return IsSymbol(exp);
}
