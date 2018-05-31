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
#include <stdlib.h>
#include <time.h>
#include "../src/list.h"


#define ERROR() printf("\nERROR: %d\n", __LINE__); exit(1)
#define BEGIN(msg) printf("\n*** Begin test %s ***\n", msg)
#define END() printf("\n*** Test finished ***\n")

#define QUANT 1000

void testAddGetRemove(void);
void testAddGetRemoveAtPositionClear(void);
void advancedTest1(void);
void advancedTest2(void);

int main()
{
    srand(time(NULL));

    testAddGetRemove();
    testAddGetRemoveAtPositionClear();
    advancedTest1();
    advancedTest2();

    return 0;
}

void testAddGetRemove(void) {
    BEGIN("testAddGetRemove");

    int array[QUANT];
    int i;

    LIST l = listCreate(QUANT, sizeof(int));
    if (l == NULL) {
        ERROR();
    }

    if (listSize(l) != 0) {
        ERROR();
    }

    if (listLimit(l) != QUANT) {
        ERROR();
    }

    for (i=0; i<QUANT; i++) {
        array[i] = rand() % QUANT;

        if ( listAdd(l, &array[i]) == LIST_IS_FULL) {
            ERROR();
        }
    }

    if ( listAdd(l, &array[0]) != LIST_IS_FULL) {
        ERROR();
    }

    for (i=0; i<QUANT; i++) {
        int e;
        if ( listGet(l, &e, i) == INVALID_POSITION) {
            ERROR();
        }

        if (array[i] != e) {

            ERROR();
        }
    }

    for (i=0; i<QUANT; i++) {
        if ( listRemove(l, &array[i]) == NOT_FOUND ) {
            ERROR();
        }

        if (listSize(l) + i + 1 != QUANT) {
            ERROR();
        }
    }

    listFree(l);
    END();
}

void testAddGetRemoveAtPositionClear(void) {
    BEGIN("testAddGetRemoveAtPositionClear");
    int array[QUANT];
    int i;
    int element;

    LIST l = listCreate(QUANT, sizeof(int));
    if (l == NULL) {
        ERROR();
    }

    for (i=0; i<QUANT; i++) {
        if ( listAdd(l, &array[i]) == LIST_IS_FULL) {
            ERROR();
        }
    }
    if (listAdd(l, &array[0]) != LIST_IS_FULL) {
        ERROR();
    }

    LIST l2 = listCreate(QUANT, sizeof(int));
    if (l2 == NULL) {
        ERROR();
    }

    while (listSize(l) > 0) {
        int pos = rand() % listSize(l);

        if ( listGet(l, &element, pos) == INVALID_POSITION ) {
            ERROR();
        }

        if ( listRemoveAtPosition(l, pos) == INVALID_POSITION) {
            ERROR();
        }

        if (listAdd(l2, &element) == LIST_IS_FULL) {
            ERROR();
        }
    }

    listClear(l2);
    if (listSize(l2) != 0) {
        ERROR();
    }

    listClear(l);
    if (listSize(l) != 0) {
        ERROR();
    }

    listFree(l);
    listFree(l2);
    END();
}

void advancedTest1(void) {
    BEGIN("advancedTest1");
    int array[QUANT];
    int i;
    int element;

    LIST l = listCreate(QUANT, sizeof(int));
    if (l == NULL) {
        ERROR();
    }

    LIST l2 = listCreate(QUANT, sizeof(int));
    if (l2 == NULL) {
        ERROR();
    }

    for (i=0; i<QUANT; i++) {
        do {
            element = rand() % (QUANT * 100);
        } while( listGetPosition(l, &element) != NOT_FOUND);

        if ( listAdd(l, &element) == LIST_IS_EMPTY ) {
            ERROR();
        }

        array[i] = element;

        int e2 = -1 * i;
        if (listAdd(l2, &e2) == LIST_IS_EMPTY) {
            ERROR();
        }
    }

    int i2;
    for (i=0; i<QUANT; i++) {
        for(i2=0; i2<QUANT; i2++) {
            if (i != i2 && array[i] == array[i2]) {
                ERROR();
            }
        }
    }

    listFree(l);
    listFree(l2);
    END();
}

void advancedTest2(void) {
    BEGIN("advancedTest2");
    int array2[QUANT];
    int i;

    LIST l = listCreate(QUANT, sizeof(int));
    if (l == NULL) {
        ERROR();
    }

    LIST l2 = listCreate(QUANT, sizeof(int));
    if (l2 == NULL) {
        ERROR();
    }

    int array[QUANT];

    for (i=0; i<QUANT; i++) {
        int element;
        do {
            element = rand() % (QUANT * 100);
        } while( listGetPosition(l, &element) != NOT_FOUND);

        if ( listAdd(l, &element) == LIST_IS_EMPTY ) {
            ERROR();
        }
        array[i] = element;

        int e2 = -i;
        array2[i] = e2;
        if (listAdd(l2, &e2) == LIST_IS_EMPTY) {
            ERROR();
        }
    }

    for (i=0; i<QUANT; i++) {
        int pos = rand() % listSize(l);
        int element;
        if (listGet(l, &element, pos) == INVALID_POSITION) {
            ERROR();
        }

        if ( listRemoveAtPosition(l, pos) == INVALID_POSITION) {
            ERROR();
        }

        if (listRemoveAtPosition(l2, i) == INVALID_POSITION) {
            ERROR();
        }

        if (listAddAtPosition(l2, &element, i) == INVALID_POSITION) {
            ERROR();
        }

        array2[i] = element;

        int i2;
        for (i2=0; i2<QUANT; i2++) {
            if (listGet(l2, &element, i2) == INVALID_POSITION) {
                ERROR();
            }

            if (element != array2[i2] && element != -i2) {
                ERROR();
            }
        }
    }

    for (i=0; i<QUANT; i++) {
        if (listAdd(l, &array[i]) == LIST_IS_FULL) {
            ERROR();
        }
    }

    LIST l3 = listCreate(QUANT, sizeof(int));
    if (l3 == NULL) {
        ERROR();
    }

    for(i=0; i<QUANT; i++) {

        int element;
        if (listGet(l2, &element, i) == INVALID_POSITION) {
            ERROR();
        }

        int pos = listGetPosition(l, &element);
        if (pos == NOT_FOUND) {
            ERROR();
        }

        if (listGetPosition(l3, &pos) != NOT_FOUND) {
            ERROR();
        }

        if (listAdd(l3, &pos) == LIST_IS_FULL) {
            ERROR();
        }
    }

    for (i=0; i<QUANT; i++) {
        int element;
        if (listGet(l2, &element, i) == INVALID_POSITION) {
            ERROR();
        }

        if (element != array2[i]) {
            ERROR();
        }
    }

    listFree(l);
    listFree(l2);
    listFree(l3);
    END();
}
