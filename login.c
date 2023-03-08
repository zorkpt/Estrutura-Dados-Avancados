#include "funcoes.h"
#include <string.h>


int IniciarLogin(Clientes *clientes, int totalClientes, Gestores *gestores, int totalGestores) {
    char utilizador[50];
    char password[50];
    while(1){
        printf("Nome de Utilizador?\n");
        scanf("%s",utilizador);
        printf("Palavra-Passe?\n");
        scanf("%s",password);

        for (int i = 0; i < totalClientes; i++) {
            if (strcmp(utilizador, clientes[i].login) == 0 && strcmp(password, clientes[i].password) == 0) {
                printf("Login efetuado com sucesso. Bem-vindo %s\n", clientes[i].nome);
                // Call client menu functionls
                return 1;
            }
        }

        for (int i = 0; i < totalGestores; i++) {
            if (strcmp(utilizador, gestores[i].nome) == 0 && strcmp(password, gestores[i].password) == 0) {
                printf("Login efetuado como Gestor, %s\n", gestores[i].nome);
                // Call manager menu function
                return 2;
            }
        }
        
        printf("Utilizador ou senha errado.\n");
        limpaSTDIN();
        }
    return 0;
}