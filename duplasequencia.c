#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"

int double_input_cartas(wchar_t cartaString[][56], wchar_t cartaHex[][56],int numcartas){
    if ((numcartas % 2) == 1){
        return 0;
    }
    if(numcartas  < 6 ){
        return 0;
    }
    int atual = 0;
    wchar_t listafinal[56];

    for (int i = 0; i < numcartas; i++){
            for (int j = i + 1; j < numcartas; j++){

                if (cartaHex[i][4] == cartaHex[j][4]){
                    listafinal[atual] = *cartaString[j];
                    atual ++;
                    break;
                }
                }
                }
   listafinal[atual] = '\0';
   
   if( atual  == (numcartas /2)){
   
    if (isSequencia(listafinal)==1) {
        return 1;
        }
    else {
        return 0;
        }
        }
    return 0;
}

