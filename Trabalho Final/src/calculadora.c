/*Trabalho Final de Métodos de Programação
Professor: Jan Correa
Alunos: Marcos Paulo Cayres Rosa - 14/0027131
	Ingrid Santana Lopes - 14/0083065
	Felipe Lira Fernandes dos Santos - 14/0019821
- Módulo auxiliar, presente na pasta src junto com o 'Makefile', 'pilha.c' e 'testa_calculadora.c'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pilha.h"
#include "calculadora.h"

void criaNovoArquivo(void){
	FILE *fp = fopen ("operacoes.txt","w");
	if(!fp){
		printf("\nNão foi possível criar um novo arquivo.\n");
		exit(1);
	}/*if*/
	fclose(fp);
}

int validacao(char *seq){
	int par = 0, col = 0, chv = 0, marc_parent = 0, marc_oper = 0;
	size_t i = (size_t)1;
	size_t j;
	char ant_oper = '\0';

	for(; i < (strlen(seq)-1); i++){
		if(seq[i] == '(' || seq[i] == '[' || seq[i] == '{'){
			ant_oper = seq[i];
			if(seq[i-2] == ')' || seq[i-2] == ']' || seq[i-2] == '}'){
				printf("\n\tEstá faltando algum operador.");
				return EXIT_FAILURE;
			}/*if*/
			marc_parent = 1;
			if(seq[i+2] != '*' && seq[i+2] != '/' && seq[i+2] != '^'){
				marc_oper = 0;
			}/*if*/
			if(seq[i] == '(') par++;
			if(seq[i] == '[') col++;
			if(seq[i] == '{') chv++;
		}/*if*/
		else if(seq[i] >= '0' && seq[i] <= '9'){
			marc_parent = 0;
			marc_oper = 0;
		}/*if*/
		else if(seq[i] == ')' || seq[i] == ']' || seq[i] == '}'){
			if(ant_oper == '(' && (seq[i] == ']' || seq[i] == '}')){
				printf("\n\tA parentização está incorreta.");
				return EXIT_FAILURE;
			}/*if*/
			else if(ant_oper == '[' && (seq[i] == ')' || seq[i] == '}')){
				printf("\n\tA parentização está incorreta.");
				return EXIT_FAILURE;
			}/*if*/
			else if(ant_oper == '{' && (seq[i] == ')' || seq[i] == ']')){
				printf("\n\tA parentização está incorreta.");
				return EXIT_FAILURE;
			}/*if*/
			if(marc_parent == 1){
				printf("\n\tHá um conjunto de parênteses que não apresenta expressão.");
				return EXIT_FAILURE;
			}/*if*/
			if( (par == 0 && seq[i] == ')') ||
			    (col == 0 && seq[i] == ']') || 
			    (chv == 0 && seq[i] == '}') ){
				printf("\n\tA parentização está incorreta.");
				return EXIT_FAILURE;
			}/*if*/
			if(seq[i] == ')') par--;
			if(seq[i] == ']') col--;
			if(seq[i] == '}') chv--;
			ant_oper = seq[i];
		}/*if*/
		else if(seq[i] == '+' || seq[i] == '-' || seq[i] == '*' || seq[i] == '/' || seq[i] == '^'){
		    	if(seq[i] == '/' && seq[i+2] == '0'){
				for(j = i+3; seq[j] == '0'; j++);
				if(seq[j] != '.' && !(seq[j] > '0' && seq[j] <= '9')){
					printf("\n\tErro: divisão por zero.");
					return EXIT_FAILURE;
				}/*if*/
			}/*if*/
			if(marc_oper == 1 || seq[i+2] == ')'){
				printf("\n\tHá operadores que não se referem à um valor numérico ou estão em local incorreto.");
				if(seq[i] == '-' && marc_oper == 1) printf("\n\tCaso estivesse se referindo ao negativo de um número, coloque entre parênteses ou no início da expressão.");
				return EXIT_FAILURE;
			}/*if*/
			marc_oper = 1;
		}/*if*/
	}/*if*/	

	if(par != 0 || col != 0 || chv != 0){
		printf("\n\tA parentização está incorreta.");
		return EXIT_FAILURE;
	}/*if*/
	return EXIT_SUCCESS;
}

