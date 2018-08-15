/*
TITULO: Biblioteca com fun��es para calcular o tempo
DATA: 12/Mar�o/2010
*/

/* AGORA a fun��o funciona com precis�o de microssegundos tamb�m
 * para o Windows. Testado com SUCESSO no Dev++
 */
#ifndef __TEMPO__
/* Sempre que se cria uma biblioteca � prudente usar um define para ela.
 * Veja, as defini��es abaixo s� ocorrer�o se N�O HOUVER AINDA a constante
 * __TEMPO__. Isto evita erros com duplas inclus�es, ou seja, dois ou mais
 * #include "tempo.h". Apenas o primeiro ter� efeito e os demais nada
 * definir�o. Todos os .h deveriam usar isto.
 * */
#define __TEMPO__

//#ifdef LINUX
#include <sys/time.h>
#include <termios.h>
#include <time.h>
#define clrscr()    printf("\033[2J")

//#else
/* --------------------------- WINDOWS SESSION */
//#include <conio.h>
//#include <time.h>
//#include <windows.h>

//#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
//#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
//#else                           /*  */
//#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
//#endif                          /*  */
/*struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag = 0;
    if (NULL != tv) {
        GetSystemTimeAsFileTime(&ft);
        tmpres |= ft.dwHighDateTime;
        tmpres <<= 32;
        tmpres |= ft.dwLowDateTime;
        tmpres /= 10;
        tmpres -= DELTA_EPOCH_IN_MICROSECS;
        tv->tv_sec = (long) (tmpres / 1000000UL);
        tv->tv_usec = (long) (tmpres % 1000000UL);
    }
    if (NULL != tz) {
        if (!tzflag) {
            _tzset();
            tzflag++;
        }
        tz->tz_minuteswest = _timezone / 60;
        tz->tz_dsttime = _daylight;
    }
    return 0;
}*/

/* ----------- FIM DO WINDOWS SESSION */
#endif         

/* para muitos c�digos, um inteiro longo sem sinal � o ideal.
Se for um compilador de 32 bits, isto resultar� em um inteiro
de 32 bits. Por�m se for um compilador de 64 bits, ser� um inteiro
de 64 bits.

Crio um typedef pois � muita coisa ficar digitando unsigned long int
Assim, s� se coloca ulong
*/
typedef unsigned long int ulong;

/* uma fun��o para medir o tempo.
Ela retorna a quantidade de microsegundos que se passaram
desde a �ltima vez que a mesma fun��o foi chamada.
* 
* Agora ela � a mesma para Linux e para Windows, pois o problema � que no
* Windows n�o tinha a fun��o gettimeofday, mas agora tem uma implementa��o
* para Windows no in�cio deste c�digo
*/
ulong tempo()
{
    static struct timeval ti, tf;
    static int vezes = 0;
    ulong ms;
    
    if (vezes == 0) {

        /* Primeira invoca��o */
        vezes = 1;
        gettimeofday(&ti, NULL);
        return (0);
    }

/* pega o tempo atual. Funcao para LINUX */
    gettimeofday(&tf, NULL);
    ms = (tf.tv_sec - ti.tv_sec) * 1000000 + (tf.tv_usec - ti.tv_usec);

    /* Ajusta o tempo de agora para esperar a pr�xima invoca��o */
    gettimeofday(&ti, NULL);

    /* retorna o tempo que se passou em microsegundos
       1s = 1.000.000 us
     */
    vezes++;
    return (ms);
}


/* Retorna uma string com o tempo formatado em  seg,  mseg e useg */
char *formata(ulong m)
{
    static char tempo[30];
    ulong s, ms, us;
    s = m / 1000000;
    ms = (m % 1000000) / 1000;
    us = (m % 1000);
    sprintf(tempo, "%02lus %03lums %03luus", s, ms, us);
    return (tempo);
}
//#endif


/* FIM DO ifdef LINUX */

/* Dispon�vel como tempo.h
 * Para usar coloque o tempo.h no mesmo diret�rio do teu c�digo fonte e 
 * inclua ele da seguinte forma:
 * 
 * #include "tempo.h"
 * 
 */
