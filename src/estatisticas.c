#include <stdio.h>
#include <time.h>
#include "estatisticas.h"

Est* criaEst(){
    Est* aux = malloc(sizeof(Est));

    aux->fwriteC = 0;
    aux->freadC = 0;
    aux->tempoC = 0.0;

    aux->fwriteP = 0;
    aux->freadP = 0;
    aux->tempoP = 0.0;

    aux->fwriteTotal = 0;
    aux->freadTotal = 0;
    aux->tempoTotal = 0.0;
    aux->comparacoes = 0;

    return aux;
}

void freeEst(Est* est){
    free(est);
}

// Gets
int getFwriteC(Est* est){
    return est->fwriteC;
}
int getFreadC(Est* est){
    return est->freadC;
}
double getTempoC(Est* est){
    return est->tempoC;
}
int getFwriteP(Est* est){
    return est->fwriteP;
}
int getFreadP(Est* est){
    return est->freadP;
}
double getTempoP(Est* est){
    return est->tempoP;
}
int getFwriteTotal(Est* est){
    return est->fwriteTotal;
}
int getFreadTotal(Est* est){
    return est->freadTotal;
}
int getComparacoes(Est* est){
    return est->comparacoes;
}
double getTempoTotal(Est* est){
    return est->tempoTotal;
}

// Sets
void setFwriteC(Est* est, int x){
    est->fwriteC = x;
}
void setFreadC(Est* est, int x){
    est->freadC = x;
}
void setTempoC(Est* est, double x){
    est->tempoC = x;
}
void setFwriteP(Est* est, int x){
    est->fwriteP = x;
}
void setFreadP(Est* est, int x){
    est->freadP = x;
}
void setTempoP(Est* est, double x){
    est->tempoP = x;
}
void setFwriteTotal(Est* est){
    est->fwriteTotal = est->fwriteC + est->fwriteP;
}
void setFreadTotal(Est* est){
    est->freadTotal = est->freadC + est->freadP;
}
void setComparacoes(Est* est, int x){
    est->comparacoes = x;
}
void setTempoTotal(Est* est){
    est->tempoTotal = est->tempoC + est->tempoP;
}

// Increments
void incrementaFwriteC(Est* est){
    est->fwriteC++;
}
void incrementaFreadC(Est* est){
    est->freadC++;
}
void incrementaFwriteP(Est* est){
    est->fwriteP++;
}
void incrementaFreadP(Est* est){
    est->freadP++;
}
void incrementaFwriteTotal(Est* est){
    est->fwriteTotal++;
}
void incrementaFreadTotal(Est* est){
    est->freadTotal++;
}
void incrementaComparacoes(Est* est){
    est->comparacoes++;
}