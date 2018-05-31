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
#include "list.h"

struct List {
    void * data;
    int size;
    size_t limit;
    size_t elementSize;
};

LIST listCreate(size_t limit, size_t elementSize) {
    struct List * l = malloc(sizeof(struct List));
    if (l == NULL) {
        return NULL;
    }

    l->data = malloc(limit * elementSize);
    if (l->data == NULL) {
        free(l);
        return NULL;
    }

    l->size = 0;
    l->limit = limit;
    l->elementSize = elementSize;

    return l;
}

void listFree(LIST l) {
    struct List * li = (struct List *) l;

    free(li->data);
    free(li);
}

int listAdd(LIST l, const void * element) {
    struct List * li = (struct List *)l;

    if (li->size == li->limit) {
        return LIST_IS_FULL; // ERROR.
    }

    memcpy(&li->data[li->size * li->elementSize], element, li->elementSize);
    li->size++;

    return li->size;
}

static int _list_valid_pos(struct List * li, int position) {
    if (position > li->size) {
        return INVALID_POSITION;
    }

    if (position < 0) {
        return INVALID_POSITION;
    }

    return position;
}

int listAddAtPosition(LIST l, const void * element, int position) {
    struct List * li = (struct List *)l;

    if (li->size == li->limit) {
        return LIST_IS_FULL; // ERROR.
    }

    position = _list_valid_pos(li, position);
    if (position == INVALID_POSITION) {
        return INVALID_POSITION; // ERROR.
    }

    int i;

    for (i=li->size; i>position; i--) {
        memcpy(&li->data[i* li->elementSize], &li->data[(i-1)* li->elementSize], li->elementSize);
    }

    memcpy(&li->data[position * li->elementSize], element, li->elementSize);

    li->size++;

    return li->size;
}

static int _list_remove(LIST l, int position) {
    struct List * li = (struct List *)l;
    int i;

    for (i=position; i<li->size-1; i++) {
        memcpy(&li->data[i * li->elementSize], &li->data[(i+1) * li->elementSize], li->elementSize);
    }

    li->size--;

    return li->size;
}

int listRemove(LIST l, const void * element) {
    int i = listGetPosition(l, element);

    if (i >= 0) {
        _list_remove(l, i);
    }

    return i;
}


int listRemoveAtPosition(LIST l, int position) {
    struct List * li = (struct List *)l;

    if (li->size == 0) {
        return INVALID_POSITION; // ERROR.
    }

    position = _list_valid_pos(li, position);
    if (position == INVALID_POSITION) {
        return INVALID_POSITION; // ERROR.
    }

    return _list_remove(l, position);
}

int listGetPosition(LIST l, const void * element) {
    struct List * li = (struct List *)l;
    int i;
    for (i=0; i<li->size; i++) {
        if (memcmp(&li->data[i * li->elementSize], element, li->elementSize) == 0) {
            return i;
        }
    }

    return NOT_FOUND;
}

int listSet(LIST l, const void * element, int position) {
    struct List * li = (struct List *)l;

    if (li->size == 0) {
        return INVALID_POSITION; // ERROR
    }

    position = _list_valid_pos(li, position);
    if (position == INVALID_POSITION) {
        return INVALID_POSITION;
    }

    memcpy(&li->data[position * li->elementSize], element, li->elementSize);

    return 0;
}

int listGet(LIST l, void * element, int position) {
    struct List * li = (struct List *)l;

    if (li->size == 0) {
        return INVALID_POSITION; // ERROR
    }

    position = _list_valid_pos(li,position);
    if (position == INVALID_POSITION) {
        return INVALID_POSITION;
    }

    memcpy(element, &li->data[position * li->elementSize], li->elementSize);

    return 0;
}

void listClear(LIST l) {
    struct List * li = (struct List *)l;

    li->size = 0;
}

int listSize(const LIST l) {
    return ((struct List *)l)->size;
}

size_t listLimit(const LIST l) {
    return ((struct List *)l)->limit;
}
