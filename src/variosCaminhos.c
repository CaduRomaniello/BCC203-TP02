#include "variosCaminhos.h"
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

typedef struct Intercala{
    Regs* reg;
    FILE* arq;
    int qntdLidos;
    bool fim;
    double notaReg;
}Intercala;


int mainVariosCaminhos(FILE* input, Est* est){

    time_t inicio, fim;

    FILE* fitasEntrada[QNTD_FITAS];
    FILE* fitasSaida[QNTD_FITAS];

    char nomeArq[17];
    for (int i = 0; i < QNTD_FITAS; i++){ /* Abrindo todas as fitas de entrada */
        strcpy(nomeArq, "");
        sprintf(nomeArq, "Fitas/fita%d.txt", i + 1);

        fitasEntrada[i] = fopen(nomeArq, "w+");
    }


    inicio = time(NULL);
    lerArmazenarDados(fitasEntrada, input, est);
    fim = time(NULL);
    setTempoC(est, (fim - inicio));

    for(int i = 0; i < QNTD_FITAS; i++){
        fclose(fitasEntrada[i]);
    }
    
    bool terminou = false;
    int contadorIter = 1;
    
    Regs* regMax = constructorRegs();
    setNota(regMax, DOUBLE_MAX);

    // Aloca struct de intercalação
    Intercala **intercalador = malloc(TAM_MEM * sizeof(Intercala*));
    for (int i = 0; i < TAM_MEM; i++){
        intercalador[i] = malloc(sizeof(Intercala));
        intercalador[i]->reg = constructorRegs();
    }

    // Intercalação
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
                intercalador[i]->qntdLidos = 0;
                intercalador[i]->fim = false;
            }
            
            // Intercala
            terminou = intercalacao(intercalador, fitasEntrada, fitasSaida, contadorIter, est);
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
                intercalador[i]->qntdLidos = 0;
                intercalador[i]->fim = false;
            }
            
            // Intercala
            terminou = intercalacao(intercalador, fitasSaida, fitasEntrada, contadorIter, est);
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

void lerArmazenarDados(FILE** fitasEntrada, FILE* input, Est *est){

    int contador      = 0;
    int contadorRegs  = 0;
    int contadorFitas = 0;
    bool leu;

    Regs** registros  = malloc(TAM_MEM * sizeof(Regs*));
    for (int i = 0; i < TAM_MEM; i++){
        registros[i] = constructorRegs();
    }

    // Lendo registros do Input
    for (int i = 0; i < QUANTIDADE; i++){

        leu = lerReg(registros[contador], input);
        incrementaFreadC(est);
        if (!leu){ 
            puts("ERRO DE LEITURA - lerArmazenarDados"); 
            exit(1);
        }
        if (VERBOSE){
            printaListaReg(registros[contador]);
        }
        
        contador++;
        contadorRegs++;

        if (contador == TAM_MEM || contadorRegs == QUANTIDADE){
            //ordenar e escrever nas fitas
            quick_sort(registros, contador, est);

            for (int k = 0; k < contador; k++){
                escreverReg(registros[k], fitasEntrada[contadorFitas]);
                incrementaFwriteC(est);
            }

            contador = 0;
            contadorFitas++;
            if (contadorFitas > QNTD_FITAS - 1){
                contadorFitas = 0;
            }
        }
    }

    for (int i = 0; i < TAM_MEM; i++){
        freeRegs(registros[i]);
    }
    free(registros);
    

}

bool intercalacao(Intercala** intercalador, FILE** fitaLeitura, FILE** fitaEscrita, int contadorIter, Est *est){

    int contFita = 0;

    // Se houver apenas 1 fita não vazia, terminou intercalação
    int ignorar;
    int retornoFScanf = fscanf(fitaLeitura[1], "%d", &ignorar);
    incrementaFreadP(est);
    if (retornoFScanf == 0 || retornoFScanf == EOF){
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

    while(podeIntercalar(intercalador)){

        quick_sort_intercala(intercalador , TAM_MEM, est);
        escreverReg(intercalador[0]->reg, fitaEscrita[contFita]);
        incrementaFwriteP(est);
        intercalador[0]->qntdLidos++;

        if (!(lerReg(intercalador[0]->reg, intercalador[0]->arq))){
            setNota(intercalador[0]->reg, DOUBLE_MAX);
            intercalador[0]->notaReg = DOUBLE_MAX;
            intercalador[0]->fim = true;
        }
        else{
            intercalador[0]->notaReg = getNota(intercalador[0]->reg);
        }
        incrementaFreadP(est);
        if (intercalador[0]->qntdLidos == (int) ceil(pow(20, contadorIter))){
            intercalador[0]->notaReg = DOUBLE_MAX;
        }

        if (saltarFitas(intercalador, contadorIter)){
            contFita++;
            for (int i = 0; i < TAM_MEM; i++){
                intercalador[i]->qntdLidos = 0;
                intercalador[i]->notaReg = getNota(intercalador[i]->reg);
            }
            if (contFita == QNTD_FITAS){
                contFita = 0;
            }
        }
    }

    return false;

}

bool podeIntercalar(Intercala **intercalador){
    bool aux = true;

    for (int i = 0; i < TAM_MEM; i++){
        aux = aux && intercalador[i]->fim;
    }
    
    return !aux;
}

bool saltarFitas(Intercala **intercalador, int contadorIter){
    bool retorno = true;
    bool lidos;

    for (int i = 0; i < TAM_MEM; i++){
        if (intercalador[i]->qntdLidos == (int) ceil(pow(20, contadorIter))){
            lidos = true;
        }
        else{
            lidos = false;
        }
        retorno = retorno && (intercalador[i]->fim || lidos);
    }
    return retorno;
}


//Sort para o tipo Intercala
void quick_sort_intercala(Intercala **v , int n, Est* est) {
    quick_sort_ordena_intercala(v , 0, n-1, est);
}

void quick_sort_ordena_intercala(Intercala **vet, int esq, int dir, Est* est){
	int i, j;
	quick_sort_particao_intercala(vet, esq, dir, &i, &j, est);

	if(esq < j){
		quick_sort_ordena_intercala(vet, esq, j, est);
	}
	if(dir> i){
		quick_sort_ordena_intercala(vet, i, dir, est);
	}
}

void quick_sort_particao_intercala(Intercala **vet, int esq, int dir, int* i, int* j, Est* est){
	double pivo; 
    Intercala *aux;

	*i = esq;
	*j = dir;

	pivo = (vet[(*i + *j) / 2]->notaReg);

	do{
        incrementaComparacoes(est);
		while(pivo > (vet[*i]->notaReg)){
            incrementaComparacoes(est);
			(*i)++;
		}

        incrementaComparacoes(est);
		while(pivo < (vet[*j]->notaReg)){
            incrementaComparacoes(est);
			(*j)--;
		}
        
		if(*i <= *j){
			aux = vet[*i];
			vet[*i] = vet[*j];
			vet[*j] = aux;
			(*i)++;
			(*j)--;
		}
	}while(*i <= *j);
}