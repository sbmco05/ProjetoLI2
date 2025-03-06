#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"

/* Começa por inicializar a variavel result a 0 (1) e por ler a primeira carta 
    da linha (2) dada como argumento. 
   No ciclo percorre a linha (3) e para cada carta verifica se é igual à primeira 
    carta, num diferente naipe através da função compararCartas. Caso haja alguma carta 
    na linha, num numero diferente da primeira carta da linha, a função dá falso.
*/
int isConjunto(const wchar_t *linha){
    int result = 1; //1
    wchar_t fstCarta = linha[0]; //2
    for(int i = 1; linha[i] != L'\0'; i++){ //3
        if (!compararCartas(fstCarta, linha[i])){ //5
            result = 0; 
            break;
        }
    }
    return result; //5
}