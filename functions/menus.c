#include <stdio.h>

#include "abelhas.h"
#include "agenda.h"
#include "colors.h"
#include "menus.h"
#include "storage.h"
#include "utils.h"

static void menuSensores(void);
static void menuRelatorios(void);

void menuPrincipal(void)
{
    int opcao;

    do {
        limparTela();
        verde("===== BEECARE - CONTROLE DE MANEJO =====\n");
        ciano("Startup de cadastro e manejo de abelhas sem ferrao\n\n");
        printf("1. Gerenciar abelhas\n");
        printf("2. Gerenciar sensores\n");
        printf("3. Relatorios\n");
        printf("4. Agenda BeeCare\n");
        printf("5. Sair\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                menuAbelhas();
                break;
            case 2:
                menuSensores();
                break;
            case 3:
                menuRelatorios();
                break;
            case 4:
                menuAgenda();
                break;
            case 5:
                salvarTudo();
                verde("\nDados salvos. Encerrando o BeeCare...\n");
                break;
            default:
                vermelho("\nOpcao invalida.\n");
                pausar();
                break;
        }
    } while (opcao != 5);
}

static void menuSensores(void)
{
    int opcao;

    do {
        limparTela();
        amarelo("===== GERENCIAR SENSORES =====\n");
        printf("1. Cadastrar sensor\n");
        printf("2. Listar sensores\n");
        printf("3. Buscar por ID da abelha\n");
        printf("4. Alterar leitura\n");
        printf("5. Remover\n");
        printf("6. Voltar\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        if (opcao >= 1 && opcao <= 5) {
            amarelo("\nModulo de sensores reservado para implementacao do grupo.\n");
            pausar();
        } else if (opcao != 6) {
            vermelho("\nOpcao invalida.\n");
            pausar();
        }
    } while (opcao != 6);
}

static void menuRelatorios(void)
{
    int opcao;

    do {
        limparTela();
        magenta("===== RELATORIOS =====\n");
        printf("1. Media geral de producao de mel\n");
        printf("2. Media de temperatura dos sensores\n");
        printf("3. Quantidade de abelhas por regiao\n");
        printf("4. Voltar\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        if (opcao >= 1 && opcao <= 3) {
            amarelo("\nModulo de relatorios reservado para implementacao do grupo.\n");
            pausar();
        } else if (opcao != 4) {
            vermelho("\nOpcao invalida.\n");
            pausar();
        }
    } while (opcao != 4);
}
