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
#include "../Headers/importexport.h"
#include "../Headers/verificacoes.h"
#include "../Headers/caminho.h"
#include "../Headers/transportes.h"
#include "../Headers/viagem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100
#define MAX_CHARS 50


/// @brief Switch case para o menu do gestor
/// @param headClientes Pointer para o header da lista de clientes
/// @param headGestores Pointer para o header da lista de gestores
/// @param headTransportes Pointer para o header da lista de transportes
/// @param headTransacoes Pointer para o header da lista de transacoes
int MenuGestor(struct NodeClientes* headClientes, struct NodeGestores* headGestores, 
                struct NodeTransporte* headTransportes, NodeTipoTransporte* headTipoTransporte, 
                struct NodeTransacoes* headTransacoes, Vertice *headVertice, Viagem *headViagem )
    {
    int id;
    while(1)
    {   
        // Verificar se o centro de recolha está definido
        if (headVertice->idCentroRecolha == -1) {
            
            printf("\nATENÇÃO: O centro de recolha não está definido!\n");
            printf("Por favor, defina o local para o centro de recolha:\n");
            int idLocal = VerificarInt();

            if (ProcuraVertice(headVertice, idLocal)) {
                headVertice->idCentroRecolha = idLocal;
                printf("O centro de recolha foi definido para o local: [%d] %s\n", idLocal, GetNomeLocal(headVertice, idLocal));
            } else {
                printf("O local com ID: %d não existe. Por favor, insira um ID válido.\n", idLocal);
                continue;
            }
        }

        int nif;
        int escolha = listaMenuGestor();
        switch (escolha)
        {

            // Adicionar Cliente
            case 1:
                struct Clientes clientes;
                char nome[MAX_CHARS], morada[MAX_CHARS], login[MAX_CHARS], password[MAX_CHARS];
                int nif, localAtual;
                float saldo;

                printf("Insira os dados do novo cliente:\n");
                LerTextoInput("Nome: ", nome, MAX_CHARS);
                printf("NIF: ");
                nif = VerificarInt();
                LerTextoInput("Morada: ", morada, MAX_CHARS);
                printf("Saldo: ");
                saldo = VerificarFloat();
                LerTextoInput("Nome de Utilizador: ", login, MAX_CHARS);
                LerTextoInput("Password: ", password, MAX_CHARS);
                printf("Localização Atual: ");
                localAtual = VerificarInt();

                clientes = AdicionarCliente(headClientes, nome, morada, nif, saldo, login, password, localAtual);

                if (InserirCliente(&headClientes, clientes))
                    printf("Cliente adicionado com sucesso!\n");
                else
                    printf("Erro ao adicionar cliente!\n");
                break;

            // Editar Cliente
            case 2:
                struct Clientes* clienteEditar;
                char nomeEditar[MAX_CHARS], moradaEditar[MAX_CHARS], loginEditar[MAX_CHARS], passwordEditar[MAX_CHARS];
                printf("Inserir NIF do Cliente: \n");
                nif = VerificarInt();
                clienteEditar = ProcuraCliente(headClientes, nif);
                if (clienteEditar != NULL) {
                    printf("Cliente encontrado:\n");
                    printf("Nome: %s\n", clienteEditar->nome);
                    printf("NIF: %d\n", clienteEditar->nif);
                    printf("Morada: %s\n", clienteEditar->morada);
                    printf("Saldo: %0.2f\n", clienteEditar->saldo);
                    printf("Login: %s\n", clienteEditar->login);
                    printf("\nInsira os novos dados do cliente:\n");
                    LerTextoInput("Nome: ", nomeEditar, MAX_CHARS);
                    LerTextoInput("Morada: ", moradaEditar, MAX_CHARS);
                    LerTextoInput("Nome de Utilizador: ", loginEditar, MAX_CHARS);
                    LerTextoInput("Password: ", passwordEditar, MAX_CHARS);
                    if (EditarCliente(clienteEditar, nomeEditar, moradaEditar, loginEditar, passwordEditar)) {
                        printf("Cliente Editado Com Sucesso!\n");
                    } else {
                        printf("Operação cancelada.");
                    }
                } else {
                    printf("Cliente nao encontrado!\n");
                }
                break;

            // Remover Cliente
            case 3:
                printf("Inserir NIF do Cliente: ");
                nif = VerificarInt();
                if(RemoverCliente(&headClientes,nif)) printf("Cliente com NIF %d eliminado.",nif);
                else printf("Não foi encontrado nenhum cliente com o NIF: %d",nif);
                break;

            // Procurar Cliente por NIF
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

            // Listar Clientes
            case 5:
                if(MostrarClientes(headClientes)==0)printf("Não existem clientes registados.");
                break;

            // Adicionar Transporte
            case 11:
                struct Transporte transporte;
                int tipo;
                int idTransporte, localizacao, nivelBateria, estado;
                float preco;
                printf("Insira os dados do novo transporte:\n");
                printf("ID: ");
                idTransporte = VerificarInt();
                if(!VerificaIdTransportes(headTransportes, idTransporte)) {
                break;
                }
                printf("Nivel de Bateria: ");
                nivelBateria = VerificarInt();
                printf("Tipo: ");
                tipo = VerificarInt();
                printf("Localização: ");
                localizacao = VerificarInt();
                printf("Estado: ");
                estado = VerificarInt();
                printf("Preço: ");
                preco = VerificarFloat();
                
                transporte = EscreveTransporte(&headTipoTransporte, idTransporte, tipo, nivelBateria, localizacao, estado);
                if(InserirTransporte(&headTransportes, transporte))
                    printf("Transporte adicionado com sucesso!\n");
                    else printf("Erro ao adicionar o transporte.");
                break;

            // Editar Transporte
            case 12:
                char tipoEditar[MAX_CHARS];
                int nivelBateriaEditar, estadoEditar, localizacaoEditar;
                float precoEditar;
                struct Transporte* transporteEditar;
                printf("Inserir ID do transporte: ");
                id = VerificarInt();
                if(!VerificaIdTransportes(headTransportes,id)){
                    printf("Transporte não encontrado!");
                    break;
                }
                transporteEditar = ProcurarTransporte(headTransportes, id);
                
                if (transporteEditar != NULL) {
                    printf("Transporte encontrado:\n");
                    printf("ID: %d\n", transporteEditar->id);
                    //printf("Tipo: %s\n", transporteEditar->tipo);
                    printf("Bateria: %d\n", transporteEditar->nivelBateria);
                    printf("Preço / hora: %0.2f\n", transporteEditar->tipo->precoPorKm);
                    printf("Localização: %d\n", transporteEditar->localizacao);
                    printf("Estado: %d\n", transporteEditar->estado);
                }
                printf("\nNovos Dados do transporte:\n");
                LerTextoInput("Tipo?", tipoEditar, MAX_CHARS);
                printf("Bateria: ");
                nivelBateriaEditar = VerificarInt();
                printf("Preço por Hora: ");
                precoEditar = VerificarFloat();
                printf("Localização: ");
                localizacaoEditar = VerificarInt();
                printf("Estado do transporte: ");
                estadoEditar = VerificarInt();
                if (EditarTransporte(transporteEditar, id, estadoEditar, nivelBateriaEditar, precoEditar, localizacaoEditar)) { 
                    printf("Transporte Editado Com Sucesso!\n");
                } else {
                    printf("Operação cancelada.");
                }
                break;

            // Remover transporte
            case 13:
                printf("Inserir ID do transporte: ");
                id = VerificarInt();
                if(RemoverTransporte(&headTransportes,id)) 
                    printf("Transporte com o ID %d eliminado.",id);
                else 
                    printf("Não foi encontrado nenhum transporte com o ID: %d",id);
                break;

            // Procurar transporte por ID
            case 14:
                id = VerificarInt();
                ProcurarTransporte(headTransportes,id);
                break;

            // Mostrar transportes
            case 15:
                if(!MostrarTransportes(headTransportes)) printf("Não existem transportes registados.");
                break;

            // Ver transportes disponiveis
            case 16:
                VerTransportesDisponiveis(headTransportes,headVertice,headVertice->idCentroRecolha);
                break;

            // Mostrar transportes ordenados por bateria
            case 17:
                MostrarTransportesOrdenados(headTransportes);
                break;

            // Procurar por geocodigo
            case 18:
                //procurar por geocodigo
                break;

            // Alterar Preço de um tipo de transporte
            case 19:
                ListarTiposTransporte(headTipoTransporte);
                printf("Digite o ID do tipo de transporte que deseja alterar o preço: ");
                int idTipo = VerificarInt();
                
                printf("Digite o novo preço por Km para esse tipo de transporte: ");
                float novoPreco = VerificarFloat();
                
                int resultado = AlterarPrecoTransporte(headTipoTransporte, idTipo, novoPreco);

                if (resultado) {
                    printf("O preço foi alterado com sucesso.\n");
                } else {
                    printf("Não foi encontrado nenhum tipo de transporte com o ID fornecido.\n");
                }
                break;

            // Adicionar Gestor
            case 21: 
                struct Gestores gestorNovo;
                char nomeGestor[MAX_LENGTH];
                char passwordGestor[MAX_LENGTH];
                LerTextoInput("Insira os dados do novo Gestor: ", nomeGestor, MAX_LENGTH);
                if(VerificaGestor(headGestores, nomeGestor)) {
                    printf("Gestor com esse nome já existe.\n");
                    break;
                }
                LerTextoInput("Insira a password do Gestor: ", passwordGestor, MAX_LENGTH);
                gestorNovo = AdicionarGestor(headGestores, nomeGestor, passwordGestor);
                if(InserirGestor(&headGestores, gestorNovo))
                    printf("Gestor adicionado com sucesso!\n");
                else 
                    printf("Erro ao adicionar Gestor!\n");
                break;

            // Eliminar Gestor
            case 22:
                char nomeGestorRemover[MAX_LENGTH];
                LerTextoInput("Inserir nome do Gestor para eliminar: ",nomeGestorRemover,MAX_LENGTH);
                if(RemoverGestor(&headGestores,nomeGestorRemover)) printf("Gestor %s Eliminado.",nomeGestorRemover);
                else printf("Não foi encontrado nenhum Gestor: %s",nomeGestorRemover);
                break;

            // Mostrar Gestores
            case 23:
                if(!MostrarGestores(headGestores)) printf("Não existem gestores registados.");
                break;

            // Mostrar Viagens/Transações
            case 31:
                int totalTransacoes = MostrarTransacoes(headVertice, headViagem);
                if(totalTransacoes == 0) printf("Não existem transacoes registadas.");
                else printf("Total de transacoes: %d",totalTransacoes);
                break;

            // Mostrar Transações de um Cliente
            case 32:
                int idCliente;
                printf("Inserir ID do Cliente: ");
                idCliente = VerificarInt();
                if(!MostrarTransacoesCliente(headTransacoes,idCliente)) printf("Não existem transacoes registadas para o cliente com o ID: %d",idCliente);
                break;

            // Procurar Transação
            case 33:
                struct Transacoes* transacaoEditar;
                int idClienteEditar, idTransporteEditar, tempoAlugadoEditar;
                printf("Inserir ID da Transação");
                id = VerificarInt();
                transacaoEditar = ProcurarTransacao(headTransacoes, id);
                if (transacaoEditar != NULL) {
                    printf("Transação encontrada:\n");
                    printf("ID do Cliente: %d\n", transacaoEditar->idClienteAAlugar);
                    printf("ID do Transporte: %d\n", transacaoEditar->idTransporte);
                    printf("Tempo Alugado: %d\n", transacaoEditar->tempoAlugado);
                    printf("A editar transação:\n");
                    printf("Tempo alugado: ");
                    tempoAlugadoEditar = VerificarInt();
                    printf("ID Cliente: ");
                    idClienteEditar = VerificarInt();
                    printf("ID Transporte: ");
                    idTransporteEditar = VerificarInt();

                    if(EditarTransacao(transacaoEditar,tempoAlugadoEditar,idClienteEditar,idTransporteEditar)) printf("Transação editada com sucesso.\n"); 
                    else printf("Operação cancelada.");   
                } else {
                    printf("Transação nao encontrada!\n");
                }
                break;

            // Remover Transação
            case 34:
                int idTransacao;
                idTransacao = VerificarInt();
                if(!RemoverTransacao(&headTransacoes,idTransacao)) printf("Não foi encontrada nenhuma transação com o ID: %d",idTransacao);
                else printf("Transação com o ID: %d eliminada.",idTransacao);
                break;

            // Recolha de transportes - Greedy Search
            case 99:
                Caminho *caminho = GreedySearch(headTransportes, headVertice, headVertice->idCentroRecolha);
                printf("Caminho encontrado:\n");
                ImprimirCaminho(caminho,headVertice->idCentroRecolha);
                break;

            //Exportar dados
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
                if(!ExportarTiposTransporte(headTipoTransporte)) {
                    printf("Erro ao exportar dados dos Tipos de Transporte.\n");
                }else printf("Tipos de Transporte exportados com sucesso.\n");
                if(!ExportaVertices(headVertice)) {
                    printf("Erro ao exportar dados dos Vertices.\n");
                }else printf("Vertices exportados com sucesso.\n");
                break;

            default:
                printf("\nInsere uma das opções mostradas.\n");
                break;        
        }
    }
    }