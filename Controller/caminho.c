#include "../Headers/caminho.h"
#include <stdlib.h>
#include <math.h>

/// @brief Cria um novo elemento de caminho com as informações fornecidas
/// @param idVertice ID do vértice no elemento de caminho
/// @param distancia Distância acumulada até este vértice no caminho
/// @return Ponteiro para o novo elemento de caminho criado      
Caminho* CriarCaminho(int idVertice, float distancia) {
    Caminho *novoCaminho = (Caminho *)malloc(sizeof(Caminho));
    novoCaminho->idVertice = idVertice;
    novoCaminho->distancia = distancia;
    novoCaminho->proximo = NULL;
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
