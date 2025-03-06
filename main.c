#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_NR_CARTAS 56



int carta_maior (wchar_t carta1, wchar_t carta2){

    int valor1 = carta1 % 16;
    int valor2 = carta2 % 16;

    if (valor1 > valor2) return 1;
    else if (valor1 < valor2) return 0;
    else{
        if ((carta1 - carta2) <= 0) return 0;
        else return 1;
    }

    return 0;
}

int limparlinhaMatriz (wchar_t *linha_matriz, int nr_linhas){
    memset(linha_matriz, L'\0', sizeof(linha_matriz) * 5);
    return (nr_linhas - 1);
}

int limparArray (wchar_t *array_temporario, wchar_t *mao, int i){
    memset(array_temporario, L'\0', sizeof(wchar_t) * 5);
    array_temporario[0] = mao[i];
    return 1;
}

int copiarParaMatriz (wchar_t *linha, wchar_t *array_temporario, int k){
    memcpy(linha, array_temporario, sizeof(wchar_t) * 5);
    return (k + 1);
}

wchar_t maiorLinha (wchar_t *linha){

    wchar_t maior = L'\0';
    int i = 0;
    for (; linha[i] != L'\0'; i++);

    maior = linha[i-1];

    return maior;
}

int filtraLinhaMatriz(wchar_t *linha, wchar_t *jogada, int tamanho_jogada){
    int resultado = 0;
    int encontrou_superior = 0;

    for (; *linha != L'\0' && !encontrou_superior;){
        if (carta_maior(*linha, jogada[tamanho_jogada-1])) encontrou_superior = 1;
        else remove_umaCarta(*linha, linha);
    }

    if (linha[0] == L'\0') resultado = 1;
    
    return resultado;
}

int shiftMatriz (wchar_t matriz[][5], wchar_t *linha){
    int i;

    for(i = 0; i < 14; i++){
        if(wcscmp(matriz[i], linha) == 0) {
            for(;i < 14; i++){
                memcpy(matriz[i], matriz[i+1], sizeof(matriz[i+1]));
            }
            break;
        }
    }

    return 0;
}

int shiftMatrizDireita (wchar_t matriz[][5], int nr_linhas){

    for (int i = nr_linhas; i >= 0; i--){
        memcpy(matriz[i+1], matriz[i], sizeof(matriz[i]));
    }

    return 0;
}

int filtrarLinhaMatrizExcecao (wchar_t *linha, int tamanho_linha, wchar_t *jogada, int tamanho_jogada){

    int j = 0;

    for (; j < tamanho_linha;){
        if (!carta_maior(linha[j], jogada[tamanho_jogada-1])){
            remove_umaCarta(linha[j], linha);
            tamanho_linha--;
        }

        else j++;
    }

    if (linha[0] == L'\0') return 1;

    return 0;
}

int filtrarMatrizExcecao (wchar_t matriz[][5], int k, wchar_t *jogada, int tamanho_jogada){
    int nr_linhas = k;
    int i = 0;
    int tamanho_linha = 0;

    for (; i < nr_linhas;){
        if (matriz[i][0] % 16 == 14){
            int resultado = 0;
            tamanho_linha = wcslen(matriz[i]);
            resultado = filtrarLinhaMatrizExcecao(matriz[i], tamanho_linha, jogada, tamanho_jogada);

            if (!resultado){
                wchar_t array_temp[5];
                memcpy(array_temp, matriz[i], sizeof(matriz[i])); // copia para array temporario a string
                shiftMatrizDireita (matriz, nr_linhas-2); // -2 para não considerar os reis
                memcpy(matriz[0], array_temp, sizeof(array_temp)); //copia os reis para a primeira posição
                i++;
                continue; // se não removeu a linha, continua para a próxima iteração
            }
        }

        if (wcslen(matriz[i]) != 4){
            i = i + shiftMatriz(matriz, matriz[i]);
            nr_linhas--;
            continue;
        }

        else{
            i++;
        }
    }

    return nr_linhas;
}

int filtrarMatriz(wchar_t matriz[][5], wchar_t *jogada, int tamanho_jogada, int k){
    int nr_linhas = k;
    int i = 0;

    for (; i < nr_linhas;){
        if ((int) wcslen(matriz[i]) < tamanho_jogada){
            i = i + shiftMatriz(matriz, matriz[i]);
            nr_linhas--;
            continue;
        }

        if (tamanho_jogada == 1){
            int filtrou = filtraLinhaMatriz(matriz[i], jogada, tamanho_jogada);
            nr_linhas = nr_linhas - filtrou;
            if (filtrou) i = i + shiftMatriz(matriz, matriz[i]);
            else i++;
        }

        else{
            wchar_t carta_maior_linha = L'\0';
            carta_maior_linha = maiorLinha(matriz[i]);
            if (!carta_maior(carta_maior_linha, jogada[tamanho_jogada-1])){
                i = i + shiftMatriz(matriz, matriz[i]);
                nr_linhas--;
            }
            
            else i++;
        }
    }

    return nr_linhas;
}

