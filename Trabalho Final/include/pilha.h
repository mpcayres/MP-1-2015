/*Trabalho Final de Métodos de Programação
Professor: Jan Correa
Alunos: Marcos Paulo Cayres Rosa - 14/0027131
	Ingrid Santana Lopes - 14/0083065
	Felipe Lira Fernandes dos Santos - 14/0019821
- Arquivo de cabeçalho, presente na pasta lib junto com 'calculadora.h'
*/
/** @file */

#ifndef PILHA_H
#define PILHA_H

/*********************************************************************//**
* @brief Estrutura de uma lista, incluindo ponteiro para o próximo elemento e uma variável de float \n
* @remark Assertivas Estruturais:
*   - l->prox != NULL => l != NULL
*************************************************************************/
typedef struct lista{
	float elem;
	struct lista *prox;
} Lista;

/*********************************************************************//**
* @brief Estrutura de uma pilha, incluindo um ponteiro de Lista para indicar o topo da pilha \n
* @remark Assertivas Estruturais:
*   - P != NULL => p->topo == l || p->topo == NULL
************************************************************************/
typedef struct pilha{
	Lista *topo;
} Pilha;

/*********************************************************************//**
* @brief Criar uma pilha; \n
* Aloca um espaço para pilha e faz o elemento  'topo' apontar para
* NULL, este que será o início da lista a ser utilizada. 
* @param Nenhum
* @return A pilha alocada
* @remark Estrutura implícita:
* 	- Não é usada variáveis globais, arquivos externos ou condições de 
* retorno
* @remark Estrutura Explícita:
* 	- Não recebe parâmetro, mas retorna uma pilha
* @remark Requesitos:
* 	- Deve ser capaz de alocar espaço para uma pilha
* 	- Caso não haja espaço na memória, cessar o procedimento\n
* @remark Hipótese:
* 	- O usuário irá usar uma vez a função antes de qualquer operação
* com a pilha
***************************************************************************/
Pilha* cria_pilha();

/***********************************************************************//**
* @brief Verificar se a pilha está vazia; \n
* Analisa se a pilha está vazia e retorna a resposta correspondente;
* @param p - ponteiro para a pilha que será verificada
* @return Inteiro que corresponderá a informação da pilha estar ou não vazia \n
* @remark Estrutura implícita:
* 	- Não é usada variáveis globais, arquivos externos ou condições de 
* retorno
* @remark Estrutura Explícita:
* 	- Recebe uma pilha p como parâmetro e retorna um inteiro 
* @remark Requesitos:
* 	- Deve ser capaz de informar se a pilha está vazia 
* @remark Hipótese:
* 	- O usuário irá passar como parâmetro uma pilha alocada
***************************************************************************/
int pilha_vazia(Pilha *p);

/***********************************************************************//**
* @brief Fazer Push na pilha (adição de elemento) \n
* Acrescente um elemento do tipo float no início de uma lista e 
* aponta a estrutura de topo da pilha para este, além do fazer o último
* elemento da pilha apontar para NULL.
* @param c - número que será incluído na pilha
* @param p - ponteiro para a pilha que receberá o inteiro n
* @return Nenhum
* @remark Assertiva de entrada:
* 	- p != NULL
* @remark Estrutura implícita:
* 	- Não é usada variáveis globais, arquivos externos ou condições de 
* retorno, porém a Pilha é retornada por passagem por referência
* @remark Estrutura Explícita:
* 	- Recebe como parâmetro uma pilha p e um valor inteiro n para ser
* acrescentado nela
* @remark Requesitos:
* 	- Deve ser capaz de criar um novo elemento da lista pela função 
* malloc
* 	- Caso não haja espaço na memória, cessar o procedimento
* @remark Hipótese:
* 	- O valor fornecido pelo usuário será um número real
* 	- O ponteiro de pilha fornecido está indicando o topo da lista
***************************************************************************/
void push(Pilha *p, float c);

