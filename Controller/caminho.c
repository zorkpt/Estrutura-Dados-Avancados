/**
 * @file caminho.c
 * @author Hugo Poças
 * @brief Este ficheiro contém as funções de caminho.
 * @version 0.2
 * @date 27-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../Headers/caminho.h"
#include "../Headers/grafo.h"
#include <stdlib.h>
#include <math.h>

/// @brief Cria um novo elemento de caminho com as informações fornecidas
/// @param idVertice ID do vértice no elemento de caminho
/// @param distancia Distância acumulada até este vértice no caminho
/// @return Ponteiro para o novo elemento de caminho criado      
Caminho* CriarCaminho(int idVertice, float distancia) {
    Caminho* novoCaminho = (Caminho*)malloc(sizeof(Caminho));
    novoCaminho->idVertice = idVertice;
    novoCaminho->distancia = distancia;
    novoCaminho->proximo = NULL;
    novoCaminho->distanciaTotal = 0;
    return novoCaminho;
}



/// @brief Vê o valor de distância do último node.
/// @param caminho Um ponteiro para a estrutura Caminho que representa o caminho a ser analisado.
/// @return A distância total do caminho fornecido. Retorna INFINITY se o caminho for NULL.
float DistanciaCaminho(Caminho *caminho) {
    if (caminho == NULL) {
        return INFINITY;
    }
    return caminho->distanciaTotal;
}



/// @brief Liberta a memória alocada para uma lista encadeada de estruturas Caminho
/// @param caminho Um ponteiro para a estrutura Caminho que representa o caminho a ser Libertado
void FreeCaminho(Caminho *caminho) {
    Caminho *aux;
    while (caminho != NULL) {
        aux = caminho;
        caminho = caminho->proximo;
        free(aux);
    }
}



/// @brief Concatena dois caminhos
/// @param caminho1 Um ponteiro para a lista encadeada de estruturas Caminho, o primeiro caminho a ser concatenado
/// @param caminho2 Um ponteiro para a lista encadeada de estruturas Caminho, o segundo caminho a ser concatenado
/// @return Retorna um ponteiro para o novo caminho concatenado
Caminho* ConcatenarCaminhos(Caminho *caminho1, Caminho *caminho2) {
    // Se o primeiro caminho é NULL, retorna o segundo caminho
    if (caminho1 == NULL) {
        return caminho2;
    }

    // Se o segundo caminho é NULL, retorna o primeiro caminho
    if (caminho2 == NULL) {
        return caminho1;
    }

    // Encontra o último nó do primeiro caminho para poder concatenar o segundo caminho
    Caminho *ultimoCaminho1 = caminho1;
    while (ultimoCaminho1->proximo != NULL) {
        ultimoCaminho1 = ultimoCaminho1->proximo;
    }

    // Concatena o segundo caminho ao final do primeiro caminho
    ultimoCaminho1->proximo = caminho2->proximo;

    // Atualiza a distância total no primeiro nó do caminho concatenado
    caminho1->distanciaTotal += caminho2->distanciaTotal;

    return caminho1;
}


/// @brief Cria um único caminho (lista de vértices) com o vértice de origem dado
/// @param origem O ID do vértice de origem
/// @return Um ponteiro para o caminho criado
Caminho* CaminhoUnicoVertice(int origem) {
    // Alocando memória para o novo caminho
    Caminho* caminho = (Caminho*) malloc(sizeof(Caminho));
    if (caminho == NULL) {
        return NULL;  // Retornar NULL se a alocação de memória falhar
    }

    // Inicializando o caminho com os valores fornecidos
    caminho->idVertice = origem;
    caminho->distancia = 0.0;
    caminho->distanciaTotal = 0.0;
    caminho->proximo = NULL;
    return caminho;
}


/// @brief Constrói o caminho de retorno a partir de um vértice de destino no grafo
/// @param grafo O grafo que contém o vértice de destino
/// @param destino O ID do vértice de destino
/// @return Um ponteiro para o caminho construído
Caminho* ConstruirCaminho(Vertice* grafo, int destino) {
    // Procura o vértice de destino no grafo
    Vertice* verticeDestino = ProcuraVertice(grafo, destino);

    // Se o predecessor do vértice de destino é -1, isso significa que não há caminho para o destino,
    // então a função retorna NULL
    if (verticeDestino->predecessor == -1) {
        return NULL;
    }

    // Inicializa um ponteiro para o caminho como NULL
    Caminho* caminho = NULL;

    // Começa a partir do vértice de destino
    Vertice* atual = verticeDestino;

    // Continua até que não haja mais predecessores
    while (atual != NULL) {
        // Cria um novo elemento no caminho usando a função CriarCaminho
        Caminho* novoCaminho = CriarCaminho(atual->idVertice, atual->distancia);

        // Se a alocação falhou, liberar a memória já alocada e retornar NULL
        if (novoCaminho == NULL) {
            FreeCaminho(caminho);
            return NULL;
        }

        // Define o próximo elemento do caminho como o caminho atual
        novoCaminho->proximo = caminho;

        // Define o caminho atual como o novo caminho
        caminho = novoCaminho;

        // Move para o predecessor do vértice atual se houver um, caso contrário, define atual como NULL
        if (atual->predecessor != -1) {
            atual = ProcuraVertice(grafo, atual->predecessor);
        } else {
            atual = NULL;
        }
    }

    // Define a distância total do caminho como a distância do vértice de destino
    caminho->distanciaTotal = verticeDestino->distancia;

    // Retorna o caminho construído
    return caminho;
}



/// @brief Imprime o caminho percorrido pelo camião
/// @param caminho O caminho percorrido pelo camião
/// @param centroRecolha A localização do centro de recolha
void ImprimirCaminho(Caminho *caminho, int centroRecolha) {
    // Verifica se o caminho é nulo
    if (caminho == NULL) {
        printf("Caminho não encontrado.\n");
        return;
    }

    // Inicializa a contagem de passos e a distância total
    int passo = 1;
    float distanciaTotal = caminho->distanciaTotal;
    int localizacaoAtual = caminho->idVertice;
    int deixouCentroRecolha = 0;

    printf("Caminho encontrado:\n");

    // Percorre o caminho
    for (Caminho *aux = caminho; aux != NULL; aux = aux->proximo) {
        int idVertice = aux->idVertice;
        float distancia = aux->distancia;
        
        // Verifica a localização atual e a próxima para determinar a ação do caminhão
        if (localizacaoAtual == centroRecolha && idVertice != centroRecolha && !deixouCentroRecolha) {
            printf("O camião deixou o centro de recolha e se dirigiu ao vértice %d\n", idVertice);
            deixouCentroRecolha = 1;
        } else if (localizacaoAtual != centroRecolha && idVertice == centroRecolha && (aux->proximo == NULL || aux->proximo->idVertice == centroRecolha)) {
            printf("O camião retornou ao centro de recolha para descarregar os transportes recolhidos\n");
            deixouCentroRecolha = 0;
        } else if (localizacaoAtual != centroRecolha && idVertice != centroRecolha) {
            printf("O camião se moveu do vértice %d para o vértice %d com a distância de %.2f\n", localizacaoAtual, idVertice, distancia);
        }

        // Atualiza a localização atual para a próxima no caminho
        localizacaoAtual = idVertice;
        passo++;
    }

    // Imprime a distância total percorrida
    printf("Distância total: %.2f\n", distanciaTotal);
}

