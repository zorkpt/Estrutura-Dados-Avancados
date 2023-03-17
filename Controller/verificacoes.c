#include <stdio.h>
#include <string.h>
#include "../Headers/verificacoes.h"

int VerificaNif(struct NodeClientes* head, int nif) {
    struct NodeClientes* current = head;
    while (current != NULL) {
        if (current->cliente.nif == nif) {
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

int VerificaGestor(struct NodeGestores* head, char *login) {
    struct NodeGestores* current = head;
    while (current != NULL) {

        if (strcmp(current->gestor.nome,login)==0) {
            return 1;
        }
        current = current->proximo;
    }
    return 0;
}


float VerificarFloat(){
  float resultado = 0;
  char buffer[1024] = {0};

  while (1) {
    fgets(buffer, 1024, stdin);
    if (sscanf(buffer, "%f", &resultado) == 1) {
      return resultado;
    } else if (buffer[0] != '\n') {
      printf("Insere um numero válido: ");
    }
  }
}


int VerificarInt() {
  int resultado = 0;
  char buffer[1024] = {0};

  while (1) {
    fgets(buffer, 1024, stdin);
    if (sscanf(buffer, "%d", &resultado) == 1) {
      return resultado;
    } else if (buffer[0] != '\n') {
      printf("Insere um numero inteiro: ");
    }
  }
}



int VerificaIdTransportes(struct NodeTransporte* head, int id) {
    struct NodeTransporte* current = head;
    while (current != NULL) {
        if (current->transporte.id == id) {
            return 0;
        }
        current = current->proximo;
    }
    return 1;
}


int LerTextoInput(char *texto, char *resultado, int max_length) {
    printf("%s", texto);
    while (1) {
        fgets(resultado, max_length, stdin);
        int len = strlen(resultado);
        if (len > 0 && resultado[len-1] == '\n') {
            resultado[len-1] = '\0';
        }
        if (strlen(resultado) > 0) {
            return 1;
        } else {
            printf("Entrada Inválida.\n%s", texto);
        }
    }
}