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
#include "stack.h"

struct Stack {
    void * v;
    int size;
    int capacity;
    size_t elementSize;
};

STACK stackCreate(size_t capacity, size_t elementSize) {
    struct Stack * s = malloc(sizeof(struct Stack));
    if (s == NULL) {
        return NULL;
    }

    s->v = malloc(elementSize * capacity);
    if (s->v == NULL) {
        free(s);
        return NULL;
    }

    s->capacity = capacity;
    s->size = 0;
    s->elementSize = elementSize;
    return (STACK) s;
}

void stackFree(STACK s) {
    struct Stack * st = (struct Stack *) s;
    free(st->v);
    free(s);
}

void stackClear(STACK s) {
    ((struct Stack *)s)->size = 0;
}

int stackPush(STACK s, void * element) {
    struct Stack * st = (struct Stack *) s;

    // variável lógica: permite armazenar quando a fila não estiver cheia.
    int add = (st->size < st->capacity);

    // Se permite armazenar ...
    if (add) {
        // Armazena o elemento na próxima posição vaga.
        void * target = st->v + (st->size * st->elementSize);
        memcpy(target, element, st->elementSize);

        // Como foi acrescentado um elemento, o fim é incrementado em um.
        st->size++;
    }

    return add;
}

int stackPop(STACK s, void * element) {
    int remove = stackPeekTop(s, element);

    if (remove) {
        ((struct Stack *)s)->size--;
    }

    return remove;
}

int stackPeekTop(STACK s, void * element) {
    int peek = (stackSize(s) > 0);

    if (peek) {
        struct Stack * st = (struct Stack *)s;
        void * target = st->v + ((st->size-1) * st->elementSize);
        memcpy(element, target, st->elementSize);
    }

    return peek;
}

int stackSize(STACK s) {
    return ((struct Stack *)s)->size;
}

int stackCapacity(STACK s) {
    return ((struct Stack *)s)->capacity;
}