float calcula(char *op){
	int i, j, marcado = 0;
	float resul = 0.0, aux1, aux2;
	char *aux;
	Pilha *p;

	aux = (char*)malloc(strlen(op)*sizeof(char));
	if(!aux){
		printf("\nNão foi possível alocar memória.\n");
		exit(2);
	}/*if*/
	p = cria_pilha();

	for(i = 0; op[i] != '\0'; i++){
		switch (op[i]){
			case '+':
				aux2 = top(p); pop(p);
				aux1 = top(p); pop(p);
		    		push(p, (aux1 + aux2));
		    		break;
		    	case '*':
				aux2 = top(p); pop(p);
				aux1 = top(p); pop(p);
		    		push(p, (aux1 * aux2));
		   		break;
		    	case '-':
				if(op[i+1] >= '0' && op[i+1] <= '9')
					marcado = 1;
				else{
					aux2 = top(p); pop(p);
					aux1 = top(p); pop(p);
			    		push(p, (aux1 - aux2));
				}/*if*/
		    		break; 
		    	case '/':
		    		aux2 = top(p); pop(p);
				aux1 = top(p); pop(p);
	        		push(p, (aux1 / aux2));
		   		break;
			case '^':
		 		aux2 = top(p); pop(p);
				aux1 = top(p); pop(p);
				push(p, pow(aux1,aux2));
				break;
			case ' ':
				break;
		    	default:
				for(j = 0; op[i] != ' '; i++, j++)
					aux[j] = op[i];
				aux[j] = '\0';
				if(marcado == 0)
					push(p, atof(aux));
				else{
					push(p, -atof(aux));
					marcado = 0;
				}/*if*/
		    		break;
		}/*switch*/
	}/*for*/

	resul = top(p);
	libera_pilha(p);

	return resul;
}

char *transfPolInv(char *operacao){
	char *final, *aux, c = '\0', ant = '\0', parent = '\0';
	int cont = 0, i, j, marcado = 0, neg_expr = -1;
	size_t tam;

	tam = strlen(operacao);
   	final = malloc( (tam+1) * sizeof (char));
	if(!final){
		printf("\nNão foi possível alocar memória.\n");
		exit(3);
	}/*if*/

   	aux = malloc( tam * sizeof (char));
	if(!aux){
		printf("\nNão foi possível alocar memória.\n");
		exit(4);
	}/*if*/

   	aux[cont++] = operacao[0];
   	for (j = 0, i = 1; operacao[i] != '\0'; i++){
		if(i != 1) ant = operacao[i-2];
      		switch (operacao[i]){
         		case '(':
			case '[':
			case '{':
				if(marcado == 0)
					aux[cont++] = operacao[i];
				else{
					aux[cont++] = operacao[i];
					final[j++] = '0';
					final[j++] = ' ';
					neg_expr = 0;
					marcado = 0;
				}/*if*/
				if(neg_expr >= 0) neg_expr++;
                   		break;
         		case ')':
			case ']':
			case '}':
				parent = operacao[i];
				if(neg_expr >= 0) neg_expr--;
				if(neg_expr == 0){
					final[j++] = '-';
					neg_expr = -1;
				}/*if*/
				if(parent == ')') parent = '(';
				else if(parent == ']') parent = '[';
				else if(parent == '}') parent = '{';
				while((c = aux[--cont]) != parent){
					if(final[j-1] != ' ') final[j++] = ' ';
                      			final[j++] = c;
				}/*while*/
                   		break;
         		case '+': 
         		case '-':
				if((ant == '(' || ant == '[' || ant == '{') || i == 1)
					marcado = 1;
				else{
					c = aux[cont-1];
					while(c != '(' && c != '[' && c != '{'){
						if(final[j-1] != ' ') final[j++] = ' ';
		              			final[j++] = c;
		              			cont--;
						c = aux[cont-1];
		           		}/*while*/
		           		aux[cont++] = operacao[i];
				}/*if*/
                   		break;
         		case '*':
         		case '/':
				c = aux[cont-1];
				while(c != '(' && c != '{' && c != '[' && c != '+' && c != '-'){
					if(final[j-1] != ' ') final[j++] = ' ';
                      			final[j++] = c;
                     			cont--;
					c = aux[cont-1];
                  		}/*while*/
                   		aux[cont++] = operacao[i];
                   		break;
			case '^':
				c = aux[cont-1];
				while(c != '(' && c != '{' && c != '[' && c != '+' && c != '-' && c != '*' && c != '/'){
					if(final[j-1] != ' ') final[j++] = ' ';
                      			final[j++] = c;
                     			cont--;
					c = aux[cont-1];
                  		}/*while*/
                   		aux[cont++] = operacao[i];
                   		break;
			case ' ':
				if(final[j-1] != ' ') final[j++] = ' ';
				break;
         		default:
				if(marcado == 0)
					final[j++] = operacao[i];
				else{
					final[j++] = '-';
					final[j++] = operacao[i];
					marcado = 0;
				}/*if*/
				break;
      		}/*switch*/
   	}/*for*/
   	free(aux);
   	final[j] = '\0';     
   	return final;
}

