#include "builtin.h"
#include "environment.h"

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

    TheEmptyEnvironment = TheEmptyList;
    TheGlobalEnvironment = SetupEnvironment();
}
