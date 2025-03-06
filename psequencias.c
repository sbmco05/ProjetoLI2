#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
 
// Definindo a estrutura CardCount para representar um conjunto de cartas
typedef struct { 
    char* cards[52]; // Array de ponteiros para strings de cartas // Array de valores das cartas
    wchar_t naipes[16][5]; // Array de naipes das cartas
} *CardCount;
 
// Função para criar uma estrutura CardCount a partir de um array de caracteres largos (wide characters)
void remove_Cartas(wchar_t* mao, wchar_t* jogada);

CardCount clonelistastruct(wchar_t cartas[]){
    CardCount estrutura = malloc(sizeof(*estrutura)); // Aloca memória para a estrutura
    // Inicializa os naipes das cartas como vazio
    for(int i = 0; i < 16; i++) {
        estrutura->naipes[i][0] = '\0'; //inicializar a empty
    }
    // Preenche os naipes das cartas com base no array de caracteres largos fornecido
    for(int i = 0; cartas[i]; i++){
        if (cartas[i]%16 != -1) { // Verifica se a carta é válida
            wcsncat(estrutura->naipes[cartas[i]%16], cartas + i, 1); // Adiciona o naipe da carta à estrutura
            // Atribui um valor à carta
        }
    }
    // Define as cartas como vazias
    memset(estrutura->cards, 0, sizeof(estrutura->cards));
    return estrutura;
}
 
int sequenciaValida(wchar_t *cartamaiorsequencia, wchar_t *cartasatuais, int len_sequencia){
    wchar_t cartaMaisAltaAtual = cartasatuais[len_sequencia - 1];
   
    if(cartaMaisAltaAtual % 16 == *cartamaiorsequencia % 16){ //se as cartas mais altas forem do mesmo número verifica os naipes
        return cartaMaisAltaAtual > *cartamaiorsequencia;
        
    } else {
        return (cartaMaisAltaAtual % 16) > (*cartamaiorsequencia % 16);
    }
}
// Função recursiva para gerar todas as sequências possíveis de cartas
void recursiva(CardCount estrutura, wchar_t *cartas, int nr_sequencia,int tamanho, wchar_t *cartamaiorsequencia, int indicecartaatual, wchar_t *cartasatuais, int tamanhosequencia, int* combinacoesPossiveis) {
    // Caso base: se a sequência estiver completa, imprime as cartas atuais e retorna para fechar a recursiva atual
    if (nr_sequencia == 0 && sequenciaValida(cartamaiorsequencia,  cartasatuais, tamanhosequencia)) { //////// Adicionei uma função para verificar se a jogada é válida (nao vale a pena usar a funcao que fizemos para o outro guiao já que só queremos verificar naipes basicamente)
         for(int i = 0; i < tamanho; i++){
            if(i < tamanho - 1 ){ 
            wprintf(L"%lc ", cartasatuais[i]);
            }
            else{
              wprintf(L"%lc", cartasatuais[i]);
            }
        }
        (*combinacoesPossiveis)++;
        wprintf(L"\n");
        return;
    }

    // Itera sobre os naipes da carta atual
    //quando fizer uma recursiva da shift na carta se poder estrutura->naipes[indicecartaatual][i] i++, sai de loop não tiver cartas na direita , fecha a recursiva
    for (int i = 0; estrutura->naipes[indicecartaatual][i]; i++) {
        // Aloca memória para uma nova string de cartas atuais
        wchar_t *newCartasatuais = malloc((wcslen(cartasatuais) + 2) * sizeof(wchar_t)); 
        
        // Copia as cartas atuais para a nova string
        wcscpy(newCartasatuais, cartasatuais); 
        // Adiciona o próximo naipe à nova string
        wcsncat(newCartasatuais, &estrutura->naipes[indicecartaatual][i], 1); 
        // Chama recursivamente a função para o próximo naipe na sequência, decrementa o nr_sequencia pois diminui o numero de cartas necessarios para completar a sequencia, acrecentou em cima a array
        //ao indice para chamar a carta de proximo valor, manda a array com as cartas da sequencia que ja foram postas
        recursiva(estrutura, cartas, nr_sequencia - 1, tamanho,cartamaiorsequencia, indicecartaatual + 1, newCartasatuais, tamanhosequencia, combinacoesPossiveis);
        // Libera a memória alocada para a nova string
        free(newCartasatuais); 
    }
}
 
//função para fazer a verificação , ainda não funciona , work in progress
 
 
int verficacaocartas (CardCount estrutura, int nr_sequencia, wchar_t *cartamaiorsequencia, int *arrindicecartas) {
 
    int indicemenor = (*cartamaiorsequencia % 16) - nr_sequencia + 1;
    int count = 0;
    for (int i = indicemenor; (i <= 14 - nr_sequencia +1); i++) {
 
        int valor = 0;
        for (int j = i; j < i + nr_sequencia; j++) { // Corrigindo o loop interno
            if (wcslen(estrutura->naipes[j]) == 0) { // Verificando se o naipe está vazio
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
 
 
// Função para iniciar a chamada recursiva para gerar as sequências
void chamadainicialrecursiva(wchar_t *jogada,wchar_t *cartas, int nr_sequencia, wchar_t *cartamaiorsequencia, int *combinacoesPossiveis) {
    // Inicializa uma string de cartas atuais vazia onde vai ser colocada a sequecia feita na recursiva
    wchar_t cartasatuais[2] = L""; 
    remove_Cartas(cartas, jogada); // Remove as cartas da mão que são menores que a menor carta da jogada
    
    int tamanho = nr_sequencia;
    // Cria uma estrutura CardCount a partir do array de cartas fornecido
    CardCount estrutura = clonelistastruct(cartas);
    // Print the contents of the structure
    
    // Chama a função recursiva para gerar as sequências de cartas
    int arrindicecartas[14];
    int tamanhosequencia = nr_sequencia;
    int count  = verficacaocartas (estrutura,  nr_sequencia,cartamaiorsequencia, arrindicecartas);
    for(int i = 0; i < count ; i++){
    recursiva(estrutura, cartas, nr_sequencia, tamanho, cartamaiorsequencia, arrindicecartas[i], cartasatuais, tamanhosequencia, combinacoesPossiveis);
    }
}