#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Headers/verificacoes.h"
#define BUFFER_SIZE 1024



Vertice* CriarVertice(int idVertice, char cidade[]){

	static int totalVertices = 0;

	Vertice* novo = (Vertice*)calloc(1,sizeof(Vertice));
	if(novo == NULL){
		return NULL;
	}

	novo->idVertice = idVertice;
	strcpy(novo->cidade, cidade);
	novo->proximo = NULL;

	return novo;
}

Vertice* InsereVertice(Vertice *grafo, Vertice* novo){

	Vertice* aux = grafo;
	Vertice* anterior = aux;

	if(grafo == NULL){
		grafo = novo;
		return grafo;
	}

	while(aux && aux->idVertice != novo->idVertice){
		anterior = aux;
		aux = aux->proximo;
	}

    if (anterior == NULL) {
        novo->proximo = grafo;
        grafo = novo;
    } else {
        novo->proximo = anterior->proximo;
        anterior->proximo = novo;
    }

    return grafo;
}

void MostrarGrafo(Vertice* grafo){

	if(grafo==NULL){
		return;
	}

	Vertice* aux = grafo;

	while(aux != NULL){
		printf("ID: %d\tCidade: %s\n", aux->idVertice, aux->cidade);
		aux = aux->proximo;
	}
}

Vertice* InsereAdjacente(Vertice *grafo, int origem, int destino, float distancia){

	Vertice* aux = grafo;

	if(grafo == NULL){
		return NULL;
	}

	while(aux && aux->idVertice != origem){
		aux = aux->proximo;
	}

	if(aux == NULL){
		return NULL;
	}

	Adjacente* headAdjacent = aux->adjacentes;	
	Adjacente* novo = CriaAdjacente(destino, distancia); // Pass the values to the function

	// Insert the new Adjacente node at the beginning of the list
	novo->proximo = headAdjacent;
	aux->adjacentes = novo;

	return grafo;
}

Adjacente *CriaAdjacente(int idVertice, float distancia) { // Add parameters to the function
	Adjacente *novo = (Adjacente *)malloc(sizeof(Adjacente));
	novo->idVertice = idVertice;
	novo->distancia = distancia;
	novo->proximo = NULL;
	return novo;
}



void PrintGrafo(Vertice *grafo) {
    Vertice *vertex = grafo;

    while (vertex) {
        printf("ID: %d\tCidade: %s\n", vertex->idVertice, vertex->cidade);
        
        Adjacente *adjacent = vertex->adjacentes;
        while (adjacent) {
            printf("  -> ID: %d\tDistancia: %.2f\n", adjacent->idVertice, adjacent->distancia);
            adjacent = adjacent->proximo;
        }
        
        printf("\n");
        vertex = vertex->proximo;
    }
}


void read_csv_file(char *filename, Vertice **graph) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open the file. dir errada\n");
        return;
    }

    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, file); // Skip the header

    while (fgets(buffer, BUFFER_SIZE, file)) {
        int id, adj1, dist1, adj2, dist2, adj3, dist3;
        char title[256];
        sscanf(buffer, "%d,%[^,],%d,%d,%d,%d,%d,%d", &id, title, &adj1, &dist1, &adj2, &dist2, &adj3, &dist3);

        Vertice *new_vertex = CriarVertice(id, title);
        *graph = InsereVertice(*graph, new_vertex);

        *graph = InsereAdjacente(*graph, id, adj1, dist1);
        *graph = InsereAdjacente(*graph, id, adj2, dist2);
        if (adj3) {
            *graph = InsereAdjacente(*graph, id, adj3, dist3);
        }
    }

    fclose(file);
}

int location_exists(Vertice *graph, int location_id) {
    Vertice *current = graph;
    while (current) {
        if (current->idVertice == location_id) {
            return 1;
        }
        current = current->proximo;
    }
    return 0;
}


const char* GetLocationName(Vertice *grafo, int location_id) {
    Vertice *current = grafo;
    while (current != NULL) {
        if (current->idVertice == location_id) {
            return current->cidade;
        }
        current = current->proximo;
    }
    return NULL;
}


