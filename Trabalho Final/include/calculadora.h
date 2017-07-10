/*Trabalho Final de Métodos de Programação
Professor: Jan Correa
Alunos: Marcos Paulo Cayres Rosa - 14/0027131
	Ingrid Santana Lopes - 14/0083065
	Felipe Lira Fernandes dos Santos - 14/0019821
- Arquivo de cabeçalho, presente na pasta lib junto com 'pilha.h'
*/
/** @file */

#ifndef CALCULADORA_H
#define CALCULADORA_H
/***********************************************************************//**
* @brief Cria novo arquivo para armazenar operações \n
* Cria um novo arquivo vazio para que as operações calculadas durante a
* execução do programa possam ser salvas com seus respectivos resultados e para
* posterior análise pelo usuário.
* @param Nenhum
* @return Nenhum
* @remark Assertiva de entrada:
* 	 - Nenhum
* @remark Assertiva de saída:
*	- sairá do programa caso não seja possível abrir o arquivo operacoes.txt
*	- o arquivo aberto deverá ser fechado
* @remark Estrutura implícita:
* 	- Um ponteiro to tipo FILE denominado fp que apontará para o arquivo aberto.
* @remark Estrutura Explícita:
* 	- Não há estrutura explicita
* @remark Requesitos:
* 	- Deve ser capaz de criar um novo arquivo denominado operacoes.txt caso não exista
*		- Caso já exista arquivo com esse nome, deve ser capaz de esvaziar todo seu conteúdo
*		- Deve ser capaz de sair do programa caso não seja possível abrir o arquivo
*		- Deve fechar o arquivo antes de sair do programa
* @remark Hipótese:
* 	- A função será chamada previamente a utilização do arquivo operacoes.txt
***************************************************************************/
void criaNovoArquivo(void);

/***********************************************************************//**
* @brief Confere se a expressão numérica segue os critérios estabelecidos \n
* Retorna a determinação de se a expressão foi parentizada corretamente
* (EXIT_SUCCESS, em caso positivo, e EXIT_FAILURE, em caso negativo). Como
* também, informa a existência de caracteres inválidos, a falta de operadores,
* tentativas de cálculos inválidos e erros lógicos
* @param seq - ponteiro para a expressão a ser testada
* @return Um valor inteiro que serve como booleano
* @remark Assertiva de entrada:
* 	- seq é uma string que se refere à uma expressão matemática
* @remark Assertiva de saída:
*	- valor retornado é um inteiro EXIT_SUCCESS ou EXIT_FAILURE
* 	- 'seq' é o mesmo que o de entrada
* @remark Estrutura implícita:
* 	- Não são usadas variáveis globais, arquivos externos ou condições de 
* retorno
* @remark Estrutura Explícita:
* 	- Recebe como parâmetro uma string e retorna um inteiro
* @remark Requesitos:
* 	- Deve ser capaz de verificar a parentização de uma string
*		- Deve ser capaz de conferir a corretude de uma expressão matemática
* 	- Caso não haja elementos na string, retornar como EXIT_SUCCESS
*		- Se algum elemento diferir de parênteses, colchetes, chaves, números ou operador, retornar EXIT_FAILURE
* @remark Hipótese:
* 	- O ponteiro do tipo char fornecido está indicando a string a ser analisada
***************************************************************************/
int validacao(char *seq);

/***********************************************************************//**
* @brief Calcula uma expressão utilizando lógica polonesa reversa \n
* Função que recebe como parâmetro uma string op, que possui uma expressão
* matemática em lógica polonesa reversa, e retorna um valor float representando
* o resultado dessa expressão
* @param op - string que contém a expressão a ser calculada
* @return Um valor real com o resultado da expressão
* @remark Assertiva de entrada:
* 	- op é uma string que se refere à uma expressão matemática
* @remark Assertiva de saída:
*	- valor retornado deve ser correspondente ao resultado da expressão
* 	- 'op' é o mesmo que o de entrada
* @remark Estrutura implícita:
* 	- Não são usadas variáveis globais, arquivos externos ou condições de 
* retorno
* @remark Estrutura Explícita:
* 	- Recebe como parâmetro uma string op e retorna um float
* @remark Requesitos:
* 	- Deve ser capaz de calcular o valor de uma expressão em lógica polonesa reversa
*   	- Deve ser capaz de obedecer todos as regras matemáticas de precedência
*		- Liberar qualquer estrutura utilizada para auxiliar no procedimento
* @remark Hipótese:
* 	- A string passada é diferente de NULL
*   	- A expressão passada contém apenas caracteres válidos que podem ser 
* utilizados em expressões matemáticas
***************************************************************************/
float calcula(char *op);

