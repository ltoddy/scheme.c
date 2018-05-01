#include <stdio.h>
#include "scheme/write.h"
#include "scheme/eval.h"
#include "scheme/read.h"

int main()
{

    printf("Welcome to Scheme. Use ctrl-c to exit.\n");

    while (1) {
        printf("> ");
        Write(Eval(Read(stdin)));
        printf("\n");
    }

    return 0;
}
