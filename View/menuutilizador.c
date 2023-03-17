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
#include "../Headers/verificacoes.h"
#define MAX_LENGTH 100



/// @brief Vista e opções destinadas ao utilizador/cliente
/// @param headClientes Pointer para o header da lista de clientes
/// @param headGestores Pointer para o header da lista de gestores
/// @param headTransportes Pointer para o header da lista de transportes
/// @param headTransacoes Pointer para o header da lista de transacoes
/// @param nifClienteLogado NIF do cliente que está logado
/// @return 
int MenuUtilizador(struct NodeClientes* headClientes, struct NodeGestores* headGestores, 
                struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes, 
                int nifClienteLogado ){

    while(1)
    {   
        struct Clientes* cliente = ProcuraCliente(headClientes, nifClienteLogado);
        struct Transporte* transporteAlugar;
        int escolha = ListaMenuCliente();
        switch (escolha)
        {
            case 1:
                MostrarTransportesOrdenados(headTransportes);
                break;
            case 2:
                char localEscolhido[MAX_LENGTH];
                LerTextoInput("Insere o local onde queres procurar os transportes: ", localEscolhido, MAX_LENGTH);
                struct NodeTransporte* transportesNoLocal = ProcurarTransportesPorLocal(headTransportes, localEscolhido);
                if (transportesNoLocal == NULL) {
                    printf("Não foram encontrados transportes no local %s.\n", localEscolhido);
                } else {
                    MostrarTransportes(transportesNoLocal);
                }

                break;
            case 3:
                int idTransporte, tempoAluguer;
                if (ClienteEmTransporte(headTransacoes, nifClienteLogado)) {
                    printf("Já estás a utilizar um transporte. Termina a viagem atual antes de alugar outro.\n");
                    break;
                }

                VerTransportesDisponiveis(headTransportes);
                printf("\nSaldo Atual: %.2f€",cliente->saldo);
                printf("\nEscolher um dos transportes disponiveis de momento: (ID) ");
                idTransporte = VerificarInt();
                transporteAlugar = ProcurarTransporte(headTransportes, idTransporte);
                
                if (transporteAlugar != NULL && AlugarTransporteDisponivel(transporteAlugar)) {
                    printf("\nPor quanto tempo queres alugar? ");
                    tempoAluguer = VerificarInt();
                    float custoTotal = CustoTotalAluguer(transporteAlugar, tempoAluguer);

                    if (TemSaldoSuficiente(cliente, custoTotal)) {
                        int novoIdTransaccao = ProximoIDTransacao(headTransacoes);
                        if(!AtualizarEstadoTransporte(cliente, headTransportes, headTransacoes, idTransporte, tempoAluguer, custoTotal, novoIdTransaccao)){
                            printf("Erro ao processar aluguer.");
                        }else printf("Transporte alugado com sucesso.");
                    } else {
                        printf("Saldo insuficiente para realizar o aluguer.\n");
                    }
                } else {
                    printf("Não foi encontrado Meio de Transporte para esse ID.\n");
                }
                break;
            case 4:
                if (!ClienteEmTransporte(headTransacoes, nifClienteLogado)) {
                    printf("Não estás a utilizar um transporte no momento.\n");
                    break;
                } else {
                    if (!TerminarAluguer(headTransportes, headTransacoes, nifClienteLogado)) {
                        printf("Erro ao terminar aluguer.\n");
                    } else {
                        printf("Aluguer terminado com sucesso.\n");
                    }
                }
                break;
            case 5:
                int totalTransacoes = MostrarHistoricoAlugueres(headTransacoes,nifClienteLogado);
                if(totalTransacoes==0) {
                    printf("Sem dados para mostrar.\n");
                } else {
                    printf("\nA mostrar %d registos.",totalTransacoes);
                }
                break;
            case 6:
                printf("\nSaldo Atual: %.2f€",cliente->saldo);
                break;
            case 7:
                float valorDeposito;
                valorDeposito = VerificarFloat();
                if(RealizarDeposito(cliente, valorDeposito)){
                    printf("Deposito realizado com sucesso.\n");
                }else printf("Erro ao realizar deposito.\n");
                break;
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
