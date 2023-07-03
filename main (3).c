#include <stdio.h>
#include "posfixa.h"

int main() {
    char expressao[] = "3 4 2 4 + + +";
    char expressao1[] = "3 4 2 4 + + +";
    char expressao2[] = "+ - + 3 4 9 6";
    float resultado = resolver_expressao(expressao);
    printf("Resultado: %.2f\n", resultado);

    char posfixa[] = "3 4 2 4 + + +";
    printf("Expressao posfixa: %s\n", posfixa);
    char* prefixa = P_Px(posfixa);
    printf("Expressao prefixa: %s\n", prefixa);
    char* infixa = P_Ix(expressao1);
    printf("Expressao infixa: %s\n", infixa);
    printf("Expressao posfixa: %s\n", prefixToPostfix(prefixa));
    printf("A resultado da notacao pre-fixa: %f",resolver_expressao_pre_fixa(prefixa));
    apagar_expressao(prefixa);
    apagar_expressao(infixa);
    apagar_expressao(posfixa);
    return 0;
}

