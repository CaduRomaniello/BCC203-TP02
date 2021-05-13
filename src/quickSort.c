#include "quickSort.h"

// Source
// ArqLEs gerencia Ls e Es, mesma coisa que ArqLi ArqEi
void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, Est *est){
    int i, j;

    /* Area de armazenamento interna  - Pivô*/
    Regs* area  = malloc(TAM_MEM * sizeofRegs());
    for (int i = 0; i < TAM_MEM; i++){
        setNota(&(area[i]), DOUBLE_MAX);
    }

    // Verifica se é necessário ordenação
    if (Dir - Esq < 1){
        free(area);
        return;
    }

    // Cria a área vazia
    Particao(ArqLi, ArqEi, ArqLEs, area, Esq, Dir, &i, &j, est);

    // Olha quantidade de elementos entre i e esq /// j e dir
    if (i - Esq < Dir - j)
    {
        /* Ordene primeiro o sub-arquivo menor */
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, est);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, est);
    }
    else
    {
        /* Ordene primeiro o sub-arquivo maior */
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, est);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, est);
    }

    free(area);

}

// Faz todo o processo do QuickSort externo
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, Regs *Area, int Esq, int Dir, int *i, int *j, Est *est){

    // Controladores de escrita/leitura
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0;
    double Linf = -DOUBLE_MAX, Lsup = DOUBLE_MAX;
    int pos;

    bool OndeLer = true;
    Regs UltLido, R;

    // Inicializa as variaveis ArqLi e ArqEi no arquivo
    fseek(*ArqEi, (Ei - 1) * SIZEOF_REG, SEEK_SET);
    fseek(*ArqLi, (Li - 1) * SIZEOF_REG, SEEK_SET);

    *i = Esq - 1;
    *j = Dir + 1;

    // Inicializa partição
    while (Ls >= Li)
    {
        // Faz a leitura alternada até que sobre uma posição no pivô
        if (NRArea < TAM_MEM - 1)
        {
            if (OndeLer){
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, est);
            }
            else{
                LeInf(ArqLi, &UltLido, &Li, &OndeLer, est);
            }
            
            InserirArea(Area, &UltLido, &NRArea, est);

            continue;
        }

        // Inicia condicional de Linf < chave || Lsup > chave

        // Condicional de refazer uma leitura do mesmo lado caso seja necessário
        // Para não deixar Es > Ls
        if (Ls == Es)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, est);

        else if (Li == Ei)
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, est);

        // Caso não seja necessário as condicoes acima, continua alternância
        else if (OndeLer)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, est);

        else
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, est);

        // Se a chave for > limite superior, atualiza o j, escreve no sub-arquivo A2
        incrementaComparacoes(est);
        if (getNota(&UltLido) > Lsup)
        {
            *j = Es;

            EscreveMax(ArqLEs, UltLido, &Es, est);
            continue;
        }

        // Se a chave for < limite superior, atualiza o i, escreve no sub-arquivo A1
        incrementaComparacoes(est);
        if (getNota(&UltLido) < Linf)
        {
            *i = Ei;

            EscreveMin(ArqEi, UltLido, &Ei, est);
            continue;
        }

        // Se não for escrito no sub-arquivo, escrevemos no pivô
        InserirArea(Area, &UltLido, &NRArea, est);

        // Analiza qual sub-arquivo tem menos elementos e retiramos/escrevemos o ítem baseado no nro de items do sub-arquivo
        if (Ei - Esq < Dir - Es)
        {
            pos = RetiraMin(Area, &R, &NRArea, est);
            setNota(&(Area[pos]), DOUBLE_MAX);
            EscreveMin(ArqEi, R, &Ei, est);

            Linf = getNota(&R);
        }
        else
        {
            pos = RetiraMax(Area, &R, &NRArea, est);
            setNota(&(Area[pos]), DOUBLE_MAX);
            EscreveMax(ArqLEs, R, &Es, est);

            Lsup = getNota(&R);
        }
    }

    // Após toda a partição feita, pegamos os elementos do pivô e voltamos para o arquivo,
    // escrevendo o menor elemento do pivô ao sub-arquivo A1
    while (Ei <= Es)
    {
        pos = RetiraMin(Area, &R, &NRArea, est);
        setNota(&(Area[pos]), DOUBLE_MAX);
        EscreveMin(ArqEi, R, &Ei, est);
    }

}

void InserirArea(Regs *Area, Regs *UltLido, int *NRArea, Est *est){

    /* Insere UltLido de forma ordenada na Area*/
    InsereItem(UltLido, Area, est);          // Insere de forma ordenada no pivô
    *NRArea = ObterNumCelOcupadas(Area, est); // Retorna nro de posicoes ocupadas do pivô

}

