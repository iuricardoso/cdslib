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
#include "../src/queue.h"

/* prot�tipos de fun��es dos m�dulos */
void armazenarElemento(QUEUE f);
void removerElemento(QUEUE f);
void pegarElemento(QUEUE f);
void mostrarTamanho(QUEUE f);
void limparFila(QUEUE f);
void testarFila(void);
void error(const char msg[]);
int main(void) {

    setlocale(LC_ALL, "Portuguese");
    testarFila();

    QUEUE f = queueCreate(5, sizeof(uint8_t));
    if (f == NULL) {
        printf("N�o foi poss�vel alocar mem�ria.\n");
        return 1;
    }

    char opcao;

    do {
        printf("O que desejas fazer?");
        printf("\n\tA - Adicionar elemento;");
        printf("\n\tR - Remover elemento;");
        printf("\n\tP - Pegar elemento do in�cio da fila;");
        printf("\n\tT - Mostrar Tamanho da fila;");
        printf("\n\tL - Limpar fila;");
        printf("\n\tS - Sair.");
        printf("\nOp��o: ");
        scanf("%c", &opcao);
        fflush(stdin);

        printf("\n");

        opcao = toupper(opcao);

        switch(opcao) {
            case 'A': {
                armazenarElemento(f);
                break;
            }
            case 'R': {
                removerElemento(f);
                break;
            }
            case 'P': {
                pegarElemento(f);
                break;
            }
            case 'L': {
                limparFila(f);
                break;
            }
            case 'T': {
                mostrarTamanho(f);
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

    queueFree(f);

    return 0;
}

void armazenarElemento(QUEUE f) {
    unsigned int e;

    printf("Digite o elemento a ser armazenado: ");
    scanf("%u", &e);
    fflush(stdin);

    uint8_t byte = (uint8_t) e;

    if ( queueAdd(f, &byte) ) {
        e = (int) byte;
        printf("Byte armazenado: %3d [0x%04X]\n", e, e);
        mostrarTamanho(f);
    }
    else {
        printf("ERRO: Imposs�vel armazenar elemento; fila est� cheia.");
    }
}

void removerElemento(QUEUE f) {
    uint8_t byte;

    if ( queueRemove(f, &byte) ) {
        int e = (int) byte;
        printf("Byte removido: %3d [0x%04X]\n", e, e);
        mostrarTamanho(f);
    }
    else {
        printf("ERRO: Imposs�vel remover elemento; fila est� vazia.");
    }
}

void pegarElemento(QUEUE f) {
    uint8_t byte;

    if ( queuePeek(f, &byte) ) {
        int e = (int) byte;
        printf("Byte do in�cio da fila: %3d [0x%04X]\n", e, e);
        mostrarTamanho(f);
    }
    else {
        printf("ERRO: Imposs�vel pegar elemento; fila est� vazia.");
    }
}

void limparFila(QUEUE f) {
    printf("Limpando fila... ");
    queueClear(f);
    printf("FEITO!\n");
    mostrarTamanho(f);
}

void mostrarTamanho(QUEUE f) {
    printf("H� %d elemento(s) na fila.", queueSize(f));
}

void error(const char msg[]) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

#define SIZE 5
void testarFila(void) {
    printf("Iniciando teste de Fila.\n");
    QUEUE q = queueCreate(SIZE, sizeof(uint8_t));
    if (q == NULL) {
        error("N�o conseguiu instanciar. Faltou mem�ria????");
    }

    if (queueCapacity(q) != SIZE) {
        error("Limite de elementos est� incorreto.");
    }

    uint8_t array[SIZE];
    int i;
    uint8_t e;

    srand(time(NULL));
    for(i=0; i<SIZE; i++) {
        array[i] = (uint8_t) (rand() % 256);

        if (! queueAdd(q, &array[i]) ) {
            error("Fila atingiu limite antes do devido.");
        }

        if (queueSize(q) != i + 1) {
            error("Tamanho da fila n�o est� correro durante o ciclo de adi��o.");
        }
    }

    if ( queueSize(q) != SIZE) {
        error("Tamanho da fila n�o correspondente ao correto!");
    }

    e = 50;
    if ( queueAdd(q, &e) ) {
        error("Fila armazenou elemento al�m dos limites permitidos.");
    }

    if ( queueSize(q) != SIZE) {
        error("Tamanho da fila n�o correspondente ao correto depois da remo��o!");
    }

    for (i=0; i<SIZE; i++) {
        if (! queuePeek(q, &e)) {
            error("N�o aceitou carregar elemento da frente fila quando ela n�o est� vazia.");
        }

        if (e != array[i]) {
            error("Carregamento de elemento da frente n�o est� pegando o elemento correto.");
        }

        if (! queueRemove(q, &e)) {
            error("Remo��o negada sendo que a fila n�o est� vazia.");
        }

        if (e != array[i]) {
            error("Remo��o de elementos n�o est� pegando o elemento correto.");
        }

        if (queueSize(q) != SIZE - i - 1) {
            error("Tamanho da fila n�o est� correro durante o ciclo de remo��o.");
        }
    }

    if (queueRemove(q, &e)) {
        error("Remo��o aceita sendo que a fila est� vazia.");
    }

    e = 10;
    if (! queueAdd(q, &e) ) {
        error("Negou adi��o quando a fila est� vazia.");
    }

    if (! queueRemove(q, &e) ) {
        error("Negou adi��o quando a fila est� vazia.");
    }

    if (e != 10) {
        error("Recuperou elemento incorreto.");
    }

    if (queueCapacity(q) != SIZE) {
        error("Limite de elementos est� incorreto.");
    }

    printf("Teste finalizado com sucesso!\n");
}
