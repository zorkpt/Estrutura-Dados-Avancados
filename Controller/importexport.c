/**
 * @file importexport.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef EXPORTAR_HEADER_GUARD
#define EXPORTAR_HEADER_GUARD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/clientes.h"
#include "../Headers/gestores.h"
#include "../Headers/transportes.h"
#include "../Headers/transacoes.h"
#include "../Headers/funcoes.h"


#define ficheiroClientes "Data/Bin/clientes.bin"
#define ficheiroGestores "Data/Bin/gestores.bin"
#define ficheiroTransportes "Data/Bin/transportes.bin"
#define ficheiroTransacoes "Data/Bin/transacoes.bin"
#define ficheiroVertices "Data/Bin/grafo.bin"
#define ficheiroArestas "Data/Bin/arestas.bin"

#define csvClientes "Data/Csv/clients.csv"
#define csvGestores "Data/Csv/gestores.csv"
#define csvTransportes "Data/Csv/transportes.csv"
#define csvTransacoes "Data/Csv/transacoes.csv"
#define csvGrafo "Data/Csv/matrix.csv"

/// @brief Se todos os ficheiros CSV forem carregados com sucesso, retorna 1, caso contrário, retorna 0.
/// @param headClientes 
/// @param headTransportes 
/// @param headGestores 
/// @param headTransacoes 
/// @return 
int CarregarCSV(struct NodeClientes** headClientes, struct NodeTransporte** headTransportes, 
                 struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes, Vertice** headGrafo) {
    if (CarregarFicheiroClientes(headClientes, csvClientes) &&
        CarregarFicheiroTransportes(headTransportes, csvTransportes) &&
        CarregarFicheiroGestores(headGestores, csvGestores) &&
        CarregarFicheiroTransacoes(headTransacoes, csvTransacoes) &&
        CarregarFicheiroGrafo(headGrafo, csvGrafo)) {
        return 1;
    }
    return 0;
}


/// @brief Carrega dados de ficheiros binários, caso não existam, carrega dados de ficheiros CSV.
/// @param headClientes Pointer para o header da lista de clientes.
/// @param headTransportes Pointer para o header da lista de transportes.
/// @param headGestores Pointer para o header da lista de gestores.
/// @param headTransacoes Pointer para o header da lista de transacoes.
/// @return Retorna 1 se os dados forem carregados com sucesso, retorna 
///         0 se os dados forem carregados de ficheiros CSV, retorna -1 se os dados não forem carregados.
int CarregarDados(struct NodeClientes** headClientes, struct NodeTransporte** headTransportes, 
                 struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes, Vertice** headGrafo) {
    if (CarregarBinarioClientes(headClientes) &&
        CarregarBinarioTransportes(headTransportes) &&
        CarregarBinarioGestores(headGestores) &&
        CarregarBinarioTransacoes(headTransacoes) &&
        CarregarBinarioVertices(headGrafo) && 
        CarregarBinarioAdjacentes(*headGrafo)) {
        return 1;
    }
    if(!CarregarCSV(headClientes, headTransportes, headGestores, headTransacoes, headGrafo)) {
        return -1;
    } else {
        return 0;
    }
}

int ExportarTodosDados(NodeClientes *headClientes, NodeGestores *headGestores, NodeTransporte *headTransportes, NodeTransacoes *headTransacoes, Vertice *headGrafo) {
    if (!ExportarClientes(headClientes) || !ExportarGestores(headGestores) || !ExportarTransportes(headTransportes) || !ExportarTransacoes(headTransacoes) || !ExportaVertices(headGrafo) || !ExportaAdjacentes(headGrafo)) {
        return 0;
    }
    return 1;
}


/// @brief Exporta a lista de clientes para um fichero binário.
/// @param listaClientes Pointer para o header da lista de clientes.
/// @return Retorna 1 se a exportação for bem sucedida, caso contrário, retorna 0.
int ExportarClientes(struct NodeClientes* listaClientes) {
    FILE* file = fopen(ficheiroClientes, "wb");
    if (file == NULL) {
        return 0;
    }
    struct NodeClientes* current = listaClientes;
    while (current != NULL) {
        fwrite(&current->cliente, sizeof(struct NodeClientes), 1, file);
        current = current->proximo;
    }
    fclose(file);
    return 1;
}

/// @brief Exporta a lista de gestores para um fichero binário.
/// @param listaGestores Pointer para o header da lista de gestores.
/// @return Retorna 1 se a exportação for bem sucedida, caso contrário, retorna 0.
int ExportarGestores(struct NodeGestores* listaGestores) {
    FILE* file = fopen(ficheiroGestores, "wb");
    if (file == NULL) {
        return 0;
    }

    struct NodeGestores* current = listaGestores;
    while (current != NULL) {
        fwrite(&current->gestor, sizeof(struct NodeGestores), 1, file);
        current = current->proximo;
    }
    fclose(file);
    return 1;
}

/// @brief Exporta a lista de transportes para um fichero binário.
/// @param listaTransporte Pointer para o header da lista de transportes.
/// @return Retorna 1 se a exportação for bem sucedida, caso contrário, retorna 0.
int ExportarTransportes(struct NodeTransporte* listaTransporte) {
    FILE* file = fopen(ficheiroTransportes, "wb");
    if (file == NULL) {
        return 0;
    }
    struct NodeTransporte* current = listaTransporte;
    while (current != NULL) {
        fwrite(&current->transporte, sizeof(struct NodeTransporte), 1, file);
        current = current->proximo;
    }
    fclose(file);
    return 1;
}

/// @brief Exporta a lista de transacoes para um fichero binário.
/// @param listaTransacoes Pointer para o header da lista de transacoes.
/// @return Retorna 1 se a exportação for bem sucedida, caso contrário, retorna 0.
int ExportarTransacoes(struct NodeTransacoes* listaTransacoes) {
    FILE* file = fopen(ficheiroTransacoes, "wb");
    if (file == NULL) {
        return 0;
    }

    struct NodeTransacoes* current = listaTransacoes;
    while (current != NULL) {
        fwrite(&current->transacoes, sizeof(struct NodeTransacoes), 1, file);
        current = current->proximo;
    }
    fclose(file);
    return 1;
}

/// @brief Carrega dados de clientes de um ficheiro binário.
/// @param headClientes Pointer para o header da lista de clientes.
/// @return Retorna 1 se os dados forem carregados com sucesso, caso contrário, retorna 0.
int CarregarBinarioClientes(struct NodeClientes** headClientes) {
    FILE* file = fopen(ficheiroClientes, "rb");
    if (file == NULL) {
        return 0;
    }

    struct NodeClientes nodeCliente;
    // Lê node a node do ficheiro binário e insere na lista.
    while (fread(&nodeCliente, sizeof(struct NodeClientes), 1, file) == 1) {
        InserirCliente(headClientes, nodeCliente.cliente);
    }

    fclose(file);
    return 1;
}

/// @brief Carrega dados de transportes de um ficheiro binário.
/// @param headTransportes Pointer para o header da lista de transportes.
/// @return Retorna 1 se os dados forem carregados com sucesso, caso contrário, retorna 0.
int CarregarBinarioTransportes(struct NodeTransporte** headTransportes) {
    FILE* file = fopen(ficheiroTransportes, "rb");
    if (file == NULL) {
        return 0;
    }

    struct NodeTransporte nodeTransporte;
    // Lê node a node do ficheiro binário e insere na lista.
    while (fread(&nodeTransporte, sizeof(struct NodeTransporte), 1, file) == 1) {
        InserirTransporte(headTransportes, nodeTransporte.transporte);
    }

    fclose(file);
    return 1;
}

/// @brief Carrega dados de gestores de um ficheiro binário.
/// @param headGestores Pointer para o header da lista de gestores.
/// @return Retorna 1 se os dados forem carregados com sucesso, caso contrário, retorna 0.
int CarregarBinarioGestores(struct NodeGestores** headGestores) {
    FILE* file = fopen(ficheiroGestores, "rb");
    if (file == NULL) {
        return 0;
    }

    struct NodeGestores nodeGestor;
    // Lê node a node do ficheiro binário e insere na lista.
    while (fread(&nodeGestor, sizeof(struct NodeGestores), 1, file) == 1) {
        InserirGestor(headGestores, nodeGestor.gestor);
    }

    fclose(file);
    return 1;
}

/// @brief Carrega dados de transacoes de um ficheiro binário.
/// @param headTransacoes Pointer para o header da lista de transacoes.
/// @return Retorna 1 se os dados forem carregados com sucesso, caso contrário, retorna 0.
int CarregarBinarioTransacoes(struct NodeTransacoes** headTransacoes) {
    FILE* file = fopen(ficheiroTransacoes, "rb");
    if (file == NULL) {
        return 0;
    }

    struct NodeTransacoes nodeTransacao;
    while (fread(&nodeTransacao, sizeof(struct NodeTransacoes), 1, file) == 1) {
        InserirTransacoes(headTransacoes, nodeTransacao.transacoes);
    }

    fclose(file);
    return 1;
}


int ExportaVertices(Vertice *grafo) {
    FILE *file = fopen(ficheiroVertices, "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Vertice *aux = grafo;
    while (aux != NULL) {
        fwrite(&aux->idVertice, sizeof(int), 1, file);
        fwrite(aux->cidade, sizeof(char), MAX_ID, file);
        aux = aux->proximo;
    }

    fclose(file);
    return 1;
}

int ExportaAdjacentes(Vertice *grafo) {
    FILE *file = fopen(ficheiroArestas, "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Vertice *aux = grafo;
    while (aux != NULL) {
        Adjacente *adj = aux->adjacentes;
        while (adj != NULL) {
            fwrite(&aux->idVertice, sizeof(int), 1, file);
            fwrite(&adj->idVertice, sizeof(int), 1, file);
            fwrite(&adj->distancia, sizeof(float), 1, file);
            adj = adj->proximo;
        }
        aux = aux->proximo;
    }

    fclose(file);
    return 1;
}

int CarregarBinarioVertices(Vertice** grafo) {
    FILE* file = fopen(ficheiroVertices, "rb");
    if (file == NULL) {
        return 0;
    }

    int id;
    char cidade[MAX_ID];
    while (fread(&id, sizeof(int), 1, file) == 1 && fread(cidade, sizeof(char), MAX_ID, file) == MAX_ID) {
        Vertice* novoVertice = CriarVertice(id, cidade);
        *grafo = InsereVertice(*grafo, novoVertice);
    }

    fclose(file);
    return 1;
}

int CarregarBinarioAdjacentes(Vertice* grafo) {
    FILE* file = fopen(ficheiroArestas, "rb");
    if (file == NULL) {
        return 0;
    }

    int origem, destino;
    float distancia;
    while (fread(&origem, sizeof(int), 1, file) == 1 &&
           fread(&destino, sizeof(int), 1, file) == 1 &&
           fread(&distancia, sizeof(float), 1, file) == 1) {
        Adjacente* novoAdjacente = CriaAdjacente(destino, distancia);
        grafo = InsereAdjacente(grafo, origem, novoAdjacente);
    }

    fclose(file);
    return 1;
}

#endif