#include "dados.h"

/* Vetores principais exigidos no trabalho. Os totais indicam as posicoes ocupadas. */
Abelha abelhas[MAX_ABELHAS];
Manejo manejos[MAX_MANEJOS];
int totalAbelhas = 0;
int totalManejos = 0;

int buscarIndiceAbelhaPorId(int id)
{
    int i;

    for (i = 0; i < totalAbelhas; i++) {
        if (abelhas[i].id == id) {
            return i;
        }
    }

    return -1;
}

int buscarIndiceManejoPorId(int id)
{
    int i;

    for (i = 0; i < totalManejos; i++) {
        if (manejos[i].id == id) {
            return i;
        }
    }

    return -1;
}

void reorganizarIdsAbelhas(void)
{
    int i;

    for (i = 0; i < totalAbelhas; i++) {
        abelhas[i].id = i + 1;
    }
}

void reorganizarIdsManejos(void)
{
    int i;

    for (i = 0; i < totalManejos; i++) {
        manejos[i].id = i + 1;
    }
}
