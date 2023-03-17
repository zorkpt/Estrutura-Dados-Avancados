#include "../Headers/verificacoes.h"
#include <string.h>
#include <stdio.h>
#define MAX_CHAR 100

int IniciarLogin(struct NodeClientes** clientesHead, struct NodeGestores** gestoresHead, int* nifClienteLogado) {
    char utilizador[MAX_CHAR];
    char password[MAX_CHAR];
    while (1) {
        printf("Nome de Utilizador?\n");
        scanf("%s", utilizador);
        printf("Palavra-Passe?\n");
        scanf("%s", password);

        struct NodeClientes* currentCliente = *clientesHead;
        while (currentCliente != NULL) {
            if (strcmp(utilizador, currentCliente->cliente.login) == 0 && strcmp(password, currentCliente->cliente.password) == 0) {
                printf("Login efetuado com sucesso. Bem-vindo %s\n", currentCliente->cliente.nome);
                *nifClienteLogado = currentCliente->cliente.nif;
                // Abre Menu Clientes
                return 1;
            }
            currentCliente = currentCliente->proximo;
        }

        struct NodeGestores* currentGestor = *gestoresHead;
        while (currentGestor != NULL) {
            if (strcmp(utilizador, currentGestor->gestor.nome) == 0 && strcmp(password, currentGestor->gestor.password) == 0) {
                printf("Login efetuado como Gestor, %s\n", currentGestor->gestor.nome);
                // Abre Menu Gestores
                return 2;
            }
            currentGestor = currentGestor->proximo;
        }

        printf("Utilizador ou senha errado.\n");
    }
    return 0;
}
