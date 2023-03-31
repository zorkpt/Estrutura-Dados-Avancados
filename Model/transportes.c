/**
 * @file transportes.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../Headers/transportes.h"
#include "../Headers/verificacoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRING 100



/// @brief Insere uma nova struct de Transportes na lista de NodeTransporte
/// @param headRef Pointer para o head **pointer** da lista de NodeTransporte
/// @param transporte A struct de Transportes a ser inserida
/// @return Retorna 1 se a inserção for bem sucedida, 0 caso contrário
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

/// @brief Mostra todos os Transportes da lista de NodeTransporte
/// @param head Pointer para o head da lista de NodeTransporte
/// @return Retorna 1 se a lista não estiver vazia, 0 caso contrário
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

/// @brief Remove um Transporte da lista de NodeTransporte
/// @param head Pointer para o head **pointer** da lista de NodeTransporte
/// @param id ID do transporte a remover
/// @return Retorna 1 se a remoção for bem sucedida, 0 caso contrário
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

/// @brief Edita um Transporte da lista de NodeTransporte
/// @param transporte struct de Transporte a editar
/// @param id ID do transporte para manter o mesmo
/// @return Retorna 1 se a edição for bem sucedida, 0 caso contrário      
int EditarTransporte(struct Transporte *transporte, int id, int estado, int nivelBateria, float preco, char *localizacao, char *tipo){
    transporte->estado = estado;
    transporte->nivelBateria = nivelBateria;
    transporte->preco = preco;
    strcpy(transporte->localizacao, localizacao);
    strcpy(transporte->tipo, tipo);
    //Guarda o ID sem alterar
    transporte->id = id;
    return 1;
}

/// @brief Alterar o estado de um transporte para 1 (ocupado)
/// @param headTransporte Pointer para o head da lista de NodeTransporte
/// @param id ID do transporte a editar
/// @return Retorna 1 se a edição for bem sucedida, 0 caso contrário
int EditarTransporteID(struct NodeTransporte *headTransporte, int id){ 
    struct NodeTransporte* current = headTransporte;
    while (headTransporte != NULL) {
            if (headTransporte->transporte.id == id) {
                headTransporte->transporte.estado = 1;
                return 1;
                }
        headTransporte = headTransporte->proximo;
    }
    return 0;
}



/// @brief  Procura um transporte na lista de NodeTransporte
/// @param headRef Pointer para o head da lista de NodeTransporte
/// @param id ID do transporte a procurar
/// @return Retorna o transporte se encontrado, NULL caso contrário
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
/// @brief Procura um transporte na lista de NodeTransporte por localização
/// @param headTransportes Pointer para o head da lista de NodeTransporte
/// @param local Localização a procurar
/// @return Retorna a lista de transportes encontrados, NULL caso contrário
struct NodeTransporte* ProcurarTransportesPorLocal(struct NodeTransporte* headTransportes, const char* local) {
    struct NodeTransporte* resultHead = NULL;
    struct NodeTransporte* currentNode = headTransportes;

    while (currentNode != NULL) {
        if (strcmp(currentNode->transporte.localizacao, local) == 0) {
            // adiciona o transporte à lista de resultados
            struct NodeTransporte* newNode = (struct NodeTransporte*)malloc(sizeof(struct NodeTransporte));
            newNode->transporte = currentNode->transporte;
            newNode->proximo = resultHead;
            resultHead = newNode;
        }
        currentNode = currentNode->proximo;
    }

    return resultHead;
}

/// @brief Ver todos os transportes disponiveis (estado = 0)
/// @param headTransporte Pointer para o head da lista de NodeTransporte
/// @return Retorna 1 se a operação for bem sucedida
int VerTransportesDisponiveis(struct NodeTransporte* headTransporte) {
    struct NodeTransporte* current = headTransporte;
    //cabeçalho
    printf("%-8s%-20s%-10s%-10s%-30s\n", "ID", "TIPO", "BATERIA", "PRECO/HORA", "LOCAL");    
    while (current != NULL) {
            if (current->transporte.estado == 0) {
                printf("%-8d%-20s%-10d%-10.2f%-30s\n", 
                    current->transporte.id, 
                    current->transporte.tipo, 
                    current->transporte.nivelBateria, 
                    current->transporte.preco,
                    current->transporte.localizacao
                ); }
        current = current->proximo;
    }
    return 1;
}
/// @brief Escreve os dados de um transporte 
/// @param headTransporte Pointer para o head da lista de NodeTransporte
/// @return Retorna uma struct Transporte com os dados inseridos
struct Transporte EscreveTransporte(struct NodeTransporte* headTransporte, int id, char* tipo, int nivelBateria, float preco, char* localizacao, int estado) {
    struct Transporte transporteTemp;
    transporteTemp.id = id;
    strcpy(transporteTemp.tipo, tipo);
    transporteTemp.nivelBateria = nivelBateria;
    transporteTemp.preco = preco;
    strcpy(transporteTemp.localizacao, localizacao);
    transporteTemp.estado = estado;
    return transporteTemp;
}

/// @brief Cria uma copia da lista de NodeTransporte, para usar no sorting
/// @param head pointer para o head da lista de NodeTransporte
/// @param copiedHead Copia da lista de NodeTransporte
/// @return Retorna 1 se a operação for bem sucedida, 0 caso contrário
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

/// @brief Ordena a lista de NodeTransporte por ordem decrescente de bateria
/// @param head Pointer para o head da lista de NodeTransporte
/// @return Retorna 1 se a operação for bem sucedida, 0 caso contrário
int OrdenarListaDecrescente(struct NodeTransporte *head) {
    if (head == NULL) {
        return 0;
    }

    struct NodeTransporte *current, *nextNode;
    // usado algoritmo bubble sort
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

/// @brief Mostra a lista de transportes ordenados por ordem decrescente de bateria
/// @param head Pointer para o head da lista de NodeTransporte
/// @return Retorna 1 se a operação for bem sucedida, 0 caso contrário
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

    struct NodeTransporte *current;
    while (copiedHead != NULL) {
        current = copiedHead;
        copiedHead = copiedHead->proximo;
        free(current);
    }
    return 1;
}

/// @brief Calcula o custo total do aluguer de um transporte
/// @param transporte struct Transporte
/// @param tempoAluguer Tempo de aluguer em minutos
/// @return Retorna o custo total do aluguer
float CustoTotalAluguer(struct Transporte* transporte, int tempoAluguer) {
    float tempoAluguerHoras = tempoAluguer / 60.0; // Convert minutos em horas
    return transporte->preco * tempoAluguerHoras;
}


/// @brief Verifica se um transporte está disponivel
/// @param transporte Struct Transporte
/// @return Retorna 1 se o transporte estiver disponivel, 0 caso contrário
int AlugarTransporteDisponivel(struct Transporte* transporte) {
    if (transporte->estado == 0) {
        return 1;
    } else {
        return 0;
    }
}

