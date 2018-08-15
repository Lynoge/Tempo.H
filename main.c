#include <stdio.h>
#include "tempo_h.c"

int main()
{
    printf("oie");
    tempo();
    ulong tempoPassado;
    printf("Quanto tempo sera que demora pra dar um printf?");
    tempoPassado = tempo();
    printf("\nLevou %uus (%s)\n", tempo, formata(tempo));
    
}