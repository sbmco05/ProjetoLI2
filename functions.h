#include <stddef.h>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H


int determinarCombinacao (wchar_t *jogada, int nr_cartas);
int ordena(const void *carta_a, const void *carta_b);
int double_input_cartas(wchar_t cartaString[][56], wchar_t cartaHex[][56],int numcartas);
int compararCartas(wchar_t frsCarta, wchar_t aComparar);
int isConjunto(const wchar_t *linha);
void swap (int *a, int *b);
int diferenca_entre (int numero1, int numero2);
int ordenar_primeiro_meio_ultimo (int *vetor, int primeiro, int ultimo);
int particao (int *vetor, int primeiro, int ultimo);
void quicksort_recursiva (int *vetor, int primeiro, int ultimo);
void quicksort (int *vetor, int tamanho);
int isSequencia (wchar_t *combinacao);
int isConsecutivo (int *valores_ordenados, int tamanho_array);
int isRei(wchar_t carta);
int numero_de_cartas(wchar_t* jogada);
void checkExcecoes(wchar_t* jogada, wchar_t* jogada_anterior,  int* combinacoesValidas);
int sao_do_mesmo_tipo (wchar_t *jogada, wchar_t *jogada_anterior, wchar_t cartaString[][56], wchar_t cartaHex[][56]);
void shift_array(wchar_t *mao, int i);
int imprimir_resposta (wchar_t *mao, wchar_t *jogada, int valido);
int carta_pertence_a_mao (wchar_t carta, wchar_t *mao);
wchar_t* devolve_mao(wchar_t** jogadas, int numJogadas);
int lengthMao(wchar_t* jogada);
int min(int a, int b);
int max(int a, int b);
int jogadaValida(wchar_t** jogadas, int numJogadas);
int checkSuperior(wchar_t* jogadaMaior, wchar_t* jogadaMenor);
void remove_Cartas(wchar_t* mao, wchar_t* jogada);
wchar_t* cartaMaior(wchar_t cartaString[][56], wchar_t cartaHex[][56], int numcartas);
void remove_umaCarta(wchar_t carta, wchar_t* jogada);
int proxNumExiste(wchar_t carta, wchar_t* mao);
void remove_mesmo_numero(wchar_t carta, wchar_t* mao);
void jogPossiveis_sequencia(wchar_t* mao, wchar_t* jogada, int numCartasJogada);
void chamadainicialrecursiva(wchar_t *jogada, wchar_t *cartas, int nr_sequencia, wchar_t *cartamaiorsequencia, int* combinacoesPossiveis);
void gerefuncoes (wchar_t *jogada,wchar_t *mao, int nr_cartas);
void imprimir_combinacao (wchar_t cartas[], int n, int tamanho_combinacao, int* combinacoesValidas);
int imprimirResposta (wchar_t *jogada, wchar_t *mao, int* combinacoesPossiveis);
int libertarEspacoMemoria (wchar_t **matriz, int nr_linhas);
void chamadainicialrecursivaduplasequencia(wchar_t *jogada,wchar_t *cartas, int nr_sequencia, wchar_t *cartamaiorsequencia, int* combinacoesPossiveis);
int isRei(wchar_t carta);
void removercartasmenor4(wchar_t cartaHex[56][56], wchar_t *mao, int tamanhomao);
#endif  