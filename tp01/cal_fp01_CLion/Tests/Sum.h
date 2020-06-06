/*
 * Sum.h
 */

#ifndef SUM_H_
#define SUM_H_

#include <string>
using namespace std;


/* Calcula, numa sequencia de n numeros (n > 0),
 * para cada subsequencia de m numeros (m <= n, m > 0),
 * o indice i a partir do qual a soma s dos valores dessa subsequencia é minimo.
 *
 * Argumentos:
 * 	sequence - Array com a sequencia
 * 	size - Tamanho da sequencia
 *
 * Devolve:
 * Uma string que contém com a indicacao do indice i e somatorio s, para cada m
 * i[0],s[0];i[1],s[1],i[2],s[2]...
 * Exemplo: 1,4;9,1;11,2;18,1;22,0;
 */
string calcSum(int* sequence, int size);

#endif /* SUM_H_ */
