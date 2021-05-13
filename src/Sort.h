#ifndef SORT_H
#define SORT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "registro.h"
#include "estatisticas.h"

extern bool VERBOSE;

void quick_sort(Regs **v , int n, Est *est);
void quick_sort_ordena(Regs **vet, int esq, int dir, Est *est);
void quick_sort_particao(Regs **vet, int esq, int dir, int* i, int* j, Est *est);

#endif