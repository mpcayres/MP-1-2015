/*1º Trabalho de Métodos de Programação
Professor: Jan Correa
Aluno: Marcos Paulo Cayres Rosa
Matrícula: 14/0027131
- 'Include file', presente na pasta lib
*/

/*Estrutura de uma lista, incluindo ponteiro para o próximo elemento e uma variável de inteiro*/
typedef struct lista{
	int numero;
	struct lista *prox;
} Lista;

/*Estrutura de uma pilha, incluindo um ponteiro de Lista para indicar o início da pilha*/
typedef struct pilha{
	Lista *topo;
} Pilha;

/*Aloca espaço para uma nova pilha*/
int cria_pilha(Pilha **novo);

/*Confere se uma pilha está vazia*/
int pilha_vazia(Pilha *p);

/*Insere elemento no topo da pilha*/
void push(Pilha *p, int n);

/*Retira elemento do topo da pilha*/
void pop(Pilha *p);

/*Informa o elemento no topo da pilha*/
int top(Pilha *p);

/*Libera todos os elementos de uma lista*/
void libera_lista(Lista *l);

/*Libera todos os elementos de uma pilha*/
void libera_pilha(Pilha *p);
