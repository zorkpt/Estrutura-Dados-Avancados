#include "clientes.h"
#include "../Controller/verificacoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




int InserirCliente(struct NodeClientes** headRef, struct Clientes cliente) {
     // Aloca memoria um novo NodeClientes e aloca os seus campos
    struct NodeClientes* newNode = (struct NodeClientes*) malloc(sizeof(struct NodeClientes));
    if (!newNode) {
        // verificação alocação de memória
        return 0;
    }
    newNode->cliente = cliente;
    newNode->proximo = NULL;

     // Se a Lista estiver vazia o novo node torna-se o head
    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        // Senão, itera pela lista até chegar ao fim
        struct NodeClientes* current = *headRef;
        while (current->proximo != NULL) {
            current = current->proximo;
        }
        // Define o próximo pointer do ultimo node para o novo node
        current->proximo = newNode;
    }
    // Cliente adicionado
    return 1;
}

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

int EditarCliente(struct Clientes *cliente) {
    // insere novos dados do cliente diretamente na lista
    printf("\nInsira os novos dados do cliente:\n");
    LerTextoInput("Nome: ", cliente->nome, 50);
    LerTextoInput("Morada: ", cliente->morada, 50);
    LerTextoInput("Nome de Utilizador: ", cliente->login, 50);
    LerTextoInput("Password: ", cliente->password, 50);
    return 1;
}
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

struct Clientes AdicionarCliente(struct NodeClientes* headRef) {
    struct Clientes clienteTemp;
    printf("Insira os dados do novo cliente:\n");
    LerTextoInput("Nome: ", clienteTemp.nome, 50);
    printf("NIF: ");
    while(1){
        clienteTemp.nif = VerificarInt();
        if(!VerificaNif(headRef,clienteTemp.nif)) {
            printf("Já existe um cliente com o NIF: %d.\nInsere outro:\n", clienteTemp.nif);
            break;
        } 
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