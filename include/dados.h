#pragma once

#include "beecare.h"

extern Abelha abelhas[MAX_ABELHAS];
extern Manejo manejos[MAX_MANEJOS];
extern int totalAbelhas;
extern int totalManejos;

int buscarIndiceAbelhaPorId(int id);
int buscarIndiceManejoPorId(int id);
void reorganizarIdsAbelhas(void);
void reorganizarIdsManejos(void);
