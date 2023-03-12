#include "../Controller/funcoes.h"
#include <stdlib.h>
#include <stdio.h>

void InserirGestor(struct NodeGestores** headRef, struct Gestores gestor) {
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

void MostrarGestores(struct NodeGestores* head) {
if (head == NULL) {
        printf("List is empty.\n");
        
    }
     struct NodeGestores* current = head;
    while (current != NULL) {
        printf("username: %s\tPassword: %s\n",
               current->gestor.nome,
               current->gestor.password);
        current = current->proximo;
    }
}

