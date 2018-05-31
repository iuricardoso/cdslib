/*
MIT License

Copyright (c) 2018 Iuri S�nego Cardoso. iuricardoso@gmail.com

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

/* prot�tipos de fun��es dos m�dulos */
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
        printf("N�o foi poss�vel alocar mem�ria.\n");
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
        printf("\nOp��o: ");
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
                printf("\nERRO: Op��o inv�lida!\n");
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
        printf("ERRO: Imposs�vel empilhar elemento; pilha est� cheia.");
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
        printf("ERRO: Imposs�vel desempilhar elemento; pilha est� vazia.");
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
        printf("ERRO: Imposs�vel pegar elemento do topo; pilha est� vazia.");
    }
}

void limpar(STACK p) {
    printf("Limpando pilha... ");
    stackClear(p);
    printf("FEITO!\n");
    mostrarTamanho(p);
}

void mostrarTamanho(STACK p) {
    printf("H� %d elemento(s) na pilha.", stackSize(p));
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
        error("N�o conseguiu instanciar. Faltou mem�ria????");
    }

    if (stackCapacity(s) != SIZE) {
        error("Limite de elementos est� incorreto.");
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
            error("Tamanho da fila n�o est� correro durante o ciclo de adi��o.");
        }
    }

    if ( stackSize(s) != SIZE) {
        error("Tamanho da fila n�o correspondente ao correto!");
    }

    e = 50;
    if ( stackPush(s, &e) ) {
        error("Fila armazenou elemento al�m dos limites permitidos.");
    }

    if ( stackSize(s) != SIZE) {
        error("Tamanho da fila n�o correspondente ao correto depois da remo��o!");
    }

    for (i=0; i<SIZE; i++) {
        if (! stackPeekTop(s, &e)) {
            error("N�o aceitou carregar elemento da frente fila quando ela n�o est� vazia.");
        }

        if (e != array[SIZE-i-1]) {
            error("Carregamento de elemento da frente n�o est� pegando o elemento correto.");
        }

        if (! stackPop(s, &e)) {
            error("Remo��o negada sendo que a fila n�o est� vazia.");
        }

        if (e != array[SIZE-i-1]) {
            error("Remo��o de elementos n�o est� pegando o elemento correto.");
        }

        if (stackSize(s) != SIZE - i - 1) {
            error("Tamanho da fila n�o est� correro durante o ciclo de remo��o.");
        }
    }

    if (stackPop(s, &e)) {
        error("Remo��o aceita sendo que a fila est� vazia.");
    }

    e = 10;
    if (! stackPush(s, &e) ) {
        error("Negou adi��o quando a fila est� vazia.");
    }

    if (! stackPush(s, &e) ) {
        error("Negou adi��o quando a fila est� vazia.");
    }

    if (e != 10) {
        error("Recuperou elemento incorreto.");
    }

    if (stackCapacity(s) != SIZE) {
        error("Limite de elementos est� incorreto.");
    }

    printf("Teste finalizado com sucesso!\n");
}
