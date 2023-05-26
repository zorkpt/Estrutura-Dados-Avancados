/**
 * @file fila.c
 * @author Hugo Poças
 * @brief Este ficheiro contém as funções de fila.
 * @version 0.2
 * @date 27-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
// Função para adicionar um vértice à fila de prioridade
FilaPrioridade* AdicionarNaFila(FilaPrioridade *fila, Vertice *vertice) {
    // Aloca memória para o novo elemento da fila
    FilaPrioridade *novo = malloc(sizeof(FilaPrioridade));
    // Atribui o vértice passado como argumento ao novo elemento
    novo->vertice = vertice;
    // Inicializa o próximo elemento como NULL
    novo->proximo = NULL;

    // Se a fila está vazia, insere o novo elemento como o primeiro
    if (fila == NULL) {
        return novo;
    } 
    // Se o vértice do primeiro elemento da fila tem uma distância maior que o vértice a ser adicionado,
    // insere o novo elemento no início da fila
    else if (fila->vertice->distancia > vertice->distancia) {
        novo->proximo = fila;
        return novo;
    } 
    // Caso contrário, insere o novo elemento na posição correta para manter a fila ordenada
    else {
        FilaPrioridade *atual = fila;
        // Percorre a fila até encontrar a posição correta para o novo elemento
        // A posição correta é a primeira posição em que a distância do vértice atual é maior que a do vértice a ser adicionado
        while (atual->proximo != NULL && atual->proximo->vertice->distancia < vertice->distancia) {
            atual = atual->proximo;
        }
        // Insere o novo elemento na posição encontrada
        novo->proximo = atual->proximo;
        atual->proximo = novo;
        // Retorna o primeiro elemento da fila
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

