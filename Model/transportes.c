/**
 * @file transportes.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../Headers/verificacoes.h"
#include "../Headers/caminho.h"
#include "../Headers/busca.h"
#include "../Headers/fila.h"
#include "../Headers/grafo.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRING 100
#define limiteBateria 50


/// @brief Insere uma nova struct de Transportes na lista de NodeTransporte
/// @param headRef Pointer para o head **pointer** da lista de NodeTransporte
/// @param transporte A struct de Transportes a ser inserida
/// @return Retorna 1 se a inserção for bem sucedida, 0 caso contrário
int InserirTransporte(struct NodeTransporte** headRef, struct Transporte transporte) {
    struct NodeTransporte* newNode = (struct NodeTransporte*) malloc(sizeof(struct NodeTransporte));
    if (newNode == NULL) {
        return 0;
    }

    newNode->transporte = transporte;
    newNode->proximo = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        struct NodeTransporte* current = *headRef;
        while (current->proximo != NULL) {
            current = current->proximo;
        }
        current->proximo = newNode;
    }
    return 1;
}

/// @brief Mostra todos os Transportes da lista de NodeTransporte
/// @param head Pointer para o head da lista de NodeTransporte
/// @return Retorna 1 se a lista não estiver vazia, 0 caso contrário
int MostrarTransportes(struct NodeTransporte* head) {
    if (head == NULL) {
        return 0;
    }
    printf("%-5s %-20s %-10s %-10s %-20s %-10s\n", "ID", "TIPO", "BATERIA", "PRECO", "LOCALIZACAO", "ESTADO");
    struct NodeTransporte* current = head;
    while (current != NULL) {
        printf("%-5d %-20s %-10d %-10.2f %-20d %-10d\n",
               current->transporte.id,
               current->transporte.tipo->nome,
               current->transporte.nivelBateria,
               current->transporte.tipo->precoPorKm,
               current->transporte.localizacao,
               current->transporte.estado);
        current = current->proximo;
    }
    return 1;
}

/// @brief Remove um Transporte da lista de NodeTransporte
/// @param head Pointer para o head **pointer** da lista de NodeTransporte
/// @param id ID do transporte a remover
/// @return Retorna 1 se a remoção for bem sucedida, 0 caso contrário
int RemoverTransporte(struct NodeTransporte **head, int id) {
    struct NodeTransporte *current = *head;
    struct NodeTransporte *previous = NULL;

    // Percorre a lista até dar match do ID
    while (current != NULL && current->transporte.id != id) {
        previous = current;
        current = current->proximo;
    }
    // Se for encontrado, removemos da lista
    if (current != NULL) {
        // Se o node for o head da lista, damos update ao pointer do head
        if (previous == NULL) {
            *head = current->proximo;
        }
        // Senão, o node anterior passa apontar para o proximo, dando skip ao atual
        else {
            previous->proximo = current->proximo;
        }
        free(current);
        return 1;
    } else {
        return 0;
    }

}

/// @brief Edita um Transporte da lista de NodeTransporte
/// @param transporte struct de Transporte a editar
/// @param id ID do transporte para manter o mesmo
/// @return Retorna 1 se a edição for bem sucedida, 0 caso contrário      
int EditarTransporte(struct Transporte *transporte, int id, int estado, int nivelBateria, float preco, int localizacao){
    transporte->estado = estado;
    transporte->nivelBateria = nivelBateria;
    transporte->tipo->precoPorKm = preco;
    transporte->localizacao = localizacao;
    transporte->id = id;
    return 1;
}

/// @brief Alterar o estado de um transporte para 1 (ocupado)
/// @param headTransporte Pointer para o head da lista de NodeTransporte
/// @param id ID do transporte a editar
/// @return Retorna 1 se a edição for bem sucedida, 0 caso contrário
int EditarTransporteID(struct NodeTransporte *headTransporte, int id){ 
    struct NodeTransporte* current = headTransporte;
    while (headTransporte != NULL) {
            if (headTransporte->transporte.id == id) {
                headTransporte->transporte.estado = 1;
                return 1;
                }
        headTransporte = headTransporte->proximo;
    }
    return 0;
}



/// @brief  Procura um transporte na lista de NodeTransporte
/// @param headRef Pointer para o head da lista de NodeTransporte
/// @param id ID do transporte a procurar
/// @return Retorna o transporte se encontrado, NULL caso contrário
struct Transporte* ProcurarTransporte(struct NodeTransporte* headRef, int id ){
    struct NodeTransporte *current = headRef;
    while (current != NULL) {
        if (current->transporte.id == id) {
            return &current->transporte;
        }
        current = current->proximo;
    }
    return NULL;
}
/// @brief Procura um transporte na lista de NodeTransporte por localização
/// @param headTransportes Pointer para o head da lista de NodeTransporte
/// @param local Localização a procurar
/// @return Retorna a lista de transportes encontrados, NULL caso contrário
struct NodeTransporte* ProcurarTransportesPorLocal(struct NodeTransporte* headTransportes, int local) {
    struct NodeTransporte* resultHead = NULL;
    struct NodeTransporte* currentNode = headTransportes;

    while (currentNode != NULL) {
        if (currentNode->transporte.localizacao == local) {
            // adiciona o transporte à lista de resultados
            struct NodeTransporte* newNode = (struct NodeTransporte*)malloc(sizeof(struct NodeTransporte));
            newNode->transporte = currentNode->transporte;
            newNode->proximo = resultHead;
            resultHead = newNode;
        }
        currentNode = currentNode->proximo;
    }

    return resultHead;
}

/// @brief Ver todos os transportes disponiveis (estado = 0)
/// @param headTransporte Pointer para o head da lista de NodeTransporte
/// @return Retorna 1 se a operação for bem sucedida
int VerTransportesDisponiveis(struct NodeTransporte* headTransporte, struct Vertice* headGrafo, int localizacaoCliente) {
    struct NodeTransporte* current = headTransporte;
    //cabeçalho
    printf("Transportes disponiveis:\n");
printf("%-8s%-20s%-10s%-15s%-30s%20s\n", "ID", "TIPO", "BATERIA", "PRECO/KM", "LOCAL", "DISTANCIA");    
while (current != NULL) {
    if (current->transporte.estado == 0) {
        Caminho *caminho = Dijkstra(headGrafo, localizacaoCliente, current->transporte.localizacao);
        if (caminho != NULL) {
            printf("%-8d%-20s%-10d€%-15.2f[%d] - %30.30s%15.2fm\n", 
                        current->transporte.id, 
                        current->transporte.tipo->nome,
                        current->transporte.nivelBateria, 
                        current->transporte.tipo->precoPorKm,
                        current->transporte.localizacao,
                        GetNomeLocal(headGrafo, current->transporte.localizacao),
                        caminho->distanciaTotal);
                    free(caminho);
                }
            }
        current = current->proximo;
    }
    return 1;
}


/// @brief Escreve os dados de um transporte 
/// @param headTransporte Pointer para o head da lista de NodeTransporte
/// @return Retorna uma struct Transporte com os dados inseridos
struct Transporte EscreveTransporte(struct NodeTipoTransporte** headTipoTransporte, int id, int tipo, int nivelBateria, int localizacao, int estado) {
    struct Transporte transporteTemp;
    transporteTemp.id = id;
    transporteTemp.tipo = ProcuraTipoTransporte(headTipoTransporte, tipo);
    transporteTemp.idTipo = tipo; // Preserve idTipo.
    printf("Tipo: %s\n", transporteTemp.tipo->nome);
    printf("ID: %d\n", transporteTemp.idTipo);
    transporteTemp.nivelBateria = nivelBateria;
    transporteTemp.localizacao = localizacao;
    transporteTemp.estado = estado;
    return transporteTemp;
}

/// @brief Cria uma copia da lista de NodeTransporte, para usar no sorting
/// @param head pointer para o head da lista de NodeTransporte
/// @param copiedHead Copia da lista de NodeTransporte
/// @return Retorna 1 se a operação for bem sucedida, 0 caso contrário
int CopiarLista(struct NodeTransporte *head, struct NodeTransporte **copiedHead) {
    if (head == NULL) {
        return 0;
    }

    while (head != NULL) {
        struct NodeTransporte *newNode = (struct NodeTransporte *)malloc(sizeof(struct NodeTransporte));
        newNode->transporte = head->transporte;
        newNode->proximo = NULL;

        if (*copiedHead == NULL) {
            *copiedHead = newNode;
        } else {
            struct NodeTransporte *current = *copiedHead;
            while (current->proximo != NULL) {
                current = current->proximo;
            }
            current->proximo = newNode;
        }
        head = head->proximo;
    }

    return 1;
}

/// @brief Ordena a lista de NodeTransporte por ordem decrescente de bateria
/// @param head Pointer para o head da lista de NodeTransporte
/// @return Retorna 1 se a operação for bem sucedida, 0 caso contrário
int OrdenarListaDecrescente(struct NodeTransporte *head) {
    if (head == NULL) {
        return 0;
    }

    struct NodeTransporte *current, *nextNode;
    // usado algoritmo bubble sort
    for (current = head; current != NULL; current = current->proximo) {
        for (nextNode = current->proximo; nextNode != NULL; nextNode = nextNode->proximo) {
            if (current->transporte.nivelBateria < nextNode->transporte.nivelBateria) {
                struct Transporte temp = current->transporte;
                current->transporte = nextNode->transporte;
                nextNode->transporte = temp;
            }
        }
    }
    return 1;
}

/// @brief Mostra a lista de transportes ordenados por ordem decrescente de bateria
/// @param head Pointer para o head da lista de NodeTransporte
/// @return Retorna 1 se a operação for bem sucedida, 0 caso contrário
int MostrarTransportesOrdenados(struct NodeTransporte *head) {
    if (head == NULL) {
        return 0;
    }

    struct NodeTransporte *copiedHead = NULL;
    if (!CopiarLista(head, &copiedHead)) {
        return 0;
    }

    if (!OrdenarListaDecrescente(copiedHead)) {
        return 0;
    }

    if (!MostrarTransportes(copiedHead)) {
        return 0;
    }

    struct NodeTransporte *current;
    while (copiedHead != NULL) {
        current = copiedHead;
        copiedHead = copiedHead->proximo;
        free(current);
    }
    return 1;
}

/// @brief Calcula o custo total do aluguer de um transporte
/// @param transporte struct Transporte
/// @param tempoAluguer Tempo de aluguer em minutos
/// @return Retorna o custo total do aluguer
float CustoTotalAluguer(struct Transporte* transporte, int tempoAluguer) {
    float tempoAluguerHoras = tempoAluguer / 60.0; // Converte minutos em horas
    return transporte->tipo->precoPorKm * tempoAluguerHoras;
}


/// @brief Verifica se um transporte está disponivel
/// @param transporte Struct Transporte
/// @return Retorna 1 se o transporte estiver disponivel, 0 caso contrário
int AlugarTransporteDisponivel(struct Transporte* transporte) {
    if (transporte->estado == 0) {
        return 1;
    } else {
        return 0;
    }
}



NodeTransporte* TransportesParaRecolher(NodeTransporte *transportes) {
    NodeTransporte *transportesParaRecolher = NULL;
    
    while(transportes){
        if(transportes->transporte.nivelBateria < limiteBateria){
            InserirTransporte(&transportesParaRecolher, transportes->transporte);
        }
        transportes = transportes->proximo;
    }

    return transportesParaRecolher;
}



/// @brief Limpa os campos visitado da estrutura de transportes
/// @param grafo Um ponteiro para a estrutura transporte
void LimparCamposTransportes(NodeTransporte *transporte) {
    NodeTransporte *transporteAux = transporte;

    while (transporteAux != NULL) {
        transporteAux->transporte.visitado = 0;
        transporteAux = transporteAux->proximo;
    }
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
            Caminho *caminho = Dijkstra(grafo, localCliente, transporteAtual->transporte.localizacao);
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


// tipo_de_transporte
// void ListarTransportesPorTipoERaio(struct NodeTransporte* headTransportes, struct Vertice* headGrafo, int localCliente, const char* tipo, float raio) {
//     struct NodeTransporte* currentTransporte = headTransportes;

//     printf("\nTransportes do tipo %s no raio de %.2f a partir do local %d:\n", tipo, raio, localCliente);

//     while (currentTransporte != NULL) {
//         if (strcmp(currentTransporte->transporte.tipo, tipo) == 0) {
//             Caminho* caminho = Dijkstra(headGrafo, localCliente, currentTransporte->transporte.localizacao);
//             float distancia = DistanciaCaminho(caminho);
//             if (distancia <= raio) {
//                 printf("ID: %d - Localização: [%d] %s - Distância: %.2f\n",
//                     currentTransporte->transporte.id,
//                     currentTransporte->transporte.localizacao,
//                     GetNomeLocal(headGrafo, currentTransporte->transporte.localizacao),
//                     distancia);
//             }
//         }

//         currentTransporte = currentTransporte->proximo;
//     }

// }


int InserirTipoTransporte(struct NodeTipoTransporte** headRef, TipoTransporte tipoTransporte) {
    struct NodeTipoTransporte* newNode = (struct NodeTipoTransporte*) malloc(sizeof(struct NodeTipoTransporte));
    if (newNode == NULL) {
        return 0;
    }

    newNode->tipo = tipoTransporte;
    newNode->proximo = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        struct NodeTipoTransporte* current = *headRef;
        while (current->proximo != NULL) {
            current = current->proximo;
        }
        current->proximo = newNode;
    }

    return 1;
}

Camiao* InicializarCamiao(float capacidadeMaxima) {
    Camiao *camiao = (Camiao*)malloc(sizeof(Camiao));
    camiao->capacidadeMaxima = capacidadeMaxima;
    camiao->cargaAtual = 0.0;
    return camiao;
}


int PodeAdicionarTransporte(Camiao *camiao, Transporte *transporte) {
    // Retorna 1 (verdadeiro) se o peso do transporte for menor ou igual ao espaço disponível no camião, caso contrário retorna 0 (falso)
    return transporte->tipo->peso <= (camiao->capacidadeMaxima - camiao->cargaAtual);
}
void AdicionarTransporte(Camiao *camiao, Transporte *transporte) {
    camiao->cargaAtual += transporte->tipo->peso;
}

void DescarregarCamiao(Camiao *camiao) {
    camiao->cargaAtual = 0.0;
}


void RecarregarTransportes(NodeTransporte* transportes) {
    // Itera pelos transportes
    for (NodeTransporte *transporteAux = transportes; transporteAux != NULL; transporteAux = transporteAux->proximo) {
        // Define a bateria para 100
        transporteAux->transporte.nivelBateria = 100;
    }
}

void MoverTransportesParaCentro(NodeTransporte *transportes, int centroRecolha) {
    NodeTransporte *aux = transportes;
    while (aux != NULL) {
        // Só move os transportes que já foram visitados
        if (aux->transporte.visitado == 1) {
            aux->transporte.localizacao = centroRecolha;
        }
        aux = aux->proximo;
    }
}


void ListarTiposTransporte(NodeTipoTransporte* tiposTransporte) {
    NodeTipoTransporte* aux = tiposTransporte;
    printf("\nTipos de transporte:\n");
    printf("---------------------\n");
    printf("ID | Nome\t | Peso | Preço por Km\n");
    while(aux != NULL) {
        printf("%d %s %.2f %.2f\n", aux->tipo.idTipo, aux->tipo.nome, aux->tipo.peso, aux->tipo.precoPorKm);        
        aux = aux->proximo;
    }
}
int AlterarPrecoTransporte(NodeTipoTransporte *tiposTransporte, int idTipo, float novoPreco) {
    NodeTipoTransporte *aux = tiposTransporte;
    while (aux != NULL) {
        if (aux->tipo.idTipo == idTipo) {
            aux->tipo.precoPorKm = novoPreco;
            return 1;  // Retorna 1 para indicar sucesso
        }
        aux = aux->proximo;
    }

    return 0;  // Retorna 0 se não encontrar o tipo de transporte
}


int InserirViagem(Viagem** headViagem, Viagem viagem) {
    // Aloca memória para um novo node de viagem.
    Viagem* novaViagem = (Viagem*)malloc(sizeof(Viagem));
    if(novaViagem == NULL) {
        return 0;
    }

    // Copia os dados da viagem lida do ficheiro para o novo node.
    *novaViagem = viagem;
    novaViagem->proxima = NULL;

    if (*headViagem == NULL) {
        *headViagem = novaViagem; // A lista estava vazia, portanto, o novo node é o head.
    } else {
        // Encontra o último node na lista.
        Viagem* atual = *headViagem;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        // Insere o novo node no final da lista.
        atual->proxima = novaViagem;
    }
}
