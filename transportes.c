#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int VerTodosTransportes(Transporte *transporte, int totalTransportes) {
    for(int i = 0 ; i < totalTransportes; i++ ){
        printf("ID: %d\tTIPO: %s\tBATERIA: %d\t\tPRECO: %.2f\t\tLOCAL:%s\n",transporte[i].id, transporte[i].tipo, transporte[i].nivelBateria, transporte[i].preco,transporte[i].localizacao);
    }
    return 1;
}

int VerTransportesDisponiveis(Transporte *transporte, int totalTransporte, Transacoes *transacoes, int totalTransacoes){
    for(int i = 0; i < totalTransporte; i++) { 
        for(int j = 0 ; j < totalTransacoes ; j++){
            if(transporte[i].id == transacoes[j].idClienteAAlugar){
                printf("ID: %d\tTIPO: %s\tBATERIA: %d\t\tPRECO: %.2f\t\tLOCAL:%s\n",transporte[i].id, transporte[i].tipo, transporte[i].nivelBateria, transporte[i].preco,transporte[i].localizacao);
            }    
        }
    }
}

