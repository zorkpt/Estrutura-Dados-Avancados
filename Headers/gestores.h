#ifndef GESTORES_HEADER_GUARD
#define GESTORES_HEADER_GUARD
#pragma once

// ESTRUTURA GESTORES
typedef struct Gestores{
    char nome[MAX_CHAR];
    char password[MAX_CHAR];
} Gestores;

typedef struct NodeGestores
{
    struct Gestores gestor;
    struct NodeGestores *proximo;
}NodeGestores;



// Funções associadas à estrutura Gestores
int InserirGestor(struct NodeGestores** headRef, struct Gestores gestor);
int MostrarGestores(struct NodeGestores* head);
struct Gestores AdicionarGestor(struct NodeGestores* headRef, char nome[], char password[]);
int RemoverGestor(struct NodeGestores **head, char nome[]);
#endif