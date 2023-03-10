#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int MenuGestor(struct NodeClientes* headClientes, struct NodeGestores* headGestores, struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes ){
    while(1)
    {   
 int escolha = menu();
        switch (escolha)
        {
        case 1:
            if(AdicionarCliente(headClientes)) printf("Cliente Adicionado.");
            else printf("Falha ao adicionar Cliente.");
            break;

        case 2:
            int nif;
            printf("Inserir NIF do Cliente: ");
            nif = verificarInt();
            if(EditarCliente(headClientes,nif)) printf("Cliente atualizado com sucesso!\n");
            else printf("Operação cancelada pelo utilizador.\n");
            break;
        case 3:
            printf("Inserir NIF do Cliente: ");
            nif = verificarInt();
            if(RemoverCliente(&headClientes,nif)) printf("Cliente com NIF %d eliminado.",nif);
            else printf("Não foi encontrado nenhum cliente com o NIF: %d",nif);
            break;
        case 4:
            printf("Inserir NIF do Cliente: ");
            nif = verificarInt();
           if(!ProcuraCliente(headClientes,nif)) printf("Não existe nenhum cliente com esse NIF.\n");
            break;
        case 5:
            MostrarClientes(headClientes);
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
            char* nomeFicheiro = LerNomeFicheiro();
            if (nomeFicheiro == NULL) {
                printf("Erro: Não foi possivel ler o nome do ficheiro.\n");
                break;
            }
            if(ExportarParaBinario(headClientes,headGestores,headTransportes,headTransacoes,nomeFicheiro)) {
                printf("Ficheiro %s criado.",nomeFicheiro);
            }else printf("Não foi possivel exportar os dados para o ficheiro.");
            
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