int inicializarMatriz (wchar_t matriz_conjuntos[][5], wchar_t *mao, int tamanho_mao){
    
    wchar_t array_temporario[5]; // Array temporário para ir guardando os conjuntos válidos
    for (int j = 0; j < 5; j++) array_temporario[j] = L'\0';
    int k = 0; // nr. de linhas da matriz de conjuntos
    array_temporario[0] = mao[0];
    int j = 1;

    for (int i = 1; i < tamanho_mao; i++){
        if ((mao[i] % 16) == (mao[i-1] % 16)){
            array_temporario[j] = mao[i];
            j++;
        }

        else{
            k = copiarParaMatriz(matriz_conjuntos[k], array_temporario, k);
            j = limparArray(array_temporario, mao, i);
        }
    }

    if (array_temporario[0] != L'\0') k = copiarParaMatriz(matriz_conjuntos[k], array_temporario, k);

    return k;
}


int imprimirResposta (wchar_t *jogada, wchar_t *mao, int* combinacoesValidas){

    int tamanho_jogada = (int) wcslen(jogada);
    int nr_combinacao = determinarCombinacao(jogada, wcslen(jogada));

    if (nr_combinacao == 1){

        wchar_t matriz_conjuntos[15][5];
            
        for (int j = 0; j < 15; j++){
            for (int k = 0; k < 5; k++){
                matriz_conjuntos[j][k] = L'\0';
            }
        }

        int nr_linhas_matriz = inicializarMatriz(matriz_conjuntos, mao, (int) wcslen(mao));

        /* se for rei, considera exceção */

        int excecao = 0;

        if (tamanho_jogada == 1 && (jogada[0] % 16) == 14){
            nr_linhas_matriz = filtrarMatrizExcecao(matriz_conjuntos, nr_linhas_matriz, jogada, tamanho_jogada);
            excecao = 1;
        }
        
        else nr_linhas_matriz = filtrarMatriz(matriz_conjuntos, jogada, tamanho_jogada, nr_linhas_matriz);

        if (nr_linhas_matriz == 0);
        else{
            for (int i = 0; i < nr_linhas_matriz; i++){
                int nr_cartas = (int) wcslen(matriz_conjuntos[i]);
                if (excecao){
                    if ((matriz_conjuntos[i][0] % 16) == 14) imprimir_combinacao(matriz_conjuntos[i], nr_cartas, tamanho_jogada,combinacoesValidas);
                    else imprimir_combinacao(matriz_conjuntos[i], nr_cartas, nr_cartas,combinacoesValidas);
                }
                else imprimir_combinacao(matriz_conjuntos[i], nr_cartas, tamanho_jogada,combinacoesValidas);
            }
        }
    }
    return 0;
}

int main() {
    setlocale(LC_CTYPE, "C.UTF-8");
    int numTestes = 0;

    wscanf(L"%d ", &numTestes);

    for (int i = 0; i < numTestes; i++){
        int numJogadas = 0;
        int j = 0;

        wscanf(L"%d ", &numJogadas);
       
        wchar_t **matriz = malloc(2 * sizeof(wchar_t *));//criar matriz 2D com tamanho dinamico

        for(j = 0; j < 2; j++){
            matriz[j] = malloc(56 * sizeof(wchar_t)); 
            if (fgetws(matriz[j], 56, stdin)==NULL) return 0;
            wchar_t *newline = wcschr(matriz[j], L'\n');
            if (newline) *newline = L'\0';
        }

        wchar_t* ultimaCombinacao = matriz[0];
        wchar_t* mao = matriz[1];

        qsort(mao, lengthMao(mao), sizeof(wchar_t), ordena);
        qsort(ultimaCombinacao, lengthMao(ultimaCombinacao), sizeof(wchar_t), ordena);
        wprintf(L"Teste %d\n", i+1);
        //remove_Cartas(mao, ultimaCombinacao);
        //printf("%d\n",proxNumExiste(ultimaCombinacao[0], mao));
        gerefuncoes(ultimaCombinacao,mao, lengthMao(ultimaCombinacao));
        
        // for (int k = 0; mao[k]; k++){
        //     wprintf(L"%lc ", mao[k]);
        // }

        for(int i = 0; i < 2; i++) {
            free(matriz[i]);
        }
        
        free(matriz);       
    }
}

// for(int j = 0; j < lengthMao(mao_final); j++){
//     wprintf(L"%lc", mao_final[j]);
//     if (j != lengthMao(mao_final)-1){
//         wprintf(L" ");
//     }
// }