Caminho* BuscaEmLargura(Vertice *grafo, int origem, int destino) {
    if (grafo == NULL) {
        return NULL;
    }

    Vertice *verticeAux = grafo;
    Vertice *verticeOrigem = NULL;
    Vertice *verticeDestino = NULL;

    while (verticeAux) {
        if (verticeAux->idVertice == origem) {
            verticeOrigem = verticeAux;
        }
        if (verticeAux->idVertice == destino) {
            verticeDestino = verticeAux;
        }
        verticeAux = verticeAux->proximo;
    }

    if (verticeOrigem == NULL || verticeDestino == NULL) {
        return NULL;
    }

    Fila *fila = CriarFila();
    int visitado[1000] = {0};
    int predecessor[1000] = {-1};
    float distancia[1000] = {0};

    enfileirar(fila, verticeOrigem);
    visitado[verticeOrigem->idVertice] = 1;
    distancia[verticeOrigem->idVertice] = 0;

    while (!estaVazia(fila)) {
        Vertice *verticeAtual = desenfileirar(fila);
        Adjacente *adjacenteAtual = verticeAtual->adjacentes;

        while (adjacenteAtual) {
            int idAdjacente = adjacenteAtual->idVertice;
            if (!visitado[idAdjacente]) {
                visitado[idAdjacente] = 1;
                enfileirar(fila, BuscarVertice(grafo, idAdjacente));
                predecessor[idAdjacente] = verticeAtual->idVertice;
                distancia[idAdjacente] = distancia[verticeAtual->idVertice] + adjacenteAtual->distancia;

                if (idAdjacente == destino) {
                    break;
                }
            }
            adjacenteAtual = adjacenteAtual->proximo;
        }
    }

    if (predecessor[verticeDestino->idVertice] == -1) {
        return NULL;
    }

    // Construir a lista de vértices do caminho
    Caminho *caminho = NULL;
    int atual = destino;
    while (atual != -1) {
        Caminho *novoCaminho = (Caminho *)malloc(sizeof(Caminho));
        novoCaminho->idVertice = atual;
        novoCaminho->distancia = distancia[atual];
        novoCaminho->proximo = caminho;
        caminho = novoCaminho;
        atual = predecessor[atual];
    }

    return caminho;
}

Fila* CriarFila() {
    Fila *novaFila = (Fila *)malloc(sizeof(Fila));
    if (!novaFila) {
        return NULL;
    }
    novaFila->front = NULL;
    novaFila->rear = NULL;
    return novaFila;
}



// Função para enfileirar um elemento na fila
void enfileirar(Fila *fila, Vertice *vertice) {
    NoFila *novoNo = (NoFila *)malloc(sizeof(NoFila));
    novoNo->vertice = vertice;
    novoNo->proximo = NULL;

    if (fila->rear == NULL) {
        fila->front = novoNo;
        fila->rear = novoNo;
        return;
    }

    fila->rear->proximo = novoNo;
    fila->rear = novoNo;
}


// Função para desenfileirar um elemento da fila
// Retorna o elemento desenfileirado
Vertice* desenfileirar(Fila *fila) {
    if (fila->front == NULL) {
        return NULL;
    }

    NoFila *noASerRemovido = fila->front;
    Vertice *verticeRemovido = noASerRemovido->vertice;

    fila->front = noASerRemovido->proximo;

    if (fila->front == NULL) {
        fila->rear = NULL;
    }

    free(noASerRemovido);
    return verticeRemovido;
}


// Função para verificar se a fila está vazia
// Retorna 1 se a fila estiver vazia, caso contrário retorna 0
int estaVazia(Fila *fila) {
    return fila->front == NULL;
}

// Função para contar o número de vértices no grafo
// Retorna o número de vértices
int contarVertices(Vertice *grafo) {
    int contador = 0;
    Vertice *verticeAtual = grafo;

    while (verticeAtual != NULL) {
        contador++;
        verticeAtual = verticeAtual->proximo;
    }

    return contador;
}

// Função para encontrar um vértice no grafo pelo seu ID
// Retorna um ponteiro para o vértice encontrado ou NULL se não for encontrado
Vertice *encontrarVertice(Vertice *grafo, int idVertice) {
    Vertice *verticeAtual = grafo;

    while (verticeAtual != NULL) {
        if (verticeAtual->idVertice == idVertice) {
            return verticeAtual;
        }
        verticeAtual = verticeAtual->proximo;
    }

    return NULL;
}



Vertice* BuscarVertice(Vertice *grafo, int idVertice) {
    Vertice *aux = grafo;
    while (aux) {
        if (aux->idVertice == idVertice) {
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}


NodeTransporte *BuscarTransporteMaisProximo(NodeTransporte *listaTransportes, Vertice *grafo, int localCliente) {
    NodeTransporte *transporteAtual = listaTransportes;
    NodeTransporte *transporteMaisProximo = NULL;
    float menorDistancia = INFINITY;
    
    while (transporteAtual != NULL) {
        if (transporteAtual->transporte.estado == 0) { // Verifica se o transporte está disponível
            Caminho *caminho = BuscaEmLargura(grafo, localCliente, transporteAtual->transporte.localizacao);
            if (caminho != NULL) {
                float distancia = caminho->distancia;
                if (distancia < menorDistancia) {
                    menorDistancia = distancia;
                    transporteMaisProximo = transporteAtual;
                }
            }
            // Libere a memória alocada para a estrutura Caminho, se necessário
            // Por exemplo: LiberarCaminho(caminho);
        }
        transporteAtual = transporteAtual->proximo;
    }

    return transporteMaisProximo;
}




float DistanciaEntreVertices(Vertice *grafo, int origem, int destino) {
    Caminho *caminho = BuscaEmLargura(grafo, origem, destino);
    if (caminho == NULL) {
        return INFINITY;
    }
    float distancia = caminho->distancia;
    // Libere a memória alocada para a estrutura Caminho, se necessário
    // Por exemplo: LiberarCaminho(caminho);
    return distancia;
}