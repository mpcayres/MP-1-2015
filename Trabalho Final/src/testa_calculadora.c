/*Trabalho Final de Métodos de Programação
Professor: Jan Correa
Alunos: Marcos Paulo Cayres Rosa - 14/0027131
	Ingrid Santana Lopes - 14/0083065
	Felipe Lira Fernandes dos Santos - 14/0019821
- Módulo principal, compilado com 'make', estando presente na pasta src junto com o 'Makefile', 'calculadora.c' e 'pilha.c'
*/

#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "pilha.h"
#include "calculadora.h"

/* Ponteiro para variável global da Pilha e para o arquivo usado nos testes. */
static Pilha* p = NULL;
static FILE* fp_txt = NULL;

/* Função de incialização da suíte, criando uma pilha que será usada para testes e retornando EXIT_SUCCESS em caso de sucesso (EXIT_FAILURE caso contrário). */
int init_suite1(void){
	if( NULL == (p = cria_pilha()) )
		return EXIT_FAILURE;
	else
		return EXIT_SUCCESS;
}

/* Função de limpeza da suíte, liberando uma pilha que será usada para testes e retornando EXIT_SUCCESS em caso de sucesso (EXIT_FAILURE caso contrário). */
int clean_suite1(void){
	libera_pilha(p);
	if( NULL == p )
		return EXIT_FAILURE;
	else
		return EXIT_SUCCESS;
}

/* Função de incialização da suíte, abrindo um arquivo texto que será usado para testes e retornando EXIT_SUCCESS em caso de sucesso (EXIT_FAILURE caso contrário). */
int init_suite2(void){
	if( NULL == (fp_txt = fopen("testes.txt", "r+")) )
		return EXIT_FAILURE;
	else
		return EXIT_SUCCESS;
}

/* Função de limpeza da suíte, fechando um arquivo texto que será usado para testes e retornando EXIT_SUCCESS em caso de sucesso (EXIT_FAILURE caso contrário). */
int clean_suite2(void){
	if( 0 != fclose(fp_txt) )
		return EXIT_FAILURE;
	else
		return EXIT_SUCCESS;
}

/* Função de teste da função criarNovoAequivo(void). */
void testaAberturaArq(void){
	FILE* fp;
	criaNovoArquivo();
	fp = fopen("operacoes.txt","r");
	CU_ASSERT(fp != NULL);
	fclose(fp);
}

/* Função de teste da função leitura(char *nomearq). */
void testaLEITURA(void){
	char c = '\0', nomearq[50], valid_str[3];
	int validacao;
	/*Automatização do teste da função, analisando diversos arquivos e verificando se esses possuem parentização correta*/	
	while(c != EOF){	
		fscanf(fp_txt, "%s", nomearq);
		c = fgetc(fp_txt);
		while(c < 'A')
			c = fgetc(fp_txt);
		fseek(fp_txt, -1, SEEK_CUR);

		fscanf(fp_txt, "%s", valid_str);
		valid_str[3] = '\0';
		if(strcmp(valid_str,"VAL") == 0 || strcmp(valid_str,"val") == 0) validacao = EXIT_SUCCESS;
		else validacao = EXIT_FAILURE;

		if(validacao == EXIT_SUCCESS) printf("\n\t%s||VALIDO", nomearq);
		else printf("\n\t%s||INVALIDO", nomearq);
		CU_ASSERT(validacao == leitura(nomearq));

		while(c != '\n' && c != EOF)
			c = fgetc(fp_txt);
		c = fgetc(fp_txt);
		if(c != EOF) fseek(fp_txt, -1, SEEK_CUR);
	}/*while*/
}

/* Função de teste da função EditarExpr(char *nomearq). */
void testaEDICAO(void){
	char c = '\0', nomearq[50], valid_str[9], resp = '\0';
	int validacao;

	fseek(fp_txt, 0, SEEK_SET);
	/*Automatização do teste da função, analisando diversos arquivos e verificando se esses possuem parentização correta*/	
	while(c != EOF){	
		fscanf(fp_txt, "%s", nomearq);
		c = fgetc(fp_txt);
		while(c < 'A')
			c = fgetc(fp_txt);
		fseek(fp_txt, -1, SEEK_CUR);

		printf("\n\tDeseja editar a expressão do arquivo \"%s\"? (S/N) ", nomearq);
		scanf("%c", &resp);
		getchar();
		if(resp == 'S' || resp == 's'){
			printf("\n\tA expressão será válida? (S/N) ");
			scanf("%c", &resp);
			getchar();
			if(resp == 'S' || resp == 's'){
				validacao = EXIT_SUCCESS;
				strcpy(valid_str,"VALIDO");
				fprintf(fp_txt, "%s", "VAL");
			}
			else{
				validacao = EXIT_FAILURE;
				strcpy(valid_str,"INVALIDO");
				fprintf(fp_txt, "INV");
			}
			printf("\n\t%s||%s",nomearq,valid_str);
			CU_ASSERT(validacao == EditarExpr(nomearq));
		}

		while(c != '\n' && c != EOF)
			c = fgetc(fp_txt);

		c = fgetc(fp_txt);
		if(c != EOF) fseek(fp_txt, -1, SEEK_CUR);
	}/*while*/
}

/* Função principal para estabelecer e rodar os testes, retornando CUE_SUCCESS em caso de sucesso e outro 'CUnit error code' caso contrário. */
int main(){

	CU_pSuite pSuite_Pilha = NULL;
	CU_pSuite pSuite_File = NULL;

	printf("\033[2J");	
	printf("\033[1;1f");
	
	/* Inicializa o registro de testes CUnit. */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* Inclui uma suíte ao registro. */
	pSuite_Pilha = CU_add_suite("Suite_Pilha", init_suite1, clean_suite1);
	if (NULL == pSuite_Pilha) {
		CU_cleanup_registry();
		return CU_get_error();
	}/*if*/

	pSuite_File = CU_add_suite("Suite_File", init_suite2, clean_suite2);
	if (NULL == pSuite_File) {
		CU_cleanup_registry();
		return CU_get_error();
	}/*if*/

	/* Adiciona os testes às suítes. */
	if ( (NULL==CU_add_test(pSuite_File, "teste de criarNovoArquivo(void)",testaAberturaArq)) ||
	     (NULL == CU_add_test(pSuite_File, "teste de leitura(char *nomearq)", testaLEITURA)) ||
	     (NULL==CU_add_test(pSuite_File, "teste de EditarExpr(char *nomearq)",testaEDICAO)) )
   	{
		CU_cleanup_registry();
		return CU_get_error();
	}/*if*/

	/* Roda todos os teste usando o 'CUnit Basic interface'. */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	(void) CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
