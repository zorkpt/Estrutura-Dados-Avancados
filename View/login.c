#include "../Controller/funcoes.h"
#include "../Controller/verificacoes.h"
#include <string.h>

int IniciarLogin(struct NodeClientes** clientesHead, struct NodeGestores** gestoresHead) {
    char utilizador[50];
    char password[50];
    while (1) {
        printf("Nome de Utilizador?\n");
        scanf("%s", utilizador);
        printf("Palavra-Passe?\n");
        scanf("%s", password);

        struct NodeClientes* currentCliente = *clientesHead;
        while (currentCliente != NULL) {
            if (strcmp(utilizador, currentCliente->cliente.login) == 0 && strcmp(password, currentCliente->cliente.password) == 0) {
                printf("Login efetuado com sucesso. Bem-vindo %s\n", currentCliente->cliente.nome);
                // Call client menu function
                return 1;
            }
            currentCliente = currentCliente->proximo;
        }

        struct NodeGestores* currentGestor = *gestoresHead;
        while (currentGestor != NULL) {
            if (strcmp(utilizador, currentGestor->gestor.nome) == 0 && strcmp(password, currentGestor->gestor.password) == 0) {
                printf("Login efetuado como Gestor, %s\n", currentGestor->gestor.nome);
                // Call manager menu function
                return 2;
            }
            currentGestor = currentGestor->proximo;
        }

        printf("Utilizador ou senha errado.\n");
        limpaSTDIN();
    }
    return 0;
}



// int IniciarLogin(Clientes *clientes, int totalClientes, Gestores *gestores, int totalGestores) {
//     char utilizador[50];
//     char password[50];
//     while(1){
//         printf("Nome de Utilizador?\n");
//         scanf("%s",utilizador);
//         printf("Palavra-Passe?\n");
//         scanf("%s",password);

//         for (int i = 0; i < totalClientes; i++) {
//             if (strcmp(utilizador, clientes[i].login) == 0 && strcmp(password, clientes[i].password) == 0) {
//                 printf("Login efetuado com sucesso. Bem-vindo %s\n", clientes[i].nome);
//                 // Call client menu functionls
//                 return 1;
//             }
//         }

//         for (int i = 0; i < totalGestores; i++) {
//             if (strcmp(utilizador, gestores[i].nome) == 0 && strcmp(password, gestores[i].password) == 0) {
//                 printf("Login efetuado como Gestor, %s\n", gestores[i].nome);
//                 // Call manager menu function
//                 return 2;
//             }
//         }
        
//         printf("Utilizador ou senha errado.\n");
//         limpaSTDIN();
//         }
//     return 0;
// }