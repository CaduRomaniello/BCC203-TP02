// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// // Melhor caso O(n / b) onde b é o bloco de leitura feito (neste exemplo b é 1)
// // Pior caso O(n^2 / TAM_AREA) onde TAM_AREA é o tamanho do pivô, ocorre quando uma partição tem o maior tamanho possível, e a outra é vazia ou mínima
// // Caso médio O((n / b) * (log(n / TAM_AREA)))

// // PS:  Neste caso do QuickSort externo o pior caso não vai acontecer pois quando escrevemos a partição
// //      tem a condição de retirar do pivô baseado no tamanho do sub-arquivo.

// #define TAM_AREA 3
// #define TRUE 1
// #define FALSE 0
// #define INT_MIN (-2147483647 - 1)
// #define INT_MAX 2147483647

// typedef struct TipoArea
// {
//     int sla_oq;
// } TipoArea;

// typedef struct TipoRegistro
// {
//     int Chave;
// } TipoRegistro;

// // Signature
// void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir);
// void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j);
// void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea);
// void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es);
// void EscreveMin(FILE **ArqEi, TipoRegistro R, int *Ei);
// void RetiraMax(TipoArea *Area, TipoRegistro *R, int *NRArea);
// void RetiraMin(TipoArea *Area, TipoRegistro *R, int *NRArea);
// void LeSup(FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer);
// void LeInf(FILE **ArqLi, TipoRegistro *UltLido, int *Li, short *OndeLer);

// // Source
// // ArqLEs gerencia Ls e Es, mesma coisa que ArqLi ArqEi
// void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir)
// {
//     int i, j;

//     /* Area de armazenamento interna */
//     TipoArea Area; // pivô que pode ser do tipo que quiser, lista, array, mapa...

//     // Verifica se é necessário ordenação
//     if (Dir - Esq < 1)
//         return;

//     // Cria a área vazia
//     FAVazia(&Area);
//     Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j);

//     // Olha quantidade de elementos entre i e esq /// j e dir
//     if (i - Esq < Dir - j)
//     {
//         /* Ordene primeiro o sub-arquivo menor */
//         QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
//         QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
//     }
//     else
//     {
//         /* Ordene primeiro o sub-arquivo maior */
//         QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
//         QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
//     }
// }

// // Faz todo o processo do QuickSort externo
// void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j)
// {

//     // Controladores de escrita/leitura
//     int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0, Linf = INT_MIN, Lsup = INT_MAX;

//     short OndeLer = TRUE;
//     TipoRegistro UltLido, R;

//     // Inicializa as variaveis ArqLi e ArqEi no arquivo
//     fseek(*ArqLi, (Li - 1) * sizeof(TipoRegistro), SEEK_SET);
//     fseek(*ArqEi, (Ei - 1) * sizeof(TipoRegistro), SEEK_SET);

//     *i = Esq - 1;
//     *j = Dir + 1;

//     // Inicializa partição
//     while (Ls >= Li)
//     {
//         // Faz a leitura alternada até que sobre uma posição no pivô
//         if (NRArea < TAM_AREA - 1)
//         {
//             if (OndeLer)
//                 LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);

//             else
//                 LeInf(ArqLi, &UltLido, &Li, &OndeLer);

//             InserirArea(&Area, &UltLido, &NRArea);
//             continue;
//         }

//         // Inicia condicional de Linf < chave || Lsup > chave

//         // Condicional de refazer uma leitura do mesmo lado caso seja necessário
//         // Para não deixar Es > Ls
//         if (Ls == Es)
//             LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);

//         else if (Li == Ei)
//             LeInf(ArqLi, &UltLido, &Li, &OndeLer);

//         // Caso não seja necessário as condicoes acima, continua alternância
//         else if (OndeLer)
//             LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);

//         else
//             LeInf(ArqLi, &UltLido, &Li, &OndeLer);

//         // Se a chave for > limite superior, atualiza o j, escreve no sub-arquivo A2
//         if (UltLido.Chave > Lsup)
//         {
//             *j = Es;

