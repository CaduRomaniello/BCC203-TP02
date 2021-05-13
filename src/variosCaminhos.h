#ifndef VARIOSCAMINHOS_H
#define VARIOSCAMINHOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "registro.h"
#include "estatisticas.h"

extern int QUANTIDADE;
extern bool VERBOSE;
typedef struct Intercala Intercala;

int mainVariosCaminhos(FILE* input, Est* est);
void lerArmazenarDados(FILE** fitasEntrada, FILE* input, Est *est);
bool intercalacao(Intercala** intercalador, FILE** fitaLeitura, FILE** fitaEscrita, int contadorIter, Est *est);
bool podeIntercalar(Intercala **intercalador);
bool saltarFitas(Intercala **intercalador, int contadorIter);
void quick_sort_intercala(Intercala **v , int n, Est *est);
void quick_sort_ordena_intercala(Intercala **vet, int esq, int dir, Est *est);
void quick_sort_particao_intercala(Intercala **vet, int esq, int dir, int* i, int* j, Est *est);


#endif




