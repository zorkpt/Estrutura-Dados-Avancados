#include "funcoes.h"
#include "transportes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clientes.h"
#include <stdlib.h>
#include <stdio.h>

// Retorna uma lista com valor nulo.

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
        printf("List is empty.\n");
        
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




// int VerTodosTransportes(Transporte *transporte, int totalTransportes) {
//     for(int i = 0 ; i < totalTransportes; i++ ){
//         printf("ID: %d\tTIPO: %s\tBATERIA: %d\t\tPRECO: %.2f\t\tLOCAL:%s\n",transporte[i].id, transporte[i].tipo, transporte[i].nivelBateria, transporte[i].preco,transporte[i].localizacao);
//     }
//     return 1;
// }

// int VerTransportesDisponiveis(Transporte *transporte, int totalTransporte, Transacoes *transacoes, int totalTransacoes){
//     for(int i = 0; i < totalTransporte; i++) { 
//         for(int j = 0 ; j < totalTransacoes ; j++){
//             if(transporte[i].id == transacoes[j].idClienteAAlugar){
//                 printf("ID: %d\tTIPO: %s\tBATERIA: %d\t\tPRECO: %.2f\t\tLOCAL:%s\n",transporte[i].id, transporte[i].tipo, transporte[i].nivelBateria, transporte[i].preco,transporte[i].localizacao);
//             }    
//         }
//     }
// }

