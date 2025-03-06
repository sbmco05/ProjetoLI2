#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"


int determinarCombinacao (wchar_t *jogada, int nr_cartas){

    wchar_t cartaString[56][56]={0};//Array das cartas em si
    wchar_t cartaHex[56][56]={0};//Array dos hexadecimais das cartas
    wchar_t jogada2[56]={0};//array função sofia

    for(int i = 0; i < nr_cartas; i++){
        jogada2[i] = jogada[i]; //array que a função da sofia recebe
        cartaString[i][0] = jogada[i]; //Guarda a carta do input dentro da cartaString
        swprintf(cartaHex[i], 56, L"%04x", jogada[i]); //Guarda o hexadecimal da carta do input dentro da cartaHex
    }

    /* retorna 1, 2, 3 ou 0 consoante a combinação seja um conjunto, sequência, dupla-sequência ou nada */

    int nr_combinacao = 0;

    
    if (isConjunto(jogada2)){
        nr_combinacao = 1;
    }
    
    else if(nr_cartas >= 3 && isSequencia(jogada)){
        nr_combinacao = 2;
    }

    else if(double_input_cartas(cartaString, cartaHex, nr_cartas)){
        nr_combinacao = 3;
    }

    return nr_combinacao;
}
