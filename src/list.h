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

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/**
 * @page example_list Exemplo de uso de Lista
 * Exemplo de uso:<pre><code>
 #define CAPACITY 5

 //// create a list of int elements, limited to 5 elements.
 LIST l = listCreate(CAPACITY, sizeof(int));
 int e;

 //// adding 20 at the end of the list.
 e = 10;
 if (listAdd(l, &e) == LIST_IS_FULL) {
    //// error: list is full.
 }

 //// now, adding 10 at first position (position zero).
 e = 20;
 listAddAtPosition(l, &e, 0);

 //// finally, adding 30 at the end of the list.
 e = 30;
 listAdd(l, &e);

 //// here, the list has 10, 20, 30.
 //// print the size: 3.
 printf("List size: %d\n", listSize(l));

 //// remove the second element (20).
 if (listRemoveAtPosition(l, &e, 1) == INVALID_POSITION) {
    //// error: try to access a invalid position.
 }
 printf("%d", e); // print: 20

 //// print: 10 30
 while (listRemoveAtPosition(l, &e, 0) > 0) {
    printf("%d ", e);
 }

 //// don't forget this, to avoid memory leak.
 listFree(l);
 </code></pre>
 */

/**
 * O tipo de dado para armazenar uma lista de dados de tipo gen&eacute;rico.
 */
typedef void * LIST;

/**
 * Constante retornada pelas fun&ccedil;&otilde;es de adi&ccedil;&atilde;o de elementos para indicar que a
 * lista est&aacute; cheia.
 */
#define LIST_IS_FULL        -1
/**
 * Constante retornada pelas fun&ccedil;&otilde;es de remo&ccedil;&atilde;o de elementos para indicar que a
 * lista est&aacute; vazia.
 */
#define LIST_IS_EMPTY       -2

/**
 * Constante retornada pelas fun&ccedil;&otilde;es de consulta e remo&ccedil;&atilde;o de elementos para
 * indicar que a posi&ccedil;&atilde;o indicada &eacute; inv&aacute;lida.
 */
#define INVALID_POSITION    -3

/**
 * Constante retornada pelas fun&ccedil;&otilde;es que procuram um elemento dentro da lista,
 * para indicar que o elemento n&atilde;o foi encontrado.
 */
#define NOT_FOUND           -4

/**
 * Cria uma lista com um determinado limite, de elementos de um tamanho.
 * @param limit O limite de elementos a serem armazenados.
 * @param elementSize O tamanho (em bytes) dos elementos a serem armazenados.
 * @return A lista criada, ou o ponteiro NULL caso n&atilde;o tenha conseguido alocar
 * a mem&oacute;ria para lista.
 */
LIST listCreate(size_t limit, size_t elementSize);

/**
 * Libera a mem&oacute;ria ocupada pela lista.
 * @param l A lista a ter o espa&ccedil;o de mem&oacute;ria liberado.
 */
void listFree(LIST l);

/**
 * Adiciona um elemento numa lista.
 * @param l A lista a ter o elemento adicionado.
 * @param element O ponteiro para o elemento a ser copiado para dentro da lista.
 * O elemento &eacute; adicionado no final da lista.
 * @return O tamanho atual da lista ou LIST_IS_FULL caso a lista j&aacute; esteja cheia,
 * indicando que n&atilde;o foi poss&iacute;vel adicionar o elemento.
 */
int listAdd(LIST l, const void * element);

/**
 * Adiciona um elemento numa posi&ccedil;&atilde;o espec&iacute;fica de uma lista. *
 * @param l A lista a ter o elemento adicionado.
 * @param element O ponteiro para o elemento a ser copiado para dentro da lista.
 * O elemento &eacute; adicionado no final da lista.
 * @param position A posi&ccedil;&atilde;o da lista ter o elemento adicionado.
 * @return O tamanho atual da lista, ou um c&oacute;digo de erro: LIST_IS_FULL ou
 * INVALID_POSITION. O primeiro &eacute; retornado caso a lista j&aacute; esteja cheia.
 * o segundo, caso a posi&ccedil;&atilde;o seja &iacute;nvalida. Ambos os erros indicam que n&atilde;o foi
 * poss&iacute;vel adicionar o elemento.
 */
