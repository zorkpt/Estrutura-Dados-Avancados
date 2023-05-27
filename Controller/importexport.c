/**
 * @file importexport.c
 * @author Hugo Poças
 * @brief Este ficheiro contém as funções que permitem carregar dados de ficheiros CSV e binários.
 * @version 0.2
 * @date 27-05-2023
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
#include "../Headers/importexport.h"
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
// Número maximo de caracteres que cada linha pode conter
#define MAX_LINHA 1024

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
                 struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes, 
                 Vertice** headGrafo, NodeTipoTransporte** headTipoTransporte, Viagem** headViagens) {
    if(CarregarBinarioClientes(headClientes,headViagens) 
           && CarregarBinarioTiposTransporte(headTipoTransporte) 
           && CarregarBinarioTransportes(headTransportes, headTipoTransporte) 
           && CarregarBinarioGestores(headGestores)
           && CarregarBinarioTransacoes(headTransacoes)
           && CarregarBinarioVertices(headGrafo)
           && CarregarBinarioAdjacentes(*headGrafo))
    {
        // Dados carregados com sucesso dos ficheiros binários
        return 1;
    }

    // Criar uma função que limpe todas as estruturas caso alguns dos ficheiros binários sejam carregados

    // Se os dados não forem carregados dos ficheiros binários, tentar carregar dos ficheiros CSV
    if (!CarregarCSV(headClientes, headTransportes, headGestores, headTransacoes, headGrafo, headTipoTransporte)) {
        return -1;
    }

    // Dados carregados com sucesso dos ficheiros CSV
    return 0;
}

/// @brief Exporta todos os dados para arquivos binários. 
/// 
/// Esta função chama funções de exportação para cada tipo de dados. 
/// Se qualquer uma dessas chamadas de função falhar, a função retornará 0.
/// Caso contrário, retornará 1.
/// 
/// @param headClientes Ponteiro para o primeiro nó da lista de clientes.
/// @param headGestores Ponteiro para o primeiro nó da lista de gestores.
/// @param headTransportes Ponteiro para o primeiro nó da lista de transportes.
/// @param headTransacoes Ponteiro para o primeiro nó da lista de transações.
/// @param headGrafo Ponteiro para o primeiro nó do grafo.
/// @param headTipoTransportes Ponteiro para o primeiro nó da lista de tipos de transportes.
/// 
/// @return Retorna 1 se todas as operações de exportação foram bem sucedidas, senão retorna 0.
int ExportarTodosDados(NodeClientes *headClientes, NodeGestores *headGestores, NodeTransporte *headTransportes, NodeTransacoes *headTransacoes, Vertice *headGrafo, NodeTipoTransporte *headTipoTransportes) {
    if (!ExportarClientes(headClientes) || !ExportarGestores(headGestores) || !ExportarTiposTransporte(headTipoTransportes) ||
    !ExportarTransportes(headTransportes) || !ExportarTransacoes(headTransacoes) || 
    !ExportaVertices(headGrafo) || !ExportaAdjacentes(headGrafo)) {
        return 0;
    }
    return 1;
}


/// @brief Exporta a lista de clientes para um arquivo binário. 
/// 
/// Esta função percorre a lista de clientes e escreve cada cliente 
/// e o seu histórico de viagens para um arquivo binário. 
/// 
/// @param listaClientes Ponteiro para o primeiro nó da lista de clientes.
/// 
/// @return Retorna 1 se a operação de exportação foi bem sucedida, senão retorna 0.
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
int CarregarBinarioClientes(struct NodeClientes** headClientes, Viagem** headViagem) {
    FILE* file = fopen(ficheiroClientes, "rb");
    if (file == NULL) {
        return 0;
    }

    Clientes clienteBuffer;
    while (fread(&clienteBuffer, sizeof(Clientes), 1, file) == 1) {
        Viagem* headViagemCliente = NULL; // Guarda a cabeça da lista de viagens do cliente atual
        // Ler o número de viagens
        int numViagens;
        fread(&numViagens, sizeof(int), 1, file);
        // Ler as viagens
        for (int i = 0; i < numViagens; i++) {
            Viagem viagemBuffer;
            fread(&viagemBuffer, sizeof(Viagem), 1, file);
            Viagem* novaViagem = malloc(sizeof(Viagem));
            *novaViagem = viagemBuffer;
            novaViagem->proxima = headViagemCliente;
            headViagemCliente = novaViagem;

            // Atualiza a lista global de viagens
            if (*headViagem == NULL) {
                *headViagem = novaViagem;
            } else {
                Viagem *aux = *headViagem;
                while (aux->proxima != NULL) {
                    aux = aux->proxima;
                }
                aux->proxima = novaViagem;
            }
        }
        clienteBuffer.historicoViagens = headViagemCliente;
        InserirCliente(headClientes, clienteBuffer);
    }

    fclose(file);
    return 1;
}



/// @brief Carrega dados de transportes de um ficheiro binário.
/// @param headTransportes Pointer para o header da lista de transportes.
/// @return Retorna 1 se os dados forem carregados com sucesso, caso contrário, retorna 0.
int CarregarBinarioTransportes(NodeTransporte** headTransportes, NodeTipoTransporte** headTiposTransporte) {
    FILE* file = fopen(ficheiroTransportes, "rb");
    if (file == NULL) {
        return 0;
    }

    Transporte transporteBuffer;
    while (1) {
        size_t result;
        result = fread(&transporteBuffer.id, sizeof(int), 1, file);
        result += fread(&transporteBuffer.idTipo, sizeof(int), 1, file);
        result += fread(&transporteBuffer.nivelBateria, sizeof(int), 1, file);
        result += fread(&transporteBuffer.localizacao, sizeof(int), 1, file);
        result += fread(&transporteBuffer.estado, sizeof(int), 1, file);
        result += fread(&transporteBuffer.visitado, sizeof(int), 1, file);

        if (result != 6) {  // se não leu 6 itens, então chegou ao fim do arquivo ou ocorreu um erro
            break;
        }

        // Encontrar o tipo de transporte e atribuir ao transporte
        transporteBuffer.tipo = EncontrarTipoPorId(headTiposTransporte, transporteBuffer.idTipo);

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
        return 0;
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
        return 0;
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


/// @brief Carrega dados de clientes de um determinado ficheiro e passa-os para uma lista ligada.
/// @param head Pointer para o pointer do header da lista de clientes.
/// @param nomeFicheiro String com o nome do ficheiro que contem os dados dos clientes a ser carregado.
/// @return Retorna o número de clientes carregados.
int CarregarFicheiroClientes(struct NodeClientes** head, char *nomeFicheiro){
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
        char titulo[MAX_CHAR];
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

/// @brief Carrega dados de tipos de transporte de um determinado ficheiro e passa-os para uma lista ligada.
/// @param headTipos 
/// @param nomeFicheiro 
/// @return retorna o número de tipos de transporte carregados.
int CarregarFicheiroTiposTransporte(NodeTipoTransporte** headTipos, char* nomeFicheiro) {
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
    
    fgets(linha, MAX_LINHA, ficheiro); // Ignorar primeira linha
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL)
    {        
        if(sscanf(linha,"%d\t%d\t%d\t%d\t%d", 
                                                    &temp.id, 
                                                    &temp.idTipo, 
                                                    &temp.nivelBateria, 
                                                    &temp.localizacao,
                                                    &temp.estado)==5){
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

/// @brief Lê os tipos de transporte de um ficheiro e adiciona-os a uma lista.
/// @param headRef é um duplo ponteiro para a cabeça da lista de tipos de transporte.
/// @param ficheiro é o arquivo do qual os tipos de transporte serão lidos.
/// @return O total de tipos de transporte lidos e inseridos na lista.
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


/// @brief Procura um tipo de transporte na lista com base no seu id.
/// @param head é um duplo ponteiro para a cabeça da lista de tipos de transporte.
/// @param idTipo é o ID do tipo de transporte que estamos procurando.
/// @return Um ponteiro para o tipo de transporte, se encontrado. Caso contrário, retorna NULL.
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


#endif