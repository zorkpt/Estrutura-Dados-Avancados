#include "../Controller/funcoes.h"
#include "../Controller/verificacoes.h"
#include "transportes.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX_STRING 100



/// @brief 
/// @param headRef 
/// @param transporte 
/// @return 
int InserirTransporte(struct NodeTransporte** headRef, struct Transporte transporte) {
    struct NodeTransporte* newNode = (struct NodeTransporte*) malloc(sizeof(struct NodeTransporte));
    newNode->transporte = transporte;
    newNode->proximo = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        struct NodeTransporte* current = *headRef;
        while (current->proximo != NULL) {
            current = current->proximo;
        }
        current->proximo = newNode;
    }
}

int MostrarTransportes(struct NodeTransporte* head) {
    if (head == NULL) {
        return 0;
    }
    printf("%-5s %-20s %-10s %-10s %-20s %-10s\n", "ID", "TIPO", "BATERIA", "PRECO", "LOCALIZACAO", "ESTADO");
    struct NodeTransporte* current = head;
    while (current != NULL) {
        printf("%-5d %-20s %-10d %-10.2f %-20s %-10d\n",
               current->transporte.id,
               current->transporte.tipo,
               current->transporte.nivelBateria,
               current->transporte.preco,
               current->transporte.localizacao,
               current->transporte.estado);
        current = current->proximo;
    }
    return 1;
}

int RemoverTransporte(struct NodeTransporte **head, int id) {
    struct NodeTransporte *current = *head;
    struct NodeTransporte *previous = NULL;

    // Percorre a lista até dar match do ID
    while (current != NULL && current->transporte.id != id) {
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
    } else {
        return 0;
    }

}

int TransporteEncontrado(struct NodeTransporte* head){
    struct NodeTransporte *current = head;
    
    printf("\n\nTransporte encontrado:\n");
    printf("ID: %d\n", current->transporte.id);
    printf("Tipo: %s\n", current->transporte.tipo);
    printf("Bateria: %d\n", current->transporte.nivelBateria);
    printf("Preço Por Hora: %f\n", current->transporte.preco);
    printf("Localização: %s\n", current->transporte.localizacao);
    printf("Estado: %d\n", current->transporte.estado);
    printf("\n");

}

int EditarTransporte(struct Transporte *transporte, int id){

    printf("\nNovos Dados do transporte:\n");
    LerTextoInput("Tipo?",transporte->tipo, MAX_STRING);
    printf("Bateria: ");
    transporte->nivelBateria = VerificarInt();
    printf("Preço por Hora: ");
    transporte->preco = VerificarFloat();
    LerTextoInput("Localização?",transporte->localizacao, MAX_STRING);
    printf("Estado do transporte: ");
    transporte->estado = VerificarInt();

    //Guarda o ID sem pedir atualizacao
    transporte->id = id;
    return 1;
    }

struct Transporte* ProcurarTransporte(struct NodeTransporte* headRef, int id ){
    struct NodeTransporte *current = headRef;

    while (current != NULL) {
        if (current->transporte.id == id) {
            return &current->transporte;
        }
        current = current->proximo;
    }
    return NULL;
}

int VerTransportesDisponiveis(struct NodeTransporte* headTransporte, struct NodeTransacoes* headTransacoes) {
    struct NodeTransporte* current = headTransporte;
    //cabeçalho
    printf("ID\tTIPO\t\tBATERIA\t\tPRECO\t\tLOCAL\n");
    while (current != NULL) {
        struct NodeTransacoes* currentTransacoes = headTransacoes;
        while (currentTransacoes != NULL) {
            if (current->transporte.id == currentTransacoes->transacoes.idTransporte) {
                printf("%d\t%s\t%d\t%.2f\t%s\n",current->transporte.id, current->transporte.tipo, current->transporte.nivelBateria, current->transporte.preco,current->transporte.localizacao);
            }
            currentTransacoes = currentTransacoes->proximo;
        }
        current = current->proximo;
    }
}

struct Transporte EscreveTransporte(struct NodeTransporte* headTransporte) {
    struct Transporte transporteTemp;
    printf("ID: ");
    transporteTemp.id = VerificarInt();
    while (VerificaIdTransportes(headTransporte, transporteTemp.id) == 0) {
        transporteTemp.id = VerificarInt();
    }
    LerTextoInput("Tipo?", transporteTemp.tipo, MAX_STRING);
    printf("Nivel de Bateria: ");
    transporteTemp.nivelBateria = VerificarInt();
    printf("Preco: ");
    transporteTemp.preco = VerificarFloat();
    LerTextoInput("Localizacao?", transporteTemp.localizacao, MAX_STRING);
    printf("Estado: ");
    transporteTemp.estado = VerificarInt();
    return transporteTemp;
}

int CopiarLista(struct NodeTransporte *head, struct NodeTransporte **copiedHead) {
    if (head == NULL) {
        return 0;
    }

    while (head != NULL) {
        struct NodeTransporte *newNode = (struct NodeTransporte *)malloc(sizeof(struct NodeTransporte));
        newNode->transporte = head->transporte;
        newNode->proximo = NULL;

        if (*copiedHead == NULL) {
            *copiedHead = newNode;
        } else {
            struct NodeTransporte *current = *copiedHead;
            while (current->proximo != NULL) {
                current = current->proximo;
            }
            current->proximo = newNode;
        }
        head = head->proximo;
    }

    return 1;
}

int OrdenarListaDecrescente(struct NodeTransporte *head) {
    if (head == NULL) {
        return 0;
    }

    struct NodeTransporte *current, *nextNode;
    for (current = head; current != NULL; current = current->proximo) {
        for (nextNode = current->proximo; nextNode != NULL; nextNode = nextNode->proximo) {
            if (current->transporte.nivelBateria < nextNode->transporte.nivelBateria) {
                struct Transporte temp = current->transporte;
                current->transporte = nextNode->transporte;
                nextNode->transporte = temp;
            }
        }
    }

    return 1;
}

int MostrarTransportesOrdenados(struct NodeTransporte *head) {
    if (head == NULL) {
        return 0;
    }

    struct NodeTransporte *copiedHead = NULL;
    if (!CopiarLista(head, &copiedHead)) {
        return 0;
    }

    if (!OrdenarListaDecrescente(copiedHead)) {
        return 0;
    }

    if (!MostrarTransportes(copiedHead)) {
        return 0;
    }

    // Free copied list
    struct NodeTransporte *current;
    while (copiedHead != NULL) {
        current = copiedHead;
        copiedHead = copiedHead->proximo;
        free(current);
    }

    return 1;
}