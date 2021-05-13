#include "subSelecao.h"
#include "registro.h"
#include "Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#define DOUBLE_MAX (double) LONG_MAX

typedef struct Sub{
    Regs* reg;
    FILE* arq;
    bool fim;
    double notaReg;
    int pos;
}Sub;

int mainSub(FILE* input, Est *est){

    time_t inicio, fim;

    FILE* fitasEntrada[QNTD_FITAS];
    FILE* fitasSaida[QNTD_FITAS];

    // Aloca struct de intercalação
    Sub **intercalador = malloc(TAM_MEM * sizeof(Sub*));
    for (int i = 0; i < TAM_MEM; i++){
        intercalador[i] = malloc(sizeof(Sub));
        intercalador[i]->reg = constructorRegs();
    }

    char nomeArq[17];
    for (int i = 0; i < QNTD_FITAS; i++){ /* Abrindo todas as fitas de entrada */
        strcpy(nomeArq, "");
        sprintf(nomeArq, "Fitas/fita%d.txt", i + 1);

        fitasEntrada[i] = fopen(nomeArq, "w+");

        intercalador[i]->arq = fitasEntrada[i];
        intercalador[i]->fim = false;
        intercalador[i]->notaReg = DOUBLE_MAX - 1;
    }

    // Aplica substituição
    inicio = time(NULL);
    lerArmazenarDadosSub(fitasEntrada, input, intercalador, est);
    fim = time(NULL);
    setTempoC(est, (fim - inicio));
    
    for(int i = 0; i < QNTD_FITAS; i++){
        fclose(fitasEntrada[i]);
    }

    // Reiniciando o intercalador
    for (int i = 0; i < TAM_MEM; i++){
        freeRegs(intercalador[i]->reg);
        free(intercalador[i]);
    }
    free(intercalador);

    intercalador = malloc(TAM_MEM * sizeof(Sub*));
    for (int i = 0; i < TAM_MEM; i++){
        intercalador[i] = malloc(sizeof(Sub));
        intercalador[i]->reg = constructorRegs();
        intercalador[i]->pos = i;
        intercalador[i]->notaReg = DOUBLE_MAX;
    }

    // Intercalação
    bool terminou = false;
    int contadorIter = 1;
    inicio = time(NULL);
    while((!terminou) && (QUANTIDADE > TAM_MEM)){

        if (contadorIter % 2 != 0){
            for (int i = 0; i < QNTD_FITAS; i++){ /* Abrindo todas as fitas disponiveis */
                strcpy(nomeArq, "");
                sprintf(nomeArq, "Fitas/fita%d.txt", i + 1);
                fitasEntrada[i] = fopen(nomeArq, "r");

                strcpy(nomeArq, "");
                sprintf(nomeArq, "Fitas/fita%d.txt", i + 21);
                fitasSaida[i] = fopen(nomeArq, "w+");

                intercalador[i]->arq = fitasEntrada[i];
                intercalador[i]->fim = false;
            }
            
            // Intercala
            terminou = intercalacaoSub(intercalador, fitasEntrada, fitasSaida, contadorIter, est);
            contadorIter++;
        }
        else{
            for (int i = 0; i < QNTD_FITAS; i++){ /* Abrindo todas as fitas dsponiveis */
                strcpy(nomeArq, "");
                sprintf(nomeArq, "Fitas/fita%d.txt", i + 1);
                fitasEntrada[i] = fopen(nomeArq, "w+");

                strcpy(nomeArq, "");
                sprintf(nomeArq, "Fitas/fita%d.txt", i + 21);
                fitasSaida[i] = fopen(nomeArq, "r");

                intercalador[i]->arq = fitasSaida[i];
                intercalador[i]->fim = false;
            }
            
            // Intercala
            terminou = intercalacaoSub(intercalador, fitasSaida, fitasEntrada, contadorIter, est);
            contadorIter++;
        }

        for (int i = 0; i < QNTD_FITAS; i++){
            fclose(fitasEntrada[i]);
            fclose(fitasSaida[i]);
        }

    }
    fim = time(NULL);
    setTempoP(est, (fim - inicio));

    // Libera struct intercalação 
    for (int i = 0; i < TAM_MEM; i++){
        freeRegs(intercalador[i]->reg);
        free(intercalador[i]);
    }
    free(intercalador);

    return contadorIter;

}

void lerArmazenarDadosSub(FILE** fitasEntrada, FILE* input, Sub** intercalador, Est *est){

    int contadorFitas = 0;
    int contadorLidos = 0;
    bool leu;
    double notaEscrita;

    // Le os primeiros 20 registros
    for (int i = 0; i < TAM_MEM; i++){

        //verificar a variavel leu
        leu = lerReg(intercalador[i]->reg, input);
        incrementaFreadC(est);
        if (VERBOSE){
            printaListaReg(intercalador[i]->reg);
        }
        if (!leu){
            printf("Erro na leitura\n");
        }
        intercalador[i]->notaReg = getNota(intercalador[i]->reg);
        contadorLidos++;

    }

    //heap
    heapSort(intercalador, TAM_MEM, est);

    for (int i = 0; i < QUANTIDADE; i++){

        if (intercalador[0]->notaReg == DOUBLE_MAX){
            fprintf(fitasEntrada[contadorFitas], "--\r\n");
            incrementaFwriteC(est);
            
            if (contadorFitas == QNTD_FITAS - 1){
                contadorFitas = 0;
            }
            else{
                contadorFitas++;
            }

            // Retira marca
            for (int r = 0; r < TAM_MEM; r++){
                intercalador[r]->notaReg = getNota(intercalador[r]->reg);
            }
            heapSort(intercalador, TAM_MEM, est);
        }

        escreverReg(intercalador[0]->reg, fitasEntrada[contadorFitas]);
        incrementaFwriteC(est);

        // Item escrito
        if (contadorLidos >= QUANTIDADE){
            notaEscrita = DOUBLE_MAX;
        }
        else{
            notaEscrita = intercalador[0]->notaReg;
        }

        if (contadorLidos < QUANTIDADE){
            leu = lerReg(intercalador[0]->reg, input);
            incrementaFreadC(est);
            if (!leu){
                printf("Erro na leitura\n");
            }
            contadorLidos++;
            if(VERBOSE){
                printaListaReg(intercalador[0]->reg);
            }
        }
        
        if (getNota(intercalador[0]->reg) < notaEscrita || (contadorLidos > QUANTIDADE)){
            intercalador[0]->notaReg = DOUBLE_MAX;
        }
        else{
            intercalador[0]->notaReg = getNota(intercalador[0]->reg);
        }

        if (contadorLidos == QUANTIDADE){
            contadorLidos++;
        }
        heapSort(intercalador, TAM_MEM, est);

    }

    //evitando warnings
    if (leu){}

}

