#include <stdio.h>

#ifdef _WIN32
#include <direct.h>
#define criarPasta(caminho) _mkdir(caminho)
#else
#include <sys/stat.h>
#define criarPasta(caminho) mkdir(caminho, 0777)
#endif

#include "dados.h"
#include "storage.h"

#define ARQUIVO_ABELHAS "database/abelhas.bin"
#define ARQUIVO_MANEJOS "database/agenda.bin"

void carregarDados(void)
{
    FILE *arquivo;

    /* Garante a existencia da pasta onde os dados permanentes ficam salvos. */
    criarPasta("database");

    arquivo = fopen(ARQUIVO_ABELHAS, "rb");
    if (arquivo != NULL) {
        if (fread(&totalAbelhas, sizeof(int), 1, arquivo) != 1 || totalAbelhas < 0 || totalAbelhas > MAX_ABELHAS) {
            totalAbelhas = 0;
        } else if (fread(abelhas, sizeof(Abelha), totalAbelhas, arquivo) != (size_t)totalAbelhas) {
            totalAbelhas = 0;
        }
        fclose(arquivo);
    }

    arquivo = fopen(ARQUIVO_MANEJOS, "rb");
    if (arquivo != NULL) {
        if (fread(&totalManejos, sizeof(int), 1, arquivo) != 1 || totalManejos < 0 || totalManejos > MAX_MANEJOS) {
            totalManejos = 0;
        } else if (fread(manejos, sizeof(Manejo), totalManejos, arquivo) != (size_t)totalManejos) {
            totalManejos = 0;
        }
        fclose(arquivo);
    }

    reorganizarIdsAbelhas();
    reorganizarIdsManejos();
}

void salvarAbelhas(void)
{
    FILE *arquivo = fopen(ARQUIVO_ABELHAS, "wb");

    if (arquivo == NULL) {
        printf("Erro ao salvar o arquivo de abelhas.\n");
        return;
    }

    /* Salva o total e depois o vetor de structs diretamente no arquivo binario. */
    fwrite(&totalAbelhas, sizeof(int), 1, arquivo);
    fwrite(abelhas, sizeof(Abelha), totalAbelhas, arquivo);

    fclose(arquivo);
}

void salvarManejos(void)
{
    FILE *arquivo = fopen(ARQUIVO_MANEJOS, "wb");

    if (arquivo == NULL) {
        printf("Erro ao salvar o arquivo da agenda.\n");
        return;
    }

    /* O idAbelha mantem o vinculo entre o manejo da agenda e a abelha. */
    fwrite(&totalManejos, sizeof(int), 1, arquivo);
    fwrite(manejos, sizeof(Manejo), totalManejos, arquivo);

    fclose(arquivo);
}

void salvarTudo(void)
{
    salvarAbelhas();
    salvarManejos();
}
