/**
 * @file transacoes.c
 * @author Hugo Poças
 * @brief Este ficheiro contém as funções de transações.
 * @version 0.2
 * @date 27-05-2023
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
#define ERR_CLIENTE_EM_TRANSPORTE -1
#define ERR_SALDO_INSUFICIENTE 0
#define CLIENTE_PODE_ALUGAR 1
const float FACTOR_METRO_PARA_KM = 0.001f;

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
int MostrarTransacoes(Vertice* grafo, Viagem* headViagens) {
    if (grafo == NULL) {
        return 0;
    }
    printf("%-13s %-54s %-54s %-9s %-10s %-12s %s \n",
            "ID TRANS", "ORIGEM", "DESTINO", "DISTANCIA", 
            "VALOR PAGO", "CUSTO POR KM", "TIPO TRANSPORTE");
    while (headViagens != NULL) {
        printf("| %5d | [%d] %-50s | [%d] %-50s | %9.2f | %10.2f | %12.2f | %s \n",
            headViagens->idTransporte,
            headViagens->origem,
            GetNomeLocal(grafo,headViagens->origem),
            headViagens->destino,
            GetNomeLocal(grafo,headViagens->destino),
            headViagens->distancia,
            headViagens->valorPago,
            headViagens->custoPorKm,
            headViagens->tipoTransporte);
        headViagens = headViagens->proxima;
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
/// @param cliente struct de Clientes
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
    if(!EdtarEstadoTransporte(headTransportes,idTransporte)) {
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
    return (distancia * preco) * FACTOR_METRO_PARA_KM;
}

/// @brief Calcula a bateria perdida com base na distância total
/// @param distancia 
/// @return Bateria perdida
int CalculaBateriaPerdida(float distancia) {
    // Implementação da lógica de cálculo da bateria perdida com base na distância total
    int bateriaPerdida = 0;

    bateriaPerdida = (int)(distancia * FACTOR_METRO_PARA_KM);

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
                    Viagem* novaViagem = CriarNovaViagem(currentTransporte->transporte.id, localInicial, idLocalTermino, valorTotal, currentTransporte->transporte.tipo->precoPorKm, distancia, currentTransporte->transporte.tipo->nome);
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



/// @brief Cria uma nova Viagem
/// @param idTransporte ID do transporte usado na viagem
/// @param origem Local de origem da viagem
/// @param destino Local de destino da viagem
/// @param valorPago Valor pago pela viagem
/// @param custoPorKm Custo por quilometro do transporte
/// @param distancia Distancia da viagem
/// @param tipoTransporte Tipo de transporte usado na viagem
/// @return Retorna um ponteiro para a nova Viagem ou NULL se a alocação de memória falhar
Viagem* CriarNovaViagem(int idTransporte, int origem, int destino, float valorPago, float custoPorKm, float distancia, char tipoTransporte[]) {
    // Aloca memória para a nova viagem
    Viagem* novaViagem = (Viagem*)malloc(sizeof(Viagem));
    if (novaViagem == NULL) {
        return NULL;
    }
    
    // Inicializa os valores da nova viagem
    novaViagem->idTransporte = idTransporte;
    novaViagem->origem = origem;
    novaViagem->destino = destino;
    novaViagem->valorPago = valorPago;
    novaViagem->custoPorKm = custoPorKm;
    novaViagem->distancia = distancia;
    
    // Copia o tipo de transporte para a nova viagem
    strcpy(novaViagem->tipoTransporte, tipoTransporte);

    novaViagem->proxima = NULL;

    return novaViagem;
}


/// @brief Verifica se um cliente está apto a alugar um transporte.
/// @param headTransacoes Ponteiro para o início da lista de transações.
/// @param cliente Ponteiro para o cliente que se deseja verificar.
/// @param nifClienteLogado NIF do cliente que está logado no sistema.
/// @return Retorna um código de erro:
///         - 1: Se o cliente está apto a alugar um transporte.
///          - ERR_CLIENTE_EM_TRANSPORTE: Se o cliente já está num transporte.
///          - ERR_SALDO_INSUFICIENTE: Se o cliente não tem saldo suficiente.
int VerificaSePodeAlugar(NodeTransacoes *headTransacoes, struct Clientes *cliente, int nifClienteLogado ) {
    // Verifica se o cliente já está num transporte
    if (ClienteEmTransporte(headTransacoes, nifClienteLogado)) {
        return ERR_CLIENTE_EM_TRANSPORTE;
    }
    // Verifica se o cliente tem saldo suficiente
    if (cliente->saldo <= 0) {
        return ERR_SALDO_INSUFICIENTE;
    }
    // Se não houver nenhum erro, retorna 1
    return CLIENTE_PODE_ALUGAR;
}