/***********************************************************************//**
* @brief Fazer Pop na pilha (retirada do elemento do topo); \n
* Retira o elemento do tipo float do topo de um lista, a qual é 
* indicada por um ponteiro da estrutura pilha. Ademais, confere se a 
* pilha está vazia, para saber se continua com o procedimento e faz com
* que os demais elementos continuem na mesma ordem \n
* @param p - ponteiro para a pilha da qual será retirado o elemento do topo
* @return Nenhum
* @remark Assertiva de entrada:
* 	- p->topo != NULL
* @remark Estrutura implícita:
* 	- Não é usada variáveis globais, arquivos externos ou condições de 
* retorno, porém a Pilha é retornada por passagem por referência
* @remark Estrutura Explícita:
* 	- Recebe como parâmetro uma pilha p acrescentado nela
* @remark Requesitos:
* 	- Deve ser capaz de retirar o elemento do topo da pilha
* 	- Caso não haja elementos na pilha, cessar o procedimento
* @remark Hipótese:
* 	- O ponteiro de pilha fornecido está indicando o topo da lista
***************************************************************************/
void pop(Pilha *p);

/***********************************************************************//**
* @brief Fazer Top na pilha (indica o elemento do topo) \n
* Retorna o elemento do tipo float do topo de um lista, a qual é 
* indicada por um ponteiro da estrutura pilha. Ademais, confere se a 
* pilha está vazia, indicando isso na valor retornado (em caso positivo) 
* e não modifica a posição ou existência dos elementos.
* @param p - ponteiro para a pilha da qual será informado o elemento do topo
* @return o número inteiro encontrado no topo da pilha
* @remark Assertiva de entrada:
* 	- p->topo != NULL
* @remark Estrutura implícita:
* 	- Não é usada variáveis globais, arquivos externos ou condições de 
* retorno, porém a Pilha é retornada por passagem por referência
* @remark Estrutura Explícita:
* 	- Recebe como parâmetro uma pilha p e retorna um número inteiro
* @remark Requesitos:
* 	- Deve ser capaz de indicar o elemento do topo da pilha
* 	- Caso não haja elementos na pilha, indicar que a pilha está vazia
* @remark Hipótese:
* 	- Os valores fornecidos pelo usuário eram números reais
* 	- O ponteiro de pilha fornecido está indicando o topo da lista
***************************************************************************/
float top(Pilha *p);

/***********************************************************************//**
* @brief Liberar uma lista da memória \n
* Auxilia a função 'libera_pilha' a liberar da memória o espaço
* correspondente a pilha fornecida
* @param l - ponteiro para a lista recebida
* @return Nenhum
* @remark Assertiva de entrada:
* 	- l != NULL
* @remark Estrutura implícita:
* 	- Não é usada variáveis globais, arquivos externos ou condições de 
* retorno, porém é utilizada uma lista temporária para auxiliar
* @remark Estrutura Explícita:
* 	- Recebe como parâmetro uma lista l
* @remark Requesitos:
* 	- Deve ser capaz de liberar uma lista da memória
* 	- Caso não haja elementos na lista, parar o procedimento
* @remark Hipótese:
* 	- O ponteiro de lista fornecido está indicando o início da lista
***************************************************************************/
void libera_lista(Lista *l);

/***********************************************************************//**
* @brief Liberar uma pilha da memória \n
* Libera da memória o espaço correspondente a pilha fornecida
* @param p - ponteiro para a pilha recebida
* @return Nenhum
* @remark Assertiva de entrada:
* 	- p != NULL
* @remark Estrutura implícita:
* 	- Não é usada variáveis globais, arquivos externos ou condições de 
* retorno, porém é utilizada a função 'libera_lista' para auxiliar
* @remark Estrutura Explícita:
* 	- Recebe como parâmetro uma pilha p
* @remark Requesitos:
* 	- Deve ser capaz de liberar uma pilha da memória
* 	- Caso não haja elementos na pilha, parar o procedimento
* @remark Hipótese:
* 	- O ponteiro de pilha fornecido está indicando o topo da lista
***************************************************************************/
void libera_pilha(Pilha *p);

#endif
