#include <stdio.h>
#include <stdlib.h>
#include "environment.h"

static SchemeObject* EnclosingEnvironment(SchemeObject* environ)
{
    return Cdr(environ);
}

static SchemeObject* FirstFrame(SchemeObject* environ)
{
    return Car(environ);
}

static SchemeObject* MakeFrame(SchemeObject* variables, SchemeObject* values)
{
    return Cons(variables, values);
}

static SchemeObject* FrameVariables(SchemeObject* frame)
{
    return Car(frame);
}

static SchemeObject* FrameValues(SchemeObject* frame)
{
    return Cdr(frame);
}

static void AddBindingToFrame(SchemeObject* var, SchemeObject* val, SchemeObject* frame)
{
    SetCar(frame, Cons(var, Car(frame)));
    SetCdr(frame, Cons(val, Cdr(frame)));
}

static SchemeObject* ExtendEnvironment(SchemeObject* var, SchemeObject* val, SchemeObject* base_environ)
{
    return Cons(MakeFrame(var, val), base_environ);
}

SchemeObject* LookupVariableValue(SchemeObject* var, SchemeObject* environ)
{
    while (!IsTheEmptyList(environ)) {
        SchemeObject* frame = FirstFrame(environ);
        SchemeObject* vars = FrameVariables(frame);
        SchemeObject* vals = FrameValues(frame);
        while (!IsTheEmptyList(vars)) {
            if (var == Car(vars)) {
                return Car(vals);
            }
            vars = Cdr(vars);
            vals = Cdr(vals);
        }
        environ = EnclosingEnvironment(environ);
    }
    fprintf(stderr, "unbound variable.\n");
    exit(1);
}

void SetVariableValue(SchemeObject* var, SchemeObject* val, SchemeObject* environ)
{
    while (!IsTheEmptyList(environ)) {
        SchemeObject* frame = FirstFrame(environ);
        SchemeObject* vars = FrameVariables(frame);
        SchemeObject* vals = FrameValues(frame);
        while (!IsTheEmptyList(frame)) {
            if (var == Car(vars)) {
                SetCar(vals, val);
                return;
            }
            vars = Cdr(vars);
            vals = Cdr(vals);
        }
        environ = EnclosingEnvironment(environ);
    }
    fprintf(stderr, "unbound variable.\n");
    exit(1);
}

void DefineVariable(SchemeObject* var, SchemeObject* val, SchemeObject* environ)
{
    SchemeObject* frame = FirstFrame(environ);
    SchemeObject* vars = FrameVariables(frame);
    SchemeObject* vals = FrameValues(frame);

    while (!IsTheEmptyList(vals)) {
        if (var == Car(vars)) {
            SetCar(vals, val);
            return;
        }
        vars = Cdr(vars);
        vals = Cdr(vals);
    }
    AddBindingToFrame(var, val, frame);
}

static SchemeObject* SetupEnvironment()
{
    SchemeObject* initial_env = ExtendEnvironment(TheEmptyList, TheEmptyList, TheEmptyEnvironment);
    return initial_env;
}

SchemeObject* TheEmptyEnvironment = NULL;
SchemeObject* TheGlobalEnvironment = NULL;
SchemeObject* DefineSymbol = NULL;
SchemeObject* SetSymbol = NULL;
SchemeObject* OkSymbol = NULL;

void InitEnvironment()
{
    DefineSymbol = MakeSymbol("define");
    SetSymbol = MakeSymbol("set!");
    OkSymbol = MakeSymbol("ok");

    TheEmptyEnvironment = TheEmptyList;
    TheGlobalEnvironment = SetupEnvironment();
}
