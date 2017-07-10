/*2º Trabalho de Métodos de Programação
Professor: Jan Correa
Aluno: Marcos Paulo Cayres Rosa
Matrícula: 14/0027131
- 'Include file', presente na pasta lib junto com 'pilha.h'
*/

#ifndef PARENTIZACAO_H
#define PARENTIZACAO_H

int tamanho(Pilha *p);

int testa_elemento(Pilha *seq);

Pilha* inverte_pilha(Pilha *p);

int leitura(char *nomearq);

#endif
