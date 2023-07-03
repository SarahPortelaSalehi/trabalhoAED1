#include "posfixa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void inicializar(pilha* A) {
    A->topo = NULL;
}

pilha* empilhar(pilha* A, float num) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->valor = num;
        novo->proximo = A->topo;
        A->topo = novo;
        return A;
    } else {
        printf("\tErro ao alocar memoria!\n");
        return NULL;
    }   
}
No* desempilhar(pilha* A) {
    No* remover = NULL;

    if (A->topo != NULL) {
        remover = A->topo;
        A->topo = remover->proximo;
    } else {
        printf("\tPilha vazia\n");
    }
    return remover;
}
float operacao(float a, float b, char x) {
    switch (x) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '/':
            return a / b;
        case '*':
            return a * b;
        default:
            return 0.0;
    }
}

float resolver_expressao(char x[]) {
    char* pt;
    float num;
    No* n1, *n2 = NULL;
    pilha a;
    inicializar(&a);
    pt = strtok(x, " ");
    while (pt) {
        if (pt[0] == '+' || pt[0] == '-' || pt[0] == '/' || pt[0] == '*') {
            n1 = desempilhar(&a);
            n2 = desempilhar(&a);
            num = operacao(n2->valor, n1->valor, pt[0]);
            a.topo = empilhar(&a, num)->topo;
            free(n1);
            free(n2);
        } else {
            num = strtol(pt, NULL, 10);
            empilhar(&a, num);
        }
        pt = strtok(NULL, " ");
    }
    n1 = desempilhar(&a);
    num = n1->valor;
    free(n1);
    return num;
}
float resolver_expressao_pre_fixa(char exp[]) {
    pilha a;
    inicializar(&a);
    int tamanho = strlen(exp);

    for (int i = tamanho - 1; i >= 0; i--) {
        if (isdigit(exp[i])) {
            float num = (float)(exp[i] - '0');
            empilhar(&a, num);
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            No* n1 = desempilhar(&a);
            No* n2 = desempilhar(&a);

            float t = n1->valor;
            float b = n2->valor;
            float resultado=0;

            switch (exp[i]) {
                case '+':
                    resultado = t + b;
                    break;
                case '-':
                    resultado = t - b;
                    break;
                case '*':
                    resultado = t * b;
                    break;
                case '/':
                    resultado = t / b;
                    break;
            }

            empilhar(&a,resultado);
            free(n1);
            free(n2);
        }
    }

    No* n = desempilhar(&a);
    float resultado_final = n->valor;
    free(n);

    return resultado_final;
}
char* Unir(char* A, char* B, char op) {
    char* resultado = (char*) malloc(strlen(A) + 2 + strlen(B));
    sprintf(resultado, "%s %c %s", A, op, B);
    return resultado;
}
char* Unir2(char* A, char* B, char op) {
    char* resultado = (char*) malloc(strlen(A) + 2 + strlen(B));
    sprintf(resultado, "%s %s %c", A, B, op);
    return resultado;
}

void exibir(pilha* A) {
    No* i = A->topo;

    while (i != NULL) {
        printf("%s", i->string);
        i = i->proximo;
    }
}

void empilhar1(pilha* A, char* num) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->string = strdup(num);
        novo->proximo = A->topo;
        A->topo = novo;
    } else {
        printf("\tErro ao alocar memoria!\n");
    }
}

