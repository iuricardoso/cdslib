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
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

/**
 * @page example_stack Exemplo de uso de Pilha
 * <pre><code>
 #define CAPACITY 5

 //// create a stack of int elements.
 STACK s = stackCreate(CAPACITY, sizeof(int));
 int e;

 //// pushing 10 in the stck.
 e = 10;
 if (! stackPush(s, &e)) {
    //// error: stack is full.
 }

 //// now, pushing 20 and 30 in the stack.
 e = 20;
 stackPush(s, &e);
 e = 30;
 stackPush(s, &e);

 //// here, the stack has 30, 20, 10. The element 30 is on the top.
 //// print the size: 3.
 printf("Stack size: %d\n", stackSize(s));

 //// print: 30 20 10
 while (stackPop(s, &e)) {
    printf("%d ", e);
 }

 //// don't forget this, to avoid memory leak.
 stackFree(q);
 </code></pre>
 */

/** Tipo de dado que define um pilha est&aacute;tica alocada conforme o tamanho
 * definido em sua cria&ccedil;&atilde;o.
 */
typedef void * STACK;

/** Aloca uma pilha est&aacute;tica com capacidade definida por par&acirc;metro, que armazena
 * elementos com tamanho tamb&eacute;m definido em par&acirc;metro.
 *
 * A pilha alocada necessita ser liberada por meio da fun&ccedil;&atilde;o <code>stackFree</code>.
 *
 * @param capacity A capacidade m&aacute;xima de armazenaento da da pilha.
 * @param elementSize O tamanho dos elementos a serem armazenados.
 * @return A pilha est&aacute;tica alocada dinamicamente.
 *
 */
STACK stackCreate(size_t capacity, size_t elementSize);


/** Libera a mem&oacute;ria alocada para uma pilha.
 *
 * @param s Uma pilha alocada dinacamente.
 */
void stackFree(STACK s);

/** Limpa uma pilha, desempilhando todos os elementos, deixando-a vazia.
 *
 * Ap&oacute;s limpar uma pilha, o tamanho da pilha (recuperado por meio da fun&ccedil;&atilde;o
 * <code>stackSize</code>) &eacute; zero.
 *
 * @param s A pilha a ser limpa.
 */
void stackClear(STACK s);

/** Empilha um elemento no topo de uma pilha.
 *
 * A fun&ccedil;&atilde;o copia o elemento para dentro da pilha, retornando um valor l&oacute;gico
 * indicando se conseguiu empilhar ou n&atilde;o. N&atilde;o ser&aacute; poss&iacute;vel realizar a opera&ccedil;&atilde;o
 * caso a pilha j&aacute; esteja cheia.
 *
 * @param s A pilha a ter o elemento empilhado.
 * @param element O ponteiro para o elemento a ser empilhado.
 * @return O valor l&oacute;gico verdadeiro (1) caso tenha conseguido empilhar; ou o
 * valor falso (zero) em caso contr&aacute;rio.
 */
int stackPush(STACK s, void * element);

/** Desempilha o elemento do topo de uma pilha.
 *
 * A fun&ccedil;&atilde;o copia o elemento de dentro da pilha para a vari&aacute;vel, retornando um valor
 * l&oacute;gico indicando se conseguiu desempilhar ou n&atilde;o. N&atilde;o ser&aacute; poss&iacute;vel realizar
 * a opera&ccedil;&atilde;o caso a pilha j&aacute; esteja vazia. Neste caso, a vari&aacute;vel apontada pelo
 * o ponteiro passado como par&acirc;metro para receber o elemento desempilhado n&atilde;o
 * sofrer&aacute; altera&ccedil;&atilde;o.
 *
 * @param s A pilha que ter&aacute; o elemento do topo desempilhado.
 * @param element O ponteiro para a vari&aacute;vel que receber&aacute; uma c&oacute;pia do elemento
 * desempilhado.
 * @return O valor l&oacute;gico verdadeiro (1) caso tenha conseguido desempilhar; ou o
 * valor falso (zero) em caso contr&aacute;rio.
 *
 */
int stackPop(STACK s, void * element);

/** Recupera o elemento do topo da pilha, sem desempilh&aacute;-lo.
 *
 * Uma c&oacute;pia do elemento &eacute; feita na vari&aacute;vel apontada pelo ponteiro passado como
 * par&acirc;metro. Esta opera&ccedil;&atilde;o somente &eacute; realizada se a pilha n&atilde;o estiver vazia.
 * Caso contr&aacute;rio, a vari&aacute;vel passada como refer&ecirc;ncia n&atilde;o sofre altera&ccedil;&atilde;o alguma.
 * O retorno da fun&ccedil;&atilde;o indica se a opera&ccedil;&atilde;o foi bem sucedida ou n&atilde;o.
 *
 * @param s A pilha a ter o topo recuperado.
 * @param element O ponteiro da vari&aacute;vel que receber&aacute; uma c&oacute;pia do elemento do
 * topo da pilha.
 * @return O valor l&oacute;gico verdadeiro (1) caso tenha recuperado o valor; ou o
 * valor l&oacute;gico falso (zero) em caso contr&aacute;rio (pilha vazia).
 */
int stackPeekTop(STACK s, void * element);

/** Recupera o tamanho da pilha (a quantidade de elementos armazenados).
 *
 * O tamanho da pilha &eacute; um valor inteiro n, em que 0 <= n <= c, sendo que c &eacute; a
 * capacidade total da pilha; indica a quantidade m&aacute;xima de elementos que podem
 * ser armazenados na pilha.
 *
 * @param s A pilha a ter seu tamanho recuperado.
 * @return int
 *
 */
int stackSize(STACK s);

/** Recupera a capacidade m&aacute;xima da pilha (a quantidade de elementos que a pilha
 * pode comportar).
 *
 * O capacidade da pilha &eacute; um valor inteiro c, em que c >= 0; indica a quantidade
 * m&aacute;xima de elementos que podem ser armazenados na pilha.
 *
 * @param s A pilha a ter sua capacidade recuperada.
 * @return A capacidade da pilha.
 */
int stackCapacity(STACK s);

#endif // STACK_H_INCLUDED
