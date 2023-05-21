#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Headers/caminho.h"
#include "../Headers/busca.h"
#include "../Headers/grafo.h"
#include "../Headers/fila.h"

#define CAPACIDADE_CAMIAO 1000
#define PREFIX_CR "CR_" // Prefixo do Centro de recolha

Caminho* Dijkstra(Vertice* grafo, int origem, int destino) {
    // Se origem e destino são iguais, retorna um caminho com um único vértice e distância 0
    if (origem == destino) {
        return CaminhoUnicoVertice(origem);
    }

    // Inicializa todos os vértices
    LimparCamposGrafo(grafo);

    // Procura os vértices de origem e destino
    Vertice* verticeOrigem = ProcuraVertice(grafo, origem);
    Vertice* verticeDestino = ProcuraVertice(grafo, destino);

    // Se algum dos vértices não for encontrado, retorna NULL
    if (verticeOrigem == NULL || verticeDestino == NULL) {
        return NULL;
    }

    // Define a distância do vértice de origem como 0
    verticeOrigem->distancia = 0;

    // Cria a fila de prioridade e adiciona o vértice de origem
    FilaPrioridade* fila = CriarFilaPrioridade();
    fila = AdicionarNaFila(fila, verticeOrigem);
    
    // Loop enquanto a fila não estiver vazia
    while (!EstaVazia(fila)) {
        // Retira o vértice na frente da fila e marca como visitado
        Vertice* verticeAtual = RetirarDaFila(&fila);
        verticeAtual->visitado = 1;

        // Loop por todos os vértices adjacentes ao vértice atual
        Adjacente* adjacenteAtual = verticeAtual->adjacentes;
        while (adjacenteAtual != NULL) {
            // Procura o vértice adjacente na lista de vértices
            Vertice* adjacente = ProcuraVertice(grafo, adjacenteAtual->idVertice);
            
            // Calcula a nova distância do vértice adjacente
            float novaDistancia = verticeAtual->distancia + adjacenteAtual->distancia;

            // Se a nova distância for menor que a atual, atualiza a distância e o predecessor
            if (novaDistancia < adjacente->distancia) {
                adjacente->distancia = novaDistancia;
                adjacente->predecessor = verticeAtual->idVertice;

                // Se o vértice adjacente ainda não foi visitado, adiciona na fila
                if (!adjacente->visitado) {
                    fila = AdicionarNaFila(fila, adjacente);
                }
            }

            // Vai para o próximo adjacente
            adjacenteAtual = adjacenteAtual->proximo;
        }
    }

    // Se não há caminho para o destino, retorna NULL
    if (verticeDestino->predecessor == -1) {
        return NULL;
    }


    Caminho* caminho = ConstruirCaminho(grafo, destino);
    // Define a distância total do caminho
    caminho->distanciaTotal = verticeDestino->distancia;

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
    Caminho *caminho = NULL;
    int localAtual = centroRecolha;
    Camiao *camiao = InicializarCamiao(CAPACIDADE_CAMIAO);
    if (camiao == NULL) {
        return NULL;
    }    
        LimparCamposTransportes(transportes);

    while (ExistemTransportesNaoVisitados(transportes)) {
        NodeTransporte *transporteMaisProximo = NULL;
        Caminho *caminhoMaisCurto = NULL;
        float distanciaMaisCurta = INFINITY;

        for (NodeTransporte *transporteAux = transportes; transporteAux != NULL; transporteAux = transporteAux->proximo) {
            if (!transporteAux->transporte.visitado) {
                Caminho *caminhoAux = Dijkstra(grafo, localAtual, transporteAux->transporte.localizacao);
                float distanciaAux = DistanciaCaminho(caminhoAux);
                if (distanciaAux < distanciaMaisCurta) {
                    distanciaMaisCurta = distanciaAux;
                    transporteMaisProximo = transporteAux;
                    if (caminhoMaisCurto != NULL) {
                        FreeCaminho(caminhoMaisCurto);
                    }
                    caminhoMaisCurto = caminhoAux;
                } else {
                    FreeCaminho(caminhoAux);
                }
            }
        }

        if (transporteMaisProximo != NULL) {
            if (camiao->cargaAtual + transporteMaisProximo->transporte.tipo->peso > camiao->capacidadeMaxima) {
                Caminho *caminhoVolta = Dijkstra(grafo, localAtual, centroRecolha);
                caminho = ConcatenarCaminhos(caminho, caminhoVolta);
                localAtual = centroRecolha;
                camiao->cargaAtual = 0; // Camião vazio
                RecarregarTransportes(transportes); // Recarregar bateria de todos os transportes visitados
                MoverTransportesParaCentro(transportes, centroRecolha); // mover todos os transportes visitados 
                // para o centro de recolha
            }
            transporteMaisProximo->transporte.visitado = 1;
            localAtual = transporteMaisProximo->transporte.localizacao;
            caminho = ConcatenarCaminhos(caminho, caminhoMaisCurto);
            camiao->cargaAtual += transporteMaisProximo->transporte.tipo->peso;
        }
    }

    // Recarregar e mover para o centro os transportes restantes
    RecarregarTransportes(transportes);
    MoverTransportesParaCentro(transportes, centroRecolha);

    Caminho *caminhoVolta = Dijkstra(grafo, localAtual, centroRecolha);
    caminho = ConcatenarCaminhos(caminho, caminhoVolta);

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