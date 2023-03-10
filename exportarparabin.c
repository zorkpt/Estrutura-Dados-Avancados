#ifndef EXPORTAR_HEADER_GUARD
#define EXPORTAR_HEADER_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"



// Function to export data from four linked lists to a binary file
int ExportarParaBinario(struct NodeClientes* listaClientes, 
                        struct NodeGestores* listaGestores, 
                        struct NodeTransporte* listaTransporte, 
                        struct NodeTransacoes* listaTransacoes, 
                        const char* nomeFicheiro) {

    // Open the file in binary mode for writing
    FILE* file = fopen(nomeFicheiro, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write the data from the linked lists to the file
    struct NodeClientes* current = listaClientes;
    while (current != NULL) {
        fwrite(&current->cliente, sizeof(struct NodeClientes), 1, file);
        current = current->proximo;
    }
    struct NodeGestores* current2 = listaGestores;
    while (current != NULL) {
        fwrite(&current2->gestor, sizeof(struct NodeGestores), 1, file);
        current2 = current2->proximo;
    }
    struct NodeTransporte* current3 = listaTransporte;
    while (current != NULL) {
        fwrite(&current3->transporte, sizeof(struct NodeTransporte), 1, file);
        current3 = current3->proximo;
    }
    struct NodeTransacoes* current4 = listaTransacoes;
    while (current != NULL) {
        fwrite(&current4->transacoes, sizeof(struct NodeTransacoes), 1, file);
        current4 = current4->proximo;
    }

    fclose(file);
    return 1;
}


char* LerNomeFicheiro() {
    char* nomeFicheiro = (char*) malloc(256 * sizeof(char));
    if (nomeFicheiro == NULL) {
        printf("Erro: Não foi possivel alocar memoria para o nome do ficheiro.\n");
        return NULL;
    }

    // Prompt the user for the file name
    printf("Insere o nome do ficheiro: ");
    // previne que o utilizador insira mais que 255 caracteres
    scanf("%255s", nomeFicheiro);


    return nomeFicheiro;
}

#endif