/***********************************************************************//**
* @brief Transforma uma expressão para Notação Polonesa Inversa \n
* Função que recebe como parâmetro uma string com uma expressão matemática
* e retorna uma outra string com a expressão equivalente em notação polonesa
* reversa
* @param operacao - string com a expressão a ser transformada
* @return string com a expressão transformada
* @remark Assertiva de entrada:
* 	- seq é uma string que se refere à uma expressão matemática
* @remark Assertiva de saída:
* 	- 'operacao' é o mesmo que o de entrada
* @remark Estrutura implícita:
* 	- Não são usadas variáveis globais, arquivos externos ou condições de 
* retorno
* @remark Estrutura Explícita:
* 	- Recebe como parâmetro uma string com a expressão a ser transformada
* e retorna uma outra string com a expressão transformada
* @remark Requesitos:
* 	- Deve ser capaz de transformar uma expressão matemática em lógica
* polonesa reversa
*   	- Deve seguir todos as regras de precedência matemática
*   	- Deve sair do programa caso não consiga alocar a memória necessária
* para as variáveis auxiliares
* @remark Hipótese:
* 	- A string passada é diferente de NULL
*   	- A expressão passada contém apenas caracteres válidos que podem ser 
* utilizados em expressões matemáticas
***************************************************************************/
char *transfPolInv(char *operacao);

/***********************************************************************//**
* @brief Captura uma expressão matemática através de um arquivo\n
* Função que recebe como parâmetro uma string que constituída pelo nome de um
* arquivo no qual vai ser capturada uma expressão matemática, retornando uma nova
* string com a expressão
* @param nomearq - string com o nome do arquivo onde está a expressão
* @return string que possui a expressão encontrada
* @remark Assertiva de entrada:
* 	- Arquivo criado pela string passada como parâmetro é diferente de NULL
* @remark Assertiva de saída:
*	- o arquivo não sofrerá modificações
* @remark Estrutura implícita:
* 	- Não são usadas variáveis globais, arquivos externos ou condições de 
* retorno
* @remark Estrutura Explícita:
* 	- Recebe como parâmetro uma string com o nome do arquivo e retorna uma nova
* string com a expressão encontrada
* @remark Requesitos:
* 	- Deve ser capaz de encontrar uma expressão matemática presente em um arquivo
*   	- Deve ser capaz de fechar o arquivo aberto para se encontrar a expressão
* @remark Hipótese:
* 	- O arquivo aberto pela string passada como parâmetro possui apenas uma
* expressão matemática
***************************************************************************/
char* CaptExpr(char *nomearq);

/***********************************************************************//**
* @brief Testa a parentização dos elementos de uma pilha \n
* Retorna a determinação de se uma expressão encontrada em um arquivo é válida
* (EXIT_SUCCESS, em caso positivo, e EXIT_FAILURE, em caso negativo) e
* exibe essa informação na tela, juntamente ao seu resultado.
* @param nomearq - ponteiro de char indicando a string correspondente ao
* nome do arquivo/código
* @return Um valor inteiro que serve como booleano
* @remark Assertiva de entrada:
* 	- existir o arquivo passado como parâmetro
* @remark Assertiva de saída:
*	- valor retornado é um inteiro EXIT_SUCCESS ou EXIT_FAILURE
*	- arquivo não sofrerá modificações
* @remark Estrutura implícita:
* 	- Não são usadas variáveis globais, arquivos externos ou condições de 
* retorno
* @remark Estrutura Explícita:
* 	- Recebe como parâmetro uma string e retorna um inteiro
* @remark Requesitos:
* 	- Deve ser capaz de verificar a validade de uma expressão
* 	- Caso não haja encontrado o arquivo, cessar o procedimento
*		- Liberar qualquer estrutura utilizada para auxiliar no procedimento
* @remark Hipótese:
* 	- A expressão fornecida estará correta em quesitos não relativos à
* parentização ou lógica matemática
* 	- O arquivo aberto pela string passada como parâmetro possui apenas uma
* expressão matemática
***************************************************************************/
int leitura(char *nomearq);

/***********************************************************************//**
* @brief Edita a expressão que está dentro de um arquivo \n
* Função que edita uma expressão matemática que está dentro um arquivo, recebe
* como parâmetro uma string com o nome desse arquivo e retorna um inteiro com o
* valor dessa expressão calculado pela função "leitura"
* @param nomearq - string que constitui o nome do arquivo a ser editado
* @return inteiro com o valor da expressão
* @remark Assertiva de entrada:
* 	- existir o arquivo passado como parâmetro
* @remark Assertiva de saída:
*	- valor retornado é um inteiro EXIT_SUCCESS ou EXIT_FAILURE
* @remark Estrutura implícita:
* 	- Não são usadas variáveis globais, arquivos externos ou condições de 
* retorno
* @remark Estrutura Explícita:
* 	- Recebe uma string e retorna um inteiro
* @remark Requesitos:
* 	- Deve ser capaz de imprimir a expressão original na tela
*   	- Deve capturar a nova expressão pelo usuário e posteriormente sobrescrever
* o arquivo com a nova expressão
* @remark Hipótese:
* 	- A expressão fornecida estará correta em quesitos não relativos à
* parentização ou lógica matemática
* 	- Será fornecida apenas uma expressão matemática e esta será não nula
***************************************************************************/
int EditarExpr(char *nomearq);

#endif
