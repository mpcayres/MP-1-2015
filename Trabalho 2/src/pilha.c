/*2º Trabalho de Métodos de Programação
Professor: Jan Correa
Aluno: Marcos Paulo Cayres Rosa
Matrícula: 14/0027131
- Programa auxiliar, presente na pasta src junto com o 'Makefile', 'parentizacao.c' e 'testa_parentizacao.c'
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pilha.h"

Pilha* cria_pilha(){
	Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
	novo->topo = NULL;
	return novo;
}

int pilha_vazia(Pilha *p){
	return (p->topo == NULL);
}

void push(Pilha *p, char c){
	Lista *novo = (Lista*)malloc(sizeof(Lista));
	assert(novo != NULL);
	novo->elem = c;
	novo->prox = p->topo;
	p->topo = novo;
}

void pop(Pilha *p){
	Lista *l;
	if (pilha_vazia(p)) return;
	//assert(p->topo != NULL);
	
	l = p->topo;
	p->topo = l->prox;
	free(l);
}

char top(Pilha *p){
	Lista *aux = p->topo;
	if (pilha_vazia(p)) return EXIT_FAILURE;
	return aux->elem;
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
