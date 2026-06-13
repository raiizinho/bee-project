#include <stdio.h>
#include <string.h>

#include "colors.h"
#include "dados.h"
#include "sensores.h"
#include "storage.h"
#include "utils.h"

static void cadastrarSensor(void);
static void listarSensores(void);
static void buscarSensorPorAbelha(void);
static void alterarLeituraSensor(void);
static void removerSensor(void);

void menuSensores(void)
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

        switch (opcao) {
            case 1: cadastrarSensor(); break;
            case 2: listarSensores(); break;
            case 3: buscarSensorPorAbelha(); break;
            case 4: alterarLeituraSensor(); break;
            case 5: removerSensor(); break;
            case 6: break;
            default:
                vermelho("\nOpcao invalida.\n");
                pausar();
                break;
        }
    } while (opcao != 6);
}

static void cadastrarSensor(void)
{
    Sensor novo;
    int opcaoTipo;

    limparTela();
    amarelo("===== CADASTRAR SENSOR =====\n");

    if (totalSensores >= MAX_SENSORES) {
        vermelho("Limite de sensores atingido.\n");
        pausar();
        return;
    }

    if (totalAbelhas == 0) {
        amarelo("Cadastre uma abelha antes de vincular sensores.\n");
        pausar();
        return;
    }

    novo.idAbelha = lerInteiro("ID da abelha vinculada: ");
    if (buscarIndiceAbelhaPorId(novo.idAbelha) == -1) {
        vermelho("Abelha nao encontrada.\n");
        pausar();
        return;
    }

    printf("\nTipo do sensor:\n");
    printf("1. Temperatura\n");
    printf("2. Umidade\n");
    printf("3. Luminosidade\n");
    opcaoTipo = lerInteiro("Escolha: ");

    switch (opcaoTipo) {
        case 1:
            strcpy(novo.tipo, "Temperatura");
            break;
        case 2:
            strcpy(novo.tipo, "Umidade");
            break;
        case 3:
            strcpy(novo.tipo, "Luminosidade");
            break;
        default:
            vermelho("Tipo invalido. Sensor nao cadastrado.\n");
            pausar();
            return;
    }

    novo.valor = lerFloat("Valor da leitura atual: ");
    novo.id = totalSensores + 1;

    sensores[totalSensores] = novo;
    totalSensores++;
    salvarSensores();

    verde("\nSensor cadastrado com sucesso.\n");
    pausar();
}

static void listarSensores(void)
{
    int i, indiceAbelha;

    limparTela();
    ciano("===== LISTA DE SENSORES =====\n");

    if (totalSensores == 0) {
        amarelo("Nenhum sensor cadastrado.\n");
    }

    for (i = 0; i < totalSensores; i++) {
        indiceAbelha = buscarIndiceAbelhaPorId(sensores[i].idAbelha);

        ciano("\n------------------------------\n");
        printf("ID: %d\n", sensores[i].id);
        printf("Tipo: %s\n", sensores[i].tipo);
        printf("Leitura atual: %.2f\n", sensores[i].valor);
        printf("Abelha: %s (ID %d)\n",
               indiceAbelha == -1 ? "nao encontrada" : abelhas[indiceAbelha].nomePopular,
               sensores[i].idAbelha);
    }

    pausar();
}

static void buscarSensorPorAbelha(void)
{
    int idAbelha, i, encontrou = 0;

    limparTela();
    ciano("===== BUSCAR SENSOR POR ABELHA =====\n");
    idAbelha = lerInteiro("ID da abelha: ");

    if (buscarIndiceAbelhaPorId(idAbelha) == -1) {
        vermelho("Abelha nao encontrada.\n");
        pausar();
        return;
    }

    for (i = 0; i < totalSensores; i++) {
        if (sensores[i].idAbelha == idAbelha) {
            printf("\nID: %d | %s | Leitura: %.2f | Abelha ID: %d\n",
                   sensores[i].id,
                   sensores[i].tipo,
                   sensores[i].valor,
                   sensores[i].idAbelha);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        amarelo("\nNenhum sensor encontrado para essa abelha.\n");
    }

    pausar();
}

static void alterarLeituraSensor(void)
{
    int id, indice;

    limparTela();
    amarelo("===== ALTERAR LEITURA DO SENSOR =====\n");
    id = lerInteiro("Digite o ID do sensor: ");
    indice = buscarIndiceSensorPorId(id);

    if (indice == -1) {
        vermelho("Sensor nao encontrado.\n");
        pausar();
        return;
    }

    printf("Leitura atual: %.2f\n", sensores[indice].valor);
    sensores[indice].valor = lerFloat("Nova leitura: ");
    salvarSensores();

    verde("\nLeitura alterada com sucesso.\n");
    pausar();
}

static void removerSensor(void)
{
    int id, indice, i;

    limparTela();
    vermelho("===== REMOVER SENSOR =====\n");
    id = lerInteiro("Digite o ID do sensor que deseja remover: ");
    indice = buscarIndiceSensorPorId(id);

    if (indice == -1) {
        vermelho("Sensor nao encontrado.\n");
        pausar();
        return;
    }

    if (!confirmar("Deseja realmente remover este sensor? (s/n): ")) {
        amarelo("Remocao cancelada.\n");
        pausar();
        return;
    }

    for (i = indice; i < totalSensores - 1; i++) {
        sensores[i] = sensores[i + 1];
    }
    totalSensores--;
    reorganizarIdsSensores();
    salvarSensores();

    verde("\nSensor removido e vetor reorganizado.\n");
    pausar();
}

void removerSensoresDaAbelha(int idAbelhaRemovida)
{
    int i = 0;
    int j;

    while (i < totalSensores) {
        if (sensores[i].idAbelha == idAbelhaRemovida) {
            for (j = i; j < totalSensores - 1; j++) {
                sensores[j] = sensores[j + 1];
            }
            totalSensores--;
        } else {
            i++;
        }
    }

    reorganizarIdsSensores();
}
