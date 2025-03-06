#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"

int isRei(wchar_t carta){
    wchar_t rei = L'\U0001F0AE'; 
    return compararCartas(carta, rei);
}

void checkExcecoes(wchar_t *mao, wchar_t* jogAnterior,  int* combinacoesValidas){
    int numReis  = 0;

    //verificar numero de reis
    for(int j = 0; j < lengthMao(jogAnterior);j++){
        wchar_t carta = jogAnterior[j];
        if( !isRei(carta) )
            return;
        else {
            numReis++;
        }
    }

    //int check = 0;
    
    // for(int j = 0; j < lengthMao(mao);j++){
    //     wchar_t carta = mao[j];
    //     if(carta % 16 > *cartamaiorsequencia ){
    //         check = 1;    
    //     } 
    // }
    wchar_t cartapequena = L'🂡';
    wchar_t *cartamenorsequencia = &cartapequena;
    // if(check == 0){
        if(numReis==1){            
            imprimirResposta(jogAnterior, mao, combinacoesValidas);
            chamadainicialrecursivaduplasequencia(cartamenorsequencia,mao, 6,  cartamenorsequencia, combinacoesValidas);
        }
            
        if(numReis==2){
            imprimirResposta(jogAnterior, mao, combinacoesValidas);
            chamadainicialrecursivaduplasequencia(cartamenorsequencia,mao, 8,  cartamenorsequencia, combinacoesValidas);
        }
        if(numReis==3){
            chamadainicialrecursivaduplasequencia(cartamenorsequencia,mao, 10,  cartamenorsequencia, combinacoesValidas);
        }
        if(numReis==4){
            (*combinacoesValidas)++;
            wprintf(L"PASSO\n");
        }
    
}