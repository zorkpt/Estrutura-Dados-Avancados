#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define MAX_LINHAS 100



/// @brief 
/// @param cliente 
/// @param nomeFicheiro 
/// @return 
int CarregarDados(void *estrutura, enum Estrutura tipoEstrutura, char *nomeFicheiro) {
    FILE *ficheiro;

    ficheiro = fopen(nomeFicheiro, "r");
    if(ficheiro == NULL){
        printf("Erro ao abrir o ficheiro.");
        return 0;
    }
    
    int LerTransportes(Transporte *transporte, FILE *ficheiro);
    int LerClientes(Clientes *cliente, FILE *ficheiro);
    int LerGestores(Gestores *gestores, FILE *ficheiro);
    int LerTransacoes(Transacoes *transacoes, FILE *ficheiro);

    switch (tipoEstrutura)
    {
    case CLIENTES:
        Clientes *cliente = (Clientes*)estrutura;
        int totalClientes = LerClientesDeFicheiro(cliente,ficheiro);
        return totalClientes;
        break;
    
    case TRANSPORTE:
        Transporte *transporte = (Transporte*)estrutura;
        int totalTransportes = LerTransportes(transporte,ficheiro);
        return totalTransportes;
        break;
    
    case GESTORES:
        Gestores *gestores = (Gestores*)estrutura;
        int totalGestores = LerGestores(gestores,ficheiro);
        return totalGestores;

    case TRANSACOES:
        Transacoes *transacoes = (Transacoes*)estrutura;
        int totalTransacoes = LerTransacoes(transacoes,ficheiro);
        return totalTransacoes;
    }    
}

int LerClientesDeFicheiro(Clientes *cliente, FILE *ficheiro){
    char linha[MAX_LINHAS];
    int i = 0;
    while (fgets(linha, MAX_LINHAS, ficheiro) != NULL)
    {
        sscanf(linha,"%d\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\n]", 
                                                &cliente[i].nif, 
                                                cliente[i].nome, 
                                                cliente[i].morada, 
                                                &cliente[i].saldo,
                                                cliente[i].login,
                                                cliente[i].password);
        i++;
    }
    int totalClientes = i;

    return totalClientes;
}

int LerTransportes(Transporte *transporte, FILE *ficheiro){
    char linha[MAX_LINHAS];
    int i = 0;
    while (fgets(linha, MAX_LINHAS, ficheiro) != NULL)
    {
        sscanf(linha,"%d\t%[^\t]\t%d\t%f\t%[^\t]%d", 
                                                            &transporte[i].id, 
                                                            transporte[i].tipo, 
                                                            &transporte[i].nivelBateria, 
                                                            &transporte[i].preco,
                                                            transporte[i].localizacao,
                                                            &transporte[i].estado);
        i++;
    }
    int totalTransportes = i;

    for(int i = 0 ; i<totalTransportes; i++){
        printf("ID: %d\tTIPO: %s\tBATERIA: %d\t\tPRECO: %.2f\t\tLOCAL:%s\n",transporte[i].id, transporte[i].tipo, transporte[i].nivelBateria, transporte[i].preco,transporte[i].localizacao);
    }
    return totalTransportes;
}

int LerGestores(Gestores *gestores, FILE *ficheiro){
    char linha[MAX_LINHAS];
    int i = 0;
    while (fgets(linha, MAX_LINHAS, ficheiro) != NULL)
    {
        sscanf(linha,"%[^\t]\t%s\n", 
                                                            gestores[i].nome, 
                                                            gestores[i].password);
        i++;
    }
    int totalGestores = i;

    for(int i = 0 ; i<totalGestores; i++){
        printf("nome: %s\tpass: %s\n",gestores[i].nome, gestores[i].password);
    }
    return totalGestores;
}

int LerTransacoes(Transacoes *transacoes, FILE *ficheiro){
    char linha[MAX_LINHAS];
    int i = 0;
    while (fgets(linha, MAX_LINHAS, ficheiro) != NULL)
    {
        sscanf(linha,"%d\t%d\t%d\n", 
                                &transacoes[i].idClienteAAlugar, 
                                &transacoes[i].idTransporte,
                                &transacoes[i].tempoAluguerDecorrido);
        i++;
    }
    int totalTransacoes = i;
    for(int i = 0 ; i<totalTransacoes; i++){
        printf("id cliente: %d\ttempo decorrido: %d\n",transacoes[i].idClienteAAlugar, transacoes[i].tempoAluguerDecorrido);
    }
    return totalTransacoes;
}