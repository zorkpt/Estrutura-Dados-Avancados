/**
 * @file gestores.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "../Headers/gestores.h"
#include "../Headers/verificacoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRING 100


/// @brief Insere uma nova struct de Gestores na lista de NodeGestores
/// @param headRef Pointer para o head **pointer** da lista de NodeGestores
/// @param gestor A struct de Gestores a ser inserida
/// @return Retorna 1 se a inserção for bem sucedida, 0 caso contrário
int InserirGestor(struct NodeGestores** headRef, struct Gestores gestor) {
    struct NodeGestores* newNode = (struct NodeGestores*) malloc(sizeof(struct NodeGestores));
    newNode->gestor = gestor;
    newNode->proximo = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        struct NodeGestores* current = *headRef;
        while (current->proximo != NULL) {
            current = current->proximo;
        }
        current->proximo = newNode;
    }
}

/// @brief Mostra todos os Gestores da lista de NodeGestores
/// @param head Pointer para o head da lista de NodeGestores
/// @return Retorna 1 se a lista não estiver vazia, 0 caso contrário
int MostrarGestores(struct NodeGestores* head) {
if (head == NULL) {

    }
     struct NodeGestores* current = head;
    while (current != NULL) {
        printf("username: %s\tPassword: %s\n",
               current->gestor.nome,
               current->gestor.password);
        current = current->proximo;
    }
}

/// @brief Cria uma nova struct de Gestores com os dados inseridos pelo utilizador e depois validados
/// @param headRef Ponteiro para a head da lista de Gestores, usado para a verificação de Username
/// @return Retorna uma struct Gestores com os dados do novo gestor (não adiciona á lista)

struct Gestores AdicionarGestor(struct NodeGestores* headRef) {
    struct Gestores gestoresTemp;
    printf("Insira os dados do novo Gestor:\n");
    while(1){
        if(LerTextoInput("Nome: ", gestoresTemp.nome, MAX_STRING)){
            if(!VerificaGestor(headRef, gestoresTemp.nome)) break;
            else printf("Gestor com esse nome já existe.\n");
        }
    }
    LerTextoInput("Password: ", gestoresTemp.password, MAX_STRING);
    return(gestoresTemp);
}

/// @brief Remove um Gestor da lista de NodeGestores
/// @param head Pointer para o pointer do head da lista de NodeGestores
/// @param nome Nome do Gestor a ser removido
/// @return Retorna 1 se a remoção for bem sucedida, 0 caso contrário
int RemoverGestor(struct NodeGestores **head, char nome[]) {
    struct NodeGestores *current = *head;
    struct NodeGestores *previous = NULL;

    // Percorre a lista até dar match do nome
    while (current != NULL && strcmp(current->gestor.nome, nome) != 0) {
        previous = current;
        current = current->proximo;
    }
    // Se for encontrado, removemos da lista
    if (current != NULL) {
        // Se o node for o head da lista, damos update ao pointer do head
        if (previous == NULL) {
            *head = current->proximo;
        }
        // Senão, o node anterior passa apontar para o proximo, dando skip ao atual
        else {
            previous->proximo = current->proximo;
        }
        free(current);
        return 1;
    }
    return 0;
    }
