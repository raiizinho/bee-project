#include <stdio.h>
#include <string.h>

#include "agenda.h"
#include "colors.h"
#include "dados.h"
#include "storage.h"
#include "utils.h"

static void cadastrarManejo(void);
static void listarManejos(void);
static void buscarManejoPorData(void);
static void buscarManejoPorAbelha(void);
static void alterarManejo(void);
static void removerManejo(void);

void menuAgenda(void)
{
    int opcao;

    do {
        limparTela();
        azul("===== AGENDA BEECARE =====\n");
        printf("1. Cadastrar manejo\n");
        printf("2. Listar agenda\n");
        printf("3. Buscar por data\n");
        printf("4. Buscar por ID da abelha\n");
        printf("5. Alterar manejo\n");
        printf("6. Remover manejo\n");
        printf("7. Voltar\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1: cadastrarManejo(); break;
            case 2: listarManejos(); break;
            case 3: buscarManejoPorData(); break;
            case 4: buscarManejoPorAbelha(); break;
            case 5: alterarManejo(); break;
            case 6: removerManejo(); break;
            case 7: break;
            default:
                vermelho("\nOpcao invalida.\n");
                pausar();
                break;
        }
    } while (opcao != 7);
}

static void cadastrarManejo(void)
{
    Manejo novo;

    limparTela();
    azul("===== CADASTRAR MANEJO =====\n");

    if (totalManejos >= MAX_MANEJOS) {
        vermelho("Limite de manejos atingido.\n");
        pausar();
        return;
    }

    if (totalAbelhas == 0) {
        amarelo("Cadastre uma abelha antes de criar a agenda.\n");
        pausar();
        return;
    }

    novo.idAbelha = lerInteiro("ID da abelha vinculada: ");
    if (buscarIndiceAbelhaPorId(novo.idAbelha) == -1) {
        vermelho("Abelha nao encontrada.\n");
        pausar();
        return;
    }

    do {
        lerLinha("Data do manejo (dd/mm/aaaa): ", novo.data, sizeof(novo.data));
        if (!dataValida(novo.data)) {
            vermelho("Data invalida. Use o formato dd/mm/aaaa.\n");
        }
    } while (!dataValida(novo.data));

    lerLinha("Tipo de manejo: ", novo.tipo, sizeof(novo.tipo));
    lerLinha("Descricao: ", novo.descricao, sizeof(novo.descricao));
    strcpy(novo.status, "Pendente");
    novo.id = totalManejos + 1;

    manejos[totalManejos] = novo;
    totalManejos++;
    salvarManejos();

    verde("\nManejo agendado com sucesso.\n");
    pausar();
}

static void listarManejos(void)
{
    int i, indiceAbelha;

    limparTela();
    ciano("===== AGENDA DE MANEJOS =====\n");

    if (totalManejos == 0) {
        amarelo("Nenhum manejo cadastrado.\n");
    }

    for (i = 0; i < totalManejos; i++) {
        indiceAbelha = buscarIndiceAbelhaPorId(manejos[i].idAbelha);

        ciano("\n------------------------------\n");
        printf("ID: %d\n", manejos[i].id);
        printf("Data: %s\n", manejos[i].data);
        printf("Tipo: %s\n", manejos[i].tipo);
        printf("Descricao: %s\n", manejos[i].descricao);
        printf("Status: %s\n", manejos[i].status);
        printf("Abelha: %s (ID %d)\n",
               indiceAbelha == -1 ? "nao encontrada" : abelhas[indiceAbelha].nomePopular,
               manejos[i].idAbelha);
    }

    pausar();
}

static void buscarManejoPorData(void)
{
    char data[11];
    int i, encontrou = 0;

    limparTela();
    ciano("===== BUSCAR MANEJO POR DATA =====\n");
    lerLinha("Data (dd/mm/aaaa): ", data, sizeof(data));

    for (i = 0; i < totalManejos; i++) {
        if (strcmp(manejos[i].data, data) == 0) {
            printf("\nID: %d | Abelha ID: %d | %s | %s | %s\n",
                   manejos[i].id,
                   manejos[i].idAbelha,
                   manejos[i].tipo,
                   manejos[i].descricao,
                   manejos[i].status);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        amarelo("\nNenhum manejo encontrado para essa data.\n");
    }

    pausar();
}

static void buscarManejoPorAbelha(void)
{
    int idAbelha, i, encontrou = 0;

    limparTela();
    ciano("===== BUSCAR MANEJO POR ABELHA =====\n");
    idAbelha = lerInteiro("ID da abelha: ");

    if (buscarIndiceAbelhaPorId(idAbelha) == -1) {
        vermelho("Abelha nao encontrada.\n");
        pausar();
        return;
    }

    for (i = 0; i < totalManejos; i++) {
        if (manejos[i].idAbelha == idAbelha) {
            printf("\nID: %d | %s | %s | %s | %s\n",
                   manejos[i].id,
                   manejos[i].data,
                   manejos[i].tipo,
                   manejos[i].descricao,
                   manejos[i].status);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        amarelo("\nNenhum manejo encontrado para essa abelha.\n");
    }

    pausar();
}

static void alterarManejo(void)
{
    int id, indice;

    limparTela();
    amarelo("===== ALTERAR MANEJO =====\n");
    id = lerInteiro("Digite o ID do manejo que deseja alterar: ");
    indice = buscarIndiceManejoPorId(id);

    if (indice == -1) {
        vermelho("Manejo nao encontrado.\n");
        pausar();
        return;
    }

    do {
        lerLinha("Nova data (dd/mm/aaaa): ", manejos[indice].data, sizeof(manejos[indice].data));
        if (!dataValida(manejos[indice].data)) {
            vermelho("Data invalida. Use o formato dd/mm/aaaa.\n");
        }
    } while (!dataValida(manejos[indice].data));

    lerLinha("Novo tipo de manejo: ", manejos[indice].tipo, sizeof(manejos[indice].tipo));
    lerLinha("Nova descricao: ", manejos[indice].descricao, sizeof(manejos[indice].descricao));
    lerLinha("Status (Pendente/Concluido): ", manejos[indice].status, sizeof(manejos[indice].status));
    salvarManejos();

    verde("\nManejo alterado com sucesso.\n");
    pausar();
}

static void removerManejo(void)
{
    int id, indice, i;

    limparTela();
    vermelho("===== REMOVER MANEJO =====\n");
    id = lerInteiro("Digite o ID do manejo que deseja remover: ");
    indice = buscarIndiceManejoPorId(id);

    if (indice == -1) {
        vermelho("Manejo nao encontrado.\n");
        pausar();
        return;
    }

    if (!confirmar("Deseja realmente remover este manejo? (s/n): ")) {
        amarelo("Remocao cancelada.\n");
        pausar();
        return;
    }

    for (i = indice; i < totalManejos - 1; i++) {
        manejos[i] = manejos[i + 1];
    }
    totalManejos--;
    reorganizarIdsManejos();
    salvarManejos();

    verde("\nManejo removido e vetor reorganizado.\n");
    pausar();
}

void removerManejosDaAbelha(int idAbelhaRemovida)
{
    int i = 0;
    int j;

    /* Apaga os manejos vinculados para nao deixar agenda apontando para abelha removida. */
    while (i < totalManejos) {
        if (manejos[i].idAbelha == idAbelhaRemovida) {
            for (j = i; j < totalManejos - 1; j++) {
                manejos[j] = manejos[j + 1];
            }
            totalManejos--;
        } else {
            i++;
        }
    }

    reorganizarIdsManejos();
}
