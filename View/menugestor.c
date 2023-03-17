/**
 * @file menugestor.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../Headers/menugestor.h"
#include "../Headers/funcoes.h"
#include "../Headers/verificacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100



/// @brief Switch case para o menu do gestor
/// @param headClientes Pointer para o header da lista de clientes
/// @param headGestores Pointer para o header da lista de gestores
/// @param headTransportes Pointer para o header da lista de transportes
/// @param headTransacoes Pointer para o header da lista de transacoes
int MenuGestor(struct NodeClientes* headClientes, struct NodeGestores* headGestores, struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes ){
    int id;
    while(1)
    {   
        int nif;
        int escolha = listaMenuGestor();
        switch (escolha)
        {
        case 1:
            struct Clientes clientes;
            clientes = AdicionarCliente(headClientes);
            if(InserirCliente(&headClientes, clientes))
                printf("Cliente adicionado com sucesso!\n");
                else printf("Erro ao adicionar cliente!\n");
            break;

        case 2:
            struct Clientes* clienteEditar;
            printf("Inserir NIF do Cliente: ");
            nif = VerificarInt();
            clienteEditar = ProcuraCliente(headClientes, nif);
            if (clienteEditar != NULL) {
                printf("Cliente encontrado:\n");
                printf("Nome: %s\n", clienteEditar->nome);
                printf("NIF: %d\n", clienteEditar->nif);
                printf("Morada: %s\n", clienteEditar->morada);
                printf("Saldo: %0.2f\n", clienteEditar->saldo);
                printf("Login: %s\n", clienteEditar->login);
                if(EditarCliente(clienteEditar)) printf("Cliente Editado Com Sucesso!\n"); 
                else printf("Operação cancelada.");   
            } else {
                printf("Cliente nao encontrado!\n");
            }
            break;
        case 3:
            printf("Inserir NIF do Cliente: ");
            nif = VerificarInt();
            if(RemoverCliente(&headClientes,nif)) printf("Cliente com NIF %d eliminado.",nif);
            else printf("Não foi encontrado nenhum cliente com o NIF: %d",nif);
            break;
        case 4:
            struct Clientes* clienteProcurar;
            printf("Inserir NIF do Cliente: ");
            nif = VerificarInt();
            clienteProcurar = ProcuraCliente(headClientes, nif);
            if (clienteProcurar != NULL) {
                printf("Cliente encontrado:\n");
                printf("Nome: %s\n", clienteProcurar->nome);
                printf("NIF: %d\n", clienteProcurar->nif);
                printf("Morada: %s\n", clienteProcurar->morada);
                printf("Saldo: %0.2f\n", clienteProcurar->saldo);
                printf("Login: %s\n", clienteProcurar->login);
            } else {
                printf("Cliente nao encontrado!\n");
            }
            break;

        case 5:
            if(MostrarClientes(headClientes)==0)printf("Não existem clientes registados.");
            break;

        case 11:
            struct Transporte transporte;
            transporte = EscreveTransporte(headTransportes);
            if(InserirTransporte(&headTransportes, transporte))
                printf("Transporte adicionado com sucesso!\n");
                else printf("Erro ao adicionar o transporte.");
            break;

        case 12:
            struct Transporte* transporteEditar;
            printf("Inserir ID do transporte: ");
            id = VerificarInt();
            if(VerificaIdTransportes(headTransportes,id)==1)
            transporteEditar = ProcurarTransporte(headTransportes, id);
            if (transporteEditar != NULL) {
                printf("Transporte encontrado:\n");
                printf("ID: %d\n", transporteEditar->id);
                printf("Tipo: %s\n", transporteEditar->tipo);
                printf("Bateria: %d\n", transporteEditar->nivelBateria);
                printf("Preço / hora: %0.2f\n", transporteEditar->preco);
                printf("Localização: %s\n", transporteEditar->localizacao);
                printf("Estado: %d\n", transporteEditar->estado);
                if(EditarTransporte(transporteEditar,id)) printf("Transporte Editado Com Sucesso!\n"); 
                else printf("Operação cancelada.");   
            } else {
                printf("Transporte nao encontrado!\n");
            }
            break;

        case 13:
            printf("Inserir ID do transporte: ");
            id = VerificarInt();
            if(RemoverTransporte(&headTransportes,id)) printf("Transporte com o ID %d eliminado.",id);
            else printf("Não foi encontrado nenhum transporte com o ID: %d",id);
            break;
        case 14:
            id = VerificarInt();
            ProcurarTransporte(headTransportes,id);
            break;
        case 15:
            if(!MostrarTransportes(headTransportes)) printf("Não existem transportes registados.");
            break;
        case 16:
            VerTransportesDisponiveis(headTransportes);
            break;
        case 17:
            MostrarTransportesOrdenados(headTransportes);
            break;
        case 18:
            //procurar por geocodigo
            break;
        case 21: 
            struct Gestores gestor;
            gestor = AdicionarGestor(headGestores);
            if(InserirGestor(&headGestores, gestor))
                printf("Gestor adicionado com sucesso!\n");
                else printf("Erro ao adicionar Gestor!\n");
            break;
            break;
        case 22:
            char nomeGestor[MAX_LENGTH];
            LerTextoInput("Inserir nome do Gestor: ",nomeGestor,MAX_LENGTH);
            if(RemoverGestor(&headGestores,nomeGestor)) printf("Gestor %s Eliminado.",nomeGestor);
            else printf("Não foi encontrado nenhum Gestor: %s",nomeGestor);
            break;
        case 23:
            if(!MostrarGestores(headGestores)) printf("Não existem gestores registados.");
            break;
        case 31:
            if(!MostrarTransacoes(headTransacoes)) printf("Não existem transacoes registadas.");
            break;
        case 32:
            int idCliente;
            printf("Inserir ID do Cliente: ");
            idCliente = VerificarInt();
            if(!MostrarTransacoesCliente(headTransacoes,idCliente)) printf("Não existem transacoes registadas para o cliente com o ID: %d",idCliente);
            break;
        case 33:
            struct Transacoes* transacaoEditar;
            printf("Inserir ID da Transação");
            id = VerificarInt();
            transacaoEditar = ProcurarTransacao(headTransacoes, id);
            if (transacaoEditar != NULL) {
                printf("Transação encontrada:\n");
                printf("ID do Cliente: %d\n", transacaoEditar->idClienteAAlugar);
                printf("ID do Transporte: %d\n", transacaoEditar->idTransporte);
                printf("Tempo Alugado: %d\n", transacaoEditar->tempoAlugado);
                if(EditarTransacao(transacaoEditar)) printf("Transação editada com sucesso.\n"); 
                else printf("Operação cancelada.");   
            } else {
                printf("Transação nao encontrada!\n");
            }
            break;
        case 34:
            int idTransacao;
            idTransacao = VerificarInt();
            if(!RemoverTransacao(&headTransacoes,idTransacao)) printf("Não foi encontrada nenhuma transação com o ID: %d",idTransacao);
            else printf("Transação com o ID: %d eliminada.",idTransacao);
            break;
        case 0:
            if (!ExportarClientes(headClientes)) {
                printf("Erro ao exportar dados dos Clientes.\n");
            }else printf("Clientes exportados com sucesso.\n");
            if (!ExportarGestores(headGestores)) {
                printf("Erro ao exportar dados dos Gestores.\n");
            }else printf("Gestores exportados com sucesso.\n");
            if (!ExportarTransportes(headTransportes)) {
                printf("Erro ao exportar dados dos Transportes.\n");
            }else printf("Transportes exportados com sucesso.\n");
            if (!ExportarTransacoes(headTransacoes)) {
                printf("Erro ao exportar dados das Transações.\n");
            }else printf("Transacoes exportados com sucesso.\n");
            break;
        default:
            printf("\nInsere uma das opções mostradas.\n");
            break;        
        }
    }
    }