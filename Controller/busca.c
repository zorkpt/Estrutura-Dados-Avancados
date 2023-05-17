#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Headers/caminho.h"
#include "../Headers/busca.h"
#include "../Headers/fila.h"

#define PREFIX_CR "CR_"

/// @brief Realiza uma busca em largura no grafo para encontrar o caminho mais curto entre dois vértices
/// @param grafo Ponteiro para o primeiro vértice na lista de vértices do grafo
/// @param origem ID do vértice de origem
/// @param destino ID do vértice de destino
/// @return Ponteiro para o primeiro elemento da lista de caminho, 
///         que contém os vértices e suas distâncias acumuladas; 
///         retorna NULL se não houver caminho ou se algum dos vértices não for encontrado
Caminho* BuscaEmLargura(Vertice *grafo, int origem, int destino) {
    // Retorna NULL se o grafo estiver vazio
    if (grafo == NULL) {
        return NULL;
    }
    Caminho *caminho = NULL; // inicializar caminho como NULL

    if(origem == destino) { // se o destino for igual á origim, retorna um caminho com apenas um vértice (distancia 0)
        caminho = (Caminho *)malloc(sizeof(Caminho));
        caminho->idVertice = origem;
        caminho->distancia = 0;
        caminho->distanciaTotal = 0;
        caminho->proximo = NULL;
        return caminho;
    }

    // Limpar o campo visitado de todos os vértices
    LimparCamposGrafo(grafo);

    // Encontrar os vértices de origem e destino usando ProcuraVertice
    Vertice *verticeOrigem = ProcuraVertice(grafo, origem);
    Vertice *verticeDestino = ProcuraVertice(grafo, destino);

    // Retorna NULL se não encontrar os vértices de origem ou destino
    if (verticeOrigem == NULL || verticeDestino == NULL) {
        return NULL;
    }

    // Inicializar a fila vazia
    Fila *fila = CriarFila();

    // Adicionar o vértice de origem à fila e marcá-lo como visitado
    Enfileirar(fila, verticeOrigem);
    verticeOrigem->visitado = 1;
    verticeOrigem->distancia = 0;
    verticeOrigem->predecessor = -1;
    int encontrouDestino = 0;

    // Processar vértices na fila até que esteja vazia
    while (!EstaVazia(fila) && !encontrouDestino ) {
        Vertice *verticeAtual = RetiraDaFila(fila);
        Adjacente *adjacenteAtual = verticeAtual->adjacentes;

        // Verificar todos os vértices adjacentes ao vértice atual
        while (adjacenteAtual) {
            Vertice *adjacente = ProcuraVertice(grafo, adjacenteAtual->idVertice);

            if (!adjacente->visitado) {
                // Marcar vértice adjacente como visitado e adicioná-lo à fila
                adjacente->visitado = 1;
                Enfileirar(fila, adjacente);

                // Armazene o predecessor e a distância para o vértice adjacente
                adjacente->predecessor = verticeAtual->idVertice;
                adjacente->distancia = verticeAtual->distancia + adjacenteAtual->distancia;
                
                // Se encontrarmos o vértice de destino, podemos parar de procurar
                if (adjacente->idVertice == destino) {
                    encontrouDestino = 1;
                    break;
                }
            }
            adjacenteAtual = adjacenteAtual->proximo;
        }
    }

    // Se não encontrarmos um caminho para o destino, retorna NULL
    if (verticeDestino->predecessor == -1) {
        return NULL;
    }
    // Construir a lista de vértices do caminho usando predecessores e distâncias
    
    Vertice *atual = verticeDestino;
    while (atual != NULL) {
        Caminho *novoCaminho = CriarCaminho(atual->idVertice, atual->distancia);
        novoCaminho->proximo = caminho;
        caminho = novoCaminho;

        if (atual->predecessor == -1) {
            atual = NULL;
        } else {
            atual = ProcuraVertice(grafo, atual->predecessor);
        }
    }

    // Armazenar a distância total do caminho no nó principal do caminho
    if (caminho != NULL) {
        caminho->distanciaTotal = verticeDestino->distancia;
    }
    return caminho;
}




