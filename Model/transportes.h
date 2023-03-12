#ifndef TRANSPORTES_HEADER_GUARD
#define TRANSPORTES_HEADER_GUARD
#include "../Model/transacoes.h"



// ESTRUTURA TRANSPORTES
typedef struct Transporte{
    int id;
    char tipo[50];
    int nivelBateria;   
    float preco;
    char localizacao[50];
    int estado;
} Transporte;

typedef struct NodeTransporte
{
    struct Transporte transporte;
    struct NodeTransporte *proximo;
}NodeTransporte;


void InserirNoFimTransporte(struct NodeTransporte** headRef, struct Transporte transporte);
void MostrarTransportes(struct NodeTransporte* head);
int VerTransportesDisponiveis(struct NodeTransporte* head, struct NodeTransacoes* headTransacoes);
int EscreveTransporte(struct NodeTransporte* headTransporte);
int ProcurarTransporte(struct NodeTransporte* headRef, int id );    
int RemoverTransporte(struct NodeTransporte **head, int id);

#endif