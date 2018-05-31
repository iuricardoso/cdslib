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

#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

/** @mainpage P&aacute;gina Principal
 *
 * @section intro_sec Introdu&ccedil;&atilde;o
 *
 * A ANSI C Data Structutres Library possui um conjunto de defini&ccedil;&otilde;es e fun&ccedil;&otilde;es
 * de listas, pilhas e filas para uso destas estruturas de dados.
 *
 * At&eacute; o presente momento, todas as estruturas existentes na biblioteca s&atilde;o estrutras
 * est&aacute;ticas, isto &eacute;, trabalham sobre vetores, sem n&oacute;s ligados. Entretanto, estes
 * vetores s&atilde;o alocados dinamicamente, o que permite que sejam alocados com tamanhos
 * definidos na chamada das fun&ccedil;&otilde;es de aloca&ccedil;&atilde;o.
 *
 * Estas estruturas de dados tamb&eacute;m permitem armazenar qualquer tipo de dado,
 * uma vez que trabalham com aloca&ccedil;&atilde;o din&acirc;mica do vetor. Assim, estas estruturas
 * s&atilde;o gen&eacute;ricas e podem armazenar qualquer tipo de dado, desde os tipos nativos
 * da Linguagem C, at&eacute; os criados por meio de <code>struct</code>s, entre outros.
 *
 * @section summary_sec Sum&aacute;rio
 * <ol>
 *  <li><a href="./list_8h.html" target="_self">List - Lista est&aacute;tica com tamanho din&acirc;mico;</a></li>
 *  <li><a href="./queue_8h.html" target="_self">Queue - Fila est&aacute;tica com tamanho din&acirc;mico;</a></li>
 *  <li><a href="./stack_8h.html" target="_self">Stack - Pilha est&aacute;tica com tamanho din&acirc;mico.</a></li>
 * </ol>
 *
 * @section install_sec Instala&ccedil;&atilde;o
 * Para instalar a biblioteca, copie os arquivos dela (.c e .h) para a pasta do
 * projeto, incluindo-os na compila&ccedil;&atilde;o.
 */

/**
 * @page example_queue Exemplo de uso de Fila.
 * <pre><code>
 * #define CAPACITY 5
 *
 * //// create the queue.
 * QUEUE q = queueCreate(CAPACITY, sizeof(int));
 * int e;
 *
 * //// adding 10 in the queue.
 * e = 10;
 *
 * if (! queueAdd(q, &e)) {
 *      //// error: queue is full.
 * }
 *
 * //// now, adding 20 and 30 in the queue.
 * e = 20;
 * queueAdd(q, &e);
 * e = 30;
 * queueAdd(q, &e);
 *
 * //// here, the queue has 10, 20, 30.
 * //// print the size: 3.
 * printf("Queue size: %d\n", queueSize(q));
 *
 * //// print: 10 20 30
 * while (queueRemove(q, &e)) {
 *    printf("%d ", e);
 * }
 *
 * //// don't forget this, to avoid memory leak.
 * queueFree(q);
 * </code></pre>
 */

/**
 * O tipo de dado para armazenar uma fila de dados de tipo gen&eacute;rico.
 */
typedef void * QUEUE;


/**
 * Aloca espa&ccedil;o para uma nova fila est&aacute;tica circular, com defini&ccedil;&atilde;o de capacidade de
 * elementos e tamanho dos elementos, retornando ela.
 *
 * @param capacity A quantidade m&aacute;xima de elementos que podem ser armazenados na fila.
 * @param elementSize O tamanho (em bytes) dos elementos a serem armazenados.
 * @return Uma fila vazia, ou o ponteiro NULL caso n&atilde;o tenha conseguido alocar
 * mem&oacute;ria para a nova fila.
 */
QUEUE queueCreate(size_t capacity, size_t elementSize);

/** Libera a mem&oacute;ria din&acirc;mica alocada para uma fila.
 *
 * @param q A fila a ser liberada da mem&oacute;ria.
 *
 */
void queueFree(QUEUE q);

/** Limpa uma fila, excluindo todos os elementos dela, deixando-a vazia.
 *
 * @param q A fila a ser limpa.
 */
void queueClear(QUEUE q);

