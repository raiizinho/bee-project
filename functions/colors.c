#include <stdio.h>

void vermelho(const char *texto)
{
    printf("\033[31m%s\033[0m", texto);
}

void verde(const char *texto)
{
    printf("\033[32m%s\033[0m", texto);
}

void amarelo(const char *texto)
{
    printf("\033[33m%s\033[0m", texto);
}

void azul(const char *texto)
{
    printf("\033[34m%s\033[0m", texto);
}

void magenta(const char *texto)
{
    printf("\033[35m%s\033[0m", texto);
}

void ciano(const char *texto)
{
    printf("\033[36m%s\033[0m", texto);
}

void branco(const char *texto)
{
    printf("\033[37m%s\033[0m", texto);
}

void negrito(const char *texto)
{
    printf("\033[1m%s\033[0m", texto);
}