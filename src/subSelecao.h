#ifndef SUBSELECAO_H
#define SUBSELECAO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "registro.h"
#include "estatisticas.h"

extern int QUANTIDADE;
extern bool VERBOSE;

typedef struct Sub Sub;

int mainSub(FILE* input, Est *est);
void lerArmazenarDadosSub(FILE** fitasEntrada, FILE* input, Sub** intercalador, Est *est);
bool intercalacaoSub(Sub **intercalador, FILE** fitaLeitura, FILE** fitaEscrita, int contadorIter, Est *est);
void heapSort(Sub **v, int n, Est *est);
void heapConstroi(Sub **v, int n, Est *est);
void heapRefaz(Sub **v, int esq, int dir, Est *est);
bool podeIntercalarSub(Sub **intercalador);
bool saltarFitasSub(Sub **intercalador);

#endif