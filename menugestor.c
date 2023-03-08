#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int MenuGestor(Clientes *cliente, int totalClientes, Gestores *gestores, int totalGestores, Transporte *transporte, int totalTransporte,Transacoes *transacoes, int totalTransacoes){
    while(1)
    {   
 int escolha = menu();
        switch (escolha)
        {
        case 1:
            if(totalClientes = LerCliente(cliente, totalClientes)) printf("\nCliente adicionado.\n");
            break;
        case 2:
            if(EditarCliente(cliente,totalClientes)==0) printf("\nNão existe nenhum cliente com esse NIF.\n");
            else printf("Cliente Editado com sucesso.");
            break;
        case 3:
            printf("Total de Clientes é de : %d", totalClientes);
            totalClientes = EliminarCliente(cliente,totalClientes);
            break;
        case 4:
            if(ProcurarCliente(cliente,totalClientes)==0) printf("Não existe nenhum cliente com esse NIF.\n");
            break;
        case 5:
            VerTodosClientes(cliente,totalClientes);
            break;
        case 6:
            //VerTodosTransportes(transporte,totalTransporte);
            break;
        case 7:
            printf("\nPremi 1 . Working.");
            break;
        case 8:
            printf("\nPremi 1 . Working.");
            break;
        case 9:
            printf("\nPremi 1 . Working.");
            break;
        case 0:
            printf("\nPremi 1 . Working.");
            break;
            
        default:
            printf("\nInsere uma opção de 0 a 9\n");
            break;        
        }
    }
    }