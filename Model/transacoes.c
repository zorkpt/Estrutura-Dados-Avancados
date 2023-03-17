#include "../Headers/transacoes.h"
#include "../Headers/transportes.h"
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
    return 1;
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


int ProximoIDTransacao(struct NodeTransacoes* headTransacoes) {
    int maiorID = 0;
    struct NodeTransacoes* current = headTransacoes;

    while (current != NULL) {
        if (current->transacoes.idTransacao > maiorID) {
            maiorID = current->transacoes.idTransacao;
        }
        current = current->proximo;
    }

    return maiorID + 1;
}

int MostrarHistoricoAlugueres(struct NodeTransacoes* headTransacoes, int nif){
        struct NodeTransacoes* current = headTransacoes;
    int count = 0;

    // Print the table header
    printf("ID Aluguer\tID Cliente\tID Transporte\tTempo Decorrido\n");

    // Iterate through the linked list of transactions
    while (current != NULL) {
        if (current->transacoes.idClienteAAlugar == nif) {
            printf("%d\t%d\t%d\t%d\n", current->transacoes.idTransacao, current->transacoes.idClienteAAlugar, current->transacoes.idTransporte, current->transacoes.tempoAlugado);
            count++;
        }
        current = current->proximo;
    }

    // Return the number of rentals found for the given NIF
    return count;
}


int ClienteEmTransporte(struct NodeTransacoes* headTransacoes, int nif) {
    struct NodeTransacoes* current = headTransacoes;
    while (current != NULL) {
        if (current->transacoes.idClienteAAlugar == nif && current->transacoes.ativo == 1) {
            return 1; // O Cliente está num transporte
        }
        current = current->proximo;
    }
    return 0; // O Cliente não está num transporte
}

int TerminarAluguer(struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes, int nifClienteLogado) {
    
    struct NodeTransacoes* current = headTransacoes;
    struct NodeTransporte* currentTransporte = headTransportes;
    while (current != NULL) {
        if (current->transacoes.idClienteAAlugar == nifClienteLogado && current->transacoes.ativo == 1) {
            current->transacoes.ativo = 0;
            while (currentTransporte != NULL) {
                if (currentTransporte->transporte.id == current->transacoes.idTransporte) {
                    currentTransporte->transporte.estado = 0;
                    return 1;
                }
                currentTransporte = currentTransporte->proximo;
            }
            return 1;
        }
        current = current->proximo;
    }
    return 0;
}

int AtualizarEstadoTransporte(struct Clientes* cliente, struct NodeTransporte* headTransportes, 
                            struct NodeTransacoes* headTransacoes, int idTransporte, 
                            int tempoAluguer, float custoTotal, int novoIdTransacao) {
    struct Transporte* transporteAlugar = ProcurarTransporte(headTransportes, idTransporte);


    if(!EditarTransporteID(headTransportes,idTransporte)) {
        return 0;
    }
    // Create a new transaction
    struct Transacoes novaTransacao;
    novaTransacao.idClienteAAlugar = cliente->nif;
    novaTransacao.idTransporte = idTransporte;
    novaTransacao.tempoAlugado = tempoAluguer;
    novaTransacao.idTransacao = novoIdTransacao;
    novaTransacao.ativo = 1;
    // Add the new transaction to the transacoes list
    if(!InserirTransacoes(&headTransacoes, novaTransacao)){
        return 0;
    }else {
        // Deduct the cost of the transaction from the client's saldo
        cliente->saldo -= custoTotal;
    return 1;
    }
}