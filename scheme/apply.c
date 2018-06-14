#include <stdio.h>
#include <stdlib.h>
#include "apply.h"

extern SchemeObject*
ApplyProc(SchemeObject* arguments)
{
    fprintf(stderr, "illegal state: The body of the apply primitive procedure should not execute.\n");
    exit(1);
}

extern SchemeObject*
ApplyOperator(SchemeObject* arguments)
{
    return Car(arguments);
}

static SchemeObject*
PrepareApplyOperands(SchemeObject* arguments)
{
    if (IsTheEmptyList(Cdr(arguments))) {
        return Car(arguments);
    } else {
        return Cons(Car(arguments), PrepareApplyOperands(Cdr(arguments)));
    }
}

extern SchemeObject*
ApplyOperands(SchemeObject* arguments)
{
    return PrepareApplyOperands(Cdr(arguments));
}
