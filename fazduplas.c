#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"
 
 
// Definindo a estrutura CardCount para representar um conjunto de cartas
typedef struct { 
    char* cards[52]; // Array de ponteiros para strings de cartas
    wchar_t naipes[16][5]; // Array de naipes das cartas
} *CardCount;

typedef struct { 
    char* cards[52]; // Array de ponteiros para strings de cartas // Array de valores das cartas
    wchar_t naipes[16][16][16]; // Array de naipes das cartas
} *structconjuntos;
 
// Função para criar uma estrutura CardCount a partir de um array de caracteres largos (wide characters)
 
 void remove_Cartas(wchar_t* mao, wchar_t* jogada);

CardCount clonelistastruct2(wchar_t cartas[]){
    CardCount estrutura = malloc(sizeof(*estrutura)); // Aloca memória para a estrutura
    // Inicializa os naipes das cartas como vazio
    for(int i = 0; i < 16; i++) {
        estrutura->naipes[i][0] = L'\0'; //inicializar a empty
    }
    // Preenche os naipes das cartas com base no array de caracteres largos fornecido
    for(int i = 0; cartas[i]; i++){
        if (cartas[i]%16 != -1) { // Verifica se a carta é válida
            wcsncat(estrutura->naipes[cartas[i]%16], cartas + i, 1); // Adiciona o naipe da carta à estrutura
        }
    }
    // Define as cartas como vazias
    memset(estrutura->cards, 0, sizeof(estrutura->cards));
    return estrutura;
}
 
int sequenciaValida2(wchar_t *cartamaiorsequencia, wchar_t *cartasatuais, int len_sequencia){
    wchar_t cartaMaisAltaAtual = cartasatuais[len_sequencia - 1];
    if(cartaMaisAltaAtual % 16 == *cartamaiorsequencia % 16){ //se as cartas mais altas forem do mesmo número verifica os naipes
        return cartaMaisAltaAtual > *cartamaiorsequencia;
    } else {
        return (cartaMaisAltaAtual % 16) > (*cartamaiorsequencia % 16);
    }
}

// Função recursiva para gerar todas as sequências possíveis de cartas
void recursiva2(structconjuntos estrutura, wchar_t *cartas, int nr_sequencia,int tamanho, wchar_t *cartamaiorsequencia, 
    int indicecartaatual, wchar_t *cartasatuais, int tamanhosequencia, int* combinacoesPossiveis) {
    // Caso base: se a sequência estiver completa, imprime as cartas atuais e retorna para fechar a recursiva atual
    if (nr_sequencia == 0 && sequenciaValida2(cartamaiorsequencia,  cartasatuais, tamanhosequencia)) { 
         for(int i = 0; i < tamanho; i++){ 
            if (i == tamanho - 1) {
                wprintf(L"%lc", cartasatuais[i]); // Print without space if it's the last card
            } else {
                wprintf(L"%lc ", cartasatuais[i]);
            }
        }
        (*combinacoesPossiveis)++;
        wprintf(L"\n");
        return;
    }
    // Itera sobre os naipes da carta atual
    //quando fizer uma recursiva da shift na carta se poder estrutura->naipes[indicecartaatual][i] i++, sai de loop não tiver cartas na direita , fecha a recursiva
    for (int i = 0; estrutura->naipes[indicecartaatual][i][0]; i++) {
        // Aloca memória para uma nova string de cartas atuais
        wchar_t *newCartasatuais = malloc(2*(wcslen(cartasatuais) + 2) * sizeof(wchar_t)); 
        // Copia as cartas atuais para a nova string
        wcscpy(newCartasatuais, cartasatuais); 
        // Adiciona o próximo naipe à nova string
        wcsncat(newCartasatuais, &estrutura->naipes[indicecartaatual][i][0], 1); 
        wcsncat(newCartasatuais, &estrutura->naipes[indicecartaatual][i][1], 1); 
        // Chama recursivamente a função para o próximo naipe na sequência, decrementa o nr_sequencia pois diminui o numero de cartas necessarios para completar a sequencia, acrecentou em cima a array
        //ao indice para chamar a carta de proximo valor, manda a array com as cartas da sequencia que ja foram postas
        recursiva2(estrutura, cartas, nr_sequencia - 1, tamanho,cartamaiorsequencia, indicecartaatual + 1, newCartasatuais, tamanhosequencia, combinacoesPossiveis);
        // Libera a memória alocada para a nova string
        free(newCartasatuais); 
    }
}
 
