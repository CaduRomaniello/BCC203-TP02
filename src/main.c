#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "registro.h"
#include "variosCaminhos.h"
#include "subSelecao.h"
#include "quickSort.h"
#include "estatisticas.h"

void help();
void verifyArguments(int, int, int);
void printaEstatisticas(Est *est);
void printaDados(Est *est, FILE *arq);
void printaFita(int fita, Regs *reg);
void renomearArquivo(char *arq);
bool VERBOSE = false;
int QUANTIDADE = 0;

/**
 * Trabalho de Estrutura de dados II - UFOP - 2021
 * 
 * Professor:
 *      - Guilherme Tavares de Assis
 *
 * Alunos: 
 *      - Carlos Eduardo Gonzaga Romaniello de Souza (19.1.4003) 
 *      - Vinicius Gabriel Angelozzi Verona de Resende (19.1.4005)
 * 
*/
int main(int argc, char* argv[]){

    srand(time(NULL));

    char command[100];

    // Handle input error
    if (!(argc == 4 || argc == 5)){
        help();
    }

    int method = atoi(argv[1]);
    QUANTIDADE = atoi(argv[2]);
    int sort = atoi(argv[3]);

    verifyArguments(method, QUANTIDADE, sort);
    
    if (argc == 5){
        char* verbose = argv[4]; 
        if (strcmp(verbose, "-P") == 0){
            VERBOSE = true;
        }
    }

    // Copy file
    #ifdef __unix__
        if (sort == 1){
            strcpy(command, "cp ../Input/PROVAO_CRESCENTE.txt ../Input/PROVAO_CRESCENTE_COPIA.txt" );
            system(command);
        }
        else if(sort == 2){
            strcpy(command, "cp ../Input/PROVAO_DECRESCENTE.txt ../Input/PROVAO_DECRESCENTE_COPIA.txt" );
            system(command);
        }
        else{
            strcpy(command, "cp ../Input/PROVAO_DESORDENADO.txt ../Input/PROVAO_DESORDENADO_COPIA.txt" );
            system(command);
        }
    #else
        if (sort == 1){
            strcpy(command, "copy ..\\Input\\PROVAO_CRESCENTE.txt ..\\Input\\PROVAO_CRESCENTE_COPIA.txt" );
            system(command);
        }
        else if(sort == 2){
            strcpy(command, "copy ..\\Input\\PROVAO_DECRESCENTE.txt ..\\Input\\PROVAO_DECRESCENTE_COPIA.txt" );
            system(command);
        }
        else{
            strcpy(command, "copy ..\\Input\\PROVAO_DESORDENADO.txt ..\\Input\\PROVAO_DESORDENADO_COPIA.txt" );
            system(command);
        }
    #endif

    FILE *input = NULL;
    FILE *ArqEi = NULL;
    FILE *ArqLEs = NULL;

    Est* est = criaEst();
    FILE *arqDados;
    char printaQuick[100] = "";
    char dir[100] = "";
    int fitaDeSaida;
    Regs* reg = constructorRegs();

    if (sort == 1){
        input = fopen("../Input/PROVAO_CRESCENTE_COPIA.txt", "r+");
        strcpy(printaQuick, "../Input/PROVAO_CRESCENTE_COPIA.txt");
        if (method == 3){
            ArqEi = fopen("../Input/PROVAO_CRESCENTE_COPIA.txt", "r+");
            ArqLEs = fopen("../Input/PROVAO_CRESCENTE_COPIA.txt", "r+");
        }
    }
    else if(sort == 2){
        input = fopen("../Input/PROVAO_DECRESCENTE_COPIA.txt", "r+");
        strcpy(printaQuick, "../Input/PROVAO_DECRESCENTE_COPIA.txt");
        if (method == 3){
            ArqEi = fopen("../Input/PROVAO_DECRESCENTE_COPIA.txt", "r+");
            ArqLEs = fopen("../Input/PROVAO_DECRESCENTE_COPIA.txt", "r+");
        }
    }
    else{
        input = fopen("../Input/PROVAO_DESORDENADO_COPIA.txt", "r+");
        strcpy(printaQuick, "../Input/PROVAO_DESORDENADO_COPIA.txt");
        if (method == 3){
            ArqEi = fopen("../Input/PROVAO_DESORDENADO_COPIA.txt", "r+");
            ArqLEs = fopen("../Input/PROVAO_DESORDENADO_COPIA.txt", "r+");
        }
    }

    switch (method){
        case 1:
            /* Intercalacao de varios caminhos */

            sprintf(dir, "../dados/variosCaminhos/quantidade-%d_ordenacao-%d.txt", QUANTIDADE, sort);
            arqDados = fopen(dir, "w+");
            fitaDeSaida = mainVariosCaminhos(input, est);
            if (VERBOSE){
                printaFita(fitaDeSaida, reg);
            }

            fclose(input);
            break;
        
        case 2:
            /* Selecao por substituicao */

            sprintf(dir, "../dados/subSelecao/quantidade-%d_ordenacao-%d.txt", QUANTIDADE, sort);
            arqDados = fopen(dir, "w+");
            fitaDeSaida = mainSub(input, est);
            if (VERBOSE){
                printaFita(fitaDeSaida, reg);
            }

            fclose(input);
            break;

        case 3:
            /* Quicksort externo */

            if (VERBOSE){
                for (int i = 0; i < QUANTIDADE; i++){
                    lerReg(reg, input);
                    printaListaReg(reg);
                }
            }

            sprintf(dir, "../dados/quickSort/quantidade-%d_ordenacao-%d.txt", QUANTIDADE, sort);
            arqDados = fopen(dir, "w+");
            time_t inicio, fim;

            inicio = time(NULL);
            QuicksortExterno(&input, &ArqEi, &ArqLEs, 1, QUANTIDADE, est);
            fim = time(NULL);
            setTempoP(est, (difftime(fim, inicio)));

            fclose(input);
            if (method == 3){
                fclose(ArqEi);
                fclose(ArqLEs);
            }

            if (VERBOSE){
                input = fopen(printaQuick, "r");
                printf("\n");
                printf("===================================================================================================\n");
                printf("===================================================================================================\n\n");
                for (int i = 0; i < QUANTIDADE; i++){
                    lerReg(reg, input);
                    printaListaReg(reg);
                }
                printf("\n");
                fclose(input);
            }

            break;            
        default:
            break;
    }

    setFwriteTotal(est);
    setFreadTotal(est);
    setTempoTotal(est);
    printaEstatisticas(est);
    printaDados(est, arqDados);

    fclose(arqDados);
    freeRegs(reg);

    // Renomeando fita
    if (method == 1 || method == 2){
        if (fitaDeSaida % 2 == 0 || QUANTIDADE <= TAM_MEM){ //fita 1
            renomearArquivo("./Fitas/fita1.txt");
        }
        else{ //fita 21
            renomearArquivo("./Fitas/fita21.txt");
        }
    }
    else{
        if (sort == 1){
            renomearArquivo("../Input/PROVAO_CRESCENTE_COPIA.txt");
        }
        else if(sort == 2){
            renomearArquivo("../Input/PROVAO_DECRESCENTE_COPIA.txt");
        }
        else{
            renomearArquivo("../Input/PROVAO_DESORDENADO_COPIA.txt");
        }
    }
    

    return 0;

}

