#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

/* Calcular o Numero de cartas de uma jogada */
int lengthMao(wchar_t* jogada){
    int len = 0;
    for(int i = 0; jogada[i] !='\n' && jogada[i] != '\0' && jogada[i]; i++, len++);
    return len;
}

/* Calcular o minimo entre dois números */
int min(int a, int b) {
    if(a < b) return a;
    else return b;
}

/* Calcular o máximo entre dois números */
int max(int a, int b) {
    if(a > b) return a;
    else return b;
}

/* Verificar se a primeira jogada é maior que a segunda */
int checkSuperior(wchar_t* jogadaMaior, wchar_t* jogadaMenor){ //Se alguem quiser fazer uma melhor pff
    
    if(jogadaMenor == NULL) return 0;

    int nr_cartas_jogadaMaior = lengthMao(jogadaMaior);
    int nr_cartas_jogadaMenor = lengthMao(jogadaMenor);

    wchar_t cartasMaiores[2]={jogadaMaior[nr_cartas_jogadaMaior-1], jogadaMenor[nr_cartas_jogadaMenor-1]};
    qsort(cartasMaiores, 2, sizeof(wchar_t), ordena);
    wchar_t cartaMaior = cartasMaiores[1];

    return cartaMaior == jogadaMaior[nr_cartas_jogadaMaior-1];
}

/* Verificar se duas cartas têm o mesmo número */
int compararCartas(wchar_t frsCarta, wchar_t aComparar){
    int result = 0;
    for(int j = 1; j < 4; j++){
        if (  (aComparar == frsCarta + 16 * j) || (aComparar == frsCarta - 16 * j) || (aComparar == frsCarta ) ){ //4
            result = 1;
            break;
        }
    }
    return result;
}

 /* Calcular a maior carta de uma mão */
wchar_t* cartaMaior(wchar_t cartaString[][56], wchar_t cartaHex[][56], int numcartas) {
    
    wchar_t ultCharMaior = cartaHex[0][4];//ultimo char do primeiro hexadecimal da array
    wchar_t* cartaM = cartaString[0];//carta maior
    wchar_t penulCharMaior = cartaHex[0][3];//penultimo char do primeiro hexadecimal da array

    for (int i = 0; i < numcartas; i++) 
    {    
         //ver qual a maior carta utilizando o ultimo char do hexadecimal
         //se os ultimos chars forem iguais, ou seja, se forem cartas com o mesmo número, então passo a usar o penultimo char para ver o naipe
        if (cartaHex[i][4] > ultCharMaior || (cartaHex[i][4] == ultCharMaior && cartaHex[i][3] > penulCharMaior)) 
        {
            //depois vou atualizando as variaveis com os novos valores
            ultCharMaior = cartaHex[i][4];
            penulCharMaior = cartaHex[i][3];
            cartaM = cartaString[i];
        }
    }

    return cartaM;
}
