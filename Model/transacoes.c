/**
 * @file transacoes.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../Headers/transacoes.h"
#include "../Headers/transportes.h"
#include <stdlib.h>
#include <stdio.h>

/// @brief Insere uma nova struct de Transacoes na lista de NodeTransacoes
/// @param headRef Pointer para o head **pointer** da lista de NodeTransacoes
/// @param transacoes A struct de Transacoes a ser inserida
/// @return Retorna 1 se a inserção for bem sucedida, 0 caso contrário
int InserirTransacoes(struct NodeTransacoes** headRef, struct Transacoes transacoes) {
    struct NodeTransacoes* newNode = (struct NodeTransacoes*) malloc(sizeof(struct NodeTransacoes));
    newNode->transacoes = transacoes;
    newNode->proximo = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        struct NodeTransacoes* current = *headRef;
        while (current->proximo != NULL) {
            current = current->proximo;
        }
        current->proximo = newNode;
    }
    return 1;
}

/// @brief Mostra todos as Transações da lista de NodeTransacoes
/// @param head Pointer para o head da lista de NodeTransacoes
/// @return Retorna 1 se a lista não estiver vazia, 0 caso contrário
int MostrarTransacoes(struct NodeTransacoes* head) {
    if (head == NULL) {
        return 0;
    }
    printf("%-12s %-12s %-15s %s\n", "ID TRAN", "ID CLIENTE", "ID TRANSPORTE", "Tempo Decorrido");
    struct NodeTransacoes* current = head;
    while (current != NULL) {
        printf("%-12d %-12d %-15d %d\n",
               current->transacoes.idTransacao,
               current->transacoes.idClienteAAlugar,
               current->transacoes.idTransporte,
               current->transacoes.tempoAlugado);
        current = current->proximo;
    }
    return 1;
}

/// @brief Mostra as transações de um cliente específico
/// @param head Pointer para o head da lista de NodeTransacoes
/// @param idCliente ID do cliente a procurar
/// @return retorna o número de transações encontradas
int MostrarTransacoesCliente(struct NodeTransacoes* head, int idCliente) {
    int count = 0;
    if (head == NULL) {
        return 0;
    }
    struct NodeTransacoes* current = head;
    printf("ID CLIENTE\tID TRANSPORTE\tTempo Decorrido:\n");
    
    while (current != NULL) {
        if (current->transacoes.idClienteAAlugar == idCliente) {
            printf("%d\t\t%d\t\t%d\n",
                            current->transacoes.idClienteAAlugar,
                            current->transacoes.idTransporte,
                            current->transacoes.tempoAlugado);
            count++;
        }
        current = current->proximo;
    }
    return count;
}

/// @brief Procura por uma Transação na lista usando o seu ID
/// @param headRef Pointer para o head da lista de NodeTransacoes
/// @param idTransacao ID da transação a procurar
/// @return Retorna o endereço da transação encontrada, NULL caso contrário
struct Transacoes* ProcurarTransacao(struct NodeTransacoes* head, int idTransacao) {
    if (head == NULL) {
        return NULL;
    }
    struct NodeTransacoes* current = head;
    while (current != NULL) {
        if (current->transacoes.idTransacao == idTransacao) {
            return &current->transacoes;
        }
        current = current->proximo;
    }
    return NULL;
}

/// @brief Remove uma Transação da lista de NodeTransacoes
/// @param head Pointer para o head **pointer** da lista de NodeTransacoes
/// @param idTransacao ID da transação a remover
/// @return Retorna 1 se a remoção for bem sucedida, 0 caso contrário
int RemoverTransacao(struct NodeTransacoes **head, int idTransacao) {
    struct NodeTransacoes *current = *head;
    struct NodeTransacoes *previous = NULL;

    // Percorre a lista até dar match do ID
    while (current != NULL && current->transacoes.idTransacao != idTransacao) {
        previous = current;
        current = current->proximo;
    }
    // Se for encontrado, removemos da lista
    if (current != NULL) {
        // Se o node for o head da lista, damos update ao pointer do head
        if (previous == NULL) {
            *head = current->proximo;
        } else {
            previous->proximo = current->proximo;
        }
        free(current);
        return 1;
    }
    return 0;
}


/// @brief Editar os dados de uma transação
/// @param cliente A struct de Transacoes a ser editada
/// @return Retorna 1 se a edição for bem sucedida
int EditarTransacao(struct Transacoes * transacao, int tempoAlugado, int idClienteAAlugar, int idTransporte) {
    transacao->tempoAlugado = tempoAlugado;
    transacao->idClienteAAlugar = idClienteAAlugar;
    transacao->idTransporte = idTransporte;
    return 1;
}


/// @brief Determina o proximo ID a ser usado na lista de transacoes
/// @param headTransacoes Pointer para o head da lista de NodeTransacoes
/// @return Retorna o proximo ID a ser usado
int ProximoIDTransacao(struct NodeTransacoes* headTransacoes) {
    int maiorID = 0;
    struct NodeTransacoes* current = headTransacoes;

    while (current != NULL) {
        if (current->transacoes.idTransacao > maiorID) {
            maiorID = current->transacoes.idTransacao;
        }
        current = current->proximo;
    }

    return maiorID + 1;
}

/// @brief Mostra o histórico de alugueres de um cliente
/// @param headTransacoes Pointer para o head da lista de NodeTransacoes
/// @param nif NIF do cliente a procurar
/// @return Retorna o número de alugueres encontrados
int MostrarHistoricoAlugueres(struct NodeTransacoes* headTransacoes, int nif){
    struct NodeTransacoes* current = headTransacoes;
    if (current == NULL) {
        return 0;
    }
    int count = 0;
    // Cabeçalho da tabela
    printf("ID Aluguer\tID Cliente\tID Transporte\tTempo Decorrido\n");
    while (current != NULL) {
        if (current->transacoes.idClienteAAlugar == nif) {
            printf("%d\t%d\t%d\t%d\n",  current->transacoes.idTransacao, 
                                        current->transacoes.idClienteAAlugar, 
                                        current->transacoes.idTransporte, 
                                        current->transacoes.tempoAlugado);
            count++;
        }
        current = current->proximo;
    }
    return count;
}


/// @brief Verifica se um cliente está num transporte
/// @param headTransacoes Pointer para o head da lista de NodeTransacoes
/// @param nif NIF do cliente a procurar
/// @return Retorna 1 se o cliente estiver num transporte, 0 caso contrário
int ClienteEmTransporte(struct NodeTransacoes* headTransacoes, int nif) {
    struct NodeTransacoes* current = headTransacoes;
    while (current != NULL) {
        if (current->transacoes.idClienteAAlugar == nif && current->transacoes.ativo == 1) {
            return 1; 
        }
        current = current->proximo;
    }
    return 0; 
}

/// @brief Termina o aluguer de um transporte a um cliente
/// @param headTransportes Pointer para o head da lista de NodeTransporte
/// @param headTransacoes Pointer para o head da lista de NodeTransacoes
/// @param nifClienteLogado NIF do cliente a terminar o aluguer
/// @return Retorna 1 se o aluguer for terminado com sucesso, 0 caso contrário
int TerminarAluguer(struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes, int nifClienteLogado) { 
    struct NodeTransacoes* currentTransacao = headTransacoes;
    struct NodeTransporte* currentTransporte = headTransportes;
    while (currentTransacao != NULL) {
        if (currentTransacao->transacoes.idClienteAAlugar == nifClienteLogado && currentTransacao->transacoes.ativo == 1) {
            currentTransacao->transacoes.ativo = 0;
            while (currentTransporte != NULL) {
                if (currentTransporte->transporte.id == currentTransacao->transacoes.idTransporte) {
                    currentTransporte->transporte.estado = 0;
                    return 1;
                }
                currentTransporte = currentTransporte->proximo;
            }
        }
        currentTransacao = currentTransacao->proximo;
    }
    return 0;
}

/// @brief Atualiza o estado de um transporte
/// @param cliente struct de Clientes, passada para atualizar o saldo
/// @param headTransportes Pointer para o head da lista de NodeTransporte, passada para atualizar o estado do transporte
/// @param headTransacoes Pointer para o head da lista das transacoes, passada para para atualizar o estado da transacao
/// @param idTransporte ID do transporte a ser atualizado
/// @param tempoAluguer Tempo de aluguer do transporte
/// @param custoTotal Custo total do aluguer
/// @param novoIdTransacao ID para usar na criação da nova transacao
/// @return  Retorna 1 se o transporte for atualizado com sucesso, 0 caso contrário
int AtualizarEstadoTransporte(struct Clientes* cliente, struct NodeTransporte* headTransportes, 
                            struct NodeTransacoes* headTransacoes, int idTransporte, 
                            int tempoAluguer, float custoTotal, int novoIdTransacao) {
    if(!EditarTransporteID(headTransportes,idTransporte)) {
        return 0;
    }
    // Criada nova transacção
    struct Transacoes novaTransacao;
    novaTransacao.idClienteAAlugar = cliente->nif;
    novaTransacao.idTransporte = idTransporte;
    novaTransacao.tempoAlugado = tempoAluguer;
    novaTransacao.idTransacao = novoIdTransacao;
    novaTransacao.ativo = 1;
    // adicionar a nova transação á lista
    if(!InserirTransacoes(&headTransacoes, novaTransacao)){
        return 0;
    }else {
        cliente->saldo -= custoTotal;
        return 1;
    }
}