char* P_Ix(char exp[]) {
    char* pt;
    char* res;
    No* n1, *n2 = NULL;
    pilha a;
    inicializar(&a);
    pt = strtok(exp, " ");
    while (pt) {
        if (pt[0] == '+' || pt[0] == '-' || pt[0] == '/' || pt[0] == '*') {
            n1 = desempilhar(&a);
            n2 = desempilhar(&a);
            res = Unir(n2->string, n1->string, pt[0]);
            empilhar1(&a, res);
            free(n1);
            free(n2);
        } else {
            empilhar1(&a, pt);
        }
        pt = strtok(NULL, " ");
    }
    n1 = desempilhar(&a);
    res = n1->string;
    free(n1);
    return res;
}
char* P_Px(char exp[]) {
    char* pt;
    char* res;
    No* n1, *n2 = NULL;
    pilha a;
    inicializar(&a);
    pt = strtok(exp, " ");
    while (pt) {
        if (pt[0] == '+' || pt[0] == '-' || pt[0] == '/' || pt[0] == '*') {
            n1 = desempilhar(&a);
            n2 = desempilhar(&a);
            res = Unir1(pt[0], n2->string, n1->string);
            empilhar1(&a, res);
            free(n1);
            free(n2);
        } else {
            empilhar1(&a, pt);
        }
        pt = strtok(NULL, " ");
    }
    n1 = desempilhar(&a);
    res = n1->string;
    free(n1);
    return res;
}
char* Pre_Posx(char exp[]) {
     char* pt;
    char* res;
    No* n1, *n2 = NULL;
    pilha a;
    inicializar(&a);
    pt = strtok(exp, " ");
    while (pt) {
        if (pt[0] == '+' || pt[0] == '-' || pt[0] == '/' || pt[0] == '*') {
            n1 = desempilhar(&a);
            n2 = desempilhar(&a);
            res = UnirPP(pt[0], n2->string, n1->string);
            empilhar1(&a, res);
            free(n1);
            free(n2);
        } else {
            empilhar1(&a, pt);
        }
        pt = strtok(NULL, " ");
    }
    n1 = desempilhar(&a);
    res = n1->string;
    free(n1);
    return res;
}
char* UnirPP(char op, char* A, char* B) {
    char* resultado = (char*) malloc(strlen(A) + strlen(B) + 3);
    resultado[0] = '\0';
    strcat(resultado, A);
    strcat(resultado, " ");
    strcat(resultado, B);
    char operador[2] = {op, '\0'};
    strcat(resultado, " ");
    strcat(resultado, operador);
    return resultado;
}
char* infixToPrefix(char* expression){
    char reversedExp[strlen(expression) + 1];
    int j = 0;

    // Inverte a expressão infixa
    for (int i = strlen(expression) - 1; i >= 0; i--) {
        if (expression[i] == '(')
            reversedExp[j++] = ')';
        else if (expression[i] == ')')
            reversedExp[j++] = '(';
        else
            reversedExp[j++] = expression[i];
    }
    reversedExp[j] = '\0';

    // Converte a expressão infixa invertida para posfixa
    char* postfixExp = P_Ix(reversedExp);

    // Inverte novamente a expressão posfixa para obter a notação prefixa
    char* prefixExp = strdup(postfixExp);
    int len = strlen(prefixExp);
    for (int i = 0; i < len / 2; i++) {
        char temp = prefixExp[i];
        prefixExp[i] = prefixExp[len - i - 1];
        prefixExp[len - i - 1] = temp;
    }

    // Libera a memória alocada
    apagar_expressao(postfixExp);

    return prefixExp;
}
int precedencia(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else
        return 0;
}
char* infixToPostfix(char* expression) {
    char* postfixExp = (char*)malloc(strlen(expression) + 1);
    int j = 0;
    pilha a;
    inicializar(&a);

    char* pt = strtok(expression, " ");
    while (pt) {
        if (isdigit(pt[0])) {
            strcat(postfixExp, pt);
            strcat(postfixExp, " ");
        } else if (pt[0] == '(') {
            empilhar1(&a, pt);
        } else if (pt[0] == ')') {
            while (a.topo != NULL && a.topo->string[0] != '(') {
                No* n = desempilhar(&a);
                strcat(postfixExp, n->string);
                strcat(postfixExp, " ");
                free(n);
            }
            if (a.topo != NULL && a.topo->string[0] == '(') {
                No* n = desempilhar(&a);
                free(n);
            }
        } else if (pt[0] == '+' || pt[0] == '-' || pt[0] == '*' || pt[0] == '/') {
            while (a.topo != NULL && precedencia(pt[0]) <= precedencia(a.topo->string[0])) {
                No* n = desempilhar(&a);
                strcat(postfixExp, n->string);
                strcat(postfixExp, " ");
                free(n);
            }
            empilhar1(&a, pt);
        }
        pt = strtok(NULL, " ");
    }

    while (a.topo != NULL) {
        No* n = desempilhar(&a);
        strcat(postfixExp, n->string);
        strcat(postfixExp, " ");
        free(n);
    }

    return postfixExp;
}
char* prefixToPostfix(char exp[]) {
    char* pt;
    pilha a,b;
    inicializar(&a);
    inicializar(&b);
    int tamanho = strlen(exp);

    for (int i = tamanho - 1; i >= 0; i--) {
        if (isdigit(exp[i])) {
            char num[2] = {exp[i], '\0'};
            empilhar1(&a, num);
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            No* n1 = desempilhar(&a);
            No* n2 = desempilhar(&a);

            char t[2] = {exp[i], '\0'};
            char* resultado = Unir2(n1->string, n2->string, t[0]);
            empilhar1(&a, resultado);

            free(n1);
            free(n2);
        }
    }

    No* n = desempilhar(&a);
    char* resultado_final = n->string;
    free(n);

    return resultado_final;
}
char* prefixToInfix(char* expression) {
    pilha a;
    inicializar(&a);
    char* pt;
    char* res;

    pt = strtok(expression, " ");
    while (pt){
        if (pt[0] == '+' || pt[0] == '-' || pt[0] == '*' || pt[0] == '/') {
            No* n1 = desempilhar(&a);
            No* n2 = desempilhar(&a);
            res = UnirPP(pt[0], n1->string, n2->string);
            empilhar1(&a, res);
            free(n1);
            free(n2);
        } else {
            empilhar1(&a, pt);
        }
        pt = strtok(NULL, " ");
    }
    No* n = desempilhar(&a);
    res = n->string;
    free(n);
    return res;
}
char* Unir1(char op, char* A, char* B) {
    char* resultado = (char*) malloc(strlen(A) + strlen(B) + 2);
    resultado[0] = op;
    strcpy(resultado + 1, A);
    strcat(resultado, B);
    return resultado;
}
void apagar_expressao(char* expressao){
	free(expressao);
}
/*
void inicializar(pilha* A) {
    A->topo = NULL; // Inicializa a pilha com o topo apontando para NULL (pilha vazia).
}

pilha* empilhar(pilha* A, float num) {
    // ...
    // Aloca um novo nó na memória, atribui o valor passado e faz o novo nó apontar para o antigo topo.
}

No* desempilhar(pilha* A) {
    // ...
    // Desempilha um elemento da pilha e retorna o nó desempilhado.
}

float operacao(float a, float b, char x) {
    // ...
    // Realiza a operação aritmética (+, -, *, /) entre os valores a e b.
}

float resolver_expressao(char x[]) {
    // ...
    // Resolve uma expressão posfixa (notação pós-fixa) usando uma pilha de valores.
}

float resolver_expressao_pre_fixa(char exp[]) {
    // ...
    // Resolve uma expressão pré-fixa (notação pré-fixa) usando uma pilha de valores.
}

char* Unir(char* A, char* B, char op) {
    // ...
    // Concatena duas strings e insere o operador entre elas, formando uma nova expressão.
}

void empilhar1(pilha* A, char* num) {
    // ...
    // Cria um novo nó na pilha para armazenar uma string.
}

char* P_Ix(char exp[]) {
    // ...
    // Converte uma expressão infixa para uma expressão posfixa (notação pós-fixa).
}

char* P_Px(char exp[]) {
    // ...
    // Converte uma expressão infixa para uma expressão pré-fixa (notação pré-fixa).
}

char* Pre_Posx(char exp[]) {
    // ...
    // Converte uma expressão pré-fixa para uma expressão posfixa (notação pós-fixa).
}

char* UnirPP(char op, char* A, char* B) {
    // ...
    // Concatena duas strings e insere o operador no início, formando uma nova expressão pré-fixa.
}

char* infixToPrefix(char* expression) {
    // ...
    // Converte uma expressão infixa para uma expressão pré-fixa usando as funções auxiliares.
}

int precedencia(char op) {
    // ...
    // Define a precedência dos operadores.
}

char* infixToPostfix(char* expression) {
    // ...
    // Converte uma expressão infixa para uma expressão posfixa usando uma pilha.
*/
