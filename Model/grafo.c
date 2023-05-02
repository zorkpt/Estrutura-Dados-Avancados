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

/// @brief Insere um novo vértice no grafo, mantendo a ordem crescente dos IDs dos vértices.
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
/// @return Retorna o ponteiro para o grafo atualizado ou NULL se a operação falhar
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

    return grafo;
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
/// @param grafo 
/// @param localID 
/// @return 
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
        verticeAux->distancia = 0;
        verticeAux = verticeAux->proximo;
    }
}

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

    // construir a lista de vértices do caminho usando predecessores e distâncias
    Caminho *caminho = NULL;
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

    return caminho;
}

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



/// @brief Vê o valor de distância do último node.
/// @param caminho Um ponteiro para a estrutura Caminho que representa o caminho a ser analisado.
/// @return A distância total do caminho fornecido. Retorna INFINITY se o caminho for NULL.
float DistanciaCaminho(Caminho *caminho) {
    if (caminho == NULL) {
        return INFINITY;
    }

    float distancia = 0;
    while (caminho != NULL) {
        distancia = caminho->distancia;
        caminho = caminho->proximo;
    }

    return distancia;
}

/// @brief Procura o transporte mais próximo de um cliente
/// @param listaTransportes A lista de transportes disponíveis
/// @param grafo O grafo que representa a mapa dos transportes
/// @param localCliente O ID do vértice que representa o local do cliente
/// @return Retorna um ponteiro para o transporte mais próximo ou NULL se nenhum transporte estiver disponível
NodeTransporte *ProcuraTransporteMaisProximo(NodeTransporte *listaTransportes, Vertice *grafo, int localCliente) {
    NodeTransporte *transporteAtual = listaTransportes;
    NodeTransporte *transporteMaisProximo = NULL;
    float menorDistancia = INFINITY;

    while (transporteAtual != NULL) {
        if (transporteAtual->transporte.estado == 0) { // Verifica se o transporte está disponível
            Caminho *caminho = BuscaEmLargura(grafo, localCliente, transporteAtual->transporte.localizacao);
            if(caminho == NULL) {
                return NULL;
            }
            
            float distancia = DistanciaCaminho(caminho);

            if (distancia != INFINITY) {
                if (distancia < menorDistancia) {
                    menorDistancia = distancia;
                    transporteMaisProximo = transporteAtual;
                }
            }
        }
        transporteAtual = transporteAtual->proximo;
    }

    return transporteMaisProximo;
}