// Escreve do lado Superior
void EscreveMax(FILE **ArqLEs, Regs R, int *Es, Est *est){

    // Da mesma forma que no LeSup, por ArqLEs controlar leitura e escrita
    // devemos dar um fseek antes, escrever e decrementar o *Es
    fseek(*ArqLEs, (*Es - 1) * SIZEOF_REG, SEEK_SET);
    escreverReg(&R, *ArqLEs);
    incrementaFwriteP(est);

    (*Es)--;

}

// Escreve do lado Inferior
void EscreveMin(FILE **ArqEi, Regs R, int *Ei, Est *est){

    escreverReg(&R, *ArqEi);
    incrementaFwriteP(est);
    (*Ei)++;

}

// Trabalha para retirar o maior elemento do pivô
int RetiraMax(Regs *Area, Regs *R, int *NRArea, Est *est){
    int pos;
    pos = RetiraUltimo(Area, R, est);               // Retira da ultima posicao do pivo
    *NRArea = ObterNumCelOcupadas(Area, est); // Retorna nro de elementos no pivô
    return pos;

}

// Trabalha para retirar o menor elemento do pivô
int RetiraMin(Regs *Area, Regs *R, int *NRArea, Est *est){
    int pos;
    pos = RetiraPrimeiro(Area, R, est);             // Retira da primeira posicao do pivo
    *NRArea = ObterNumCelOcupadas(Area, est); // Retorna nro de elementos no pivô
    return pos;

}

// A partir de ArqLEs, le um item e decrementa o Ls (valor numérico da posição)
// OndeLer controla a leitura aternada
void LeSup(FILE **ArqLEs, Regs *UltLido, int *Ls, bool *OndeLer, Est *est){

    // Como ArqLEs controla leitura e escrita, antes de ler
    // Vamos para a posicao que queremos (Ls-1)
    fseek(*ArqLEs, (*Ls - 1) * SIZEOF_REG, SEEK_SET);
    bool leu;
    leu = lerReg(UltLido, *ArqLEs);
    incrementaFreadP(est);
    if(!leu){
        printf("Nao leu LESUP: %ld\n", ftell(*ArqLEs));
    }
    else{}
    (*Ls)--;
    *OndeLer = false;

}

// A partir de ArqLi, le um item e incrementa o Li (valor numérico da posição)
// OndeLer controla a leitura aternada
void LeInf(FILE **ArqLi, Regs *UltLido, int *Li, bool *OndeLer, Est *est){

    bool leu;
    leu = lerReg(UltLido, *ArqLi);
    incrementaFreadP(est);
    if(!leu){
        printf("Nao leu LEINF\n");
    }
    else{}

    (*Li)++;
    *OndeLer = true;

}

int ObterNumCelOcupadas(Regs *area, Est *est){

    int contador = 0;

    for (int i = 0; i < TAM_MEM; i++){   
        incrementaComparacoes(est);
        if (getNota(&(area[i])) != DOUBLE_MAX){
            contador ++;
        }
    }

    return contador;
    
}

int RetiraUltimo(Regs *Area, Regs *R, Est *est){
    
    int pos = -1;
    char matricula[30];
    for (int i = (TAM_MEM - 1); i >= 0; i--){
        incrementaComparacoes(est);
        if (getNota(&(Area[i])) != DOUBLE_MAX){
            pos = i;
            strcpy(matricula, getId(&(Area[i])));

            break;
        }
    }

    copiaRegistros(R, &(Area[pos]));
    setNota(&(Area[pos]), DOUBLE_MAX);
    quick_sort_interno(Area, TAM_MEM, est);

    for (int i = 0; i < TAM_MEM; i++){
        if (strcmp(matricula, getId(&(Area[i]))) == 0){
            pos = i;
            break;
        }
    }
    setNota(&(Area[pos]), DOUBLE_MAX);

    return pos;
    
}

int RetiraPrimeiro(Regs *Area, Regs *R, Est *est){

    int pos = -1;
    char matricula[30];

    for (int i = 0; i < TAM_MEM; i++){
        incrementaComparacoes(est);
        if (getNota(&(Area[i])) != DOUBLE_MAX){
            pos = i;
            strcpy(matricula, getId(&(Area[i])));
            break;
        }
    }

    copiaRegistros(R, &(Area[pos]));
    setNota(&(Area[pos]), DOUBLE_MAX);
    quick_sort_interno(Area, TAM_MEM, est);

    for (int i = 0; i < TAM_MEM; i++){
        if (strcmp(matricula, getId(&(Area[i]))) == 0){
            pos = i;
            break;
        }
    }
    setNota(&(Area[pos]), DOUBLE_MAX);

    return pos;

}

void InsereItem(Regs *UltLido, Regs *Area, Est *est){

    for (int i = 0; i < TAM_MEM; i++){
        incrementaComparacoes(est);
        if (getNota(&(Area[i])) == DOUBLE_MAX){
            copiaRegistros(&Area[i], UltLido);
            break;
        }
    }
    quick_sort_interno(Area, TAM_MEM, est);

}
