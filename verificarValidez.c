#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int jogadaValida(wchar_t** jogadas, int numJogadas){
    
    int jogadas_anteriores = numJogadas - 2;
    int len_jogadasUteis = min(jogadas_anteriores, 3);
    wchar_t* jogadaAnterior = NULL;
    wchar_t* minha_jogada = jogadas[numJogadas-1];
    //wprintf(L"MINHA %lc ", minha_jogada[2]) ;
    if(wcscmp(minha_jogada, L"PASSO\n") == 0) return 1;
    if(len_jogadasUteis == 0) return 1;

    
    // Verificar a ultima jogada a utilizar
    for(int i = len_jogadasUteis + 1; i > 1; i--){
        wchar_t* jogadaTeste = jogadas[numJogadas-i];
        
        if(wcscmp(jogadaTeste, L"PASSO\n") == 0){ //Se for passo
            continue;
        }else {
            jogadaAnterior = jogadaTeste;
        }
    }
    int len = lengthMao(minha_jogada);
     
    //Se for sempre PASSO, dá verdadeiro se a funcao for alguma combinação
    if (jogadaAnterior == NULL){
        return determinarCombinacao(minha_jogada,len) != 0;
    }else{   
        if(determinarCombinacao(minha_jogada,len) == determinarCombinacao(jogadaAnterior,lengthMao(jogadaAnterior)) && 
        lengthMao(minha_jogada) == lengthMao(jogadaAnterior)){
            return checkSuperior(minha_jogada,jogadaAnterior);
    }}

    return 0;
}
