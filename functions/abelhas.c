#include <stdio.h>
#include <string.h>

#include "abelhas.h"
#include "agenda.h"
#include "colors.h"
#include "dados.h"
#include "storage.h"
#include "utils.h"

static void cadastrarAbelha(void);
static void listarAbelhas(void);
static void buscarAbelhaPorNome(void);
static void alterarAbelha(void);
static void removerAbelha(void);

void menuAbelhas(void)
{
    int opcao;

    do {
        limparTela();
        verde("===== GERENCIAR ABELHAS =====\n");
        printf("1. Cadastrar abelha\n");
        printf("2. Listar todas\n");
        printf("3. Buscar por nome popular\n");
        printf("4. Alterar dados\n");
        printf("5. Remover\n");
        printf("6. Voltar\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1: cadastrarAbelha(); break;
            case 2: listarAbelhas(); break;
            case 3: buscarAbelhaPorNome(); break;
            case 4: alterarAbelha(); break;
            case 5: removerAbelha(); break;
            case 6: break;
            default:
                vermelho("\nOpcao invalida.\n");
                pausar();
                break;
        }
    } while (opcao != 6);
}

static void cadastrarAbelha(void)
{
    Abelha nova;

    limparTela();
    verde("===== CADASTRAR ABELHA =====\n");

    if (totalAbelhas >= MAX_ABELHAS) {
        vermelho("Limite de abelhas atingido.\n");
        pausar();
        return;
    }

    nova.id = totalAbelhas + 1;
    lerLinha("Nome popular: ", nova.nomePopular, sizeof(nova.nomePopular));
    lerLinha("Nome cientifico: ", nova.nomeCientifico, sizeof(nova.nomeCientifico));
    lerLinha("Regiao: ", nova.regiao, sizeof(nova.regiao));
    nova.producaoMel = lerFloat("Producao media de mel (kg/mes): ");

    abelhas[totalAbelhas] = nova;
    totalAbelhas++;
    salvarAbelhas();

    verde("\nAbelha cadastrada com sucesso.\n");
    pausar();
}

static void listarAbelhas(void)
{
    int i;

    limparTela();
    ciano("===== LISTA DE ABELHAS =====\n");

    if (totalAbelhas == 0) {
        amarelo("Nenhuma abelha cadastrada.\n");
    }

    for (i = 0; i < totalAbelhas; i++) {
        ciano("\n------------------------------\n");
        printf("ID: %d\n", abelhas[i].id);
        printf("Nome popular: %s\n", abelhas[i].nomePopular);
        printf("Nome cientifico: %s\n", abelhas[i].nomeCientifico);
        printf("Regiao: %s\n", abelhas[i].regiao);
        printf("Producao media: %.2f kg/mes\n", abelhas[i].producaoMel);
    }

    pausar();
}

static void buscarAbelhaPorNome(void)
{
    char busca[40];
    int i, encontrou = 0;

    limparTela();
    ciano("===== BUSCAR ABELHA =====\n");
    lerLinha("Digite o nome popular: ", busca, sizeof(busca));

    for (i = 0; i < totalAbelhas; i++) {
        if (strstr(abelhas[i].nomePopular, busca) != NULL) {
            printf("\nID: %d | %s | %s | %s | %.2f kg/mes\n",
                   abelhas[i].id,
                   abelhas[i].nomePopular,
                   abelhas[i].nomeCientifico,
                   abelhas[i].regiao,
                   abelhas[i].producaoMel);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        amarelo("\nNenhuma abelha encontrada com esse nome.\n");
    }

    pausar();
}

static void alterarAbelha(void)
{
    int id, indice;

    limparTela();
    amarelo("===== ALTERAR ABELHA =====\n");
    listarAbelhas();

    limparTela();
    id = lerInteiro("Digite o ID da abelha que deseja alterar: ");
    indice = buscarIndiceAbelhaPorId(id);

    if (indice == -1) {
        vermelho("Abelha nao encontrada.\n");
        pausar();
        return;
    }

    lerLinha("Novo nome popular: ", abelhas[indice].nomePopular, sizeof(abelhas[indice].nomePopular));
    lerLinha("Novo nome cientifico: ", abelhas[indice].nomeCientifico, sizeof(abelhas[indice].nomeCientifico));
    lerLinha("Nova regiao: ", abelhas[indice].regiao, sizeof(abelhas[indice].regiao));
    abelhas[indice].producaoMel = lerFloat("Nova producao media de mel (kg/mes): ");
    salvarAbelhas();

    verde("\nDados alterados com sucesso.\n");
    pausar();
}

static void removerAbelha(void)
{
    int id, indice, i;

    limparTela();
    vermelho("===== REMOVER ABELHA =====\n");
    listarAbelhas();

    limparTela();
    id = lerInteiro("Digite o ID da abelha que deseja remover: ");
    indice = buscarIndiceAbelhaPorId(id);

    if (indice == -1) {
        vermelho("Abelha nao encontrada.\n");
        pausar();
        return;
    }

    printf("\nAbelha selecionada: %s\n", abelhas[indice].nomePopular);
    amarelo("Os manejos vinculados a ela tambem serao removidos.\n");

    if (!confirmar("Deseja realmente remover? (s/n): ")) {
        amarelo("Remocao cancelada.\n");
        pausar();
        return;
    }

    /* Remove deslocando os itens para a esquerda, sem deixar buracos no vetor. */
    for (i = indice; i < totalAbelhas - 1; i++) {
        abelhas[i] = abelhas[i + 1];
    }
    totalAbelhas--;

    removerManejosDaAbelha(id);
    reorganizarIdsAbelhas();

    for (i = 0; i < totalManejos; i++) {
        if (manejos[i].idAbelha > id) {
            manejos[i].idAbelha--;
        }
    }

    salvarTudo();
    verde("\nAbelha removida e vetores reorganizados.\n");
    pausar();
}
