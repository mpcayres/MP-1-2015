/*2º Trabalho de Métodos de Programação
Professor: Jan Correa
Aluno: Marcos Paulo Cayres Rosa
Matrícula: 14/0027131
- Programa auxiliar, presente na pasta src junto com o 'Makefile', 'pilha.c' e 'testa_parentizacao.c'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pilha.h"
#include "parentizacao.h"

int tamanho(Pilha *p){
    Lista *aux;
    int tam = 0;
    
    for(aux = p->topo; aux != NULL; aux = aux->prox)
	tam++;
    
    return tam;  
}

int teste_parentizacao(Pilha *seq){
	Lista *aux = NULL;
    	char ant = '\0';
	Pilha *par = cria_pilha(), *col = cria_pilha(), *chv = cria_pilha();
   
    	if( (tamanho(seq)%2 != 0) || seq->topo == NULL ) return EXIT_FAILURE;
   
    	for(aux = seq->topo; aux != NULL; aux = aux->prox){
		if(aux->elem != '(' && aux->elem != ')' &&
		   aux->elem != '[' && aux->elem != ']' &&
		   aux->elem != '{' && aux->elem != '}') return EXIT_FAILURE;

		else if(aux->elem == '(') push(par,aux->elem);
		else if(aux->elem == ')'){
	  		if(tamanho(par) == 0) return EXIT_FAILURE;
	  		pop(par);
		}
		else if(aux->elem == '[') push(col,aux->elem);
		else if(aux->elem == ']'){
	  		if(tamanho(col) == 0) return EXIT_FAILURE;
	  		pop(col);
		}
		else if(aux->elem == '{') push(chv,aux->elem);
		else if(aux->elem == '}'){
	  		if(tamanho(chv) == 0) return EXIT_FAILURE;
	  		pop(chv);
		}

		if(ant == '(' && (aux->elem == ']' || aux->elem == '}')) return EXIT_FAILURE;
		else if(ant == '[' && (aux->elem == ')' || aux->elem == '}')) return EXIT_FAILURE;
		else if(ant == '{' && (aux->elem == ')' || aux->elem == ']')) return EXIT_FAILURE;
		ant = aux->elem; 
    	}
    
    	if((tamanho(par) != 0) || (tamanho(col) != 0) || (tamanho(chv) != 0)) return EXIT_FAILURE;
    
    	return EXIT_SUCCESS;
}

Pilha* inverte_pilha(Pilha *p){
	Lista *aux;
  	Pilha *final = cria_pilha();
  
  	for(aux = p->topo; aux != NULL; aux = aux->prox)
      		push(final,aux->elem);
  
  	return final;
}

int leitura(char *nomearq){
	char c = '\0', ant = '\0';
    	int val = 0, coment_linha = 0, coment_ext = 0, aspas = 0, aspas_simp = 0;
    	Pilha *novo = cria_pilha(), *final = cria_pilha();
    	Lista *aux;
    
    	FILE *fp = fopen(nomearq, "r");
    	if(!fp){
		printf("\nNão foi possível abrir o arquivo.\n");
		return EXIT_FAILURE;
    	}
      
    	c = fgetc(fp);
    	while(c != EOF){
      		if((ant == '/')  && (c == '/') && (coment_linha == 0) && (coment_ext == 0) && (aspas == 0) && (aspas_simp == 0)) 				coment_linha = 1;
      		else if((c == '\n') && (coment_linha == 1))
			coment_linha = 0;
      		else if((ant == '/')  && (c == '*') && (coment_linha == 0) && (coment_ext == 0) && (aspas == 0) && (aspas_simp == 0)) 				coment_ext = 1;
      		else if((ant == '*') && (c == '/') && (coment_ext == 1))
			coment_ext = 0;
      		else if((c == '\"') && (ant != '\\') && (coment_linha == 0) && (coment_ext == 0) && (aspas_simp == 0)){
			if(aspas == 0) aspas = 1;
			else aspas = 0;
      		}
      		else if((c == '\'') && (ant != '\\') && (coment_linha == 0) && (coment_ext == 0) && (aspas == 0)){
			if(aspas_simp == 0) aspas_simp = 1;
			else aspas_simp = 0;
      		}
      
      		if((c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') &&
		   (coment_linha == 0) && (coment_ext == 0) && (aspas == 0) && (aspas_simp == 0)) push(novo,c);
      		ant = c;
      		c = fgetc(fp);
    	}
	fclose(fp);

    	final = inverte_pilha(novo);
	libera_pilha(novo);

    	val = teste_parentizacao(final);
	libera_pilha(final);

	if(val == EXIT_SUCCESS) printf("\n\tO arquivo \"%s\" foi compilado com sucesso.\n", nomearq);
    	else printf("\n\tO arquivo \"%s\" não foi compilado.\n", nomearq);
    
    	return val;
}
