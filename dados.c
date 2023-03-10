#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "transportes.h"
#include "gestores.h"
#include "transacoes.h"
//corrigir
#define MAX_LINHAS 100



/// @brief 
/// @param cliente 
/// @param nomeFicheiro 
/// @return 
int CarregarDados(void* head, enum Estrutura tipoEstrutura, char *nomeFicheiro) {
    FILE *ficheiro;
    int totalClientes,totalTransportes;

    ficheiro = fopen(nomeFicheiro, "r");
    if(ficheiro == NULL){
        printf("Erro ao abrir o ficheiro.");
        return 0;
    }

    switch (tipoEstrutura)
    {
    case CLIENTES:
        totalClientes =  LerClientesDeFicheiro((struct NodeClientes**)head,ficheiro);
        return totalClientes;
    
    case TRANSPORTE:
        totalTransportes =  LerTransportesDeFicheiro((struct NodeTransporte**)head,ficheiro);
        return totalTransportes;
    
    case GESTORES:
        int totalGestores = LerGestoresDeFicheiro((struct NodeGestores**)head,ficheiro);
        return totalGestores;

    case TRANSACOES:
        int totalTransacoes = LerTransacoesDeFicheiro((struct NodeTransacoes**)head,ficheiro);
        return totalTransacoes;
    }    
 }

int LerClientesDeFicheiro(struct NodeClientes** headRef, FILE *ficheiro){
    char linha[MAX_LINHAS];
    struct Clientes temp;
    int totalClientes = 0;
    while (fgets(linha, MAX_LINHAS, ficheiro) != NULL)
    {
        sscanf(linha,"%d\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\n]", 
                                                &temp.nif, 
                                                temp.nome, 
                                                temp.morada, 
                                                &temp.saldo,
                                                temp.login,
                                                temp.password);
    InserirCliente(headRef, temp);
    totalClientes++;
    }
    return totalClientes;
}

int LerTransportesDeFicheiro(struct NodeTransporte** headRef, FILE *ficheiro){
    char linha[MAX_LINHAS];
    struct Transporte temp;
    int totalTransportes = 0;
    while (fgets(linha, MAX_LINHAS, ficheiro) != NULL)
    {
        sscanf(linha,"%d\t%[^\t]\t%d\t%f\t%[^\t]%d", 
                                                            &temp.id, 
                                                            temp.tipo, 
                                                            &temp.nivelBateria, 
                                                            &temp.preco,
                                                            temp.localizacao,
                                                            &temp.estado);
        InserirNoFimTransporte(headRef,temp);
        totalTransportes++;
    }

    return totalTransportes;
}

int LerGestoresDeFicheiro(struct NodeGestores** headRef, FILE *ficheiro){
    char linha[MAX_LINHAS];
    struct Gestores temp;
    int totalGestores = 0;
    while (fgets(linha, MAX_LINHAS, ficheiro) != NULL)
    {
        sscanf(linha,"%[^\t]\t%s\n", 
                                                            temp.nome, 
                                                            temp.password);
        InserirGestor(headRef,temp);
        totalGestores++;
    }
    return totalGestores;
}

int LerTransacoesDeFicheiro(struct NodeTransacoes** headRef, FILE *ficheiro){
    char linha[MAX_LINHAS];
    struct Transacoes temp;
    int totalTransacoes = 0;
    while (fgets(linha, MAX_LINHAS, ficheiro) != NULL)
    {
        sscanf(linha,"%d\t%d\t%d\n", 
                                &temp.idClienteAAlugar, 
                                &temp.idTransporte,
                                &temp.tempoAluguerDecorrido);

        InserirTransacoes(headRef,temp);
        totalTransacoes++;
    }

    return totalTransacoes;
}