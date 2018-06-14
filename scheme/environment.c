#include <stdio.h>
#include <stdlib.h>
#include "environment.h"
#include "builtin.h"

static SchemeObject*
EnclosingEnvironment(SchemeObject* environ)
{
    return Cdr(environ);
}

extern SchemeObject*
FirstFrame(SchemeObject* environ)
{
    return Car(environ);
}

static SchemeObject*
MakeFrame(SchemeObject* variables, SchemeObject* values)
{
    return Cons(variables, values);
}

extern SchemeObject*
FrameVariables(SchemeObject* frame)
{
    return Car(frame);
}

extern SchemeObject*
FrameValues(SchemeObject* frame)
{
    return Cdr(frame);
}

extern void
AddBindingToFrame(SchemeObject* var, SchemeObject* val, SchemeObject* frame)
{
    SetCar(frame, Cons(var, Car(frame)));
    SetCdr(frame, Cons(val, Cdr(frame)));
}

extern SchemeObject*
ExtendEnvironment(SchemeObject* var, SchemeObject* val, SchemeObject* base_environ)
{
    return Cons(MakeFrame(var, val), base_environ);
}

extern SchemeObject*
LookupVariableValue(SchemeObject* var, SchemeObject* environ)
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
    fprintf(stderr, "unbound variable, %s\n", var->data.symbol.value);
    exit(1);
}

extern void
SetVariableValue(SchemeObject* var, SchemeObject* val, SchemeObject* environ)
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
    fprintf(stderr, "unbound variable, %s\n", var->data.symbol.value);
    exit(1);
}

extern SchemeObject*
SetupEnvironment()
{
    SchemeObject* initial_env = ExtendEnvironment(TheEmptyList, TheEmptyList, TheEmptyEnvironment);
    return initial_env;
}

extern SchemeObject*
InteractionEnvironmentProc(SchemeObject* arguments)
{
    return TheGlobalEnvironment;
}

extern SchemeObject*
NullEnvironmentProc(SchemeObject* arguments)
{
    return SetupEnvironment();
}

extern SchemeObject*
MakeEnvironment()
{
    SchemeObject* env;
    env = SetupEnvironment();
    PopulateEnvironment(env);
    return env;
}

extern SchemeObject*
EnvironemntProc(SchemeObject* arguments)
{
    return MakeEnvironment();
}

extern SchemeObject*
EvalProc(SchemeObject* arguments)
{
    fprintf(stderr, "illagel state: The body of the eval primitive should not execute.\n");
    exit(1);
}