int listAddAtPosition(LIST l, const void * element, int position);

/**
 * Remove um elemento de uma lista. O elemento passado como argumento &eacute;
 * procurado na lista, e se encontrado pelo menos uma vez, sua primeira
 * ocorr&ecirc;ncia &eacute; removida da lista.
 * @param l A lista a ter o elemento removido.
 * @param element O ponteiro do elemento a ter sua primeira ocorr&ecirc;ncia removida.
 * @return O tamanho da lista ap&oacute;s a remo&ccedil;&atilde;o (um n&uacute;mero maior ou igual a zero),
 * ou a constante NOT_FOUND indicando que element n&atilde;o foi encontrado.
 */
int listRemove(LIST l, const void * element);

/**
 * Remove um elemento de uma posi&ccedil;&atilde;o espec&iacute;fica da lista.
 * @param l A lista a ter o elemento removido.
 * @param position A posi&ccedil;&atilde;o a ter o elemento removido da lista.
 * @return O tamanho da lista ap&oacute;s a remo&ccedil;&atilde;o (um n&uacute;mero maior ou igual a zero),
 * ou a constante INVALID_POSITION indicando que position &eacute; inv&aacute;lida.
 */
int listRemoveAtPosition(LIST l, int position);

/**
 * Recupera a posi&ccedil;&atilde;o da primeira ocorr&ecirc;ncia de um elemento em uma lista.
 * @param l A lista a ter o elemento procurado.
 * @param element O ponteiro do elemento a ser procurado na lista.
 * @return A posi&ccedil;&atilde;o da primeira ocorr&ecirc;ncia encontrada, ou ent&atilde;o a contante
 * NOT_FOUND caso o elemento n&atilde;o seja encontrado na lista.
 */
int listGetPosition(const LIST l, const void * element);

/**
 * Atribui um novo elemento para uma determinada posi&ccedil;&atilde;o de uma lista. A posi&ccedil;&atilde;o
 * j&aacute; deve ter um elemento previamente armazenado.
 * @param l A lista a ter seu elemento alterado.
 * @param element O ponteiro para o elemento a ser atribuido na posi&ccedil;&atilde;o especificada.
 * @param position A posi&ccedil;&atilde;o da lista a ter seu elemento modificado.
 * @return Zero caso a opera&ccedil;&atilde;o tenha executado com sucesso; a constante
 * INVALID_POSITION caso a posi&ccedil;&atilde;o especificada seja &iacute;nvalida.
 */
int listSet(LIST l, const void * element, int position);

/**
 * Recupera um elemento de uma posi&ccedil;&atilde;o espec&iacute;fica de uma lista.
 * @param l A lista a ter seu elemento alterado.
 * @param element O ponteiro para uma vari&aacute;vel que ir&aacute; receber o elemento recuperado.
 * @param position A posi&ccedil;&atilde;o da lista a ter seu elemento recuperado.
 * @return Zero caso a opera&ccedil;&atilde;o tenha executado com sucesso; a constante
 * INVALID_POSITION caso a posi&ccedil;&atilde;o especificada seja &iacute;nvalida.
 */
int listGet(LIST l, void * element, int position);

/**
 * Limpa uma lista, removendo todos os elementos.
 * @param l A lista a ser limpa.
 */
void listClear(LIST l);

/**
 * Recupera o tamanho de uma lista.
 * @param l A lista a ter seu tamanho recuperado.
 * @return O tamanho da lista (zero ou um valor positivo).
 */
int listSize(const LIST l);

/**
 * Recupera o limite de uma lista.
 * @param l A lista a ter seu tamanho recuperado.
 * @return O limite da lista (zero ou um valor positivo).
 */
size_t listLimit(const LIST l);

#endif // LIST_H_INCLUDED