/** Adiciona um elemento novo no fim da fila, retornando um valor l&oacute;gico que indica
 * se foi poss&iacute;vel adicionar ou n&atilde;o.
 *
 * Deve-se passar um ponteiro para o elemento
 * a ser adicionado, sendo que este elemento deve ter o tamanho passado na
 * fun&ccedil;&atilde;o <code>queueCreate</code>. Este elemento ser&aacute; copiado para dentro da
 * fila, n&atilde;o sendo referenciado por esta.
 *
 * Deve haver espa&ccedil;o na fila para que seja poss&iacute;vel adicionar o elemento. Caso
 * exista, retorna o valor l&oacute;gico verdadeiro (1). Caso
 * n&atilde;o exista, esta fun&ccedil;&atilde;o retorna o valor l&oacute;gico falso (zero). A capacidade de
 * armazenamento da fila &eacute; definida na sua cria&ccedil;&atilde;o, pela chamda da fun&ccedil;&atilde;o
 * <code>queueCreate</code>.
 *
 * @param q A fila a ter o elemento adicionado.
 * @param element O ponteiro para o elemento a ser adicionado.
 * @return O valor 1 caso tenha conseguido adicionar; 0 (zero) em caso contr&aacute;rio.
 *
 */
int queueAdd(QUEUE q, const void * element);

/** Remove o elemento do in&iacute;cio da fila, carregando-o para o argumento <code>element</code>,
 * retornando um valor l&oacute;gico indicando se foi poss&iacute;vel ou n&atilde;o a remo&ccedil;&atilde;o.
 *
 * Caso a fila tenha elementos, a remo&ccedil;&atilde;o &eacute; bem sucedida, retornando o valor
 * l&oacute;gico verdadeiro (1); caso a fila esteja vazia, a remo&ccedil;&atilde;o n&atilde;o ocorre,
 * retornando o valor l&oacute;gico falso (zero).
 *
 * @param q A fila a ter o elemento removido.
 * @param element O ponteiro para a vari&aacute;vel que ir&aacute; receber o elemento removido.
 * Caso nenhum elemento seja removido, a vari&aacute;vel apontada pelo ponteiro permanece
 * com o mesmo valor existente antes da execu&ccedil;&atilde;o da fun&ccedil;&atilde;o.
 * @return O valor l&oacute;gico verdadeiro (1) caso tenha conseguido remover um elemento;
 * ou o valor l&oacute;gico falso caso a fila esteja vazia antes da chamada desta fun&ccedil;&atilde;o.
 */
int queueRemove(QUEUE q, void * element);

/** Carrega o elemento do in&iacute;cio da fila no argumento <code>element</code>,
 * retornando um valor l&oacute;gico indicando se foi poss&iacute;vel ou n&atilde;o carregar o elemento.
 *
 * Caso a fila tenha elementos, a carga &eacute; bem sucedida, retornando o valor
 * l&oacute;gico verdadeiro (1); caso a fila esteja vazia, a carga n&atilde;o ocorre,
 * retornando o valor l&oacute;gico falso (zero).
 *
 * @param q A fila a ter o elemento carregado.
 * @param element O ponteiro para a vari&aacute;vel que ir&aacute; receber o elemento.
 * Caso nenhum elemento seja carregado, a vari&aacute;vel apontada pelo ponteiro permanece
 * com o mesmo valor existente antes da execu&ccedil;&atilde;o da fun&ccedil;&atilde;o.
 * @return O valor l&oacute;gico verdadeiro (1) caso tenha conseguido carregar um elemento;
 * ou o valor l&oacute;gico falso caso a fila esteja vazia antes da chamada desta fun&ccedil;&atilde;o.
 */
int queuePeek(const QUEUE q, void * element);

/** Retorna o tamanho atual da fila.
 *
 * O tamanho atual da fila &eacute; um valor inteiro n, em que 0 <= n <= c, sendo que c
 * &eacute; a capacidade m&aacute;xima de elementos que cabem dentro da fila.
 * @param q A lista que deseja-se saber o tamanho.
 * @return A quantidade de elementos existentes na fila.
 *
 */
int queueSize(const QUEUE q);

/** Retorna o limite m&aacute;ximo (a capacidade) de elementos que a fila pode comportar.
 *
 * O limite da fila &eacute; um valor inteiro maior ou igual a zero.
 * @param q A lista que deseja-se saber o limite m&aacute;ximo de elementos.
 * @return O limite m&aacute;ximo de elementos que cabem na fila.
 *
 */
int queueCapacity(const QUEUE q);

#endif // QUEUE_H_INCLUDED
