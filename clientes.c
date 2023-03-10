#include "clientes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int limpaSTDIN(){
    int valor;
    while((valor = getchar()) != '\n' && valor != EOF);    
}

int VerificaNif(struct NodeClientes* head, int nif) {
    struct NodeClientes* current = head;
    while (current != NULL) {
        if (current->cliente.nif == nif) {
            printf("Já existe um cliente com o NIF: %d.\nInsere outro:\n", nif);
            return 1;
        }
        current = current->proximo;
    }
    return 0;
}

int VerificaUser(struct NodeClientes* head, char *login) {
    struct NodeClientes* current = head;
    while (current != NULL) {

        if (strcmp(current->cliente.login,login)==0) {
            printf("Já existe um cliente com esse nome de utilizador.\nInsere outro.\n");
            return 1;
        }
        current = current->proximo;
    }
    return 0;
}

int verificarInt(){
    int valor;
        while (scanf("%d",&valor)== 0) {
        printf("Insere um número válido.\n");
        limpaSTDIN();
    }   
    return valor;
}

int verificarFloat(float valor){
        while (scanf("%f",&valor)== 0) {
        printf("Insere um número válido.\n");
        limpaSTDIN();
    }   
    return valor;
}

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

            // Ask user for confirmation to edit the client
            limpaSTDIN();
            char resposta;
            printf("Editar este cliente? (S/N): ");
            scanf("%c", &resposta);
            if (resposta == 'S' || resposta == 's') {
                // Get new client information from user
                printf("\nInsira os dados do novo cliente:\n");
                printf("Nome: ");
                getchar();
                scanf("%[^\n]", clienteTemp.nome);
                printf("Morada: ");
                getchar();
                scanf("%[^\n]", clienteTemp.morada);
                printf("Login: ");
                getchar();
                scanf("%[^\n]", clienteTemp.login);
                printf("Password: ");
                getchar();
                scanf("%[^\n]", clienteTemp.password);    

                //Guarda o nif e saldo atual sem pedir atualizacao
                clienteTemp.nif = current->cliente.nif;
                clienteTemp.saldo = current->cliente.saldo; 

                // Update the client's information
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
    clienteTemp.nif = verificarInt();
    if(!VerificaNif(headRef,clienteTemp.nif)) {
        break;
    } 
}
    printf("Morada: ");
    getchar();
    scanf("%[^\n]", clienteTemp.morada);
    printf("Saldo: ");
    scanf("%f", &clienteTemp.saldo);

    printf("Nome de Utilizador: ");
    getchar();

    while(1){
        if(scanf("%[^\n]", clienteTemp.login)){
            limpaSTDIN();
            if(!VerificaUser(headRef,clienteTemp.login)) break;
        }
    }


    printf("Password: ");
    getchar();
    scanf("%[^\n]", clienteTemp.password);

    // Add the new client to the end of the list
    InserirCliente(&headRef, clienteTemp);
    printf("Cliente adicionado com sucesso!\n");
}