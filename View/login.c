/**
 * @file login.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../Headers/verificacoes.h"
#include <string.h>
#include <stdio.h>
#define MAX_CHAR 100

/// @brief Tenta fazer login com o nome de utilizador e palavra-passe fornecidos
/// @param clientesHead Pointer para o pointer do header da lista de clientes
/// @param gestoresHead  Pointer para o pointer do header da lista de gestores
/// @param nifClienteLogado NIF do cliente que fez login
/// @return  Retorna 1 se o login for efetuado como cliente, retorna 2 se o login for efetuado como gestor, retorna 0 se o login falhar
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
