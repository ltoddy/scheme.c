#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "object.h"
#include "read.h"
#include "eval.h"
#include "environment.h"
#include "builtin.h"
#include "write.h"

SchemeObject* LoadProcedure(SchemeObject* arguments)
{
    SchemeObject* exp;
    SchemeObject* result = NULL;

    char* filename = Car(arguments)->data.string.value;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        fprintf(stderr, "cloud not load file: %s.\n", filename);
        exit(1);
    }
    while ((exp = Read(in)) != NULL) {
        result = Eval(exp, TheGlobalEnvironment);
    }
    fclose(in);
    return result;
}

static SchemeObject* MakeInputPort(FILE* stream)
{
    SchemeObject* obj = AllocObject();
    obj->type = INPUT_PORT;
    obj->data.input_port.stream = stream;
    return obj;
}

SchemeObject* OpenInputPortProcedure(SchemeObject* arguments)
{
    char* filename = Car(arguments)->data.string.value;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        fprintf(stderr, "could not open file: \"%s\".\n", filename);
        exit(1);
    }
    return MakeInputPort(in);
}

SchemeObject* CloseInputPortProcedure(SchemeObject* arguments)
{
    int result = fclose(Car(arguments)->data.input_port.stream);
    if (result == EOF) {
        fprintf(stderr, "could not close port.\n");
        exit(1);
    }
    return OkSymbol;
}

static char IsInputPort(SchemeObject* obj)
{
    return obj->type == INPUT_PORT;
}

SchemeObject* IsInputPortProcedure(SchemeObject* arguments)
{
    return IsInputPort(Car(arguments)) ? True : False;
}

SchemeObject* ReadProcedure(SchemeObject* arguments)
{
    FILE* in = IsTheEmptyList(arguments) ?
               stdin :
               Car(arguments)->data.input_port.stream;
    SchemeObject* result = Read(in);
    return (result == NULL) ? EOF_OBJ : result;
}

SchemeObject* ReadCharProcedure(SchemeObject* arguments)
{
    FILE* in = IsTheEmptyList(arguments) ?
               stdin :
               Car(arguments)->data.input_port.stream;
    int result = getc(in);
    return (result == EOF) ? EOF_OBJ : MakeCharacter((char) result);
}

