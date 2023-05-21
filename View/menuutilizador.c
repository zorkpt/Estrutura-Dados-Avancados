/**
 * @file menuutilizador.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/menuutilizador.h"
#include "../Headers/caminho.h"
#include "../Headers/funcoes.h"
#include "../Headers/verificacoes.h"
#define MAX_LENGTH 100



/// @brief Mostar o cabeçalho do menu do cliente
/// @param cliente 
/// @param headGrafo 
void MostrarCabecalhoCliente(Clientes *cliente, Vertice *headGrafo) {
    printf("\n\nBem-vindo %s\n", cliente->nome);
    printf("Estás em [%d] %s\n", cliente->localCliente, GetNomeLocal(headGrafo, cliente->localCliente));
    printf("Saldo Atual: %.2f€\n", cliente->saldo);
}



/// @brief Vista e opções destinadas ao utilizador/cliente
/// @param headClientes Pointer para o header da lista de clientes
/// @param headGestores Pointer para o header da lista de gestores
/// @param headTransportes Pointer para o header da lista de transportes
/// @param headTransacoes Pointer para o header da lista de transacoes
/// @param nifClienteLogado NIF do cliente que está logado
/// @return 
int MenuUtilizador(struct NodeClientes* headClientes, struct NodeGestores* headGestores, 
                struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes, Vertice* headGrafo,
                int nifClienteLogado, NodeTipoTransporte* headTipoTransporte ){
    while (1) {
        struct Clientes *cliente = ProcuraCliente(headClientes, nifClienteLogado);
        struct Transporte *transporteAlugar;

        MostrarCabecalhoCliente(cliente, headGrafo);
        int escolha = ListaMenuCliente();

        switch (escolha)
        {
            // Caso 1: Visualizar todos os meios de mobilidade elétrica disponíveis
            case 1:
                MostrarTransportesOrdenados(headTransportes);
                break;

            // Caso 2: Visualizar meios de mobilidade elétrica disponíveis por geocódigo
            case 2:
                int localEscolhido;
                printf("Insere o local onde queres procurar os transportes: ");
                localEscolhido = VerificarInt();

                // Verificar se o local inserido é válido
                Vertice *localValido = ProcuraVertice(headGrafo, localEscolhido);
                if (localValido == NULL) {
                    printf("Local não encontrado.\n");
                } else {
                    struct NodeTransporte *transportesNoLocal = ProcurarTransportesPorLocal(headTransportes, localEscolhido);
                    if (transportesNoLocal == NULL) {
                        printf("Não foram encontrados transportes no local %d.\n", localEscolhido);
                    } else {
                        MostrarTransportes(transportesNoLocal);
                    }
                }
                break;
            // Caso 3: Alugar um meio de mobilidade elétrica
            case 3:
                int idTransporte;
                int podeAlugar = VerificaSePodeAlugar(headTransacoes, cliente, nifClienteLogado);
                if(podeAlugar == -1){
                    printf("Não podes alugar um transporte enquanto estiver num transporte.\n");
                    break;
                }else if(podeAlugar == 0) {
                    printf("Não tens saldo suficiente para alugar um transporte.\n");
                    break;
                }

                VerTransportesDisponiveis(headTransportes,headGrafo,cliente->localCliente);
                printf("Escolher um dos transportes disponiveis de momento: (ID) ");
                idTransporte = VerificarInt();
                transporteAlugar = ProcurarTransporte(headTransportes, idTransporte);

                if (transporteAlugar != NULL && AlugarTransporteDisponivel(transporteAlugar)) {
                    int novoIdTransaccao = ProximoIDTransacao(headTransacoes);
                    if (!AtualizarEstadoTransporte(cliente, headTransportes, headTransacoes, idTransporte, novoIdTransaccao)) {
                        printf("Erro ao processar aluguer.\n");
                    } else {
                        printf("Transporte alugado com sucesso.\n");
                    }
                } else {
                    printf("Não foi encontrado Meio de Transporte para esse ID.\n");
                }
                break;


            // Caso 4: Terminar Viagem
            case 4:
                if (!ClienteEmTransporte(headTransacoes, nifClienteLogado)) {
                    printf("Não estás a utilizar um transporte no momento.\n");
                } else {
                    Clientes *cliente = ProcuraCliente(headClientes, nifClienteLogado);
                    int IdlocalTermino;
                    printf("Em que local Terminaste a viagem? ");
                    IdlocalTermino = VerificarInt();
                    Vertice *localTermino = ProcuraVertice(headGrafo, IdlocalTermino);

                    if (localTermino == NULL) {
                        printf("Local não encontrado.\n");
                    } else {
                        Caminho *caminho = Dijkstra(headGrafo, cliente->localCliente, IdlocalTermino);

                        if (!TerminarAluguer(headTransportes, headTransacoes, headClientes, nifClienteLogado, IdlocalTermino, caminho)) {
                            printf("Erro ao terminar aluguer.\n");
                        } else {
                            printf("Aluguer terminado com sucesso.\n");
                        }
                    }
                }
                break;

            // Caso 5: Visualizar histórico de alugueres
            case 5:
                if (cliente->historicoViagens == NULL) {
                    printf("O cliente %s (NIF: %d) não tem nenhuma viagem registrada.\n", cliente->nome, cliente->nif);
                    break;
                }
                MostrarHistoricoViagens(cliente);
                break;

            // Caso 6: Procurar transporte mais próximo
            case 6:
                NodeTransporte *transporteMaisProximo = ProcuraTransporteMaisProximo(headTransportes, headGrafo, cliente->localCliente);
                if (transporteMaisProximo) {
                    printf("O transporte mais próximo é:\n[%d] -  - Localizado em [%d] %s\n",
                        transporteMaisProximo->transporte.id,
                        transporteMaisProximo->transporte.localizacao, 
                        GetNomeLocal(headGrafo , transporteMaisProximo->transporte.localizacao));
                } else {
                    printf("Nenhum transporte disponível foi encontrado.\n");
                }
                break;

            // Caso 7: Realizar depósito
            case 7:
                float valorDeposito;
                printf("Insira o valor do depósito: ");
                valorDeposito = VerificarFloat();
                if (RealizarDeposito(cliente, valorDeposito)) {
                    printf("Depósito realizado com sucesso.\n");
                } else {
                    printf("Erro ao realizar depósito.\n");
                }
                break;

            // Caso 8: Alterar senha
            case 8:
                char novaSenha[MAX_LENGTH];
                LerTextoInput("Insere a nova senha: ", novaSenha, MAX_LENGTH);
                if (AlterarSenha(cliente, novaSenha)) {
                    printf("Senha alterada com sucesso.\n");
                } else {
                    printf("Erro ao alterar senha.\n");
                }
                break;

            case 9:
                char tipo[MAX_LENGTH];
                LerTextoInput("Tipo de transporte a procurar?\n",tipo, MAX_LENGTH);
                printf("Raio de busca: ");
                float raio = VerificarFloat();
                // tipo_de_transporte
              //  ListarTransportesPorTipoERaio(headTransportes, headGrafo, cliente->localCliente, tipo, raio);
                break;

            // Caso 9: Exportar todos os dados e sair do programa
            case 10:
                if (ExportarTodosDados(headClientes, headGestores, headTransportes, headTransacoes, headGrafo, headTipoTransporte)) {
                    printf("Todos os dados foram exportados com sucesso.\n");
                    exit(0);
                } else {    
                    printf("Erro ao exportar dados.\n");
                }
                break;

            default:
                printf("\nInsere uma das opções mostradas.\n");
                break;  
        }
    }
}
