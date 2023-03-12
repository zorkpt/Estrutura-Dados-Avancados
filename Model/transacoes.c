#include "../Controller/funcoes.h"
#include <stdlib.h>
#include <stdio.h>

void InserirTransacoes(struct NodeTransacoes** headRef, struct Transacoes transacoes) {
    struct NodeTransacoes* newNode = (struct NodeTransacoes*) malloc(sizeof(struct NodeTransacoes));
    newNode->transacoes = transacoes;
    newNode->proximo = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        struct NodeTransacoes* current = *headRef;
        while (current->proximo != NULL) {
            current = current->proximo;
        }
        current->proximo = newNode;
    }
}

void MostrarTransacoes(struct NodeTransacoes* head) {
if (head == NULL) {
        printf("List is empty.\n");
        
    }
     struct NodeTransacoes* current = head;
    while (current != NULL) {
        printf("ID CLIENTE: %d\tID TRANSPORTE: %d\tTempo Decorrido: %d\n",
               current->transacoes.idClienteAAlugar,
               current->transacoes.idTransporte,
               current->transacoes.tempoAluguerDecorrido);
        current = current->proximo;
    }
}