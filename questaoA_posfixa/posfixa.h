#ifndef POSFIXA_H
#define POSFIXA_H

typedef struct no{
    float valor;
    struct no *proximo;
} No;

No* empilhar(No *pilha, float num);
No* desempilhar(No **pilha);
float operacao(float a, float b, char x);
float resolver_expressao(char x[]);

#endif
