#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../Headers/verificacoes.h"
#include "../Headers/menugestor.h"
#include "../Headers/menuutilizador.h"
#include "../Headers/funcoes.h"



int main() {

    struct NodeClientes* headClientes = NULL;
    struct NodeTransporte* headTransportes = NULL;
    struct NodeGestores* headGestores = NULL;
    struct NodeTransacoes* headTransacoes = NULL;
    int nifClienteLogado;
    int dadosCarregados = CarregarDados(&headClientes, &headTransportes, &headGestores, &headTransacoes);
    if (dadosCarregados) {
        printf("Dados carregados dos arquivos binários.\n");
    } else {
        printf("Dados carregados dos arquivos CSV.\n");
    }
    int tipoMenu;
    tipoMenu = IniciarLogin(&headClientes,&headGestores,&nifClienteLogado); 

    switch(tipoMenu)
    {
    case 1:
        MenuUtilizador(headClientes,headGestores,headTransportes,headTransacoes,nifClienteLogado);
        break;
    case 2:
        MenuGestor(headClientes,headGestores,headTransportes,headTransacoes);
        break;

    default:
        break;
    };
  }

    