/**
 * Displays help menu.
*/
void help(){
    printf("WARNING - O programa deve ser executado com 3 ou 4 parametros!\n\n");
    printf("Sintaxe: ./pesquisa <metodo> <qntd de alunos> <ordenacao> [-P]\n");
    printf("- metodo <1 a 3>    | Intercalação de vários caminhos '2f' fitas (1), Seleção por substituição (2), QuickSort Externo (3).\n");
    printf("- quantidade <int>  | 100, 1000, 10000, 100000, 471705.\n");
    printf("- ordenacao <1 a 3> | arquivo ordenado ascendentemente (1), arquivo ordenado descendentemente (2), arquivo desordenado (3).\n");
    printf("- -P                | habilita print.\n");
}

void verifyArguments(int method, int quantity, int sort){

    if(method < 1 || method > 3){
        printf("ERRO          : parâmetro <metodo> inválido!\n");
        printf("Valor esperado: {1, 2, 3}\n");
        printf("Valor recebido: %d\n", method);
        exit(0);
    }

    if(!(quantity == 100 || quantity == 1000 || quantity == 10000 || quantity == 100000 || quantity == 471705)){
        printf("ERRO          : parâmetro <qntd de alunos> inválido!\n");
        printf("Valor esperado: {100, 1000, 10000, 100000, 471705}\n");
        printf("Valor recebido: %d\n", quantity);
        exit(0);
    }

    if(sort < 1 || sort > 3){
        printf("ERRO          : parâmetro <ordenacao> inválido!\n");
        printf("Valor esperado: {1, 2, 3}\n");
        printf("Valor recebido: %d\n", sort);
        exit(0);
    }

}

