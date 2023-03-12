#include <stdio.h>
#include "../Controller/verificacoes.h"
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

// int VerificarInt(){
//     int valor;
//         while (scanf("%d",&valor)== 0) {
//         printf("Insere um número válido.\n");
//         limpaSTDIN();
//     }   
//     return valor;
// }

float VerificarFloat(){
    float valor;
        while (scanf("%f",&valor)== 0) {
        printf("Insere um número válido.\n");
        limpaSTDIN();
    }   
    return valor;
}


int VerificarInt() {
  int resultado = 0;
  char buffer[1024] = {0};

  while (1) {
    fgets(buffer, 1024, stdin);
    if (sscanf(buffer, "%d", &resultado) == 1) {
      return resultado;
    }   
    printf("Insere um numero inteiro: ");
  }
}


int VerificaIdTransportes(struct NodeTransporte* head, int id) {
    struct NodeTransporte* current = head;
    while (current != NULL) {
        if (current->transporte.id == id) {
            printf("Já existe um Transporte com esse ID: %d.\nInsere outro:\n", id);
            return 0;
        }
        current = current->proximo;
    }
    return 1;
}