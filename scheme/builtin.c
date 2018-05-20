#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"
#include "environment.h"
#include "define.h"
#include "assignment.h"
#include "if.h"
#include "procedure.h"
#include "object.h"
#include "cond.h"
#include "let.h"
#include "predicate.h"
#include "apply.h"

SchemeObject* True = NULL;
SchemeObject* False = NULL;
SchemeObject* TheEmptyList = NULL;
SchemeObject* SymbolTable = NULL;
SchemeObject* QuoteSymbol = NULL;
SchemeObject* TheEmptyEnvironment = NULL;
SchemeObject* TheGlobalEnvironment = NULL;
SchemeObject* DefineSymbol = NULL;
SchemeObject* SetSymbol = NULL;
SchemeObject* OkSymbol = NULL;
SchemeObject* IfSymbol = NULL;
SchemeObject* LambdaSymbol = NULL;
SchemeObject* BeginSymbol = NULL;
SchemeObject* CondSymbol = NULL;
SchemeObject* ElseSymbol = NULL;
SchemeObject* LetSymbol = NULL;
SchemeObject* AndSymbol = NULL;
SchemeObject* OrSymbol = NULL;

#define ADD_PRIMITIVE(scheme_name, c_name) \
    DefineVariable(MakeSymbol(scheme_name), MakePrimitiveProc(c_name), TheGlobalEnvironment);

void InitScheme()
{
    True = AllocObject();
    True->type = BOOLEAN;
    True->data.boolean.value = 1;

    False = AllocObject();
    False->type = BOOLEAN;
    False->data.boolean.value = 0;

    TheEmptyList = AllocObject();
    TheEmptyList->type = THE_EMPTY_LIST;
    SymbolTable = TheEmptyList;
    QuoteSymbol = MakeSymbol("quote");

    DefineSymbol = MakeSymbol("define");
    SetSymbol = MakeSymbol("set!");
    OkSymbol = MakeSymbol("ok");
    IfSymbol = MakeSymbol("if");
    LambdaSymbol = MakeSymbol("lambda");
    BeginSymbol = MakeSymbol("begin");
    CondSymbol = MakeSymbol("cond");
    ElseSymbol = MakeSymbol("else");
    LetSymbol = MakeSymbol("let");
    AndSymbol = MakeSymbol("and");
    OrSymbol = MakeSymbol("or");

    TheEmptyEnvironment = TheEmptyList;
    TheGlobalEnvironment = SetupEnvironment();

    // builtin procedure
    ADD_PRIMITIVE("+", AddProcedure)
    ADD_PRIMITIVE("-", SubProcedure)
    ADD_PRIMITIVE("*", MulProcedure)
    ADD_PRIMITIVE("/", QuotientProcedure)
    ADD_PRIMITIVE("quotient", QuotientProcedure)
    ADD_PRIMITIVE("remainder", RemainderProcedure)
    ADD_PRIMITIVE("=", IsNumberEqualProcedure)
    ADD_PRIMITIVE("<", IsLessThanProcedure)
    ADD_PRIMITIVE(">", IsGreaterThanProcedure)
    ADD_PRIMITIVE("cons", ConsProcedure)
    ADD_PRIMITIVE("car", CarProcedure)
    ADD_PRIMITIVE("cdr", CdrProcedure)
    ADD_PRIMITIVE("set-car!", SetCarProcedure)
    ADD_PRIMITIVE("set-cdr!", SetCdrProcedure)
    ADD_PRIMITIVE("list", ListProcedure)
    ADD_PRIMITIVE("eq?", IsEqProcedure)
    ADD_PRIMITIVE("null?", IsNullProcedure)
    ADD_PRIMITIVE("boolean?", IsBooleanProcedure)
    ADD_PRIMITIVE("symbol?", IsSymbolProcedure)
    ADD_PRIMITIVE("integer?", IsIntegerProcedure)
    ADD_PRIMITIVE("char?", IsCharProcedure)
    ADD_PRIMITIVE("string?", IsStringProcedure)
    ADD_PRIMITIVE("pair?", IsPairProcedure)
    ADD_PRIMITIVE("procedure?", IsProcedureProcedure)
    ADD_PRIMITIVE("number->string", NumberToStringProcedure)
    ADD_PRIMITIVE("string->number", StringToNumberProcedure)
    ADD_PRIMITIVE("symbol->string", SymbolToStringProcedure)
    ADD_PRIMITIVE("string->symbol", StringToSymbolProcedure)
    ADD_PRIMITIVE("char->integer", CharToIntegerProcedure)
    ADD_PRIMITIVE("integer->char", IntegerToCharProcedure)
    ADD_PRIMITIVE("apply", ApplyProc)
}

