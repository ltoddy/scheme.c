#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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
    char* basedir;
    if ((basedir = getcwd(NULL, 0)) == NULL) {
        exit(-1);
    }
    char builtin[128];
    sprintf(builtin, "%s/%s", basedir, "lib/builtin.scm");

    SchemeObject* exp;
    InitScheme();

    SchemeObject* stdlib = AllocObject();
    stdlib->type = PAIR;
    stdlib->data.pair.car = AllocObject();
    stdlib->data.pair.car->type = STRING;
    stdlib->data.pair.car->data.string.value = builtin;
    stdlib->data.pair.cdr = TheEmptyList;

    LoadProcedure(stdlib);

    prompt();

    for (;;) {
        printf("> ");
        exp = Reader(stdin);
        if (exp == NULL) {
            break;
        }
        Writer(stdout, Eval(exp, TheGlobalEnvironment));
        printf("\n");
    }

    free(basedir);
    free(exp);

    return 0;
}
