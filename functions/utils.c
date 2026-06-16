#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void limparTela(void)
{
    printf("\033[2J\033[H");
}

void pausar(void)
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void lerLinha(const char *mensagem, char *destino, int tamanho)
{
    int caractere;
    int leuLinhaCompleta;

    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);
    leuLinhaCompleta = strchr(destino, '\n') != NULL || strchr(destino, '\r') != NULL;
    destino[strcspn(destino, "\r\n")] = '\0';

    if (!leuLinhaCompleta) {
        while ((caractere = getchar()) != '\n') {   
        }
    }
}

int lerInteiro(const char *mensagem)
{
    char entrada[30];
    char *fim;
    long valor;

    while (1) {
        lerLinha(mensagem, entrada, sizeof(entrada));
        valor = strtol(entrada, &fim, 10);

        if (entrada[0] != '\0' && *fim == '\0') {
            return (int)valor;
        }

        printf("Entrada invalida. Digite um numero inteiro.\n");
    }
}

float lerFloat(const char *mensagem)
{
    char entrada[30];
    char *fim;
    float valor;

    while (1) {
        lerLinha(mensagem, entrada, sizeof(entrada));
        valor = strtof(entrada, &fim);

        if (entrada[0] != '\0' && *fim == '\0') {
            return valor;
        }

        printf("Entrada invalida. Digite um numero decimal. Exemplo: 2.5\n");
    }
}

int confirmar(const char *mensagem)
{
    char resposta[10];

    lerLinha(mensagem, resposta, sizeof(resposta));
    return tolower((unsigned char)resposta[0]) == 's';
}

int dataValida(const char *data)
{
    int dia, mes, ano;
    int diasMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        return 0;
    }

    if (sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3) {
        return 0;
    }

    if (ano < 2020 || mes < 1 || mes > 12 || dia < 1) {
        return 0;
    }

    if ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)) {
        diasMes[1] = 29;
    }

    return dia <= diasMes[mes - 1];
}
