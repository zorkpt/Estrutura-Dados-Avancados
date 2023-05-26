/**
 * @file grafo.c
 * @author Hugo Poças
 * @brief Este ficheiro contém as funções de criação e manipulação do grafo.
 * @version 0.2
 * @date 27-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Headers/verificacoes.h"
#define BUFFER_SIZE 1024

/// @brief Função para criar um novo vértice
/// @param idVertice 
/// @param cidade 
/// @return novo vértice
Vertice* CriarVertice(int idVertice, char cidade[]){
	Vertice* novo = (Vertice*)calloc(1,sizeof(Vertice));
	if(novo == NULL){
		return NULL;
	}

	novo->idVertice = idVertice;
	strcpy(novo->cidade, cidade);
	novo->proximo = NULL;

	return novo;
}

/// @brief Insere um novo vértice no grafo(lista de vertices), mantendo a ordem crescente dos 
///        IDs dos vértices.
/// @param grafo: Ponteiro para o primeiro vértice do grafo (lista ligada simples de vértices).
/// @param novo: Ponteiro para o novo vértice a ser inserido no grafo.
/// @return Ponteiro para o primeiro vértice do grafo após a inserção do novo vértice.
Vertice* InsereVertice(Vertice *grafo, Vertice* novo) {
    Vertice* anterior = NULL;
    Vertice* atual = grafo;

    // Encontra a posição correta para inserir o novo vértice
    while (atual != NULL && atual->idVertice < novo->idVertice) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Insere o novo vértice na posição correta
    if (anterior == NULL) {
        novo->proximo = grafo;
        grafo = novo;
    } else {
        novo->proximo = anterior->proximo;
        anterior->proximo = novo;
    }

    return grafo;
}


/// @brief Cria um novo nó adjacente com o ID do vértice e a distância especificada
/// @param idVertice O ID do vértice adjacente
/// @param distancia A distância entre o vértice atual e o vértice adjacente
/// @return Um ponteiro para o novo nó adjacente criado ou NULL se a alocação de memória falhar
Adjacente *CriaAdjacente(int idVertice, float distancia) {
    Adjacente *novo = (Adjacente *)malloc(sizeof(Adjacente));
    
    if (novo == NULL) {
        return NULL;
    }
    
    novo->idVertice = idVertice;
    novo->distancia = distancia;
    novo->proximo = NULL;
    
    return novo;
}

/// @brief Insere um vértice adjacente no grafo, dado o vértice de origem e o vértice adjacente previamente criado
/// @param grafo Ponteiro para o grafo onde o vértice adjacente será inserido
/// @param origem ID do vértice de origem
/// @param novoAdjacente Ponteiro para o vértice adjacente previamente criado
/// @return Retorna o ponteiro para o Vertice com a lista de adjacencas atualizada ou NULL 
///         se a operação falhar
Vertice* InsereAdjacente(Vertice *grafo, int origem, Adjacente* novoAdjacente){

    // Encontra o vértice de origem no grafo
    Vertice* aux = grafo;
    while (aux && aux->idVertice != origem) {
        aux = aux->proximo;
    }

    // Se o vértice de origem não for encontrado, retorna NULL
    if (aux == NULL) {
        return NULL;
    }

    // Insere o novo vértice adjacente na lista de adjacentes do vértice de origem
    novoAdjacente->proximo = aux->adjacentes;
    aux->adjacentes = novoAdjacente;

    // Incrementa o contador de vértices adjacentes para o vértice de origem
    aux->numAdjacentes++;

    return aux;
}

/// @brief Imprime o grafo, mostrando vértices e adjacências
/// @param grafo O ponteiro para o grafo
void PrintGrafo(Vertice *grafo) {
    Vertice *vertice = grafo;

    // Iterar pelos vértices do grafo
    while (vertice) {
        printf("ID: %d\tCidade: %s\n", vertice->idVertice, vertice->cidade);
        
        Adjacente *adjacent = vertice->adjacentes;

        // Iterar pelas adjacências do vértice atual
        while (adjacent) {
            printf("  -> ID: %d\tDistancia: %.2f\n", adjacent->idVertice, adjacent->distancia);
            adjacent = adjacent->proximo;
        }
        
        printf("\n");
        vertice = vertice->proximo;
    }
}

/// @brief Função para saber o nome do local a partir do id
/// @param grafo ponteiro para o grafo
/// @param localID id do local
/// @return string com o nome do local
const char* GetNomeLocal(Vertice *grafo, int localID) {
    Vertice *current = grafo;
    while (current != NULL) {
        if (current->idVertice == localID) {
            return current->cidade;
        }
        current = current->proximo;
    }
    return NULL;
}

/// @brief Limpa os campos visitado, predecessor e distância de todos os vértices do grafo
/// @param grafo Um ponteiro para a estrutura Vertice que representa o grafo a ser limpo
void LimparCamposGrafo(Vertice *grafo) {
    Vertice *verticeAux = grafo;

    while (verticeAux != NULL) {
        verticeAux->visitado = 0;
        verticeAux->predecessor = -1;
        verticeAux->distancia = INFINITY;
        verticeAux = verticeAux->proximo;
    }
}


/// @brief Procura um vértice no grafo com base no ID.
/// @param grafo O grafo no qual o vértice vai ser procurado.
/// @param idVertice O ID do vértice a procurar.
/// @return Retorna um ponteiro para o vértice encontrado ou NULL se não encontrar.
Vertice* ProcuraVertice(Vertice *grafo, int idVertice) {
    // Cria um ponteiro auxiliar para percorrer a lista de vértices
    Vertice *aux = grafo;

    // Enquanto houver vértices na lista
    while (aux) {
        // Verifica se o ID do vértice atual corresponde ao ID procurado
        if (aux->idVertice == idVertice) {
            // Se encontrado, retorna o ponteiro para o vértice
            return aux;
        }
        // Avança para o próximo vértice na lista encadeada
        aux = aux->proximo;
    }

    // Se o vértice não for encontrado, retorna NULL
    return NULL;
}

/// @brief Imprime a lista de todos os locais (cidades) disponíveis no grafo.
/// @param headVertice é o vértice inicial do grafo a partir do qual a função começa a percorrer o grafo.
void ListarLocais(Vertice *headVertice) {
    // Se o grafo está vazio (i.e., não há vértices), imprimir uma mensagem indicando isso.
    if (headVertice == NULL) {
        printf("Sem dados.\n");
        return;
    }

    // Iniciar a partir do vértice inicial do grafo.
    Vertice *aux = headVertice;
    printf("\nLocais disponíveis:\n");
    
    // Percorrer todo o grafo, imprimindo o ID e o nome da cidade de cada vértice.
    while (aux != NULL) {
        printf("[%d] %s\n", aux->idVertice, aux->cidade);
        aux = aux->proximo;
    }
}
