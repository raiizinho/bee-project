#pragma once

#include "beecare.h"

extern Abelha abelhas[MAX_ABELHAS];
extern Manejo manejos[MAX_MANEJOS];
extern Sensor sensores[MAX_SENSORES];
extern int totalAbelhas;
extern int totalManejos;
extern int totalSensores;

int buscarIndiceAbelhaPorId(int id);
int buscarIndiceManejoPorId(int id);
int buscarIndiceSensorPorId(int id);
void reorganizarIdsAbelhas(void);
void reorganizarIdsManejos(void);
void reorganizarIdsSensores(void);
