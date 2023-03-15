#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Controller/funcoes.h"
// Número maximo de caracteres que cada linha pode conter
#define MAX_LINHA 100


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

int LerClientesDeFicheiro(struct NodeClientes** headRef, FILE *ficheiro){
    char linha[MAX_LINHA];
    struct Clientes temp;
    int totalClientes=0;
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL)
    {
        if(sscanf(linha,"%d\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\n]", 
                                                                &temp.nif, 
                                                                temp.nome, 
                                                                temp.morada, 
                                                                &temp.saldo,
                                                                temp.login,
                                                                temp.password)==6){
            InserirCliente(headRef, temp);
            totalClientes++;
        }
            
    }
    return totalClientes;
}

int LerTransportesDeFicheiro(struct NodeTransporte** headRef, FILE *ficheiro){
    char linha[MAX_LINHA];
    struct Transporte temp;
    int totalTransportes=0;
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL)
    {
        if(sscanf(linha,"%d\t%[^\t]\t%d\t%f\t%[^\t]%d", 
                                                    &temp.id, 
                                                    temp.tipo, 
                                                    &temp.nivelBateria, 
                                                    &temp.preco,
                                                    temp.localizacao,
                                                    &temp.estado)==6){
            InserirTransporte(headRef,temp);
            totalTransportes++;
        }
            
    }

    return totalTransportes;
}

int LerGestoresDeFicheiro(struct NodeGestores** headRef, FILE *ficheiro){
    char linha[MAX_LINHA];
    struct Gestores temp;
    int totalGestores=0;
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL)
    {
        if(sscanf(linha,"%[^\t]\t%s\n",temp.nome,temp.password)==2){
            InserirGestor(headRef,temp);
            totalGestores++;
        }
            
    }
    return totalGestores;
}

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
            InserirTransacoes(headRef,temp);
            totalTransacoes++;
        }
            
        }
    return totalTransacoes;
}