void printaEstatisticas(Est *est){

    printf("\n----------Estatisticas----------\n");
    printf("Leituras totais   : %d\n", getFreadTotal(est));
    printf("Escritas totais   : %d\n", getFwriteTotal(est));
    printf("Comparacoes totais: %d\n", getComparacoes(est));
    printf("Tempo total       : %.2lf\n", getTempoTotal(est));
    printf("--------------------------------\n\n");

}

void printaDados(Est *est, FILE *arq){

    fprintf(arq, "Leituras Criacao  : %d\n", getFreadC(est));
    fprintf(arq, "Escritas Criacao  : %d\n", getFwriteC(est));
    fprintf(arq, "Tempo Criacao     : %.2lf\n\n", getTempoC(est));

    fprintf(arq, "Leituras Ordenacao: %d\n", getFreadP(est));
    fprintf(arq, "Escritas Ordenacao: %d\n", getFwriteP(est));
    fprintf(arq, "Tempo Ordenacao   : %.2lf\n\n", getTempoP(est));

    fprintf(arq, "Leituras totais   : %d\n", getFreadTotal(est));
    fprintf(arq, "Escritas totais   : %d\n", getFwriteTotal(est));
    fprintf(arq, "Comparacoes totais: %d\n", getComparacoes(est));
    fprintf(arq, "Tempo total       : %.2lf\n", getTempoTotal(est));

}

void printaFita(int fita, Regs *reg){

    if (QUANTIDADE <= TAM_MEM){ //fita 1
        FILE *arq = fopen("Fitas/fita1.txt", "r");
        printf("\n");
        printf("===================================================================================================\n");
        printf("===================================================================================================\n\n");
        for (int i = 0; i < QUANTIDADE; i++){
            lerReg(reg, arq);
            printaListaReg(reg);
        }
        printf("\n");
        fclose(arq);
        return;
    }

    if (fita % 2 == 0){ //fita 1
        FILE *arq = fopen("Fitas/fita1.txt", "r");
        printf("\n");
        printf("===================================================================================================\n");
        printf("===================================================================================================\n\n");
        for (int i = 0; i < QUANTIDADE; i++){
            lerReg(reg, arq);
            printaListaReg(reg);
        }
        fclose(arq);
        printf("\n");
    }
    else{ //fita 21
        FILE *arq = fopen("Fitas/fita21.txt", "r");
        printf("\n");
        printf("===================================================================================================\n");
        printf("===================================================================================================\n\n");
        for (int i = 0; i < QUANTIDADE; i++){
            lerReg(reg, arq);
            printaListaReg(reg);
        }
        fclose(arq);
        printf("\n");
    }

}

void renomearArquivo(char *arq){
    int renomeado = -1;

    renomeado = rename(arq, "./Resultado/PROVAO_RESULTADO.txt");

    if (renomeado == -1){
        int removeu = remove("Resultado/PROVAO_RESULTADO.txt");

        if (removeu != 0){
            printf("Erro ao remover arquivo Resultado/PROVAO_RESULTADO.txt\n");
        
        }
        else{
            renomeado = rename(arq, "./Resultado/PROVAO_RESULTADO.txt");

            if (renomeado == -1){
                char *erro = "";
                sprintf(erro, "Erro ao renomear arquivo %s", arq);
                printf("%s\n", erro);
            }
        }
    }
}