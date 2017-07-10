/*2º Trabalho de Métodos de Programação
Professor: Jan Correa
Aluno: Marcos Paulo Cayres Rosa
Matrícula: 14/0027131
- Programa principal, compilado com 'make', estando presente na pasta src junto com o 'Makefile', 'parentizacao.h' e 'pilha.c'
  Maiores detalhes da compilação presentes no pdf, em "II. Funções analisadas"
*/

#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "pilha.h"
#include "parentizacao.h"

/* Ponteiro para o arquivo usado nos testes e para variável global da Pilha. */
static Pilha* p;

/* Função de incialização da suíte, criando uma pilha que será usada para testes e retornando zero em caso de sucesso (-1 caso contrário). */
int init_suite1(void){
	p = cria_pilha();
  
	if(p != NULL) return EXIT_SUCCESS;
	else return EXIT_FAILURE;
}

/* Função de limpeza da suíte, liberando uma pilha que será usada para testes e retornando zero em caso de sucesso (-1 caso contrário). */
int clean_suite1(void){
	libera_pilha(p);
	if(p == NULL) return EXIT_FAILURE;
	else return EXIT_SUCCESS;
}

/* Função de teste da função top(Pilha *p). */
void testeTAM(void){
	/*Confere se o valor do topo da pilha é o mesmo retornado*/
	push(p,'3');
	CU_ASSERT(1 == tamanho(p));	
	
	/*Mesmo procedimento para uma pilha com mais de um elemento*/
	push(p,'4');
	CU_ASSERT(2 == tamanho(p));
	
	/*Confere se a função retorna EXIT_FAILURE ao procurar o elemento do topo de uma lista vazia*/
	pop(p); // retirada de '4'
	pop(p); // retirada de '3'
	CU_ASSERT(0 == tamanho(p));
}

void testePARENT(void){
	/*Confere se o valor do topo da pilha é o mesmo retornado*/
	push(p,'}');
	CU_ASSERT(EXIT_FAILURE == teste_parentizacao(p));	
	
	/*Mesmo procedimento para uma pilha com mais de um elemento*/
	push(p,'{');
	CU_ASSERT(EXIT_SUCCESS == teste_parentizacao(p));
	
	/*Confere se a função retorna EXIT_FAILURE ao procurar o elemento do topo de uma lista vazia*/
	pop(p); // retirada de '4'
	pop(p); // retirada de '3'
	CU_ASSERT(EXIT_FAILURE == teste_parentizacao(p));

	push(p,'a');
	CU_ASSERT(EXIT_FAILURE == teste_parentizacao(p));
	pop(p);

	push(p,']'); push(p,'['); push(p,'(');
	CU_ASSERT(EXIT_FAILURE == teste_parentizacao(p));
	pop(p); pop(p); pop(p);

	push(p,'('); push(p,'('); push(p,')'); push(p,')');
	CU_ASSERT(EXIT_FAILURE == teste_parentizacao(p));
	pop(p); pop(p); pop(p); pop(p);

	push(p,'}'); push(p,')'); push(p,'{'); push(p,'(');
	CU_ASSERT(EXIT_FAILURE == teste_parentizacao(p));
	pop(p); pop(p); pop(p); pop(p);

	push(p,'{'); push(p,'['); push(p,'('); push(p,')'); push(p,'('); push(p,')'); push(p,']'); push(p,'}');
	p = inverte_pilha(p);
	CU_ASSERT(EXIT_SUCCESS == teste_parentizacao(p));
	pop(p); pop(p); pop(p); pop(p); pop(p); pop(p); pop(p); pop(p);

	push(p,'{'); push(p,'}'); push(p,'('); push(p,')'); push(p,'('); push(p,')'); push(p,'['); push(p,']');
	p = inverte_pilha(p);
	CU_ASSERT(EXIT_SUCCESS == teste_parentizacao(p));
	pop(p); pop(p); pop(p); pop(p); pop(p); pop(p); pop(p); pop(p);
}

void testeLEITURA(void){
	char c = '\0', nomearq[50], valid_str[9];
	int validacao;
	FILE *fp_txt = fopen("testes.txt", "r");
    	if(!fp_txt){
		printf("\nNão foi possível abrir o arquivo.\n");
		exit(0);
    	}

	while(c != EOF){	
		fscanf(fp_txt, "%s", nomearq);
		c = fgetc(fp_txt);
		while(c < 'A')
			c = fgetc(fp_txt);
		fseek(fp_txt, -1, SEEK_CUR);

		fscanf(fp_txt, "%s", valid_str);
		if(strcmp(valid_str,"VALIDO") == 0 || strcmp(valid_str,"valido") == 0) validacao = EXIT_SUCCESS;
		else validacao = EXIT_FAILURE;

		printf("\n\t%s||%s",nomearq,valid_str);
		CU_ASSERT(validacao == leitura(nomearq));

		while(c != '\n' && c != EOF)
			c = fgetc(fp_txt);
		c = fgetc(fp_txt);
		if(c != EOF) fseek(fp_txt, -1, SEEK_CUR);
	}

	fclose(fp_txt);
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
	if ( (NULL == CU_add_test(pSuite, "teste de tamanho(Pilha *p)", testeTAM)) ||
	     (NULL == CU_add_test(pSuite, "teste de paretentizacao(Pilha *p)", testePARENT)) ||
	     (NULL == CU_add_test(pSuite, "teste de leitura(char *nomearq)", testeLEITURA)) )
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