bool intercalacaoSub(Sub** intercalador, FILE** fitaLeitura, FILE** fitaEscrita, int contadorIter, Est *est){

    int contFita = 0;
    bool conseguiuLer = false;
    char tracos[7];

    // Se houver apenas 1 fita não vazia, terminou intercalação
    int ignorar;
    int retornoFScanf = fscanf(fitaLeitura[1], "%d", &ignorar);
    incrementaFreadP(est);
    if (retornoFScanf == EOF || retornoFScanf == 0){
        return true;
    }
    rewind(fitaLeitura[1]);

    // Preenche intercalador
    FILE* arqAux;
    for (int i = 0; i < TAM_MEM; i++){
        arqAux = intercalador[i]->arq;
        if (!(lerReg(intercalador[i]->reg, arqAux))){
            setNota(intercalador[i]->reg, DOUBLE_MAX);
            intercalador[i]->notaReg = DOUBLE_MAX;
            intercalador[i]->fim = true;
        }
        else{
            intercalador[i]->notaReg = getNota(intercalador[i]->reg);
        }
        incrementaFreadP(est);
    }

    // Intercala
    while(podeIntercalarSub(intercalador)){


        heapSort(intercalador , TAM_MEM, est);
        escreverReg(intercalador[0]->reg, fitaEscrita[contFita]);
        incrementaFwriteP(est);

        // Trata fim de bloco
        if (!(lerReg(intercalador[0]->reg, intercalador[0]->arq))){
            if (fscanf(intercalador[0]->arq, "%[-\r\n]", tracos)){
                conseguiuLer = lerReg(intercalador[0]->reg, intercalador[0]->arq);
                incrementaFreadP(est);
                if (conseguiuLer){
                    intercalador[0]->fim = false;
                    intercalador[0]->notaReg = DOUBLE_MAX;
                }
                else{
                    intercalador[0]->fim = true;
                    intercalador[0]->notaReg = DOUBLE_MAX;
                    setNota(intercalador[0]->reg, DOUBLE_MAX);
                }
            }
            else{
                intercalador[0]->fim = true;
                intercalador[0]->notaReg = DOUBLE_MAX;
                setNota(intercalador[0]->reg, DOUBLE_MAX);
            }
            incrementaFreadP(est);
        }
        else{
            intercalador[0]->fim = false;
            intercalador[0]->notaReg = getNota(intercalador[0]->reg);
        }
        incrementaFreadP(est);

        if (saltarFitasSub(intercalador)){
            fprintf(fitaEscrita[contFita], "--\r\n");
            incrementaFwriteP(est);
            contFita++;
            for (int i = 0; i < TAM_MEM; i++){
                intercalador[i]->notaReg = getNota(intercalador[i]->reg);
            }
            if (contFita > QNTD_FITAS - 1){
                contFita = 0;
            }
        }

    }

    return false;

}


bool podeIntercalarSub(Sub **intercalador){
    bool aux = true;

    for (int i = 0; i < TAM_MEM; i++){
        aux = aux && intercalador[i]->fim;
    }
    
    return !aux;
}

bool saltarFitasSub(Sub **intercalador){
    bool retorno = true;

    for (int i = 0; i < TAM_MEM; i++){
        retorno = retorno && (intercalador[i]->notaReg == DOUBLE_MAX);
    }
    return retorno;
}

// Heap Sort para Substituição1
void heapSort(Sub **v, int n, Est *est) {
    Sub* aux;
    heapConstroi(v, n, est);
    
    while (n > 1) {
        aux = v[n-1];
        v[n-1] = v[0];
        v[0] = aux;
        n--;
        
        heapRefaz(v, 0, n-1, est); // refaz o heap
    }
}

void heapConstroi(Sub **v, int n, Est *est) {
    int esq;
    esq = (n / 2) - 1; // esq = nó anterior ao primeiro nó folha do heap
    
    while (esq >= 0) {
        heapRefaz(v, esq, n-1, est);
        esq--;
    }
}

void heapRefaz(Sub **v, int esq, int dir, Est *est) {
    int i = esq;
    int j = i*2 + 1; // j = primeiro filho de i

    Sub *aux = v[i]; // aux = no i (pai de j)

    while (j <= dir) {
        incrementaComparacoes(est);
        if (j < dir && v[j]->notaReg < v[j+ 1]->notaReg){
            j++; // j recebe o outro filho de i
        }

        incrementaComparacoes(est);
        if (aux->notaReg >= v[j]->notaReg){
            break; // heap foi refeito corretam ente
        }

        v[i] = v[j];
        i = j;
        j = i*2 + 1; // j = primeiro filho de i
    }
    
    v[i] = aux;
}