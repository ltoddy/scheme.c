#include <stdio.h>
#include <stdlib.h>
#include "eval.h"
#include "builtin.h"
#include "environment.h"
#include "assignment.h"
#include "if.h"
#include "define.h"
#include "predicate.h"


static SchemeObject* TextOfQuotation(SchemeObject* exp)
{
    return CADR(exp);
}

static SchemeObject* EvalAssignment(SchemeObject* exp, SchemeObject* environ)
{
    SetVariableValue(AssignmentVariable(exp), Eval(AssignmentValue(exp), environ), environ);
    return OkSymbol;
}

static SchemeObject* EvalDefinition(SchemeObject* exp, SchemeObject* environ)
{
    DefineVariable(AssignmentVariable(exp), Eval(AssignmentValue(exp), environ), environ);
    return OkSymbol;
}

SchemeObject* Eval(SchemeObject* exp, SchemeObject* environ)
{
    call:
    if (IsSelfEvaluating(exp)) {
        return exp;
    } else if (IsVariable(exp)) {
        return LookupVariableValue(exp, environ);
    } else if (IsQuote(exp)) {
        return TextOfQuotation(exp);
    } else if (IsAssignment(exp)) {
        return EvalAssignment(exp, environ);
    } else if (IsDefine(exp)) {
        return EvalDefinition(exp, environ);
    } else if (IsIf(exp)) {
        exp = IsTrue(Eval(IfPredicate(exp), environ)) ? IfConsequent(exp) : IfAlternative(exp);
        goto call;
    } else {
        fprintf(stderr, "cannot eval unknown expression type.\n");
        exit(1);
    }
    fprintf(stderr, "eval illegal state.\n");
    exit(1);
}

