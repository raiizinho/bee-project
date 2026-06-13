#include <stdio.h>

#include "abelhas.h"
#include "agenda.h"
#include "colors.h"
#include "menus.h"
#include "sensores.h"
#include "storage.h"
#include "relatorios.h"
#include "utils.h"

void menuPrincipal(void) {
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
