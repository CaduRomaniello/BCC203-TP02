#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "registro.h"
#include "estatisticas.h"

extern bool VERBOSE;

#define DOUBLE_MAX (double) LONG_MAX

// Tamanho em bytes da struct Regs
#define SIZEOF_REG (101 * sizeof(char))

// Signature
void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, Est *est);
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, Regs *Area, int Esq, int Dir, int *i, int *j, Est *est);
void InserirArea(Regs *Area, Regs *UltLido, int *NRArea, Est *est);
void EscreveMax(FILE **ArqLEs, Regs R, int *Es, Est *est);
void EscreveMin(FILE **ArqEi, Regs R, int *Ei, Est *est);
int RetiraMax(Regs *Area, Regs *R, int *NRArea, Est *est);
int RetiraMin(Regs *Area, Regs *R, int *NRArea, Est *est);
void LeSup(FILE **ArqLEs, Regs *UltLido, int *Ls, bool *OndeLer, Est *est);
void LeInf(FILE **ArqLi, Regs *UltLido, int *Li, bool *OndeLer, Est *est);
int ObterNumCelOcupadas(Regs *area, Est *est);
int RetiraUltimo(Regs *Area, Regs *R, Est *est);
int RetiraPrimeiro(Regs *Area, Regs *R, Est *est);
void InsereItem(Regs *UltLido, Regs *Area, Est *est);

#endif