#pragma once

#define MAX_ABELHAS 50
#define MAX_MANEJOS 100

typedef struct {
    int id;
    char nomePopular[40];
    char nomeCientifico[50];
    char regiao[30];
    float producaoMel;
} Abelha;

typedef struct {
    int id;
    int idAbelha;
    char data[11];
    char tipo[40];
    char descricao[120];
    char status[20];
} Manejo;

void executarSistema(void);
