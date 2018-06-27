#include <stdio.h>
#include "scheme/write.h"
#include "scheme/eval.h"
#include "scheme/read.h"
#include "scheme/builtin.h"
#include "scheme/environment.h"
#include "scheme/io.h"

void prompt()
{
    printf("Scheme 0.1.0.\n");
    printf("Use ctrl-d or ctrl-c to exit.\n");
}

int main()
{
    SchemeObject* exp;
    InitScheme();

    SchemeObject* stdlib = AllocObject();
    stdlib->type = PAIR;
    stdlib->data.pair.car = AllocObject();
    stdlib->data.pair.car->type = STRING;
    stdlib->data.pair.car->data.string.value = "lib/builtin.scm";

    stdlib->data.pair.cdr = TheEmptyList;

    LoadProcedure(stdlib);

    prompt();

    for (;;) {
        printf("> ");
        exp = Read(stdin);
        if (exp == NULL) {
            break;
        }
        Write(stdout, Eval(exp, TheGlobalEnvironment));
        printf("\n");
    }

    return 0;
}
