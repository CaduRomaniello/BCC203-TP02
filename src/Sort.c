#include "Sort.h"

void quick_sort(Regs **v , int n, Est *est) {
    quick_sort_ordena(v , 0, n-1, est);
}

void quick_sort_ordena(Regs **vet, int esq, int dir, Est *est){
	int i, j;
	quick_sort_particao(vet, esq, dir, &i, &j, est);

	if(esq < j){
		quick_sort_ordena(vet, esq, j, est);
	}
	if(dir> i){
		quick_sort_ordena(vet, i, dir, est);
	}
}

void quick_sort_particao(Regs **vet, int esq, int dir, int* i, int* j, Est *est){
	double pivo; 
    Regs *aux;

	*i = esq;
	*j = dir;

	pivo = getNota((vet[(*i + *j) / 2]));

	do{
		incrementaComparacoes(est);
		while(pivo > getNota((vet[*i]))){
			incrementaComparacoes(est);
			(*i)++;
		}

		incrementaComparacoes(est);
		while(pivo < getNota((vet[*j]))){
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