int ProcurarCentroRecolha(struct Vertice* headGrafo) {
    Vertice* currentVertice = headGrafo;

    while (currentVertice != NULL) {
        if (strncmp(currentVertice->cidade, PREFIX_CR, 3) == 0) { // Verifica se o nome do local começa com "CR_"
            return currentVertice->idVertice;
        }
        currentVertice = currentVertice->proximo;
    }

    // Retorna -1 se não encontrar o centro de recolha
    return -1;
}



/// @brief Encontra um caminho aproximado para recolher todos os transportes usando uma abordagem greedy.
/// @param transportes Um ponteiro para a estrutura NodeTransporte que representa a lista de transportes a ser recolhida
/// @param grafo Um ponteiro para a estrutura Vertice que representa o grafo
/// @param centroRecolha A localização do centro de recolha
/// @return Um ponteiro para a estrutura Caminho que representa o caminho aproximado para recolher os transportes
Caminho* GreedySearch(NodeTransporte *transportes, Vertice *grafo, int centroRecolha) {
    // Inicializa o caminho final como NULL e define o local atual como o centro de recolha
    Caminho *caminho = NULL;
    int localAtual = centroRecolha;

    // Limpa os campos "visitado" dos transportes
    LimparCamposTransportes(transportes);

    // Enquanto houver transportes não visitados
    while (ExistemTransportesNaoVisitados(transportes)) {
        NodeTransporte *transporteMaisProximo = NULL;
        Caminho *caminhoMaisCurto = NULL;
        float distanciaMaisCurta = INFINITY;

        // Itera pelos transportes
        for (NodeTransporte *transporteAux = transportes; transporteAux != NULL; transporteAux = transporteAux->proximo) {
            // Verifica se o transporte não foi visitado
            if (!transporteAux->transporte.visitado) {
                // Realiza a busca em largura para encontrar o caminho até o transporte
                Caminho *caminhoAux = BuscaEmLargura(grafo, localAtual, transporteAux->transporte.localizacao);

                // Calcula a distância do caminho encontrado
                float distanciaAux = DistanciaCaminho(caminhoAux);

                // Atualiza o transporte mais próximo, se necessário
                if (distanciaAux < distanciaMaisCurta) {   
                    // Verifica se a distância até o transporte atual é menor do que a menor distância encontrada até agora
                    
                    distanciaMaisCurta = distanciaAux;
                    // Se for, atualiza a menor distância encontrada até agora para a distância até o transporte atual
                    
                    transporteMaisProximo = transporteAux;
                    // E atualiza o transporte mais próximo para o transporte atual

                    if (caminhoMaisCurto != NULL) {
                        FreeCaminho(caminhoMaisCurto);
                    }
                    caminhoMaisCurto = caminhoAux;
                } else {
                    FreeCaminho(caminhoAux);
                }
            }
        }

        // Atualiza o caminho total e marca o transporte como visitado e altera o local atual
        if (transporteMaisProximo != NULL) {
            transporteMaisProximo->transporte.visitado = 1;
            localAtual = transporteMaisProximo->transporte.localizacao;

            // Adiciona o caminho mais curto ao caminho total
            caminho = ConcatenarCaminhos(caminho, caminhoMaisCurto);
        }
    }

    // Adiciona o caminho de volta ao centro de recolha
    Caminho *caminhoVolta = BuscaEmLargura(grafo, localAtual, centroRecolha);

    // Concatena o caminho de volta ao caminho total
    caminho = ConcatenarCaminhos(caminho, caminhoVolta);
    printf("Distância TOTAL CAMINHO VOLTA: %.2f\n", caminhoVolta->distanciaTotal);
    // Retorna o caminho total encontrado
    return caminho;
}


/// @brief Verifica se existem transportes não visitados na lista de transportes
/// @param transportes Um ponteiro para a lista encadeada de estruturas NodeTransporte
/// @return Retorna 1 se houver transportes não visitados, caso contrário retorna 0
int ExistemTransportesNaoVisitados(NodeTransporte *transportes) {
    NodeTransporte *aux = transportes;

    while (aux != NULL) {
        if (aux->transporte.visitado == 0) {
            return 1;
        }
        aux = aux->proximo;
    }

    return 0;
}