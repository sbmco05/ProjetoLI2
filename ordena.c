#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"


int ordena(const void *carta_a, const void *carta_b) 
{
    wchar_t ordem[] = L"🂡🂱🃁🃑🂢🂲🃂🃒🂣🂳🃃🃓🂤🂴🃄🃔🂥🂵🃅🃕🂦🂶🃆🃖🂧🂷🃇🃗🂨🂸🃈🃘🂩🂹🃉🃙🂪🂺🃊🃚🂫🂻🃋🃛🂬🂼🃌🃜🂭🂽🃍🃝🂮🂾🃎🃞";
    wchar_t *ca = wcschr(ordem, *(wchar_t*)carta_a);
    wchar_t *cb = wcschr(ordem, *(wchar_t*)carta_b);
    
    return ca - cb;//se ca apontar para uma posição anterior a cb, eo e a  =qsort coloca esta carta primeiro
                   //se apontarem para o mesmo sitio, ou seja, são forem cartas iguais mantem igual
                   //se ca apontar para uma posição posterior a cb, então este resultado será positivo e a qsort coloca esta carta em segundo 
}