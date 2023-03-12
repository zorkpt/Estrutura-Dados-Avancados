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

void MostrarClientes(struct NodeClientes* head) {
if (head == NULL) {
        printf("A Lista está vazia.\n");
        
    }
     struct NodeClientes* current = head;
    while (current != NULL) {
        printf("%d\t%s\t%s\t%.2f€\t%s\t%s\n",
               current->cliente.nif,
               current->cliente.nome,
               current->cliente.morada,
               current->cliente.saldo,
               current->cliente.login,
               current->cliente.password);
        current = current->proximo;
    }
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

int EditarCliente(struct NodeClientes *head, int nif) {
    struct NodeClientes *current = head;
    struct Clientes clienteTemp;

    // Procura Cliente Pelo NIF
    while (current != NULL) {
        if (current->cliente.nif == nif) {
            printf("\n\nCliente encontrado:\n");
            printf("Nome: %s\n", current->cliente.nome);
            printf("NIF: %d\n", current->cliente.nif);
            printf("Morada: %s\n", current->cliente.morada);
            printf("Saldo: %f\n", current->cliente.saldo);
            printf("Login: %s\n", current->cliente.login);
            printf("\n");

            // Pergunta por confirmação para editar o cliente
            limpaSTDIN();
            char resposta;
            printf("Editar este cliente? (S/N): ");
            scanf("%c", &resposta);
            if (resposta == 'S' || resposta == 's') {
                // Inserir novos dados:
                printf("\nInsira os dados do novo cliente:\n");
                printf("Nome: ");
                limpaSTDIN();
                scanf("%[^\n]", clienteTemp.nome);
                printf("Morada: ");
                limpaSTDIN();
                scanf("%[^\n]", clienteTemp.morada);
                printf("Login: ");
                limpaSTDIN();
                scanf("%[^\n]", clienteTemp.login);
                printf("Password: ");
                limpaSTDIN();
                scanf("%[^\n]", clienteTemp.password);    

                //Guarda o nif e saldo atual sem pedir atualizacao
                clienteTemp.nif = current->cliente.nif;
                clienteTemp.saldo = current->cliente.saldo; 

                // Atuliza a informação do cliente
                current->cliente = clienteTemp;
                return 1;
            } else {
                return 0;
            }
        }
        current = current->proximo;
    }

    printf("Cliente com NIF %d não encontrado.\n", nif);
    return 0;
}

int ProcuraCliente(struct NodeClientes* headRef, int nif){
    struct NodeClientes *current = headRef;
    
    // Search for the client with the given NIF
    while (current != NULL) {
        if (current->cliente.nif == nif) {
            printf("\n\nCliente encontrado:\n");
            printf("Nome: %s\n", current->cliente.nome);
            printf("NIF: %d\n", current->cliente.nif);
            printf("Morada: %s\n", current->cliente.morada);
            printf("Saldo: %f\n", current->cliente.saldo);
            printf("Login: %s\n", current->cliente.login);
            printf("\n");
            return 1;
        }else return 0;
    }
}

int AdicionarCliente(struct NodeClientes* headRef) {
    struct Clientes clienteTemp;

    printf("Insira os dados do novo cliente:\n");
    printf("Nome: ");
    limpaSTDIN();
    scanf("%[^\n]", clienteTemp.nome);

    printf("NIF: ");
while(1){
    clienteTemp.nif = VerificarInt();
    if(!VerificaNif(headRef,clienteTemp.nif)) {
        break;
    } 
}
    printf("Morada: ");
    limpaSTDIN();
    scanf("%[^\n]", clienteTemp.morada);
    printf("Saldo: ");
    clienteTemp.saldo = VerificarFloat();
    printf("Nome de Utilizador: ");
    limpaSTDIN();
    while(1){
        if(scanf("%[^\n]", clienteTemp.login)){
            limpaSTDIN();
            if(!VerificaUser(headRef,clienteTemp.login)) break;
        }
    }


    printf("Password: ");
    scanf("%[^\n]", clienteTemp.password);

    // Add the new client to the end of the list
    InserirCliente(&headRef, clienteTemp);
    printf("Cliente adicionado com sucesso!\n");
}