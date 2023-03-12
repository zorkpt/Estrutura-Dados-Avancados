#ifndef GESTORES_HEADER_GUARD
#define GESTORES_HEADER_GUARD

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
void InserirGestor(struct NodeGestores** headRef, struct Gestores gestor);
void MostrarGestores(struct NodeGestores* head);
#endif