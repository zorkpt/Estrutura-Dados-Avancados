/**
 * @file verificacoes.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <string.h>
#include "../Headers/verificacoes.h"

/// @brief Verifica se um NIF existe na lista de clientes.
/// @param head pointer para o header da lista de clientes.
/// @param nif O nif a verificar
/// @return Retorna 1 se o nif existir, retorna 0 se o nif não existir.
int VerificaNif(struct NodeClientes* head, int nif) {
    struct NodeClientes* current = head;
    while (current != NULL) {
        if (current->cliente.nif == nif) {
            return 1;
        }
        current = current->proximo;
    }
    return 0;
}

/// @brief Verifica se um login existe na lista de clientes.
/// @param head pointer para o header da lista de clientes.
/// @param login o login a verificar
/// @return Retorna 1 se o login existir, retorna 0 se o login não existir.
int VerificaUser(struct NodeClientes* head, char *login) {
    struct NodeClientes* current = head;
    while (current != NULL) {

        if (strcmp(current->cliente.login,login)==0) {
            printf("Já existe um cliente com esse nome de utilizador.\nInsere outro.\n");
            return 1;
        }
        current = current->proximo;
    }
    return 0;
}

/// @brief Verifica se um login existe na lista de gestores.
/// @param head pointer para o header da lista de gestores.
/// @param login o login a verificar
/// @return Retorna 1 se o login existir, retorna 0 se o login não existir.
int VerificaGestor(struct NodeGestores* head, char *login) {
    struct NodeGestores* current = head;
    while (current != NULL) {

        if (strcmp(current->gestor.nome,login)==0) {
            return 1;
        }
        current = current->proximo;
    }
    return 0;
}


/// @brief Lê um real do input do user e verifica se é válido. 
/// @return Retorna o float lido e validado.
float VerificarFloat(){
    float resultado = 0;
    // tamanho maximo do buffer inicializado a 0
    char buffer[1024] = {0};

    // enquanto o utilizador não inserir um float válido
    while (1) {
        fgets(buffer, 1024, stdin);
        if (sscanf(buffer, "%f", &resultado) == 1) {
            return resultado;
        } else if (buffer[0] != '\n') {
            printf("Insere um numero válido: ");
        }
  }
}


/// @brief Lê um inteiro do input do user e verifica se é válido.  
/// @return Retorna o inteiro lido e validado.
int VerificarInt() {
    int resultado = 0;
    // tamanho maximo do buffer inicializado a 0
    char buffer[1024] = {0};

    // enquanto o utilizador não inserir um inteiro válido
    while (1) {
        fgets(buffer, 1024, stdin);
        if (sscanf(buffer, "%d", &resultado) == 1) {
            return resultado;
        } else if (buffer[0] != '\n') {
            printf("Insere um numero inteiro: ");
        }
  }
}

/// @brief Verifica se um id de transporte existe na lista de transportes.
/// @param head pointer para o header da lista de transportes.
/// @param id id a verificar
/// @return  Retorna 1 se o id existir, retorna 0 se o id não existir.
int VerificaIdTransportes(struct NodeTransporte* head, int id) {
    struct NodeTransporte* current = head;
    while (current != NULL) {
        if (current->transporte.id == id) {
            return 1;
        }
        current = current->proximo;
    }
    return 0;
}

/// @brief Lê um texto do input do user e verifica se é válido.
/// @param texto texto a ser mostrado ao user antes da inserção do input
/// @param resultado resultado da leitura do input
/// @param max_length inteiro que representa o tamanho máximo do input
/// @return Retorna 1 se o input for válido
int LerTextoInput(char *texto, char *resultado, int max_length) {
    printf("%s", texto);
    while (1) {
        fgets(resultado, max_length, stdin);
        int len = strlen(resultado);
        if (len > 0 && resultado[len-1] == '\n') {
            resultado[len-1] = '\0';
        }
        if (strlen(resultado) > 0) {
            return 1;
        } else {
            printf("Entrada Inválida.\n%s", texto);
        }
    }
}