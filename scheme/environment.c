#include <stdio.h>
#include <stdlib.h>
#include "environment.h"
#include "builtin.h"

static SchemeObject* EnclosingEnvironment(SchemeObject* environ)
{
    return Cdr(environ);
}

SchemeObject* FirstFrame(SchemeObject* environ)
{
    return Car(environ);
}

static SchemeObject* MakeFrame(SchemeObject* variables, SchemeObject* values)
{
    return Cons(variables, values);
}

SchemeObject* FrameVariables(SchemeObject* frame)
{
    return Car(frame);
}

SchemeObject* FrameValues(SchemeObject* frame)
{
    return Cdr(frame);
}

void AddBindingToFrame(SchemeObject* var, SchemeObject* val, SchemeObject* frame)
{
    SetCar(frame, Cons(var, Car(frame)));
    SetCdr(frame, Cons(val, Cdr(frame)));
}

SchemeObject* ExtendEnvironment(SchemeObject* var, SchemeObject* val, SchemeObject* base_environ)
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

SchemeObject* SetupEnvironment()
{
    SchemeObject* initial_env = ExtendEnvironment(TheEmptyList, TheEmptyList, TheEmptyEnvironment);
    return initial_env;
}
