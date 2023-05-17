#ifndef GESTORES_HEADER_GUARD
#define GESTORES_HEADER_GUARD
#pragma once

// ESTRUTURA GESTORES
typedef struct Gestores{
    char nome[50];
    char password[50];
} Gestores;

typedef struct NodeGestores
{
    struct Gestores gestor;
    struct NodeGestores *proximo;
}NodeGestores;



// novas e confirmadas
int InserirGestor(struct NodeGestores** headRef, struct Gestores gestor);
int MostrarGestores(struct NodeGestores* head);
struct Gestores AdicionarGestor(struct NodeGestores* headRef, char nome[], char password[]);
int RemoverGestor(struct NodeGestores **head, char nome[]);
#endif