/* ---------------- end primitive procedure ---------------- */
SchemeObject* AddProcedure(SchemeObject* arguments) /* + */
{
    long result = 0;

    while (!IsTheEmptyList(arguments)) {
        result += (Car(arguments))->data.fixnum.value;
        arguments = Cdr(arguments);
    }
    return MakeFixnum(result);
}

SchemeObject* SubProcedure(SchemeObject* arguments) /* - */
{
    long result = (Car(arguments))->data.fixnum.value;

    while (!IsTheEmptyList(arguments = Cdr(arguments))) {
        result -= (Car(arguments))->data.fixnum.value;
    }
    return MakeFixnum(result);
}

SchemeObject* MulProcedure(SchemeObject* arguments) /* * */
{
    long result = 1;

    while (!IsTheEmptyList(arguments)) {
        result *= (Car(arguments))->data.fixnum.value;
        arguments = Cdr(arguments);
    }
    return MakeFixnum(result);
}

SchemeObject* QuotientProcedure(SchemeObject* arguments) /* quotient */
{
    return MakeFixnum((Car(arguments))->data.fixnum.value /
                      (CADR(arguments))->data.fixnum.value);
}

SchemeObject* RemainderProcedure(SchemeObject* arguments) /* remainder */
{
    return MakeFixnum((Car(arguments))->data.fixnum.value %
                      (CADR(arguments))->data.fixnum.value);
}

SchemeObject* IsNumberEqualProcedure(SchemeObject* arguments) /* = */
{
    long value = (Car(arguments))->data.fixnum.value;

    while (!IsTheEmptyList(arguments = Cdr(arguments))) {
        if (value != (Car(arguments))->data.fixnum.value) {
            return False;
        }
    }
    return True;
}

SchemeObject* IsLessThanProcedure(SchemeObject* arguments) /* < */
{
    long previous = (Car(arguments))->data.fixnum.value;
    long next;
    while (!IsTheEmptyList(arguments = Cdr(arguments))) {
        next = (Car(arguments))->data.fixnum.value;
        if (previous < next) {
            return True;
        } else {
            return False;
        }
    }
    return True;
}

SchemeObject* IsGreaterThanProcedure(SchemeObject* arguments) /* > */
{
    long previout = (Car(arguments))->data.fixnum.value;
    long next;
    while (!IsTheEmptyList(arguments = Cdr(arguments))) {
        next = (Car(arguments))->data.fixnum.value;
        if (previout < next) {
            return False;
        } else {
            return True;
        }
    }
    return True;
}

SchemeObject* ConsProcedure(SchemeObject* arguments) /* (cons ...) */
{
    return Cons(Car(arguments), CADR(arguments));
}

SchemeObject* CarProcedure(SchemeObject* arguments) /* (car ...) */
{
    return CAAR(arguments);
}

SchemeObject* CdrProcedure(SchemeObject* arguments) /* (cdr ...) */
{
    return CDAR(arguments);
}

SchemeObject* SetCarProcedure(SchemeObject* arguments) /* (set-car! ...) */
{
    SetCar(Car(arguments), CADR(arguments));
    return OkSymbol;
}

SchemeObject* SetCdrProcedure(SchemeObject* arguments) /* (set-cdr! ...) */
{
    SetCdr(Car(arguments), CADR(arguments));
    return OkSymbol;
}

