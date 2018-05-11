#include <stdio.h>
#include <stdlib.h>
#include "eval.h"

SchemeObject* Eval(SchemeObject* exp)
{
    if (IsSelfEvaluting(exp)) {
        return exp;
    } else if (IsQuote(exp)) {
        return TextOfQuotation(exp);
    } else {
        fprintf(stderr, "cannot eval unknown expression type.\n");
        exit(1);
    }
    fprintf(stderr, "eval illegal state.\n");
    exit(1);
}
