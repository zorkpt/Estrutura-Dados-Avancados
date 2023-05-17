#include <stdlib.h>
#include "../Headers/fila.h"
#define PREFIX_CR "CR_"


/// @brief Cria uma nova fila vazia
/// @return Ponteiro para a nova fila criada, ou NULL em caso de falha na alocação de memória
Fila* CriarFila() {
    Fila *novaFila = (Fila *)malloc(sizeof(Fila));
    if (!novaFila) {
        return NULL;
    }
    novaFila->front = NULL;
    novaFila->rear = NULL;
    return novaFila;
}




/// @brief Adiciona um elemento ao final da fila
/// @param fila A fila à qual o elemento será adicionado
/// @param vertice O vértice a ser adicionado à fila
/// @return Retorna 1 se a operação for bem-sucedida e 0 se houver alguma falha
int Enfileirar(Fila *fila, Vertice *vertice) {
    NodeFila *novoNo = (NodeFila *)malloc(sizeof(NodeFila));
    if (novoNo == NULL) {
        return 0; // Retornar 0 se a alocação de memória falhar
    }
    novoNo->vertice = vertice;
    novoNo->proximo = NULL;

    if (fila->rear == NULL) {
        fila->front = novoNo;
        fila->rear = novoNo;
    } else {
        fila->rear->proximo = novoNo;
        fila->rear = novoNo;
    }
    
    return 1; // Retornar 1 se a operação for bem-sucedida
}



/// @brief Remove o primeiro elemento da fila e retorna o vértice associado
/// @param fila A fila da qual o elemento será removido
/// @return Retorna o vértice associado ao elemento removido ou NULL se a fila estiver vazia
Vertice* RetiraDaFila(Fila *fila) {
    if (fila->front == NULL) {
        return NULL;
    }

    NodeFila *noASerRemovido = fila->front;
    Vertice *verticeRemovido = noASerRemovido->vertice;

    fila->front = noASerRemovido->proximo;

    if (fila->front == NULL) {
        fila->rear = NULL;
    }

    free(noASerRemovido);
    return verticeRemovido;
}



/// @brief Verifica se a fila está vazia
/// @param fila A fila que será verificada
/// @return Retorna 1 se a fila estiver vazia, caso contrário retorna 0
int EstaVazia(Fila *fila) {
    if (fila->front == NULL) {
        return 1;
    }
    return 0;
}