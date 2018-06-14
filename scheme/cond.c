#include <stdlib.h>
#include "cond.h"
#include "predicate.h"
#include "lambda.h"
#include "begin.h"
#include "if.h"
#include <stdio.h>

extern char
IsCond(SchemeObject* exp)
{
    return IsTaggedList(exp, CondSymbol);
}

static SchemeObject*
CondClauses(SchemeObject* exp)
{
    return Cdr(exp);
}

static SchemeObject*
CondPredicate(SchemeObject* exp)
{
    return Car(exp);
}

static SchemeObject*
CondAction(SchemeObject* exp)
{
    return Cdr(exp);
}

static char
IsCondElseClause(SchemeObject* clause)
{
    return CondPredicate(clause) == ElseSymbol;
}

static SchemeObject*
SequenceToExp(SchemeObject* seq)
{
    if (IsTheEmptyList(seq)) {
        return seq;
    } else if (IsLastExp(seq)) {
        return FirstExp(seq);
    } else {
        return MakeBegin(seq);
    }
}

static SchemeObject*
ExpandClauses(SchemeObject* clauses)
{
    SchemeObject* first;
    SchemeObject* rest;

    if (IsTheEmptyList(clauses)) {
        return False;
    } else {
        first = Car(clauses);
        rest = Cdr(clauses);

        if (IsCondElseClause(first)) {
            if (IsTheEmptyList(rest)) {
                return SequenceToExp(CondAction(first));
            } else {
                fprintf(stderr, "else clause isn't last cond->if.");
                exit(1);
            }
        } else {
            return MakeIf(CondPredicate(first), SequenceToExp(CondAction(first)), ExpandClauses(rest));
        }
    }
}

extern SchemeObject*
CondToIf(SchemeObject* exp)
{
    return ExpandClauses(CondClauses(exp));
}
