#include <stdio.h>
#include "tempo_h.c"

int main()
{
    printf("oie");
    tempo();
    ulong tempoo;
    printf("Quanto tempo sera que demora pra dar um printf?");
    tempoo = tempo();
    printf("\nLevou %uus (%s)\n", tempo, formata(tempo));
    
}