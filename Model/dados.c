/**
 * @file dados.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../Headers/funcoes.h"
// Número maximo de caracteres que cada linha pode conter
#define MAX_LINHA 1024


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
        printf("Erro ao abrir ficheiro grafos");
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
        int id, adj1, dist1, adj2, dist2, adj3, dist3;
        char title[256];
        sscanf(linha, "%d,%[^,],%d,%d,%d,%d,%d,%d", 
                                                &id, title, 
                                                &adj1, &dist1, 
                                                &adj2, &dist2, 
                                                &adj3, &dist3);

        Vertice *novoVertice = CriarVertice(id, title);
        *grafo = InsereVertice(*grafo, novoVertice);

        Adjacente* novoAdjacente;

        if (adj1) {
            novoAdjacente = CriaAdjacente(adj1, dist1);
            *grafo = InsereAdjacente(*grafo, id, novoAdjacente);
        }
        if (adj2) {
            novoAdjacente = CriaAdjacente(adj2, dist2);
            *grafo = InsereAdjacente(*grafo, id, novoAdjacente);
        }
        if (adj3) {
            novoAdjacente = CriaAdjacente(adj3, dist3);
            *grafo = InsereAdjacente(*grafo, id, novoAdjacente);
        }

        totalVertices++;
    }
    return totalVertices;
}


/// @brief Carrega dados de transportes de um determinado ficheiro e passa-os para uma lista ligada.
/// @param head Pointer para o pointer do header da lista de transportes.
/// @param nomeFicheiro String com o nome do ficheiro que contem os dados dos transportes a ser carregado.
/// @return Retorna o número de transportes carregados.
int CarregarFicheiroTransportes(struct NodeTransporte** head, char* nomeFicheiro) {
    FILE *ficheiro;
    ficheiro = fopen(nomeFicheiro, "r");
    int totalTransportes = 0;
    if(ficheiro == NULL){
        return 0;
    }
    totalTransportes = LerTransportesDeFicheiro(head,ficheiro);
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
int LerTransportesDeFicheiro(struct NodeTransporte** headRef, FILE *ficheiro){
    char linha[MAX_LINHA];
    struct Transporte temp;
    int totalTransportes=0;
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL)
    {
        if(sscanf(linha,"%d\t%[^\t]\t%d\t%f\t%d\t%d", 
                                                    &temp.id, 
                                                    temp.tipo, 
                                                    &temp.nivelBateria, 
                                                    &temp.preco,
                                                    &temp.localizacao,
                                                    &temp.estado)==6){
            if(InserirTransporte(headRef,temp))
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
        printf("%s",linha);
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