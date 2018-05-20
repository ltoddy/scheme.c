#include <stdio.h>
#include <stdlib.h>
#include "apply.h"

SchemeObject* ApplyProc(SchemeObject* arguments)
{
    fprintf(stderr, "illegal state: The body of the apply primitive procedure should not execute.\n");
    exit(1);
}

SchemeObject* ApplyOperator(SchemeObject* arguments)
{
    return Car(arguments);
}

static SchemeObject* PrepareApplyOperands(SchemeObject* arguments)
{
    if (IsTheEmptyList(Cdr(arguments))) {
        return Car(arguments);
    } else {
        return Cons(Car(arguments), PrepareApplyOperands(Cdr(arguments)));
    }
}

SchemeObject* ApplyOperands(SchemeObject* arguments)
{
    return PrepareApplyOperands(Cdr(arguments));
}
