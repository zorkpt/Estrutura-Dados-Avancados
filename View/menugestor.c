#include "../Controller/funcoes.h"
#include "../Controller/verificacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100



int MenuGestor(struct NodeClientes* headClientes, struct NodeGestores* headGestores, struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes ){
    int id;
    while(1)
    {   
        int nif;
        int escolha = menu();
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
            if(VerificaIdTransportes(headTransportes,id)==0)
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
            VerTransportesDisponiveis(headTransportes,headTransacoes);
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
            char nomeGestor[MAX_CHAR];
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
            char* nomeFicheiro = LerNomeFicheiro();
            if (nomeFicheiro == NULL) {
                printf("Erro: Não foi possivel ler o nome do ficheiro.\n");
                break;
            }
            if(ExportarParaBinario(headClientes,headGestores,headTransportes,headTransacoes,nomeFicheiro)) {
                printf("Ficheiro %s criado.",nomeFicheiro);
            }else printf("Não foi possivel exportar os dados para o ficheiro.");
            
            break;

        default:
            printf("\nInsere uma opção de 0 a 9\n");
            break;        
        }
    }
    }