char* CaptExpr(char *nomearq){
	char c = '\0', ant = '\0', *operacao;
    	int tam, i = 0, marc_num = 0;

    	FILE *fp = fopen(nomearq, "r+");
    	if(!fp){
		printf("\nNão foi possível abrir o arquivo.\n");
		return " ";
    	}/*if*/

	fseek(fp,0,SEEK_END);
	tam = ftell(fp);
	operacao = (char*) malloc((tam+1)*2*sizeof(char));
	if(!operacao){
		printf("\nNão foi possível alocar memória.\n");
		exit(5);
	}/*if*/
	
	fseek(fp,0,SEEK_SET);
    	c = fgetc(fp);
	operacao[i++] = '(';
    	while(c != EOF){
		while((c >= '0' && c <= '9') || c == '.'){
			operacao[i++] = c;
			ant = c;
			marc_num = 1;
			c = fgetc(fp);
		}/*while*/
		if(ant >= '0' && ant <= '9'){
			operacao[i++] = ' ';
		}/*if*/

		if(c == '(' || c == '[' || c == '{' ){
			if(marc_num == 1){
				operacao = (char*) realloc(operacao,(tam+3)*2*sizeof(char));
				if(!operacao){
					printf("\nNão foi possível realocar memória.\n");
					exit(6);
				}/*if*/
				operacao[i++] = '*';
				operacao[i++] = ' ';
			}/*if*/
			operacao[i++] = c;
			operacao[i++] = ' ';
		}/*if*/
		else if(c == ')' || c == ']' ||c == '}' || c == '*'|| c == '/' || c == '^'){
			operacao[i++] = c;
			operacao[i++] = ' ';
		}/*if*/
		else if(c == '+' || c == '-'){
			if(ant == '(' || ant == '\0'){
				if(c == '-') operacao[i++] = c;
			} else{
				operacao[i++] = c;
				operacao[i++] = ' ';
			}/*if*/
		}
		else if(c != ' ' && c != '\n' && c != EOF && c != '\0'){
			operacao[0] = c;
		}/*if*/

		if(c != ' ') marc_num = 0;

		ant = c;
      		c = fgetc(fp);
    	}/*while*/
	operacao[i] = ')';
	operacao[i+1] = '\0';

	fclose(fp);

	return operacao;
}

int leitura(char *nomearq){
	char *operacao, *op_final;
    int val = 0;
    size_t i = (size_t) 1;
	float resul;
	FILE* fp;

	operacao = CaptExpr(nomearq);
	if(strlen(operacao) <= 3){
		printf("\n\tNão há expressão.\n");
		return EXIT_FAILURE;
	}/*if*/
	if(operacao[0] != '('){
		printf("\n\tArquivo apresenta caracter inválido: '%c'.\n", operacao[0]);
		if(operacao[0] == '.' || operacao[0] == ',') printf("\tConfira se está usando o ponto como separador decimal.\n");
		if(operacao[0] == 'x') printf("\tConfira se não está usando 'x' ao invés de '*' para efetuar multiplicações.\n");
		return EXIT_FAILURE;
	}/*if*/

	val = validacao(operacao);
	printf("\n\t");
	for(; i < (strlen(operacao)-1); i++){
		if(operacao[i] != ' ')
			printf("%c", operacao[i]);
	}/*for*/
	if(val == EXIT_FAILURE){
		printf(" é inválida.\n");
		return EXIT_FAILURE;
	}/*if*/
	
	op_final = transfPolInv(operacao);
	printf(" => %s = ", op_final);
	resul = calcula(op_final);
	printf("%g\n", resul);

	fp = fopen("operacoes.txt","a+");
	if(!fp){
		printf("\nNão foi possível abrir arquivo.\n");
		exit(1);
	}/*if*/
	
	for(i = 1; i < (strlen(operacao)-1); i++)
		if(operacao[i] != ' ') fprintf(fp, "%c", operacao[i]);
	fprintf(fp, " => %s = %g\n", op_final, resul);

	fclose(fp);
    
    	return val;
}

int EditarExpr(char *nomearq){
	char *operacao, op_nova[200];
    int val;
    size_t i = (size_t)1;
    FILE* fp;

	operacao = CaptExpr(nomearq);
	printf("\n\tExpressão original: ");
	for(; i < (strlen(operacao)-1); i++)
		if(operacao[i] != ' ') printf("%c", operacao[i]);

	printf("\n\tDigite a nova expressão: ");
	scanf("%s", op_nova);
	getchar();

	fp = fopen(nomearq, "w");
    	if(!fp){
		printf("\nNão foi possível abrir o arquivo.\n");
		return EXIT_FAILURE;
    	}/*if*/

	fprintf(fp,"%s",op_nova);

	fclose(fp);

	val = leitura(nomearq);
	return val;
}
