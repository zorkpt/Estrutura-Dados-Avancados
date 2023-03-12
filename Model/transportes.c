#include "../Controller/funcoes.h"
#include "../Controller/verificacoes.h"
#include "transportes.h"
#include <stdlib.h>
#include <stdio.h>



void InserirNoFimTransporte(struct NodeTransporte** headRef, struct Transporte transporte) {
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

void MostrarTransportes(struct NodeTransporte* head) {
if (head == NULL) {
        printf("Não existem Transportes para mostrar.\n");
        
    }
     struct NodeTransporte* current = head;
    while (current != NULL) {
        printf("%d\t%s\t%d\t%.2f\t%s\t%d\n",
               current->transporte.id,
               current->transporte.tipo,
               current->transporte.nivelBateria,
               current->transporte.preco,
               current->transporte.localizacao,
               current->transporte.estado);
        current = current->proximo;
    }
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

int EditarTransporte(struct NodeTransporte *head, int id){
    struct NodeTransporte *current = head;
    struct Transporte transporteTemp;

    // Procura Cliente Pelo NIF
    while (current != NULL) {
        if (current->transporte.id == id) {
            TransporteEncontrado(current);
            // Pergunta por confirmação para editar o cliente
            limpaSTDIN();
            char resposta;
            printf("Editar este cliente? (S/N): ");
            scanf("%c", &resposta);
            if (resposta == 'S' || resposta == 's') {
                // Inserir novos dados:
                printf("\nInsira os dados do novo cliente:\n");
                printf("Tipo: ");
                limpaSTDIN();
                scanf("%[^\n]", transporteTemp.tipo);
                printf("Bateria: ");
                limpaSTDIN();
                transporteTemp.nivelBateria = VerificarInt();
                printf("Preço por Hora: ");
                limpaSTDIN();
                transporteTemp.preco = VerificarFloat();
                printf("Localização: ");
                limpaSTDIN();
                scanf("%[^\n]", transporteTemp.localizacao);    
                printf("Estado do transporte: ");
                limpaSTDIN();
                transporteTemp.estado = VerificarInt();

                //Guarda o ID sem pedir atualizacao
                transporteTemp.id = current->transporte.id;

                // Atuliza a informação do cliente
                current->transporte = transporteTemp;
                return 1;
            } else {
                return 0;
            }
        }
        current = current->proximo;
}
}

int ProcurarTransporte(struct NodeTransporte* headRef, int id ){
    struct NodeTransporte *current = headRef;

    while (current != NULL) {
        if (current->transporte.id == id) {
            printf("\n\nTransporte encontrado:\n");
            printf("ID: %d\n", current->transporte.id);
            printf("Tipo: %s\n", current->transporte.tipo);
            printf("Bateria: %d\n", current->transporte.nivelBateria);
            printf("Preço Por Hora: %f\n", current->transporte.preco);
            printf("Localização: %s\n", current->transporte.localizacao);
            printf("Estado: %d\n", current->transporte.estado);
            printf("\n");
            return 1;
        }
        current = current->proximo;
    }
    return 0;
}

int VerTransportesDisponiveis(struct NodeTransporte* headTransporte, struct NodeTransacoes* headTransacoes) {
    struct NodeTransporte* current = headTransporte;
    while (current != NULL) {
        struct NodeTransacoes* currentTransacoes = headTransacoes;
        while (currentTransacoes != NULL) {
            if (current->transporte.id == currentTransacoes->transacoes.idTransporte) {
                printf("ID: %d\tTIPO: %s\tBATERIA: %d\t\tPRECO: %.2f\t\tLOCAL:%s\n",current->transporte.id, current->transporte.tipo, current->transporte.nivelBateria, current->transporte.preco,current->transporte.localizacao);
            }
            currentTransacoes = currentTransacoes->proximo;
        }
        current = current->proximo;
    }
}

int EscreveTransporte(struct NodeTransporte* headTransporte) {
    struct Transporte transporteTemp;
    printf("ID: ");

    transporteTemp.id = VerificarInt();
    while (VerificaIdTransportes(headTransporte, transporteTemp.id) == 0) {
        transporteTemp.id = VerificarInt();
    }

    printf("Tipo: ");
    limpaSTDIN();
    fgets(transporteTemp.tipo, 50, stdin);
    printf("Nivel de Bateria: ");
    transporteTemp.nivelBateria = VerificarInt();
    printf("Preco: ");
    transporteTemp.preco = VerificarFloat();
    printf("Localizacao: ");
    limpaSTDIN();
    fgets(transporteTemp.localizacao, 50, stdin);
    printf("Estado: ");
    transporteTemp.estado = VerificarInt();
    InserirNoFimTransporte(&headTransporte, transporteTemp);
    return 0;
}

