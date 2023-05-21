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
#include "../Headers/viagem.h"

#define ficheiroClientes "Data/Bin/clientes.bin"
#define ficheiroGestores "Data/Bin/gestores.bin"
#define ficheiroTransportes "Data/Bin/transportes.bin"
#define ficheiroTransacoes "Data/Bin/transacoes.bin"
#define ficheiroVertices "Data/Bin/grafo.bin"
#define ficheiroArestas "Data/Bin/arestas.bin"
#define ficheiroViagens "Data/Bin/viagens.bin"
#define ficheiroTipoTransporte "Data/Bin/tipoTransporte.bin"

#define csvClientes "Data/Csv/clients.csv"
#define csvGestores "Data/Csv/gestores.csv"
#define csvTransportes "Data/Csv/transportes.csv"
#define csvTransacoes "Data/Csv/transacoes.csv"
#define csvGrafo "Data/Csv/matrix.csv"
#define csvTipoTransportes "Data/Csv/tipostransportes.csv"

/// @brief Se todos os ficheiros CSV forem carregados com sucesso, retorna 1, caso contrário, retorna 0.
/// @param headClientes 
/// @param headTransportes 
/// @param headGestores 
/// @param headTransacoes 
/// @return 
int CarregarCSV(struct NodeClientes** headClientes, struct NodeTransporte** headTransportes, 
                 struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes, Vertice** headGrafo, NodeTipoTransporte** headTipoTransporte) {
    if (CarregarFicheiroClientes(headClientes, csvClientes) &&
        CarregarFicheiroTiposTransporte(headTipoTransporte, csvTipoTransportes) &&
        CarregarFicheiroTransportes(headTransportes, headTipoTransporte, csvTransportes) &&
        CarregarFicheiroGestores(headGestores, csvGestores) &&
        CarregarFicheiroTransacoes(headTransacoes, csvTransacoes) &&
        CarregarFicheiroGrafo(headGrafo, csvGrafo) ) {
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
                 struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes, Vertice** headGrafo, NodeTipoTransporte** headTipoTransporte) {
    if (!CarregarBinarioClientes(headClientes)) {
        printf("Error loading client binary data\n");
    } else if (!CarregarBinarioTiposTransporte(headTipoTransporte)) {
        printf("Error loading transport type binary data\n");
    } else if (!CarregarBinarioTransportes(headTransportes)) {
        printf("Error loading transport binary data\n");
    } else if (!CarregarBinarioGestores(headGestores)) {
        printf("Error loading manager binary data\n");
    } else if (!CarregarBinarioTransacoes(headTransacoes)) {
        printf("Error loading transaction binary data\n");
    } else if (!CarregarBinarioVertices(headGrafo)) {
        printf("Error loading vertex binary data\n");
    } else if (!CarregarBinarioAdjacentes(*headGrafo)) {
        printf("Error loading adjacency binary data\n");
    } else {
        // All binary data loaded successfully
        return 1;
    }

    // If we reach this point, some binary loading has failed
    printf("Attempting to load from CSV...\n");
    if (!CarregarCSV(headClientes, headTransportes, headGestores, headTransacoes, headGrafo, headTipoTransporte)) {
        printf("Error loading CSV data\n");
        return -1;
    }

    // CSV data loaded successfully after binary loading failed
    return 0;
}


int ExportarTodosDados(NodeClientes *headClientes, NodeGestores *headGestores, NodeTransporte *headTransportes, NodeTransacoes *headTransacoes, Vertice *headGrafo, NodeTipoTransporte *headTipoTransportes) {
    if (!ExportarClientes(headClientes) || !ExportarGestores(headGestores) || !ExportarTiposTransporte(headTipoTransportes) ||
    !ExportarTransportes(headTransportes) || !ExportarTransacoes(headTransacoes) || 
    !ExportaVertices(headGrafo) || !ExportaAdjacentes(headGrafo)) {
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
        fwrite(&current->cliente, sizeof(Clientes), 1, file);
        // Contar o número de viagens
        int numViagens = 0;
        Viagem* viagemAtual = current->cliente.historicoViagens;
        while(viagemAtual != NULL) {
            numViagens++;
            viagemAtual = viagemAtual->proxima;
        }
        // Escrever o número de viagens
        fwrite(&numViagens, sizeof(int), 1, file);
        // Escrever as viagens
        viagemAtual = current->cliente.historicoViagens;
        while(viagemAtual != NULL) {
            fwrite(viagemAtual, sizeof(Viagem), 1, file);
            viagemAtual = viagemAtual->proxima;
        }
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

int ExportarTransportes(struct NodeTransporte* listaTransportes) {
    FILE* file = fopen(ficheiroTransportes, "wb");
    if (file == NULL) {
        return 0;
    }

    struct NodeTransporte* current = listaTransportes;
    while (current != NULL) {
        fwrite(&current->transporte.id, sizeof(int), 1, file);
        fwrite(&current->transporte.idTipo, sizeof(int), 1, file);
        fwrite(&current->transporte.nivelBateria, sizeof(int), 1, file);
        fwrite(&current->transporte.localizacao, sizeof(int), 1, file);
        fwrite(&current->transporte.estado, sizeof(int), 1, file);
        fwrite(&current->transporte.visitado, sizeof(int), 1, file);
        current = current->proximo;
    }

    fclose(file);
    return 1;
}



int ExportarTiposTransporte(struct NodeTipoTransporte* listaTiposTransporte) {
    FILE* file = fopen(ficheiroTipoTransporte, "wb");
    if (file == NULL) {
        return 0;
    }

    struct NodeTipoTransporte* current = listaTiposTransporte;
    while (current != NULL) {
        fwrite(&current->tipo, sizeof(TipoTransporte), 1, file);
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

/// @brief Exporta a lista de vertices para um fichero binário.
/// @param headTipoTransporte  Pointer para o header da lista de vertices.
/// @return 1 se a exportação for bem sucedida, caso contrário, retorna 0.
int CarregarBinarioTiposTransporte(struct NodeTipoTransporte** headTiposTransporte) {
    FILE* file = fopen(ficheiroTipoTransporte, "rb");
    if (file == NULL) {
        return 0;
    }

    TipoTransporte buffer;
    while (fread(&buffer, sizeof(TipoTransporte), 1, file) == 1) {
        InserirTipoTransporte(headTiposTransporte, buffer);
    }

    fclose(file);
    return 1;
}

/// @brief Carrega dados de deslocações de um ficheiro binário.
/// @param headViagem 
/// @return 1 se a exportação for bem sucedida, caso contrário, retorna 0.
int CarregarBinarioViagens(struct Viagem** headViagem) {
    FILE* file = fopen(ficheiroViagens, "rb");
    if (file == NULL) {
        return 0;
    }

    struct Viagem viagem;
    // Lê node a node do ficheiro binário e insere na lista.
    while (fread(&viagem, sizeof(struct Viagem), 1, file) == 1) {
        InserirViagem(headViagem, viagem);
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
        printf("XXXX FALHEI");
        return 0;
    }

    Clientes clienteBuffer;
    while (fread(&clienteBuffer, sizeof(Clientes), 1, file) == 1) {
        Viagem* headViagem = NULL;
        // Ler o número de viagens
        int numViagens;
        fread(&numViagens, sizeof(int), 1, file);
        // Ler as viagens
        for (int i = 0; i < numViagens; i++) {
            Viagem viagemBuffer;
            fread(&viagemBuffer, sizeof(Viagem), 1, file);
            Viagem* novaViagem = malloc(sizeof(Viagem));
            *novaViagem = viagemBuffer;
            novaViagem->proxima = headViagem;
            headViagem = novaViagem;
        }
        clienteBuffer.historicoViagens = headViagem;
        InserirCliente(headClientes, clienteBuffer);
    }

    fclose(file);
    printf("XXXX CLIEntes SUCESSO");
    return 1;
}


/// @brief Carrega dados de transportes de um ficheiro binário.
/// @param headTransportes Pointer para o header da lista de transportes.
/// @return Retorna 1 se os dados forem carregados com sucesso, caso contrário, retorna 0.
int CarregarBinarioTransportes(NodeTransporte** headTransportes) {
    FILE* file = fopen(ficheiroTransportes, "rb");
    if (file == NULL) {
        return 0;
    }

    Transporte transporteBuffer;
    while (fread(&transporteBuffer, sizeof(Transporte), 1, file) == 1) {
        InserirTransporte(headTransportes, transporteBuffer);
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
        printf("XXXX GESTORES FALHEI");
        return 0;
    }

    struct NodeGestores nodeGestor;
    // Lê node a node do ficheiro binário e insere na lista.
    while (fread(&nodeGestor, sizeof(struct NodeGestores), 1, file) == 1) {
        InserirGestor(headGestores, nodeGestor.gestor);
    }

    fclose(file);
    printf("XXXX GESTORES SUCESSO");
    return 1;
}

/// @brief Carrega dados de transacoes de um ficheiro binário.
/// @param headTransacoes Pointer para o header da lista de transacoes.
/// @return Retorna 1 se os dados forem carregados com sucesso, caso contrário, retorna 0.
int CarregarBinarioTransacoes(struct NodeTransacoes** headTransacoes) {
    FILE* file = fopen(ficheiroTransacoes, "rb");
    if (file == NULL) {
        printf("XXXX TRANSACOES FALHEI");
        return 0;
    }

    struct NodeTransacoes nodeTransacao;
    while (fread(&nodeTransacao, sizeof(struct NodeTransacoes), 1, file) == 1) {
        InserirTransacoes(headTransacoes, nodeTransacao.transacoes);
    }

    fclose(file);
    printf("XXXX TRANSACOES SUCESSO");
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
        printf("XXXX VERTICES FALHEI");
        return 0;
    }

    int id;
    char cidade[MAX_ID];
    while (fread(&id, sizeof(int), 1, file) == 1 && fread(cidade, sizeof(char), MAX_ID, file) == MAX_ID) {
        Vertice* novoVertice = CriarVertice(id, cidade);
        *grafo = InsereVertice(*grafo, novoVertice);
    }

    fclose(file);
    printf("XXXX VERTICES SUCESSO");
    return 1;
}

int CarregarBinarioAdjacentes(Vertice* grafo) {
    FILE* file = fopen(ficheiroArestas, "rb");
    if (file == NULL) {
        printf("XXXX ADJACENTES FALHEI");
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
    printf("XXXX ADJACENTES SUCESSO");
    return 1;
}

// Número maximo de caracteres que cada linha pode conter
#define MAX_LINHA 1024


/// @brief Carrega dados de clientes de um determinado ficheiro e passa-os para uma lista ligada.
/// @param head Pointer para o pointer do header da lista de clientes.
/// @param nomeFicheiro String com o nome do ficheiro que contem os dados dos clientes a ser carregado.
/// @return Retorna o número de clientes carregados.
int CarregarFicheiroClientes(struct NodeClientes** head, char *nomeFicheiro){
    printf("A carregar ficheiro de clientes...\n");
    FILE *ficheiro;
    ficheiro = fopen(nomeFicheiro, "r");
    int totalClientes = 0;
    if(ficheiro == NULL){
        return 0;
    }
    totalClientes = LerClientesDeFicheiro(head,ficheiro);
    return totalClientes;
}

/// @brief 
/// @param grafo 
/// @param nomeFicheiro 
/// @return 
int CarregarFicheiroGrafo(Vertice **grafo, char *nomeFicheiro){
    FILE *ficheiro;
    ficheiro = fopen(nomeFicheiro, "r");
    int totalVertices = 0;
    if(ficheiro == NULL){
        return 0;
    }
    totalVertices = LerGrafoDeFicheiro(grafo,ficheiro);
    fclose(ficheiro); 
    return totalVertices;
}

/// @brief 
/// @param grafo 
/// @param ficheiro 
/// @return 
int LerGrafoDeFicheiro(Vertice **grafo, FILE *ficheiro){
    char linha[MAX_LINHA];
    int totalVertices = 0;

    fgets(linha, MAX_LINHA, ficheiro); // Pular a primeira linha (cabeçalho)
    while(fgets(linha, MAX_LINHA, ficheiro) != NULL){
        int id;
        char titulo[256];
        char *token, *delim = ",";
        
        sscanf(linha, "%d,%[^,],", &id, titulo);
        
        Vertice *novoVertice = CriarVertice(id, titulo);
        *grafo = InsereVertice(*grafo, novoVertice);

        
        token = strtok(linha, delim); // ID
        token = strtok(NULL, delim); // Título, NULL para continuar na mesma string
        token = strtok(NULL, delim); // Primeiro par adjacente-distância

        while (token != NULL) {
            int adj;
            float dist;
            sscanf(token, "%d", &adj); // ID adjacente
            token = strtok(NULL, delim); // Distância até ao adjacente, NULL para continuar na mesma string
            sscanf(token, "%f", &dist); // Distância até ao adjacente

            Adjacente* novoAdjacente = CriaAdjacente(adj, dist); // Cria novo adjacente
            novoVertice = InsereAdjacente(novoVertice, id, novoAdjacente); // Insere novo adjacente na lista de adjacências do vértice

            token = strtok(NULL, delim); // Próximo par adjacente-distância
        }

        totalVertices++;
    }
    return totalVertices;
}


/// @brief Carrega dados de transportes de um determinado ficheiro e passa-os para uma lista ligada.
/// @param head Pointer para o pointer do header da lista de transportes.
/// @param nomeFicheiro String com o nome do ficheiro que contem os dados dos transportes a ser carregado.
/// @return Retorna o número de transportes carregados.
int CarregarFicheiroTransportes(struct NodeTransporte** head, NodeTipoTransporte** headTipo, char* nomeFicheiro) {
    printf("A carregar ficheiro de transportes...\n");
    FILE *ficheiro;
    ficheiro = fopen(nomeFicheiro, "r");
    int totalTransportes = 0;
    if(ficheiro == NULL){
        return 0;
    }
    totalTransportes = LerTransportesDeFicheiro(head,headTipo,ficheiro);
    fclose(ficheiro);
    return totalTransportes;
}

/// @brief Carrega dados de gestores de um determinado ficheiro e passa-os para uma lista ligada.
/// @param head Pointer para o pointer do header da lista de gestores.
/// @param nomeFicheiro String com o nome do ficheiro que contem os dados dos gestores a ser carregado.
/// @return Retorna o número de gestores carregados.
int CarregarFicheiroGestores(struct NodeGestores** head, char* nomeFicheiro) {
    FILE *ficheiro;
    printf("A carregar ficheiro de gestores...\n");
    ficheiro = fopen(nomeFicheiro, "r");
    int totalGestores = 0;
    if(ficheiro == NULL){
        return 0;
    }
    totalGestores = LerGestoresDeFicheiro(head,ficheiro);
    return totalGestores;
}

/// @brief Carrega dados de transações de um determinado ficheiro e passa-os para uma lista ligada.
/// @param head Pointer para o pointer do header da lista de transações.
/// @param nomeFicheiro String com o nome do ficheiro que contem os dados dos transações a ser carregado.
/// @return Retorna o número de transações carregadas.
int CarregarFicheiroTransacoes(struct NodeTransacoes** head, char* nomeFicheiro){
    FILE *ficheiro;
    ficheiro = fopen(nomeFicheiro, "r");
    int totalTransacoes = 0;
    if(ficheiro == NULL){
        return 0;
    }
    totalTransacoes = LerTransacoesDeFicheiro(head,ficheiro);
    return totalTransacoes;
}


int CarregarFicheiroTiposTransporte(NodeTipoTransporte** headTipos, char* nomeFicheiro) {
    printf("A carregar tipos de transporte...\n");
    FILE *ficheiro;
    ficheiro = fopen(nomeFicheiro, "r");
    int totalTipos = 0;
    if(ficheiro == NULL){
        return 0;
    }
    totalTipos = LerTiposTransporteDeFicheiro(headTipos,ficheiro);
    fclose(ficheiro);
    return totalTipos;
}




/// @brief Lê os dados dos clientes do ficheiro e passa-os para uma lista ligada.
/// @param headRef Pointer para o pointer do header da lista de clientes.
/// @param ficheiro Ficheiro que contem os dados dos clientes a ser carregado.
/// @return Retorna o número de clientes carregados.
int LerClientesDeFicheiro(struct NodeClientes** headRef, FILE *ficheiro){
    char linha[MAX_LINHA];
    struct Clientes temp;
    int totalClientes=0;
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL)
    {
            if(sscanf(linha,"%d\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\t]\t%d", 
                                                                    &temp.nif, 
                                                                    temp.nome, 
                                                                    temp.morada, 
                                                                    &temp.saldo,
                                                                    temp.login,
                                                                    temp.password,
                                                                    &temp.localCliente)==7){
            temp.historicoViagens = NULL; // Inicializar lista de viagens como NULL
            if(InserirCliente(headRef, temp))
                totalClientes++;
        }
            
    }
    return totalClientes;
}

/// @brief Lê os dados dos transportes do ficheiro e passa-os para uma lista ligada.
/// @param headRef Pointer para o pointer do header da lista de transportes.
/// @param ficheiro Ficheiro que contem os dados dos transportes a ser carregado.
/// @return Retorna o número de transportes carregados.
int LerTransportesDeFicheiro(struct NodeTransporte** headRef, NodeTipoTransporte** headTipos, FILE *ficheiro){
    char linha[MAX_LINHA];
    struct Transporte temp;
    int totalTransportes=0;
    printf("Entre LerTransportesDeFicheiro\n");
    
    fgets(linha, MAX_LINHA, ficheiro); // Ignorar primeira linha
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL)
    {
        printf("Linha: %s\n",linha);
        
        if(sscanf(linha,"%d\t%d\t%d\t%d\t%d", 
                                                    &temp.id, 
                                                    &temp.idTipo, 
                                                    &temp.nivelBateria, 
                                                    &temp.localizacao,
                                                    &temp.estado)==5){
        printf("idTipo: %d\n", temp.idTipo);
        Transporte novoTransporte = EscreveTransporte(headTipos, temp.id, temp.idTipo, temp.nivelBateria, temp.localizacao, temp.estado);
        if(InserirTransporte(headRef,novoTransporte))
            totalTransportes++; 
        }
    }

    return totalTransportes;
}



/// @brief Lê os dados dos gestores do ficheiro e passa-os para uma lista ligada.
/// @param headRef Pointer para o pointer do header da lista de gestores.
/// @param ficheiro Ficheiro que contem os dados dos gestores a ser carregado.
/// @return Retorna o número de gestores carregados.
int LerGestoresDeFicheiro(struct NodeGestores** headRef, FILE *ficheiro){
    char linha[MAX_LINHA];
    struct Gestores temp;
    int totalGestores=0;
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL)
    {
        if(sscanf(linha,"%[^\t]\t%s\n",temp.nome,temp.password)==2){
            if(InserirGestor(headRef,temp))
                totalGestores++;
        }
            
    }
    return totalGestores;
}

/// @brief Lê os dados das transações do ficheiro e passa-os para uma lista ligada.
/// @param headRef Pointer para o pointer do header da lista de transações.
/// @param ficheiro Ficheiro que contem os dados das transações a ser carregado.
/// @return Retorna o número de transações carregadas.
int LerTransacoesDeFicheiro(struct NodeTransacoes** headRef, FILE *ficheiro){
    char linha[MAX_LINHA];
    struct Transacoes temp;
    int totalTransacoes=0;
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL)
    {
        if(sscanf(linha,"%d\t%d\t%d\t%d\n",
                            &temp.idTransacao,
                            &temp.idClienteAAlugar,
                            &temp.idTransporte,
                            &temp.tempoAlugado)==4){
            if(InserirTransacoes(headRef,temp))
                totalTransacoes++;
        }
            
        }
    return totalTransacoes;
}

int LerTiposTransporteDeFicheiro(NodeTipoTransporte** headRef, FILE *ficheiro){
    char linha[MAX_LINHA];
    TipoTransporte temp;
    int totalTipos=0;
    fgets(linha, MAX_LINHA, ficheiro); // Ignorar a linha do cabeçalho
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL)
    {
        if(sscanf(linha,"%d\t%[^\t]\t%f\t%f", 
                                                    &temp.idTipo, 
                                                    temp.nome, 
                                                    &temp.peso, 
                                                    &temp.precoPorKm)==4){
                                                   
            if(InserirTipoTransporte(headRef,temp))
                totalTipos++;
        }
            
    }

    return totalTipos;
}


#endif


TipoTransporte* ProcuraTipoTransporte(NodeTipoTransporte** head, int idTipo) {
    NodeTipoTransporte* current = *head;
    while(current != NULL) {
        if(current->tipo.idTipo == idTipo) {
            return &(current->tipo);
        }
        current = current->proximo;
    }
    return NULL; // Retorna NULL se o tipo de transporte não foi encontrado
}
