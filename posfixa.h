#ifndef POSFIXA_H
#define POSFIXA_H

typedef struct no {
    float valor;
    char* string;
    struct no* proximo;
} No;

typedef struct {
    No* topo;
} pilha;

void inicializar(pilha* A);
pilha* empilhar(pilha* A, float num);
No* desempilhar(pilha* A);
float operacao(float a, float b, char x);
float resolver_expressao(char x[]);
float resolver_expressao_pre_fixa(char exp[]);
char* P_Ix(char exp[]);
void exibir(pilha* A);
void empilhar1(pilha* A, char* num);
char* Unir(char* A, char* B, char op);
char* P_Px(char exp[]);
char* Pre_Posx(char exp[]);
char* UnirPP(char op, char* A, char* B);
char* infixToPrefix(char* expression);
char* infixToPostfix(char* expression);
char* prefixToInfix(char* expression);
char* prefixToPostfix(char* expression);
char* Unir1(char op, char* A, char* B);
void apagar_expressao(char* expressao);
#endif

