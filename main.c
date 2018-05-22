#include <stdio.h>
#include "scheme/write.h"
#include "scheme/eval.h"
#include "scheme/read.h"
#include "scheme/builtin.h"
#include "scheme/environment.h"

int main()
{
    InitScheme();

    printf("Welcome to Scheme. Use ctrl-c to exit.\n");

    for (;;) {
        printf("> ");
        Write(Eval(Read(stdin), TheGlobalEnvironment));
        printf("\n");
    }

    return 0;
}