//             EscreveMax(ArqLEs, UltLido, &Es);
//             continue;
//         }

//         // Se a chave for < limite superior, atualiza o i, escreve no sub-arquivo A1
//         if (UltLido.Chave < Linf)
//         {
//             *i = Ei;

//             EscreveMin(ArqEi, UltLido, &Ei);
//             continue;
//         }

//         // Se não for escrito no sub-arquivo, escrevemos no pivô
//         InserirArea(&Area, &UltLido, &NRArea);

//         // Analiza qual sub-arquivo tem menos elementos e retiramos/escrevemos o ítem baseado no nro de items do sub-arquivo
//         if (Ei - Esq < Dir - Es)
//         {
//             RetiraMin(&Area, &R, &NRArea);
//             EscreveMin(ArqEi, R, &Ei);

//             Linf = R.Chave;
//         }
//         else
//         {
//             RetiraMax(&Area, &R, &NRArea);
//             EscreveMax(ArqLEs, R, &Es);

//             Lsup = R.Chave;
//         }
//     }

//     // Após toda a partição feita, pegamos os elementos do pivô e voltamos para o arquivo,
//     // escrevendo o menor elemento do pivô ao sub-arquivo A1
//     while (Ei <= Es)
//     {
//         RetiraMin(&Area, &R, &NRArea);
//         EscreveMin(ArqEi, R, &Ei);
//     }
// }

// void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea)
// {
//     /* Insere UltLido de forma ordenada na Area*/
//     InsereItem(*UltLido, Area);          // Insere de forma ordenada no pivô
//     *NRArea = ObterNumCelOcupadas(Area); // Retorna nro de posicoes ocupadas do pivô
// }

// // Escreve do lado Superior
// void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es)
// {
//     // Da mesma forma que no LeSup, por ArqLEs controlar leitura e escrita
//     // devemos dar um fseek antes, escrever e decrementar o *Es
//     fseek(*ArqLEs, (*Es - 1) * sizeof(TipoRegistro), SEEK_SET);
//     fwrite(&R, sizeof(TipoRegistro), 1, *ArqLEs);

//     (*Es)--;
// }

// // Escreve do lado Inferior
// void EscreveMin(FILE **ArqEi, TipoRegistro R, int *Ei)
// {
//     fwrite(&R, sizeof(TipoRegistro), 1, *ArqEi);
//     (*Ei)++;
// }

// // Trabalha para retirar o maior elemento do pivô
// void RetiraMax(TipoArea *Area, TipoRegistro *R, int *NRArea)
// {
//     RetiraUltimo(Area, R);               // Retira da ultima posicao do pivo
//     *NRArea = ObterNumCelOcupadas(Area); // Retorna nro de elementos no pivô
// }

// // Trabalha para retirar o menor elemento do pivô
// void RetiraMin(TipoArea *Area, TipoRegistro *R, int *NRArea)
// {
//     RetiraPrimeiro(Area, R);             // Retira da primeira posicao do pivo
//     *NRArea = ObterNumCelOcupadas(Area); // Retorna nro de elementos no pivô
// }

// // A partir de ArqLEs, le um item e decrementa o Ls (valor numérico da posição)
// // OndeLer controla a leitura aternada
// void LeSup(FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer)
// {
//     // Como ArqLEs controla leitura e escrita, antes de ler
//     // Vamos para a posicao que queremos (Ls-1)
//     fseek(*ArqLEs, (*Ls - 1) * sizeof(TipoRegistro), SEEK_SET);
//     fread(UltLido, sizeof(TipoRegistro), 1, *ArqLEs);

//     (*Ls)--;
//     *OndeLer = FALSE;
// }

// // A partir de ArqLi, le um item e incrementa o Li (valor numérico da posição)
// // OndeLer controla a leitura aternada
// void LeInf(FILE **ArqLi, TipoRegistro *UltLido, int *Li, short *OndeLer)
// {
//     fread(UltLido, sizeof(TipoRegistro), 1, *ArqLi);

//     (*Li)++;
//     *OndeLer = TRUE;
// }