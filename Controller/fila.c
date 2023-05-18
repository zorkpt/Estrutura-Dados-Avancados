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

FilaPrioridade* CriarFilaPrioridade() {
    // Como a fila está vazia inicialmente, simplesmente retornamos NULL
    return NULL;
}

// Função para adicionar um vértice à fila de prioridade
FilaPrioridade* AdicionarNaFila(FilaPrioridade *fila, Vertice *vertice) {
    FilaPrioridade *novo = malloc(sizeof(FilaPrioridade));
    novo->vertice = vertice;
    novo->proximo = NULL;

    if (fila == NULL) {
        return novo;
    } else if (fila->vertice->distancia > vertice->distancia) {
        novo->proximo = fila;
        return novo;
    } else {
        FilaPrioridade *atual = fila;
        while (atual->proximo != NULL && atual->proximo->vertice->distancia < vertice->distancia) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
        return fila;
    }
}

// Função para retirar e retornar o vértice na frente da fila de prioridade
Vertice* RetirarDaFila(FilaPrioridade **fila) {
    // Se a fila está vazia, não há vértice para retirar, então retorna NULL
    if (*fila == NULL) {
        return NULL;
    }

    // Retira o nó na frente da fila e obtém o vértice associado a ele
    FilaPrioridade *retirar = *fila;
    Vertice *vertice = retirar->vertice;

    // Atualiza a frente da fila para o próximo nó e libetra a memória do nó retirado
    *fila = retirar->proximo;
    free(retirar);

    // Retorna o vértice associado ao nó retirado
    return vertice;
}

// Função para verificar se a fila de prioridade está vazia
int EstaVazia(FilaPrioridade *fila) {
    // Se a fila está vazia, retorna 1 (verdadeiro), senão retorna 0 (falso)
    if(fila == NULL) {
        return 1;
    }
    return 0;
}

