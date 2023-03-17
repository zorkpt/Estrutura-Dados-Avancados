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



/// @brief função Main que inicializa as listas, carrega os dados e inicia o login/menu.
/// @return 
int main() {
    // Inicializar variáveis
    struct NodeClientes* headClientes = NULL;
    struct NodeTransporte* headTransportes = NULL;
    struct NodeGestores* headGestores = NULL;
    struct NodeTransacoes* headTransacoes = NULL;
    int nifClienteLogado;
    // verificar se os ficheiros binários existem, se não existirem, carregar os dados dos ficheiros CSV, ou se não carrega nada
    int dadosCarregados = CarregarDados(&headClientes, &headTransportes, &headGestores, &headTransacoes);
    if (dadosCarregados == 1) {
        printf("Dados carregados dos arquivos binários.\n");
    } else if(dadosCarregados == 0) {
        printf("Dados carregados dos arquivos CSV.\n");
    } else {
        printf("Erro ao carregar dados.\n");
    }
    // login, retorna 1 se for cliente, 2 se for gestor, 0 se não for nenhum dos dois
    int tipoMenu = IniciarLogin(&headClientes,&headGestores,&nifClienteLogado); 

    switch(tipoMenu)
    {
    case 1:
        MenuUtilizador(headClientes,headGestores,headTransportes,headTransacoes,nifClienteLogado);
        break;
    case 2:
        MenuGestor(headClientes,headGestores,headTransportes,headTransacoes);
        break;

    default:
        printf("Erro ao iniciar sessão.\n");
        break;
    };
  }

    


