#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
extern bool VERBOSE;

typedef struct estatistica{

    // Criacao do arquivo
    int fwriteC;
    int freadC;
    double tempoC;

    // Pesquisa do arquivo
    int fwriteP;
    int freadP;
    double tempoP;

    // Total
    int fwriteTotal;
    int freadTotal;
    int comparacoes;
    double tempoTotal;

} Est;

// Constructor
Est* criaEst();
void freeEst(Est* est);

// Set
void setFwriteC(Est* est, int x);
void setFreadC(Est* est, int x);
void setTempoC(Est* est, double x);

void setFwriteP(Est* est, int x);
void setFreadP(Est* est, int x);
void setTempoP(Est* est, double x);

void setFwriteTotal(Est* est);
void setFreadTotal(Est* est);
void setComparacoes(Est* est, int x);
void setTempoTotal(Est* est);

// Get
int getFwriteC(Est* est);
int getFreadC(Est* est);
double getTempoC(Est* est);

int getFwriteP(Est* est);
int getFreadP(Est* est);
double getTempoP(Est* est);

int getFwriteTotal(Est* est);
int getFreadTotal(Est* est);
int getComparacoes(Est* est);
double getTempoTotal(Est* est);

// Increment
void incrementaFwriteC(Est* est);
void incrementaFreadC(Est* est);

void incrementaFwriteP(Est* est);
void incrementaFreadP(Est* est);

void incrementaFwriteTotal(Est* est);
void incrementaFreadTotal(Est* est);
void incrementaComparacoes(Est* est);

#endif