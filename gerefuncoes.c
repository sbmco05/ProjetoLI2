#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"


void gerefuncoes (wchar_t *jogada,wchar_t *mao, int nr_cartas){
    int combinacoesValidas = 0;
    int* apontCombinacoesValidas = &combinacoesValidas;

    wchar_t cartaString[56][56]={0};//Array das cartas em si
    wchar_t cartaHex[56][56]={0};//Array dos hexadecimais das cartas
    wchar_t jogada2[56]={0};//array função sofia

    for(int i = 0; i < nr_cartas; i++){
        jogada2[i] = jogada[i]; //array que a função da sofia recebe
        cartaString[i][0] = jogada[i]; //Guarda a carta do input dentro da cartaString
        swprintf(cartaHex[i], 56, L"%04x", jogada[i]); //Guarda o hexadecimal da carta do input dentro da cartaHex
    }

    /* retorna 1, 2, 3 ou 0 consoante a combinação seja um conjunto, sequência, dupla-sequência ou nada */



    wchar_t *cartamaior =  cartaMaior( cartaString,  cartaHex,  nr_cartas);

    if(isRei(*jogada)){
        checkExcecoes(mao, jogada, apontCombinacoesValidas);
    }
    else if (isConjunto(jogada2)){    
         imprimirResposta(jogada, mao, apontCombinacoesValidas);
    }
    
    else if(nr_cartas >= 3 && isSequencia(jogada)){
        chamadainicialrecursiva(jogada,mao, nr_cartas,  cartamaior, apontCombinacoesValidas);
    }

    else if(double_input_cartas(cartaString, cartaHex, nr_cartas)){
        chamadainicialrecursivaduplasequencia(jogada,mao,  nr_cartas,  cartamaior, apontCombinacoesValidas);
    }

    if(combinacoesValidas == 0){
        wprintf(L"PASSO\n");
}
}