SchemeObject* ListProcedure(SchemeObject* arguments) /* (list ...) */
{
    return arguments;
}

SchemeObject* IsEqProcedure(SchemeObject* arguments) /* (eq? ...) */
{
    SchemeObject* obj1 = Car(arguments);
    SchemeObject* obj2 = CADR(arguments);

    if (obj1->type != obj2->type) {
        return False;
    }

    switch (obj1->type) {
        case FIXNUM:
            return (obj1->data.fixnum.value == obj2->data.fixnum.value) ? True : False;
        case CHARACTER:
            return (obj1->data.character.value == obj2->data.character.value) ? True : False;
        case STRING:
            return (obj1->data.string.value == obj2->data.string.value) ? True : False;
        default:
            return obj1 == obj2 ? True : False;
    }
}

SchemeObject* IsNullProcedure(SchemeObject* arguments) /* (null? ...) */
{
    return IsTheEmptyList(Car(arguments)) ? True : False;
}

SchemeObject* IsBooleanProcedure(SchemeObject* arguments) /* (boolean? ...) */
{
    return IsBoolean(Car(arguments)) ? True : False;
}

SchemeObject* IsSymbolProcedure(SchemeObject* arguments) /* (symbol? ...) */
{
    return IsSymbol(Car(arguments)) ? True : False;
}

SchemeObject* IsIntegerProcedure(SchemeObject* arguments) /* (integer? ...) */
{
    return IsFixnum(Car(arguments)) ? True : False;
}

SchemeObject* IsCharProcedure(SchemeObject* arguments) /* (char? ...) */
{
    return IsCharacter(Car(arguments)) ? True : False;
}

SchemeObject* IsStringProcedure(SchemeObject* arguments) /* (string? ...) */
{
    return IsString(Car(arguments)) ? True : False;
}

SchemeObject* IsPairProcedure(SchemeObject* arguments) /* (pair? ...) */
{
    return IsPair(Car(arguments)) ? True : False;
}

SchemeObject* IsProcedureProcedure(SchemeObject* arguments) /* (procedure? ...) */
{
    SchemeObject* obj = Car(arguments);

    return (IsPrimitiveProc(obj)) || (IsCompoundProc(obj)) ? True : False;
}

SchemeObject* NumberToStringProcedure(SchemeObject* arguments) /* (number->string ...) */
{
    char buffer[100];

    sprintf(buffer, "%ld", Car(arguments)->data.fixnum.value);
    return MakeString(buffer);
}

SchemeObject* StringToNumberProcedure(SchemeObject* arguments) /* (string->number ...) */
{
    return MakeFixnum(atoi(Car(arguments)->data.string.value));
}

SchemeObject* SymbolToStringProcedure(SchemeObject* arguments) /* (symbol->string ...) */
{
    return MakeString(Car(arguments)->data.symbol.value);
}

SchemeObject* StringToSymbolProcedure(SchemeObject* arguments) /* (string->symbol ...) */
{
    return MakeSymbol(Car(arguments)->data.string.value);
}

SchemeObject* CharToIntegerProcedure(SchemeObject* arguments) /* (char->integer ...) */
{
    return MakeFixnum(Car(arguments)->data.character.value);
}

SchemeObject* IntegerToCharProcedure(SchemeObject* arguments) /* (integer->char ...) */
{
    return MakeCharacter((char) Car(arguments)->data.fixnum.value);
}
/* ---------------- end primitive procedure ---------------- */


/* ---------------- compound procedure ---------------- */
SchemeObject* MakeCompoundProc(SchemeObject* parameters, SchemeObject* body, SchemeObject* env)
{
    SchemeObject* obj = AllocObject();

    obj->type = COMPOUND_PROCEDURE;
    obj->data.compound_proc.parameters = parameters;
    obj->data.compound_proc.body = body;
    obj->data.compound_proc.env = env;

    return obj;
}

extern char IsCompoundProc(SchemeObject* obj)
{
    return obj->type == COMPOUND_PROCEDURE;
}
/* ---------------- end compound procedure ---------------- */
