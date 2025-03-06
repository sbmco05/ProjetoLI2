#include <wchar.h>
#include <stdlib.h>
#include "functions.h"


int isConsecutivo (int *valores_ordenados, int tamanho_array){

    int resultado = 1;

    for (int j = 0; j < tamanho_array && resultado == 1; j++){

        if (j + 1 != tamanho_array){

            if (valores_ordenados[j+1] - valores_ordenados[j] > 1 || valores_ordenados[j] == valores_ordenados[j+1]){
                resultado = 0;
            }
        }
    }
    return resultado;
}


int isSequencia (wchar_t *combinacao){

    int resultado;
    int tamanho_array = lengthMao(combinacao);
    int *combinacao_valores_ordenados = malloc(tamanho_array * sizeof(int)); // alocar espaço de memória para um array de inteiros (valores ordenados das cartas). O tamanho do array tem de ser obviamente igual ao do array original.

    for (int i = 0; combinacao[i]!= L'\0'; i++){
        combinacao_valores_ordenados[i] = combinacao[i] % 16;
    }

    qsort(combinacao_valores_ordenados, tamanho_array, sizeof(wchar_t), ordena); // ordena o array de inteiros, usando o algoritmo quick sort

    resultado = isConsecutivo(combinacao_valores_ordenados, tamanho_array); // passa como argumentos o array de inteiros ordenado e o seu tamanho

    free(combinacao_valores_ordenados);// "livrar" do array, libertando o espaço de memória alocado no ínicio da função

    return resultado;

}