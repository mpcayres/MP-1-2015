/*Trabalho Final de Métodos de Programação
Professor: Jan Correa
Alunos: Marcos Paulo Cayres Rosa - 14/0027131
	Ingrid Santana Lopes - 14/0083065
	Felipe Lira Fernandes dos Santos - 14/0019821
- Módulo auxiliar, presente na pasta src junto com o 'Makefile', 'calculadora.c' e 'testa_calculadora.c'
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pilha.h"

Pilha* cria_pilha(){
	Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
	assert(novo != NULL);

	novo->topo = NULL;

	return novo;
}

int pilha_vazia(Pilha *p){
	return (p->topo == NULL);
}

void push(Pilha *p, float c){
	Lista *novo = (Lista*)malloc(sizeof(Lista));
	assert(novo != NULL);

	novo->elem = c;
	novo->prox = p->topo;
	p->topo = novo;
}

void pop(Pilha *p){
	Lista *l;
	if (pilha_vazia(p)) exit(0);
	
	l = p->topo;
	p->topo = l->prox;
	free(l);
}

float top(Pilha *p){
	Lista *aux = p->topo;
	if (pilha_vazia(p)) return (float)EXIT_FAILURE;
	return aux->elem;
}

void libera_lista(Lista *l){
	while(l != NULL){
		Lista *tmp = l->prox;
		free(l);
		l = tmp;
	}/*while*/
}

void libera_pilha(Pilha *p){
	Lista *l;
	if(p == NULL) exit(1);
	l = p->topo;
	libera_lista(l);
	free(p);
}
