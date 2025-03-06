#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include "functions.h"

//🃊🃚🂺

void gerar_combinacoes (wchar_t cartas[], wchar_t array_temporario[], int inicio, int fim, int indice, int tamanho_combinacao, int* combinacoesValidas){

    if (indice == tamanho_combinacao){ 
        for (int j = 0; j < tamanho_combinacao; j++){
            if ((j + 1) == tamanho_combinacao){  // garantir que o último elemento da combinação não é seguido de um espaço em branco
                wprintf(L"%lc\n", array_temporario[j]);
            }

            else{
                wprintf(L"%lc ", array_temporario[j]);
            }
        }
        (*combinacoesValidas)++;
        return;
    }

    for (int i = inicio; i <= fim && fim - i + 1 >= tamanho_combinacao - indice; i++){
        array_temporario[indice] = cartas[i];
        gerar_combinacoes(cartas, array_temporario, i + 1, fim, indice + 1, tamanho_combinacao, combinacoesValidas);
    }

}

void imprimir_combinacao (wchar_t cartas[], int n, int tamanho_combinacao, int* combinacoesValidas){

    wchar_t array_temporario[tamanho_combinacao]; // armazenar temporariamente os valores das combinações a serem impressos;

    gerar_combinacoes(cartas, array_temporario, 0, n - 1, 0, tamanho_combinacao, combinacoesValidas);

}

