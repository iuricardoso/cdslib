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
#include "../src/queue.h"

/* protótipos de funções dos módulos */
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
        printf("Não foi possível alocar memória.\n");
        return 1;
    }

    char opcao;

    do {
        printf("O que desejas fazer?");
        printf("\n\tA - Adicionar elemento;");
        printf("\n\tR - Remover elemento;");
        printf("\n\tP - Pegar elemento do início da fila;");
        printf("\n\tT - Mostrar Tamanho da fila;");
        printf("\n\tL - Limpar fila;");
        printf("\n\tS - Sair.");
        printf("\nOpção: ");
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
                printf("\nERRO: Opção inválida!\n");
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
        printf("ERRO: Impossível armazenar elemento; fila está cheia.");
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
        printf("ERRO: Impossível remover elemento; fila está vazia.");
    }
}

void pegarElemento(QUEUE f) {
    uint8_t byte;

    if ( queuePeek(f, &byte) ) {
        int e = (int) byte;
        printf("Byte do início da fila: %3d [0x%04X]\n", e, e);
        mostrarTamanho(f);
    }
    else {
        printf("ERRO: Impossível pegar elemento; fila está vazia.");
    }
}

void limparFila(QUEUE f) {
    printf("Limpando fila... ");
    queueClear(f);
    printf("FEITO!\n");
    mostrarTamanho(f);
}

void mostrarTamanho(QUEUE f) {
    printf("Há %d elemento(s) na fila.", queueSize(f));
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
        error("Não conseguiu instanciar. Faltou memória????");
    }

    if (queueCapacity(q) != SIZE) {
        error("Limite de elementos está incorreto.");
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
            error("Tamanho da fila não está correro durante o ciclo de adição.");
        }
    }

    if ( queueSize(q) != SIZE) {
        error("Tamanho da fila não correspondente ao correto!");
    }

    e = 50;
    if ( queueAdd(q, &e) ) {
        error("Fila armazenou elemento além dos limites permitidos.");
    }

    if ( queueSize(q) != SIZE) {
        error("Tamanho da fila não correspondente ao correto depois da remoção!");
    }

    for (i=0; i<SIZE; i++) {
        if (! queuePeek(q, &e)) {
            error("Não aceitou carregar elemento da frente fila quando ela não está vazia.");
        }

        if (e != array[i]) {
            error("Carregamento de elemento da frente não está pegando o elemento correto.");
        }

        if (! queueRemove(q, &e)) {
            error("Remoção negada sendo que a fila não está vazia.");
        }

        if (e != array[i]) {
            error("Remoção de elementos não está pegando o elemento correto.");
        }

        if (queueSize(q) != SIZE - i - 1) {
            error("Tamanho da fila não está correro durante o ciclo de remoção.");
        }
    }

    if (queueRemove(q, &e)) {
        error("Remoção aceita sendo que a fila está vazia.");
    }

    e = 10;
    if (! queueAdd(q, &e) ) {
        error("Negou adição quando a fila está vazia.");
    }

    if (! queueRemove(q, &e) ) {
        error("Negou adição quando a fila está vazia.");
    }

    if (e != 10) {
        error("Recuperou elemento incorreto.");
    }

    if (queueCapacity(q) != SIZE) {
        error("Limite de elementos está incorreto.");
    }

    printf("Teste finalizado com sucesso!\n");
}
