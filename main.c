#include <stdio.h>
#include "scheme/write.h"
#include "scheme/eval.h"
#include "scheme/read.h"
#include "scheme/builtin.h"
#include "scheme/environment.h"

int main()
{
    SchemeObject* exp;
    InitScheme();

    printf("Welcome to Scheme. Use ctrl-c or ctrl-d (this is the eof shortcut) to exit.\n");

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
