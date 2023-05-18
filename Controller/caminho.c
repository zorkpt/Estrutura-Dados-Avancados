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


Caminho* CaminhoUnicoVertice(int origem) {
    Caminho* caminho = malloc(sizeof(Caminho));
    caminho->idVertice = origem;
    caminho->distancia = 0.0;
    caminho->proximo = NULL;
    caminho->distanciaTotal = 0.0;
    return caminho;
}


// Função para construir o caminho de retorno a partir do vértice de destino
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
        // Cria um novo elemento no caminho
        Caminho* novoCaminho = malloc(sizeof(Caminho));

        // Define o ID do vértice e a distância para este vértice
        novoCaminho->idVertice = atual->idVertice;
        novoCaminho->distancia = atual->distancia;

        // Define o próximo elemento do caminho como o caminho atual
        novoCaminho->proximo = caminho;

        // Define o caminho atual como o novo caminho
        caminho = novoCaminho;

        // Move para o predecessor do vértice atual se houver um, caso contrário, define atual como NULL
        if (atual->predecessor == -1) {
            atual = NULL;
        } else {
            atual = ProcuraVertice(grafo, atual->predecessor);
        }
    }

    // Define a distância total do caminho como a distância do vértice de destino
    caminho->distanciaTotal = verticeDestino->distancia;

    // Retorna o caminho construído
    return caminho;
}



void ImprimirCaminho(Caminho *caminho, int centroRecolha) {
    if (caminho == NULL) {
        printf("Caminho não encontrado.\n");
        return;
    }

    int passo = 1;
    float distanciaTotal = caminho->distanciaTotal;
    int localizacaoAtual = caminho->idVertice;

    printf("Caminho encontrado:\n");

    for (Caminho *aux = caminho; aux != NULL; aux = aux->proximo) {
        int idVertice = aux->idVertice;
        float distancia = aux->distancia;
        

        if (localizacaoAtual == centroRecolha && idVertice != centroRecolha) {
            printf("O camião deixou o centro de recolha e se dirigiu ao vértice %d\n", idVertice);
        } else if (localizacaoAtual != centroRecolha && idVertice == centroRecolha) {
            printf("O camião retornou ao centro de recolha para descarregar os transportes recolhidos\n");
        } else if (localizacaoAtual != centroRecolha && idVertice != centroRecolha) {
            printf("O camião se moveu do vértice %d para o vértice %d com a distância de %.2f\n", localizacaoAtual, idVertice, distancia);
        }

        localizacaoAtual = idVertice;
        passo++;
    }

    printf("Distância total: %.2f\n", distanciaTotal);
}
