#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // Para usar o Sleep

#include "menuoptions.h"
#include "jobs.h"

int main () {
    limpar();
    menu();
int menuE = 0;
scanf("%d", &menuE);
    switch (menuE) {
        case 1:
        limpar();
        GA();
    break;
    case 2:
        limpar();
        GS();
    break;
    case 3:
        limpar();
        relatorios();
    break;
    case 4:
    printf("Programa encerrado.");
    Sleep(1000);
    break;
    
    default: 
    printf("Escolha não definida, tente novamente.");
    Sleep(2000);
    system("cls");
    main();
        break;
    }
    return 0;
}