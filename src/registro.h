#ifndef REGISTRO_H
#define REGISTRO_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "estatisticas.h"
#define TAM_MEM 20
#define QNTD_FITAS 20

typedef struct registry {
    char id[9];
    double nota;
    char notaString[6];
    char estado[3];
    char cidade[51];
    char curso[31];
}Regs;

extern int QUANTIDADE;
extern bool VERBOSE;

Regs* constructorRegs();
void freeRegs(Regs* reg);

int sizeofRegs();
char* getId(Regs* reg);
double getNota(Regs* reg);
char* getNotaString(Regs* reg);
char* getEstado(Regs* reg);
char* getCidade(Regs* reg);
char* getCurso(Regs* reg);

void setId(Regs* reg, char* id);
void setNota(Regs* reg, double nota);
void setNotaString(Regs* reg, char* notaString);
void setEstado(Regs* reg, char* estado);
void setCidade(Regs* reg, char* cidade);
void setCurso(Regs* reg, char* curso);

bool lerReg(Regs* reg, FILE* arq);
void escreverReg(Regs* reg, FILE* arq);
void printaReg(Regs* reg);

void quick_sort_interno(Regs *v , int n, Est *est);
void quick_sort_ordena_interno(Regs *vet, int esq, int dir, Est *est);
void quick_sort_particao_interno(Regs *vet, int esq, int dir, int* i, int* j, Est *est);

void copiaRegistros(Regs *regDest, Regs* regOri);
void printaListaReg(Regs *reg);

#endif