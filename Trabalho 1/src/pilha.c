/*1º Trabalho de Métodos de Programação
Professor: Jan Correa
Aluno: Marcos Paulo Cayres Rosa
Matrícula: 14/0027131
- Programa auxiliar, presente na pasta src junto com o 'Makefile' e 'tp_cunit.c'
*/

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int cria_pilha(Pilha **novo){
	*novo = (Pilha*)malloc(sizeof(Pilha));
	if(!(*novo)){
		//printf("\nNão há memória suficiente.\n");
		return EXIT_FAILURE;
	}
	(*novo)->topo = NULL;
	return EXIT_SUCCESS;
}

int pilha_vazia(Pilha *p){
	return (p->topo == NULL);
}

void push(Pilha *p, int n){
	Lista *novo = (Lista*)malloc(sizeof(Lista));
	if(!novo){
		//printf("\nNão há memória suficiente.\n");
		return;
	}
	novo->numero = n;
	novo->prox = p->topo;
	p->topo = novo;
}

void pop(Pilha *p){
	Lista *l;
	if(pilha_vazia(p)){
		//printf("\nNão há nenhum elemento na pilha.\n");
		return;
	}
	l = p->topo;
	p->topo = l->prox;
	free(l);
}

int top(Pilha *p){
	Lista *aux = p->topo;
	if (pilha_vazia(p)){
		//printf("\nNão há nenhum elemento na pilha.\n");
		return EXIT_FAILURE;
	}
	return aux->numero;
}

void libera_lista(Lista *l){
	while(l != NULL){
		Lista *tmp = l->prox;
		free(l);
		l = tmp;
	}
}

void libera_pilha(Pilha *p){
	Lista *l = p->topo;
	libera_lista(l);
	free(p);
}
