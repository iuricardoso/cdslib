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

#include <stdlib.h>
#include <string.h>
#include "queue.h"

struct Queue {
    void * v;
    int begin;
    int end;
    int capacity;
    size_t elementSize;
    int size;
};

QUEUE queueCreate(size_t capacity, size_t elementSize) {
    struct Queue * q = malloc(sizeof(struct Queue));
    if (q == NULL) {
        return NULL;
    }

    q->v = calloc(capacity, elementSize);
    if (q->v == NULL) {
        free(q);
        return NULL;
    }

    q->capacity = capacity;
    q->begin = 0;
    q->end = 0;
    q->elementSize = elementSize;
    q->size = 0;

    return q;
}
void queueFree(QUEUE q) {

    struct Queue * qu = (struct Queue *)q;
    free(qu->v);
    free(q);
}

void queueClear(QUEUE q) {
    struct Queue * qu = (struct Queue *)q;
    qu->begin = 0;
    qu->end = 0;
    qu->size = 0;
}

int queueAdd(QUEUE q, const void * element) {
    struct Queue * qu = (struct Queue *) q;
    // vari&acute;vel lógica: permite armazenar quando a fila não estiver cheia.
    int add = (qu->size < qu->capacity);

    // Se permite armazenar ...
    if (add) {
        void * target = qu->v+(qu->end * qu->elementSize);
        memcpy(target, element, qu->elementSize);

        // Como foi acrescentado um elemento, o fim é incrementado em um.
        // Se já passou da última posição, posiciona na primeira.
        qu->end = (qu->end + 1) % qu->capacity;

        qu->size++;
    }

    return add;
}

int queueRemove(QUEUE q, void * element) {
    int remove = queuePeek(q, element);

    if (remove) {
        struct Queue * qu = (struct Queue *) q;
        // incrementa o início porque o elemento do início da fila foi removido.
        qu->begin = (qu->begin + 1) % qu->capacity;

        qu->size--;
    }

    return remove;
}

int queuePeek(const QUEUE q, void * element) {
    struct Queue * qu = (struct Queue *) q;
    int remove = (qu->size > 0);

    if (remove) {
        void * target = qu->v + (qu->begin * qu->elementSize);
        // elemento a ser retornado é o primeiro da fila.
        memcpy(element, target, qu->elementSize);
    }

    return remove;
}

int queueSize(const QUEUE q) {
    return ((struct Queue *)q)->size;
}

int queueCapacity(const QUEUE q) {
    return ((struct Queue *)q)->capacity;
}

