/**
 * @file clientes.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../Headers/verificacoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRING 100

/// @brief Insere uma nova struct de Clientes na lista de NodeClientes
/// @param headRef Pointer para o head **pointer** da lista de NodeClientes
/// @param cliente A struct de Clientes a ser inserida
/// @return Retorna 1 se a inserção for bem sucedida, 0 caso contrário
int InserirCliente(struct NodeClientes** headRef, struct Clientes cliente) {
     // Aloca memoria um novo NodeClientes e aloca os seus campos
    struct NodeClientes* novoNode = (struct NodeClientes*) malloc(sizeof(struct NodeClientes));
    if (!novoNode) {
        // verificação alocação de memória
        return 0;
    }
    // inicializa o novo node com os dados do cliente e proximo pointer a NULL porque vai ser inserido no fim da lista
    novoNode->cliente = cliente;
    novoNode->proximo = NULL;

     // Se a Lista estiver vazia o novo node torna-se o head
    if (*headRef == NULL) {
        *headRef = novoNode;
    } else {
        // Senão, itera pela lista até chegar ao fim 
        struct NodeClientes* current = *headRef;
        while (current->proximo != NULL) {
            current = current->proximo;
        }
        // Define o próximo pointer do ultimo node para o novo node
        current->proximo = novoNode;
    }
    // Cliente adicionado
    return 1;
}


/// @brief Mostra todos os clientes da lista de NodeClientes
/// @param head Pointer para o head da lista de NodeClientes
/// @return Retorna 1 se a lista não estiver vazia, 0 caso contrário
int MostrarClientes(struct NodeClientes* head) {
    if (head == NULL) {
        return 0;
    }
    printf("%-12s %-20s %-30s %-10s %-15s %-15s\n", "NIF", "NOME", "MORADA", "SALDO", "LOGIN", "PASSWORD");
    struct NodeClientes* current = head;
    while (current != NULL) {
        printf("%-12d %-20s %-30s %-10.2f %-15s %-15s\n",
               current->cliente.nif,
               current->cliente.nome,
               current->cliente.morada,
               current->cliente.saldo,
               current->cliente.login,
               current->cliente.password);
        current = current->proximo;
    }
    return 1;
}

/// @brief Remove um cliente com um NIF especifico da lista de Clientes
/// @param head Pointer para o head **pointer** da lista de NodeClientes
/// @param nif NIF do cliente a ser removido
/// @return Retorna 1 se o cliente for removido, 0 caso contrário
int RemoverCliente(struct NodeClientes **head, int nif) {
    struct NodeClientes *current = *head;
    struct NodeClientes *previous = NULL;

    // Percorre a lista até dar match do NIF
    while (current != NULL && current->cliente.nif != nif) {
        previous = current;
        current = current->proximo;
    }
    // Se for encontrado, removemos da lista
    if (current != NULL) {
        // Se o node for o head da lista, damos update ao pointer do head
        if (previous == NULL) {
            *head = current->proximo;
        }
        // Senão, o node anterior passa apontar para o proximo, dando skip ao atual
        else {
            previous->proximo = current->proximo;
        }
        free(current);
        return 1;
    } else {
        return 0;
    }
}

/// @brief Editar os dados de um cliente
/// @param cliente A struct de Clientes a ser editada
/// @return Retorna 1 se a edição for bem sucedida
int EditarCliente(struct Clientes *cliente) {
    // insere novos dados do cliente diretamente na lista
    printf("\nInsira os novos dados do cliente:\n");
    LerTextoInput("Nome: ", cliente->nome, 50);
    LerTextoInput("Morada: ", cliente->morada, 50);
    LerTextoInput("Nome de Utilizador: ", cliente->login, 50);
    LerTextoInput("Password: ", cliente->password, 50);
    return 1;
}

/// @brief Procura por um Cliente na lista usando o seu NIF
/// @param headRef Pointer para o head da lista de NodeClientes
/// @param nif NIF do cliente a ser procurado
/// @return Retorna o endereço do cliente encontrado, NULL caso contrário
struct Clientes* ProcuraCliente(struct NodeClientes* headRef, int nif) {
    struct NodeClientes* current = headRef;

    while (current != NULL) {
        if (current->cliente.nif == nif) {
            // Retorna o endereço do cliente encontrado
            return &current->cliente; 
        }
        current = current->proximo;
    }
    return NULL; 
}

/// @brief Cria uma nova struct de Clientes com os dados inseridos pelo utilizador e depois validados
/// @param headRef Ponteiro para a head da lista de clientes, usado para as verificações de NIF e Username
/// @return Retorna uma struct Clientes com os dados do novo cliente (não adiciona á lista)
struct Clientes AdicionarCliente(struct NodeClientes* headRef) {
    struct Clientes clienteTemp;
    printf("Insira os dados do novo cliente:\n");
    LerTextoInput("Nome: ", clienteTemp.nome, 50);
    printf("NIF: ");
    while(1){
        clienteTemp.nif = VerificarInt();
        if(!VerificaNif(headRef,clienteTemp.nif)) {
            break;
        }else printf("Já existe um cliente com o NIF: %d.\nInsere outro:\n", clienteTemp.nif);

    }
    LerTextoInput("Morada: ", clienteTemp.morada, 50);
    printf("Saldo: ");
    clienteTemp.saldo = VerificarFloat();
    while(1){
        LerTextoInput("Nome de Utilizador?", clienteTemp.login, 50);
        if(!VerificaUser(headRef,clienteTemp.login)) break;
    }
    LerTextoInput("Password: ", clienteTemp.password, 50);   
    return(clienteTemp);
}


/// @brief Verifica se um Cliente tem saldo suficiente para realizar uma compra
/// @param cliente Pointer para a struct de Clientes a ser verificada
/// @param custoTotal Valor em float do custo total a ser verificado.
/// @return Retorna 1 se o cliente tiver saldo suficiente, 0 caso contrário
int TemSaldoSuficiente(struct Clientes* cliente, float custoTotal) {
    if (cliente->saldo >= custoTotal) {
        return 1;
    } else {
        return 0;
    }
}

/// @brief Altera a password de um cliente
/// @param cliente Pointer para a struct de Clientes a ser alterada
/// @param novaSenha Char array com a nova password
/// @return Retorna 1 se a password for alterada, 0 caso contrário
int AlterarSenha(struct Clientes* cliente, char novaSenha[]) {
    if (cliente == NULL) {
        return 0;
    }
    // Copia nova senha para a struct de cliente
    if(strcpy(cliente->password, novaSenha)) {
        return 1;
    } else {
        return 0;
    }
}

/// @brief Efetuar um deposito na conta de um cliente
/// @param cliente Pointer para a struct de Clientes a ser alterada
/// @param valor Valor em float a ser depositado
/// @return Retorna 1 se o deposito for efetuado, 0 caso contrário
int RealizarDeposito(struct Clientes* cliente, float valor) {
    if (cliente == NULL) {
        return 0;
    }
    cliente->saldo += valor;
    return 1;
}