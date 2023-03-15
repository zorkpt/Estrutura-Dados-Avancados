#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int main() {

    struct NodeClientes* headClientes = NULL;
    struct NodeTransporte* headTransportes = NULL;
    struct NodeGestores* headGestores = NULL;
    struct NodeTransacoes* headTransacoes = NULL;


    int totalClientes = CarregarFicheiroClientes(&headClientes,"./Data/clients.csv");
    if(totalClientes == 0)
    {
        printf("Erro ao carregar ficheiro de clientes");
    }else
    {
        printf("Carregados %d clientes\n",totalClientes);
    }

    int totalTransportes = CarregarFicheiroTransportes(&headTransportes,"./Data/transportes.csv");
    if(totalTransportes == 0)
    {
        printf("Erro ao carregar ficheiro de transportes");
    }else 
    {
        printf("Carregados %d transportes\n",totalTransportes);
    }

    int totalGestores = CarregarFicheiroGestores(&headGestores,"./Data/gestores.csv");
    if(totalGestores == 0)
    {
        printf("Erro ao carregar ficheiro de gestores");
    }else
    {
        printf("Carregados %d gestores\n",totalGestores);
    }

    int totalTransacoes = CarregarFicheiroTransacoes(&headTransacoes,"./Data/transacoes.csv");
    if(totalTransacoes == 0)
    {
        printf("Erro ao carregar ficheiro de transacoes");
    }else
    {
        printf("Carregados %d transacoes\n",totalTransacoes);
    }

    int tipoMenu;
    // MostrarClientes(headClientes);

    tipoMenu = IniciarLogin(&headClientes,&headGestores);
//    RemoverCliente(&headClientes,323211223);
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

    