//função para fazer a verificação , ainda não funciona , work in progress
 
 
int verficacaocartas2 (structconjuntos estrutura, int nr_sequencia, wchar_t *cartamaiorsequencia, int *arrindicecartas) {
 
    int indicemenor = (*cartamaiorsequencia % 16) - nr_sequencia + 1 ;
    int count = 0;
    for (int i = indicemenor; (i <= 14 - nr_sequencia +1); i++) {
 
        int valor = 0;
        for (int j = i; j < i + nr_sequencia; j++) { // Corrigindo o loop interno
            if (wcslen(estrutura->naipes[j][0]) == 0) { // Verificando se o naipe está vazio
                valor = 0;
                break;
            } else {
                valor = 1;
            }
        }
        if (valor == 1) {
            arrindicecartas[count] = i;
            count++;
        }
    }
    return count;
}

// int countCartasIndice(CardCount estrutura, int indiceAtual){
//     int len = 0;
//     for(;estrutura -> naipes[indiceAtual][len]; len++);
//     return len;
// }

void recursivaconjuntos(CardCount estrutura, structconjuntos conjunto, int indiceatual, int indicepcarta, int countgeral) {
    
    for (int i = indicepcarta; i < 4; i++) { //NÃO SEI QUE VALOR METER NO i < 4
        for(int j = 0; estrutura->naipes[indiceatual][j];j++){
            //VERIFICAR SE A 2 CARTA DA DUPLA É MAIOR QUE A PRIMEIRA
            if (estrutura->naipes[indiceatual][i] && estrutura->naipes[indiceatual][j] && estrutura->naipes[indiceatual][i] < estrutura->naipes[indiceatual][j]){ 
                conjunto->naipes[indiceatual][countgeral][0] = estrutura->naipes[indiceatual][i];
                conjunto->naipes[indiceatual][countgeral][1] = estrutura->naipes[indiceatual][j];
                countgeral++;
            }   
        }
    }
}


void inicializarecursivaconjuntos(CardCount estrutura,structconjuntos conjunto, int indiceatual){
   int indicepcarta = 0;
   int countgeral  = 0;
   recursivaconjuntos(estrutura,conjunto, indiceatual, indicepcarta,countgeral);
   return;
}
 
structconjuntos fazconjuntos(CardCount estrutura){
    structconjuntos conjuntos = malloc(sizeof(*conjuntos));

    for(int i = 0; i < 16; i++){
        for(int j = 0;j < 16; j++){
            for(int k = 0; k < 16; k++){
                conjuntos -> naipes[i][j][k] = L'\0';  
            }
        }
    }

    for (int i = 0; i < 16; i++){// 15 e não 14
        int indiceatual = i;
        inicializarecursivaconjuntos(estrutura ,conjuntos,indiceatual);
    }
    return conjuntos;
}


// Função para iniciar a chamada recursiva para gerar as sequências
void chamadainicialrecursivaduplasequencia(wchar_t *jogada,wchar_t *cartas, int nr_sequencia, wchar_t *cartamaiorsequencia, int* combinacoesPossiveis) {
    // Inicializa uma string de cartas atuais vazia onde vai ser colocada a sequecia feita na recursiva
    int tamanho = nr_sequencia;
    nr_sequencia = nr_sequencia/2;
    wchar_t cartasatuais[2] = L""; 
    remove_Cartas(cartas, jogada);
  
    
    // Cria uma estrutura CardCount a partir do array de cartas fornecido

    // Chama a função recursiva para gerar as sequências de cartas
    CardCount estrutura = clonelistastruct2(cartas);
    // Print the contents of the CardCount structure

    structconjuntos conjuntos = fazconjuntos(estrutura);
        
    int arrindicecartas[14];
    int tamnahosequencia = 2 * nr_sequencia;
    int count  = verficacaocartas2 (conjuntos,  nr_sequencia, cartamaiorsequencia, arrindicecartas);
    for(int i = 0; i < count ; i++){
        recursiva2(conjuntos, cartas, nr_sequencia, tamanho, cartamaiorsequencia, arrindicecartas[i], cartasatuais, tamnahosequencia, combinacoesPossiveis);
    }
}

