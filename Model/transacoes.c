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
#include "../Headers/clientes.h"
#include "../Headers/viagem.h"
#include "../Headers/transacoes.h"
#include "../Headers/caminho.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
void MostrarHistoricoViagens(Clientes* cliente) {
    Viagem* viagemAtual = cliente->historicoViagens;
    
    printf("\nHistórico de viagens para o cliente %s (NIF: %d):\n", cliente->nome, cliente->nif);
    printf("-------------------------------------------------------------------\n");
    printf("| ID Transporte | Origem | Destino | Distância | Valor Pago | Custo Por Km | Transporte Utilizado\n");
    while (viagemAtual != NULL) {
        printf("| %13d | %6d | %7d | %9.2f | %10.2f | %12.2f | %s \n",
            viagemAtual->idTransporte,
            viagemAtual->origem,
            viagemAtual->destino,
            viagemAtual->distancia,
            viagemAtual->valorPago,
            viagemAtual->custoPorKm,
            viagemAtual->tipoTransporte);
        viagemAtual = viagemAtual->proxima;
    }
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
                            int novoIdTransacao) {
    if(!EditarTransporteID(headTransportes,idTransporte)) {
        return 0;
    }
    // Criada nova transacção
    struct Transacoes novaTransacao;
    novaTransacao.idClienteAAlugar = cliente->nif;
    novaTransacao.idTransporte = idTransporte;
    novaTransacao.idTransacao = novoIdTransacao;
    novaTransacao.ativo = 1;
    // adicionar a nova transação á lista
    if(!InserirTransacoes(&headTransacoes, novaTransacao)){
        return 0;
    }else {
        return 1;
    }
}

/// @brief Atualiza o local de um cliente
/// @param cliente 
/// @param novoLocal 
void AtualizaLocalCliente(struct Clientes* cliente, int novoLocal) {
    cliente->localCliente = novoLocal;
}

/// @brief Atualiza o local de um transporte
/// @param transporte 
/// @param novoLocal 
void AtualizaLocalTransporte(struct Transporte* transporte, int novoLocal) {
    transporte->localizacao = novoLocal;
}

/// @brief Atualiza o nivel de bateria de um transporte
/// @param transporte 
/// @param bateriaPerdida 
void AtualizaNivelBateria(Transporte *transporte, int bateriaPerdida) {
    transporte->nivelBateria -= bateriaPerdida;
    if (transporte->nivelBateria < 0) {
        transporte->nivelBateria = 0;
    }
}

/// @brief Muda o estado de um transporte para disponível
/// @param transporte 
void MudaEstadoTransporte(struct Transporte* transporte) {
    transporte->estado = 0; 
}

/// @brief Atualiza o saldo de um cliente
/// @param cliente 
/// @param valor 
void AtualizaSaldoCliente(struct Clientes* cliente, float valor) {
    cliente->saldo -= valor;
}

/// @brief Calcula o valor total de um aluguer
/// @param distancia 
/// @param preco 
/// @return Valor total do aluguer
float CalculaValorTotal(float distancia, float preco) {
    return (distancia * preco)*0.01;
}

/// @brief Calcula a bateria perdida com base na distância total
/// @param distancia 
/// @return Bateria perdida
int CalculaBateriaPerdida(float distancia) {
    // Implementação da lógica de cálculo da bateria perdida com base na distância total
    int bateriaPerdida = 0;

    // Fator de conversão para bateria perdida por unidade de distância
    float fatorConversao = 0.001; 

    bateriaPerdida = (int)(distancia * fatorConversao);

    return bateriaPerdida;
}

/// @brief Termina um aluguer
/// @param headTransportes 
/// @param headTransacoes 
/// @param headClientes 
/// @param nifClienteLogado 
/// @param idLocalTermino 
/// @param caminho 
/// @return 1 se o aluguer for terminado com sucesso, 0 caso contrário
int TerminarAluguer(struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes, struct NodeClientes* headClientes, int nifClienteLogado, int idLocalTermino, Caminho* caminho) { 
    struct NodeTransacoes* currentTransacao = headTransacoes;
    struct NodeTransporte* currentTransporte = headTransportes;
    
    while (currentTransacao != NULL) {
        if (currentTransacao->transacoes.idClienteAAlugar == nifClienteLogado && currentTransacao->transacoes.ativo == 1) {
            currentTransacao->transacoes.ativo = 0;
            while (currentTransporte != NULL) {
                if (currentTransporte->transporte.id == currentTransacao->transacoes.idTransporte) {
                    int localInicial = currentTransporte->transporte.localizacao;
                    Clientes* clienteAtual = ProcuraCliente(headClientes, nifClienteLogado);
                    AtualizaLocalCliente(clienteAtual, idLocalTermino);
                    AtualizaLocalTransporte(&currentTransporte->transporte, idLocalTermino);
                    float distancia = DistanciaCaminho(caminho);
                    float valorTotal = CalculaValorTotal(distancia, currentTransporte->transporte.tipo->precoPorKm);
                    int bateriaPerdida = CalculaBateriaPerdida(distancia);
                    AtualizaNivelBateria(&currentTransporte->transporte, bateriaPerdida);
                    MudaEstadoTransporte(&currentTransporte->transporte);

                    AtualizaSaldoCliente(clienteAtual, valorTotal);

                    // Cria uma nova viagem e adiciona-a ao histórico do cliente
                    Viagem* novaViagem = (Viagem*)malloc(sizeof(Viagem));
                    novaViagem->idTransporte = currentTransporte->transporte.id;
                    novaViagem->origem = localInicial;
                    strcpy(novaViagem->tipoTransporte, currentTransporte->transporte.tipo->nome);
                    novaViagem->destino = idLocalTermino;
                    novaViagem->valorPago = valorTotal;
                    novaViagem->custoPorKm = currentTransporte->transporte.tipo->precoPorKm;
                    novaViagem->distancia = distancia;
                    novaViagem->proxima = clienteAtual->historicoViagens;
                    clienteAtual->historicoViagens = novaViagem;

                    return 1;
                }
                currentTransporte = currentTransporte->proximo;
            }
        }
        currentTransacao = currentTransacao->proximo;
    }
    return 0;
}

int VerificaSePodeAlugar(NodeTransacoes *headTransacoes, struct Clientes *cliente, int nifClienteLogado ){
    // Verifica se o cliente está num transporte
    if (ClienteEmTransporte(headTransacoes, nifClienteLogado)) {
        return -1;
    }
    // Verifica se o cliente tem saldo suficiente
    if (cliente->saldo <= 0) {
        return 0;
    }
    return 1;
}