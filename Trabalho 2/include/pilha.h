/*2º Trabalho de Métodos de Programação
Professor: Jan Correa
Aluno: Marcos Paulo Cayres Rosa
Matrícula: 14/0027131
- 'Include file', presente na pasta lib junto com 'parentizacao.h'
*/

#ifndef PILHA_H
#define PILHA_H

/*Estrutura de uma lista, incluindo ponteiro para o próximo elemento e uma variável de inteiro*/
typedef struct lista{
	char elem;
	struct lista *prox;
} Lista;

/*Estrutura de uma pilha, incluindo um ponteiro de Lista para indicar o início da pilha*/
typedef struct pilha{
	Lista *topo;
} Pilha;

/*Aloca espaço para uma nova pilha*/
Pilha* cria_pilha();

/*Confere se uma pilha está vazia*/
int pilha_vazia(Pilha *p);

/***************************************************************************
* Função: fazer Push na pilha (adição de elemento)
* Descrição
*	Acrescente um elemento do tipo inteiro no início de uma lista e 
* aponta a estrutura de topo da pilha para este, além do fazer o último
* elemento da pilha apontar para NULL.
* Parâmetros
* 	n - número inteiro que será incluído na pilha
* 	p - ponteiro para a pilha que receberá o inteiro n
* Valor retornado
* 	Nenhum
* Assertiva de entrada
* 	p != NULL
* Estrutura implícita:
* 	Não é usada variáveis globais, arquivos externos ou condições de 
* retorno, porém a Pilha é retornada por passagem por referência
* Estrutura Explícita:
* 	Recebe como parâmetro uma pilha p e um valor inteiro n para ser
* acrescentado nela
* Requesitos:
* 	- Deve ser capaz de criar um novo elemento da lista pela função 
* malloc
* 	- Caso não haja espaço na memória, cessar o procedimento
* Hipótese:
* 	- O valor fornecido pelo usuário será um número inteiro
* 	- O ponteiro de pilha fornecido está indicando o topo da lista
***************************************************************************/
void push(Pilha *p, char c);

/***************************************************************************
* Função: fazer Pop na pilha (retirada do elemento do topo)
* Descrição
*	Retira o elemento do tipo inteiro do topo de um lista, a qual é 
* indicada por um ponteiro da estrutura pilha. Ademais, confere se a 
* pilha está vazia, para saber se continua com o procedimento e faz com
* que os demais elementos continuem na mesma ordem.
* Parâmetros
* 	p - ponteiro para a pilha da qual será retirado o elemento do topo
* Valor retornado
* 	Nenhum
* Assertiva de entrada
* 	p->topo != NULL
* Estrutura implícita:
* 	Não é usada variáveis globais, arquivos externos ou condições de 
* retorno, porém a Pilha é retornada por passagem por referência
* Estrutura Explícita:
* 	Recebe como parâmetro uma pilha p
* acrescentado nela
* Requesitos:
* 	- Deve ser capaz de retirar o elemento do topo da pilha
* 	- Caso não haja elementos na pilha, cessar o procedimento
* Hipótese:
* 	- O ponteiro de pilha fornecido está indicando o topo da lista
***************************************************************************/
void pop(Pilha *p);

/***************************************************************************
* Função: fazer Top na pilha (indica o elemento do topo)
* Descrição
*	Retorna o elemento do tipo inteiro do topo de um lista, a qual é 
* indicada por um ponteiro da estrutura pilha. Ademais, confere se a 
* pilha está vazia, indicando isso na valor retornado (em caso positivo) 
* e não modifica a posição ou existência dos elementos.
* Parâmetros
* 	p - ponteiro para a pilha da qual será informado o elemento do topo
* Valor retornado
* 	o número inteiro encontrado no topo da pilha
* Assertiva de entrada
* 	p->topo != NULL
* Estrutura implícita:
* 	Não é usada variáveis globais, arquivos externos ou condições de 
* retorno, porém a Pilha é retornada por passagem por referência
* Estrutura Explícita:
* 	Recebe como parâmetro uma pilha p e retorna um número inteiro
* acrescentado nela
* Requesitos:
* 	- Deve ser capaz de indicar o elemento do topo da pilha
* 	- Caso não haja elementos na pilha, indicar que a pilha está vazia
* Hipótese:
* 	- Os valores fornecidos pelo usuário eram números inteiros
* 	- O ponteiro de pilha fornecido está indicando o topo da lista
***************************************************************************/
char top(Pilha *p);

/*Libera todos os elementos de uma lista*/
void libera_lista(Lista *l);

/*Libera todos os elementos de uma pilha*/
void libera_pilha(Pilha *p);

#endif
