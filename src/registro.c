#include "registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

Regs* constructorRegs(){
    Regs* aux = malloc(sizeof(Regs));
    return aux;
}

void freeRegs(Regs* reg){
    free(reg);
}

int sizeofRegs(){
    return sizeof(Regs);
}

char* getId(Regs* reg){
    return reg->id;
}

double getNota(Regs* reg){
    return reg->nota;
}

char* getNotaString(Regs* reg){
    return reg->notaString;
}

char* getEstado(Regs* reg){
    return reg->estado;
}

char* getCidade(Regs* reg){
    return reg->cidade;
}

char* getCurso(Regs* reg){
    return reg->curso;
}


void setId(Regs* reg, char* id){
    strcpy(reg->id, id);
}

void setNota(Regs* reg, double nota){
    reg->nota = nota;
}

void setNotaString(Regs* reg, char* notaString){
    strcpy(reg->notaString, notaString);
}

void setEstado(Regs* reg, char* estado){
    strcpy(reg->estado, estado);
}

void setCidade(Regs* reg, char* cidade){
    strcpy(reg->cidade, cidade);
}

void setCurso(Regs* reg, char* curso){
    strcpy(reg->curso, curso);
}

bool lerReg(Regs* reg, FILE* arq){

    char id[9];
    double nota;
    char notaString[6];
    char estado[3];
    char cidade[51];
    char stringAux[82];
    char curso[31];
    char ignorar[7];
    
    int aux = fscanf(arq, "%[0-9] %s %s %[A-Z a-z'-]%[\r\n]", id, notaString, estado, stringAux, ignorar);
    if (aux == 0 || aux == EOF){
        return false;
    } 

    int posCidade = 0;
    int posCurso  = 0;


    for (int j = 0; j <= strlen(stringAux); j++){

        if (j < 50){
            cidade[posCidade] = stringAux[j];
            posCidade++;
        }else if(j == 50){
            cidade[posCidade] = '\0';
        }
        else if(j > 50 && j <= 80){
            curso[posCurso] = stringAux[j];
            posCurso++;
        } else{
            curso[posCurso] = '\0';
        }

    }

    nota  = atof(notaString);
    
    setId(reg, id);
    setNota(reg, nota);
    setNotaString(reg, notaString);
    setEstado(reg, estado);
    setCidade(reg, cidade);
    setCurso(reg, curso);


    return true;

}

void escreverReg(Regs* reg, FILE* arq){
    #ifdef __unix__
        fprintf(arq, "%s %s %s %s %s\r\n", getId(reg), getNotaString(reg), getEstado(reg), getCidade(reg), getCurso(reg));
    #else
        fprintf(arq, "%s %s %s %s %s\n", getId(reg), getNotaString(reg), getEstado(reg), getCidade(reg), getCurso(reg));
    #endif
}

void printaReg(Regs* reg){
    printf("id        : %s \n", reg->id);
    printf("nota      : %lf\n", reg->nota);
    printf("notaString: %s \n", reg->notaString);
    printf("estado    : %s \n", reg->estado);
    printf("cidade    : %s \n", reg->cidade);
    printf("curso     : %s \n\n", reg->curso);
}


//Sort de registro
void quick_sort_interno(Regs *v , int n, Est *est) {
    quick_sort_ordena_interno(v , 0, n-1, est);
}

void quick_sort_ordena_interno(Regs *vet, int esq, int dir, Est *est){
	int i, j;
	quick_sort_particao_interno(vet, esq, dir, &i, &j, est);

	if(esq < j){
		quick_sort_ordena_interno(vet, esq, j, est);
	}
	if(dir> i){
		quick_sort_ordena_interno(vet, i, dir, est);
	}
}

void quick_sort_particao_interno(Regs *vet, int esq, int dir, int* i, int* j, Est *est){
	double pivo; 
    Regs aux;

	*i = esq;
	*j = dir;

	pivo = (vet[(*i + *j) / 2].nota);

	do{
        incrementaComparacoes(est);
		while(pivo > (vet[*i].nota)){
            incrementaComparacoes(est);
			(*i)++;
		}

        incrementaComparacoes(est);
		while(pivo < (vet[*j].nota)){
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

void copiaRegistros(Regs *regDest, Regs* regOri){
    setId(regDest, getId(regOri));
    setNota(regDest, getNota(regOri));
    setNotaString(regDest, getNotaString(regOri));
    setEstado(regDest, getEstado(regOri));
    setCidade(regDest, getCidade(regOri));
    setCurso(regDest, getCurso(regOri));
}

void printaListaReg(Regs *reg){
    printf("%s %s %s %s %s\n", getId(reg), getNotaString(reg), getEstado(reg), getCidade(reg), getCurso(reg));
}