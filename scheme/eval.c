#include <stdio.h>
#include <stdlib.h>
#include "eval.h"
#include "object.h"
#include "builtin.h"
#include "environment.h"
#include "assignment.h"
#include "if.h"
#include "define.h"
#include "predicate.h"
#include "procedure.h"
#include "lambda.h"
#include "begin.h"
#include "cond.h"
#include "let.h"
#include "apply.h"

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
    DefineVariable(DefinitionVariable(exp), Eval(DefinitionValue(exp), environ), environ);
    return OkSymbol;
}

static SchemeObject* EvalExpression(SchemeObject* arguments)
{
    return Car(arguments);
}

static SchemeObject* EvalEnvironment(SchemeObject* arguments)
{
    return CADR(arguments);
}

SchemeObject* ListOfValues(SchemeObject* exps, SchemeObject* environ)
{
    if (IsNoOperands(exps)) {
        return TheEmptyList;
    } else {
        return Cons(Eval(FirstOperand(exps), environ),
                    ListOfValues(RestOperands(exps), environ));
    }
}

SchemeObject* Eval(SchemeObject* exp, SchemeObject* environ)
{
    SchemeObject* procedure;
    SchemeObject* arguments;
    SchemeObject* result;

    tail:
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
        goto tail;
    } else if (IsLambda(exp)) {
        return MakeCompoundProc(LambdaParameters(exp), LambdaBody(exp), environ);
    } else if (IsBegin(exp)) {
        exp = BeginAction(exp);

        while (!IsLastExp(exp)) {
            Eval(FirstExp(exp), environ);
            exp = RestExps(exp);
        }
        exp = FirstExp(exp);

        goto tail;
    } else if (IsCond(exp)) {
        exp = CondToIf(exp);
        goto tail;
    } else if (IsLet(exp)) {
        exp = LetToApplication(exp);
        goto tail;
    } else if (IsAnd(exp)) {
        exp = AndTests(exp);
        if (IsTheEmptyList(exp)) {
            return True;
        }
        while (!IsLastExp(exp)) {
            result = Eval(FirstExp(exp), environ);
            if (IsFalse(result)) {
                return False;
            }
            exp = RestExps(exp);
        }
        exp = FirstExp(exp);
        goto tail;
    } else if (IsOr(exp)) {
        exp = OrTests(exp);
        if (IsTheEmptyList(exp)) {
            return False;
        }
        while (!IsLastExp(exp)) {
            result = Eval(FirstExp(exp), environ);
            if (IsTrue(result)) {
                return True;
            }
            exp = RestExps(exp);
        }
        exp = FirstExp(exp);
        goto tail;
    } else if (IsApplication(exp)) {
        procedure = Eval(Operator(exp), environ);
        arguments = ListOfValues(Operands(exp), environ);

        /* handle eval specially for tail call requirement */
        if (IsPrimitiveProc(procedure) && procedure->data.primitive_proc.fn == EvalProc) {
            exp = EvalExpression(arguments);
            environ = EvalEnvironment(arguments);
            goto tail;
        }

        /* handle apply specially for tail call requirement */
        if (IsPrimitiveProc(procedure) && procedure->data.primitive_proc.fn == ApplyProc) {
            procedure = ApplyOperator(arguments);
            arguments = ApplyOperands(arguments);
        }

        if (IsPrimitiveProc(procedure)) {
            return (procedure->data.primitive_proc.fn)(arguments);
        } else if (IsCompoundProc(procedure)) {
            environ = ExtendEnvironment(procedure->data.compound_proc.parameters,
                                        arguments,
                                        procedure->data.compound_proc.env);
            exp = MakeBegin(procedure->data.compound_proc.body);
            goto tail;
        } else {
            fprintf(stderr, "unknown procedure type.\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "cannot eval unknown expression type.\n");
        exit(1);
    }
    fprintf(stderr, "eval illegal state.\n");
    exit(1);
}
