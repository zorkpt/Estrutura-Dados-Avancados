/**
 * @file main.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../Headers/verificacoes.h"
#include "../Headers/menugestor.h"
#include "../Headers/menuutilizador.h"
#include "../Headers/funcoes.h"
#define BUFFER_SIZE 1024



/// @brief função Main que inicializa as listas, carrega os dados e inicia o login/menu.
/// @return 
int main() {

    Vertice *headVertice = NULL;

    read_csv_file("Data/matrix.csv", &headVertice);

     // Print the graph
    PrintGrafo(headVertice);





    // Inicializar variáveis
    NodeClientes* headClientes = NULL;
    NodeTransporte* headTransportes = NULL;
    NodeGestores* headGestores = NULL;
    NodeTransacoes* headTransacoes = NULL;
    MostrarClientes(headClientes);
    int nifClienteLogado;
    // verificar se os ficheiros binários existem, se não existirem, carregar os dados dos ficheiros CSV, ou se não, não carrega nada
    int dadosCarregados = CarregarDados(&headClientes, &headTransportes, &headGestores, &headTransacoes);
    if (dadosCarregados == 1) {
        printf("Dados carregados dos arquivos binários.\n");
    } else if(dadosCarregados == 0) {
        printf("Dados carregados dos arquivos CSV.\n");
    } else {
        printf("Erro ao carregar dados.\n");
    }
    // login, retorna 1 se for cliente, 2 se for gestor, 0 se não for nenhum dos dois




//testes
    int localCliente = 45; // teste -  ID do vértice que representa a localização do cliente

    NodeTransporte *transporteMaisProximo = BuscarTransporteMaisProximo(headTransportes, headVertice, localCliente);

    if (transporteMaisProximo) {
        printf("O transporte mais próximo é o transporte com ID %d, localizado no vértice %d\n",
               transporteMaisProximo->transporte.id, transporteMaisProximo->transporte.localizacao);
    } else {
        printf("Nenhum transporte disponível foi encontrado.\n");
    }



    int origem = 1;
    int destino = 11;
    Caminho *caminho = BuscaEmLargura(headVertice, origem, destino);

    if (caminho) {
        printf("Caminho encontrado entre %d e %d:\n", origem, destino);
        while (caminho != NULL) {
            printf("ID: %d, Cidade: %s, Distancia: %.2f\n", caminho->idVertice, GetLocationName(headVertice, caminho->idVertice), caminho->distancia);
            Caminho *caminhoTemp = caminho;
            caminho = caminho->proximo;
            free(caminhoTemp);
        }
    } else {
        printf("Nenhum caminho encontrado entre %d e %d.\n", origem, destino);
    }

//fim testes








    int tipoMenu = IniciarLogin(&headClientes,&headGestores,&nifClienteLogado); 

    switch(tipoMenu)
    {
    case 1:
        MenuUtilizador(headClientes,headGestores,headTransportes,headTransacoes,nifClienteLogado);
        break;
    case 2:
        MenuGestor(headClientes,headGestores,headTransportes,headTransacoes, headVertice);
        break;

    default:
        printf("Erro ao iniciar sessão.\n");
        break;
    };
  }

    


