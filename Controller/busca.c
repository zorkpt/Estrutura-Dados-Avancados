/**
 * @file busca.c
 * @author Hugo Poças
 * @brief Este ficheiro contém as funções de busca de caminhos.
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

#include "../Headers/caminho.h"
#include "../Headers/busca.h"
#include "../Headers/grafo.h"
#include "../Headers/fila.h"

#define CAPACIDADE_CAMIAO 10
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

/// @brief Procura o centro de recolha na lista de vértices (locais)
/// @param headGrafo Ponteiro para o vértice inicial da lista
/// @return O ID do centro de recolha se encontrado, ou -1 se não encontrado
int ProcurarCentroRecolha(struct Vertice* headGrafo) {
    Vertice* currentVertice = headGrafo;

    // Itera através da lista de vértices
    while (currentVertice != NULL) {
        // Verifica se o nome do local começa com "CR_", o que indica um centro de recolha
        if (strncmp(currentVertice->cidade, PREFIX_CR, strlen(PREFIX_CR)) == 0) {
            // Se encontrado, retorna o ID desse vértice
            return currentVertice->idVertice;
        }
        // Avança para o próximo vértice na lista
        currentVertice = currentVertice->proximo;
    }

    // Retorna -1 se o centro de recolha não for encontrado
    return -1;
}


/// @brief Encontra um caminho aproximado para recolher todos os transportes usando uma abordagem greedy.
/// @param transportes Um ponteiro para a estrutura NodeTransporte que representa a lista de transportes a ser recolhida
/// @param grafo Um ponteiro para a estrutura Vertice que representa o grafo
/// @param centroRecolha A localização do centro de recolha
/// @return Um ponteiro para a estrutura Caminho que representa o caminho aproximado para recolher os transportes
Caminho* GreedySearch(NodeTransporte *transportes, Vertice *grafo, int centroRecolha) {
    // Cria a lista de transportes a serem recolhidos.
    NodeTransporte* transportesARecolher = TransportesARecolher(transportes);

    // Inicialização do caminho e localização atual
    Caminho *caminho = NULL;
    int localAtual = centroRecolha;

    // Inicialização do camião
    Camiao *camiao = InicializarCamiao(CAPACIDADE_CAMIAO);
    if (camiao == NULL) {
        return NULL;
    }
    
    LimparCamposTransportes(transportesARecolher);

    // Continuar o processo enquanto existirem transportes não visitados na lista
    while (ExistemTransportesNaoVisitados(transportesARecolher)) {
        // Inicialização das variáveis ​​para o transporte mais próximo e o caminho mais curto
        NodeTransporte *transporteMaisProximo = NULL;
        Caminho *caminhoMaisCurto = NULL;
        float distanciaMaisCurta = INFINITY;

        // Procurar pelo transporte mais próximo
        for (NodeTransporte *transporteAux = transportesARecolher; transporteAux != NULL; transporteAux = transporteAux->proximo) {
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

        // Verificar a carga do camião e voltar ao centro de recolha se necessário
        if (transporteMaisProximo != NULL && camiao->cargaAtual + transporteMaisProximo->transporte.tipo->peso > camiao->capacidadeMaxima) {
            Caminho *caminhoVolta = Dijkstra(grafo, localAtual, centroRecolha);
            caminho = ConcatenarCaminhos(caminho, caminhoVolta);
            localAtual = centroRecolha;
            camiao->cargaAtual = 0; // esvaziar camiao
            RecarregarTransportes(transportesARecolher, transportes); // recarregar bateria transportes recolhidos ate agora
            MoverTransportesParaCentro(transportesARecolher, transportes, centroRecolha); // mover transportes recolhidos ate agora para o centro
        }

        // Marcar o transporte como visitado e atualizar a localização atual e a carga do camião
        if (transporteMaisProximo != NULL) {
            transporteMaisProximo->transporte.visitado = 1;
            localAtual = transporteMaisProximo->transporte.localizacao;
            caminho = ConcatenarCaminhos(caminho, caminhoMaisCurto);
            camiao->cargaAtual += transporteMaisProximo->transporte.tipo->peso;
        }
    }

    // Recarregar e mover para o centro os transportes restantes
    RecarregarTransportes(transportesARecolher, transportes);
    MoverTransportesParaCentro(transportesARecolher, transportes, centroRecolha);

    // Voltar ao centro de recolha
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

/// @brief Adiciona um transporte ao início da lista de transportes
/// @param headTransporte é um duplo ponteiro para a cabeça da lista de transportes.
/// @param transporte é a estrutura de transporte que você deseja adicionar à lista.
void AdicionarTransporteALista(NodeTransporte** headTransporte, Transporte transporte) {
    NodeTransporte* novoTransporte = (NodeTransporte*) malloc(sizeof(NodeTransporte));
    novoTransporte->transporte = transporte;
    novoTransporte->proximo = (*headTransporte);
    (*headTransporte) = novoTransporte;
}

/// @brief Cria uma nova lista de transportes que precisam ser recolhidos.
/// @param transportes é a lista original de transportes.
/// @return Uma nova lista contendo apenas transportes que precisam ser recolhidos.
NodeTransporte* TransportesARecolher(NodeTransporte* transportes) {
    NodeTransporte* transportesARecolher = NULL;
    for (NodeTransporte *transporteAux = transportes; transporteAux != NULL; transporteAux = transporteAux->proximo) {
        // Um transporte precisa ser recolhido se o nível de bateria for inferior a 50 e o estado for 0 (não em uso).
        if (transporteAux->transporte.nivelBateria < 50 && transporteAux->transporte.estado == 0) { 
            AdicionarTransporteALista(&transportesARecolher, transporteAux->transporte);
        }
    }
    return transportesARecolher;
}
