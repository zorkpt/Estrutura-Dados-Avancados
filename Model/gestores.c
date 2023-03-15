#include "../Controller/funcoes.h"
#include "../Controller/verificacoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRING 100

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
