#include <wchar.h>
#include <stdio.h>
#include "functions.h"


/* Calcular o Numero de cartas de uma jogada */


/* Remove apenas a carta pretendida */
void remove_umaCarta(wchar_t carta, wchar_t* jogada){
    int i;

    for(i = 0;jogada[i] !='\n' && jogada[i] != '\0'; i++){
        if(jogada[i] == carta) {
            for(;jogada[i] !='\n' && jogada[i] != '\0'; i++){
                jogada[i] = jogada[i + 1];
            }
            break;
        }
    }

    //jogada[i-1] = '\n';
}


 /* Remove todas as cartas com um numero inferior à menor carta da jogada */
void remove_Cartas(wchar_t* mao, wchar_t* jogada){
    wchar_t maoHex[lengthMao(mao)][56];
    wchar_t jogadaHex[lengthMao(jogada)][56];
    int len = lengthMao(mao);

    for(int i = 0; mao[i]; i++){
        swprintf(maoHex[i], 56, L"%04x", mao[i]); //Guarda o hexadecimal da carta do input dentro da cartaHex
    }

    for(int i = 0; jogada[i]; i++){
        swprintf(jogadaHex[i], 56, L"%04x", jogada[i]); //Guarda o hexadecimal da carta do input dentro da cartaHex
    }

    for(int i = 0; i < len; i++){    
        if (maoHex[i][4] < jogadaHex[0][4]){
            remove_umaCarta(mao[0], mao);
        }else  break;  
    }  
}
