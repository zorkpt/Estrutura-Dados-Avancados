#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

//corrigir
#define MAX_CLIENTES 100

int main() {

    struct NodeClientes* headClientes = NULL;
    struct NodeTransporte* headTransportes = NULL;
    struct NodeGestores* headGestores = NULL;
    struct NodeTransacoes* headTransacoes = NULL;

    int totalClientes = CarregarDados(&headClientes,CLIENTES,"./Data/clients.csv");
    int totalTransportes = CarregarDados(&headTransportes,TRANSPORTE,"./Data/transportes.csv");
    int totalGestores = CarregarDados(&headGestores,GESTORES,"./Data/gestores.csv");
    int totalTransacoes = CarregarDados(&headTransacoes,TRANSACOES,"./Data/transacoes.csv");
    int tipoMenu;

    tipoMenu = IniciarLogin(&headClientes,&headGestores);
    printf("%d",tipoMenu);
//    RemoverCliente(&headClientes,323211223);
//     MostrarClientes(headClientes);
//     printf("total de clientes: %d",totalClientes);
//     RemoverCliente(&headClientes,987327362);
//     MostrarTransportes(headTransportes);
//     MostrarTransacoes(headTransacoes);
//     MostrarGestores(headGestores);
    
//     MostrarClientes(headClientes);
//     AdicionarCliente(headClientes);
//     MostrarClientes(headClientes);
    
   

    

    switch(tipoMenu)
    {
    case 1:
        //MenuUtilizador(cliente,totalClientes);
        break;
    case 2:
        MenuGestor(headClientes,headGestores,headTransportes,headTransacoes);
        break;

    default:
        break;
    };
  }
// }
    


