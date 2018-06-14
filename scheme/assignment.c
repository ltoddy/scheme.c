#include "assignment.h"
#include "predicate.h"

extern char
IsAssignment(SchemeObject* exp)
{
    return IsTaggedList(exp, SetSymbol);
}

extern SchemeObject*
AssignmentVariable(SchemeObject* exp)
{
    return Car(Cdr(exp));
}

extern SchemeObject*
AssignmentValue(SchemeObject* exp)
{
    return Car(Cdr(Cdr(exp)));
}
