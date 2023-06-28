#include "posfixa.h"
#include <stdio.h>

int main(){
    char exp[50] = {"5 3 2 4 6 7 1 + * + * + *"};

    printf("Resultado de %s:\t", exp);
    printf("%f\n", resolver_expressao(exp));

    return 0;
}
