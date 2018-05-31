/*
MIT License

Copyright (c) 2018 Iuri Sônego Cardoso. iuricardoso@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <stdio.h>
#include <locale.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "../src/stack.h"

/* protótipos de funções dos módulos */
void armazenarElemento(STACK p);
void removerElemento(STACK p);
void pegarTopo(STACK p);
void mostrarTamanho(STACK p);
void limpar(STACK p);
void error(const char msg[]);
void testarPilha(void);

int main(void) {
    setlocale(LC_ALL, "Portuguese");

    testarPilha();

    STACK p = stackCreate(5, sizeof(uint8_t));
    if (p == NULL) {
        printf("Não foi possível alocar memória.\n");
        return 1;
    }

    char opcao;

    do {
        printf("O que desejas fazer?");
        printf("\n\tE - Empilhar elemento;");
        printf("\n\tD - Desempilhar elemento;");
        printf("\n\tP - Pegar elemento do topo da pilha;");
        printf("\n\tT - Mostrar Tamanho da pilha;");
        printf("\n\tL - Limpar pilha;");
        printf("\n\tS - Sair.");
        printf("\nOpção: ");
        scanf("%c", &opcao);
        fflush(stdin);

        printf("\n");

        opcao = toupper(opcao);

        switch(opcao) {
            case 'E': {
                armazenarElemento(p);
                break;
            }
            case 'D': {
                removerElemento(p);
                break;
            }
            case 'P':{
                pegarTopo(p);
                break;
            }
            case 'L': {
                limpar(p);
                break;
            }
            case 'T': {
                mostrarTamanho(p);
                break;
            }
            case 'S': {
                break;
            }
            default: {
                printf("\nERRO: Opção inválida!\n");
                break;
            }
        }
        printf("\n\n");
    } while(opcao != 'S');

    stackFree(p);

    return 0;
}

void armazenarElemento(STACK p) {
    unsigned int e;

    printf("Digite o elemento a ser armazenado: ");
    scanf("%u", &e);
    fflush(stdin);

    uint8_t byte = (uint8_t) e;

    if ( stackPush(p, &byte) ) {
        e = (int) byte;
        printf("Byte empilhado: %3d [0x%04X]\n", e, e);
        mostrarTamanho(p);
    }
    else {
        printf("ERRO: Impossível empilhar elemento; pilha está cheia.");
    }
}

void removerElemento(STACK p) {
    uint8_t byte;

    if ( stackPop(p, &byte) ) {
        int e = (int) byte;
        printf("Byte desempilhado: %3d [0x%04X]\n", e, e);
        mostrarTamanho(p);
    }
    else {
        printf("ERRO: Impossível desempilhar elemento; pilha está vazia.");
    }
}

void pegarTopo(STACK p) {
    uint8_t byte;

    if ( stackPeekTop(p, &byte) ) {
        int e = (int) byte;
        printf("Byte do topo: %3d [0x%04X]\n", e, e);
        mostrarTamanho(p);
    }
    else {
        printf("ERRO: Impossível pegar elemento do topo; pilha está vazia.");
    }
}

void limpar(STACK p) {
    printf("Limpando pilha... ");
    stackClear(p);
    printf("FEITO!\n");
    mostrarTamanho(p);
}

void mostrarTamanho(STACK p) {
    printf("Há %d elemento(s) na pilha.", stackSize(p));
}

void error(const char msg[]) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

#define SIZE 5
void testarPilha(void) {
    printf("Iniciando teste de pilha.\n");
    STACK s = stackCreate(SIZE, sizeof(uint8_t));
    if (s == NULL) {
        error("Não conseguiu instanciar. Faltou memória????");
    }

    if (stackCapacity(s) != SIZE) {
        error("Limite de elementos está incorreto.");
    }

    uint8_t array[SIZE];
    int i;
    uint8_t e;

    srand(time(NULL));
    for(i=0; i<SIZE; i++) {
        array[i] = (uint8_t) (rand() % 256);

        if (! stackPush(s, &array[i]) ) {
            error("Fila atingiu limite antes do devido.");
        }

        if (stackSize(s) != i + 1) {
            error("Tamanho da fila não está correro durante o ciclo de adição.");
        }
    }

    if ( stackSize(s) != SIZE) {
        error("Tamanho da fila não correspondente ao correto!");
    }

    e = 50;
    if ( stackPush(s, &e) ) {
        error("Fila armazenou elemento além dos limites permitidos.");
    }

    if ( stackSize(s) != SIZE) {
        error("Tamanho da fila não correspondente ao correto depois da remoção!");
    }

    for (i=0; i<SIZE; i++) {
        if (! stackPeekTop(s, &e)) {
            error("Não aceitou carregar elemento da frente fila quando ela não está vazia.");
        }

        if (e != array[SIZE-i-1]) {
            error("Carregamento de elemento da frente não está pegando o elemento correto.");
        }

        if (! stackPop(s, &e)) {
            error("Remoção negada sendo que a fila não está vazia.");
        }

        if (e != array[SIZE-i-1]) {
            error("Remoção de elementos não está pegando o elemento correto.");
        }

        if (stackSize(s) != SIZE - i - 1) {
            error("Tamanho da fila não está correro durante o ciclo de remoção.");
        }
    }

    if (stackPop(s, &e)) {
        error("Remoção aceita sendo que a fila está vazia.");
    }

    e = 10;
    if (! stackPush(s, &e) ) {
        error("Negou adição quando a fila está vazia.");
    }

    if (! stackPush(s, &e) ) {
        error("Negou adição quando a fila está vazia.");
    }

    if (e != 10) {
        error("Recuperou elemento incorreto.");
    }

    if (stackCapacity(s) != SIZE) {
        error("Limite de elementos está incorreto.");
    }

    printf("Teste finalizado com sucesso!\n");
}
