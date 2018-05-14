#include "assignment.h"
#include "predicate.h"

char IsAssignment(SchemeObject* exp)
{
    return IsTaggedList(exp, SetSymbol);
}

SchemeObject* AssignmentVariable(SchemeObject* exp)
{
    return Car(Cdr(exp));
}

SchemeObject* AssignmentValue(SchemeObject* exp)
{
    return Car(Cdr(Cdr(exp)));
}
