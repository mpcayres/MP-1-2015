/*1º Trabalho de Métodos de Programação
Professor: Jan Correa
Aluno: Marcos Paulo Cayres Rosa
Matrícula: 14/0027131
- Programa principal, compilado com 'make', estando presente na pasta src junto com o 'Makefile' e 'pilha.c'
  Maiores detalhes da compilação presentes no pdf, em "II. Funções analisadas"
*/

#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "pilha.h"

/* Ponteiro para o arquivo usado nos testes e para variável global da Pilha. */
static Pilha* p;

/* Função de incialização da suíte, criando uma pilha que será usada para testes e retornando zero em caso de sucesso (-1 caso contrário). */
int init_suite1(void){
	int avaliacao = cria_pilha(&p);
  
	if(avaliacao == 0) return EXIT_SUCCESS;
	else return EXIT_FAILURE;
}

/* Função de limpeza da suíte, liberando uma pilha que será usada para testes e retornando zero em caso de sucesso (-1 caso contrário). */
int clean_suite1(void){
	libera_pilha(p);
	if(p == NULL) return EXIT_FAILURE;
	else return EXIT_SUCCESS;
}

/* Função de teste da função push(Pilha *p). */
void testePUSH(void){
	Lista* aux;

	/*Confere se o valor no topo é o mesmo que o inserido*/
	push(p,1);
	CU_ASSERT(1 == p->topo->numero);

	/*Confere se o valor no topo é o mesmo que o inserido e se o inserido anteriormente ficou abaixo deste*/
	push(p,2);
	aux = p->topo;
	CU_ASSERT(2 == aux->numero);
	aux = aux->prox;
	CU_ASSERT(1 == aux->numero);
	
	/*Mesmo processo, conferindo se ocorre algum erro ao adicionar o mesmo número ao topo e se, ao chegar ao final da pilha, está apontando para algo*/
	push(p,2);
	aux = p->topo;
	CU_ASSERT(2 == aux->numero);
	aux = aux->prox;
	CU_ASSERT(2 == aux->numero);
	aux = aux->prox;
	CU_ASSERT(1 == aux->numero);
	CU_ASSERT(NULL == aux->prox);
}

/* Função de teste da função pop(Pilha *p). */
void testePOP(void){
	Lista* aux;
	
	/*Confere se, após retirar o elemento do topo, o que ficou então no topo era o que estava inserido na segunda posição e se o resto da pilha permanece igual*/
	pop(p); // retirada de '2'
	aux = p->topo;
	CU_ASSERT(2 == aux->numero);
	aux = aux->prox;
	CU_ASSERT(1 == aux->numero);

	/*Conferir se a pilha está vazia após a retirada de todos os elementos*/
	pop(p); // retirada de '2'
	pop(p); // retirada de '1'
	CU_ASSERT(NULL == p->topo);

	/*Confere se não houve nenhum procedimento ao tentar retirar o elemento do topo de uma pilha vazia*/
	pop(p);
	CU_ASSERT(NULL == p->topo);
}

/* Função de teste da função top(Pilha *p). */
void testeTOP(void){
	/*Confere se o valor do topo da pilha é o mesmo retornado*/
	push(p,3);
	CU_ASSERT(3 == top(p));	
	
	/*Mesmo procedimento para uma pilha com mais de um elemento*/
	push(p,4);
	CU_ASSERT(4 == top(p));
	
	/*Confere se a função retorna EXIT_FAILURE ao procurar o elemento do topo de uma lista vazia*/
	pop(p); // retirada de '4'
	pop(p); // retirada de '3'
	CU_ASSERT(EXIT_FAILURE == top(p));
}

/* Função principal para estabelecer e rodar os testes, retornando CUE_SUCCESS em caso de sucesso e outro 'CUnit error code' caso contrário. */
int main(){

	CU_pSuite pSuite = NULL;

	printf("\033[2J");	
	printf("\033[1;1f");

	/* Inicializa o registro de testes CUnit. */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* Inclui uma suíte ao registro. */
	pSuite = CU_add_suite("Suite_Pilha", init_suite1, clean_suite1);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Adiciona os testes à suíte. */
	if ( (NULL == CU_add_test(pSuite, "teste de push(Pilha *p)", testePUSH)) ||
	     (NULL == CU_add_test(pSuite, "teste de pop(Pilha *p)", testePOP)) ||
	     (NULL == CU_add_test(pSuite, "teste de top(Pilha *p)", testeTOP)) )
   	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Roda todos os teste usando o 'CUnit Basic interface'. */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
