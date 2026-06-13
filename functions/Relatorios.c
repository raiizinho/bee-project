#include <stdio.h>
#include <string.h>

#include "beecare.h"
#include "colors.h"
#include "dados.h"
#include "utils.h"

static void mediaProducaoMel(void);
static void mediaTemperaturaSensores(void);
static void quantidadeAbelhasPorRegiao(void);

void menuRelatorios(void) {
    int opcao;

    do {
        limparTela();
        magenta("===== RELATORIOS =====\n");
        printf("1. Media geral de producao de mel\n");
        printf("2. Media de temperatura dos sensores\n");
        printf("3. Quantidade de abelhas por regiao\n");
        printf("4. Voltar\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1: mediaProducaoMel(); break;
            case 2: mediaTemperaturaSensores(); break;
            case 3: quantidadeAbelhasPorRegiao(); break;
            case 4: break;
            default:
                vermelho("\nOpcao invalida.\n");
                pausar();
                break;
        }
    } while (opcao != 4);
}

static void mediaProducaoMel(void)
{
    int i;
    float soma = 0.0f, media;

    limparTela();
    ciano("===== MEDIA GERAL DE PRODUCAO DE MEL =====\n");

    if (totalAbelhas == 0) {
        amarelo("Nenhuma abelha cadastrada.\n");
        pausar();
        return;
    }

    for (i = 0; i < totalAbelhas; i++) {
        soma += abelhas[i].producaoMel;
    }

    media = soma / totalAbelhas;
    printf("\nTotal de abelhas: %d\n", totalAbelhas);
    printf("Soma da producao: %.2f kg/mes\n", soma);
    printf("\nMedia de producao de mel: %.2f kg/mes\n", media);
    pausar();
}

static void mediaTemperaturaSensores(void)
{
    int i;
    float soma = 0.0f, media;
    int contador = 0;

    limparTela();
    ciano("===== MEDIA DE TEMPERATURA DOS SENSORES =====\n");

    if (totalSensores == 0) {
        amarelo("Nenhum sensor cadastrado.\n");
        pausar();
        return;
    }

    for (i = 0; i < totalSensores; i++) {
        if (strcmp(sensores[i].tipo, "Temperatura") == 0) {
            soma += sensores[i].valor;
            contador++;
        }
    }

    if (contador == 0) {
        amarelo("Nenhum sensor de temperatura cadastrado.\n");
        pausar();
        return;
    }

    media = soma / contador;
    printf("\nTotal de sensores de temperatura: %d\n", contador);
    printf("Soma das temperaturas: %.2f\n", soma);
    printf("\nMedia de temperatura dos sensores: %.2f\n", media);
    pausar();
}

static void quantidadeAbelhasPorRegiao(void)
{
    int i, j;
    char regioes[MAX_ABELHAS][30];
    int quantidades[MAX_ABELHAS] = {0};
    int totalRegioes = 0;
    int encontrou;

    limparTela();
    ciano("===== QUANTIDADE DE ABELHAS POR REGIAO =====\n");

    if (totalAbelhas == 0) {
        amarelo("Nenhuma abelha cadastrada.\n");
        pausar();
        return;
    }

    
    for (i = 0; i < totalAbelhas; i++) {
        encontrou = 0;
        for (j = 0; j < totalRegioes; j++) {
            if (strcmp(regioes[j], abelhas[i].regiao) == 0) {
                quantidades[j]++;
                encontrou = 1;
                break;
            }
        }
        if (!encontrou) {
            strcpy(regioes[totalRegioes], abelhas[i].regiao);
            quantidades[totalRegioes] = 1;
            totalRegioes++;
        }
    }

    
    printf("\n");
    for (i = 0; i < totalRegioes; i++) {
        printf("Regiao: %s\n", regioes[i]);
        printf("Quantidade de abelhas: %d\n", quantidades[i]);
        printf("------------------------------\n");
    }

    printf("\nTotal de abelhas: %d\n", totalAbelhas);
    printf("Total de regioes distintas: %d\n", totalRegioes);

    pausar();
}
