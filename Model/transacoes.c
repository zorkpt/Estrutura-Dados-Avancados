#include "../Controller/funcoes.h"
#include <stdlib.h>
#include <stdio.h>

int InserirTransacoes(struct NodeTransacoes** headRef, struct Transacoes transacoes) {
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

int MostrarTransacoes(struct NodeTransacoes* head) {
    if (head == NULL) {
        return 0;
    }
    printf("%-12s %-12s %-15s %s\n", "ID TRAN", "ID CLIENTE", "ID TRANSPORTE", "Tempo Decorrido");
    struct NodeTransacoes* current = head;
    while (current != NULL) {
        printf("%-12d %-12d %-15d %d\n",
               current->transacoes.idTransacao,
               current->transacoes.idClienteAAlugar,
               current->transacoes.idTransporte,
               current->transacoes.tempoAlugado);
        current = current->proximo;
    }
    return 1;
}

int MostrarTransacoesCliente(struct NodeTransacoes* head, int idCliente) {
    int count = 0;
    if (head == NULL) {
        return 0;
    }
    struct NodeTransacoes* current = head;
    printf("ID CLIENTE\tID TRANSPORTE\tTempo Decorrido:\n");
    
    while (current != NULL) {
        if (current->transacoes.idClienteAAlugar == idCliente) {
            printf("%d\t\t%d\t\t%d\n",
                            current->transacoes.idClienteAAlugar,
                            current->transacoes.idTransporte,
                            current->transacoes.tempoAlugado);
            count++;
        }
        current = current->proximo;
    }
    
    if (count == 0) {
        return 0;
    }
    return count;
}

struct Transacoes* ProcurarTransacao(struct NodeTransacoes* head, int idTransacao) {
    if (head == NULL) {
        return NULL;
    }
    struct NodeTransacoes* current = head;
    while (current != NULL) {
        if (current->transacoes.idTransacao == idTransacao) {
            return &current->transacoes;
        }
        current = current->proximo;
    }
    return NULL;
}

int RemoverTransacao(struct NodeTransacoes **head, int idTransacao) {
    struct NodeTransacoes *current = *head;
    struct NodeTransacoes *previous = NULL;

    // Percorre a lista até dar match do ID
    while (current != NULL && current->transacoes.idTransacao != idTransacao) {
        previous = current;
        current = current->proximo;
    }
    // Se for encontrado, removemos da lista
    if (current != NULL) {
        // Se o node for o head da lista, damos update ao pointer do head
        if (previous == NULL) {
            *head = current->proximo;
        } else {
            previous->proximo = current->proximo;
        }
        free(current);
        return 1;
    }
    return 0;
}

int EditarTransacao(struct Transacoes * transacao) {
    printf("\nAltera os dados da transacao %d\n", transacao->idTransacao);
    printf("Tempo alugado: ");
    scanf("%d", &transacao->tempoAlugado);
    printf("ID Cliente: ");
    scanf("%d", &transacao->idClienteAAlugar);
    printf("ID Transporte: ");
    scanf("%d", &transacao->idTransporte);
    return 1;
}
