#include <stdio.h>
#include <stdlib.h>
#include "eval.h"
#include "builtin.h"
#include "environment.h"
#include "assignment.h"
#include "if.h"

static char IsSelfEvaluting(SchemeObject* exp)
{
    return IsBoolean(exp) ||
           IsFixnum(exp) ||
           IsCharacter(exp) ||
           IsString(exp);
}

static char IsVariable(SchemeObject* exp)
{
    return IsSymbol(exp);
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

static char IsQuote(SchemeObject* exp)
{
    return IsTaggedList(exp, QuoteSymbol);
}

static SchemeObject* TextOfQuotation(SchemeObject* exp)
{
    return CADR(exp);
}

static char IsAssignment(SchemeObject* exp)
{
    return IsTaggedList(exp, SetSymbol);
}

static SchemeObject* AssignmentVariable(SchemeObject* exp)
{
    return Car(Cdr(exp));
}

static SchemeObject* AssignmentValue(SchemeObject* exp)
{
    return Car(Cdr(Cdr(exp)));
}

static char IsDefine(SchemeObject* exp)
{
    return IsTaggedList(exp, DefineSymbol);
}

static SchemeObject* DefinitionVariable(SchemeObject* exp)
{
    return CADR(exp);
}

static SchemeObject* DefinitionValue(SchemeObject* exp)
{
    return CADDR(exp);
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
    if (IsSelfEvaluting(exp)) {
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

