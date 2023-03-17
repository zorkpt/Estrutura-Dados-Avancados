#ifndef TRANSPORTES_HEADER_GUARD
#define TRANSPORTES_HEADER_GUARD
#pragma once
#include "clientes.h"


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


int InserirTransporte(struct NodeTransporte** headRef, struct Transporte transporte);
int MostrarTransportes(struct NodeTransporte* head);
int VerTransportesDisponiveis(struct NodeTransporte* headTransporte);
struct Transporte EscreveTransporte(struct NodeTransporte* headTransporte);
struct Transporte* ProcurarTransporte(struct NodeTransporte* headRef, int id );    
int RemoverTransporte(struct NodeTransporte **head, int id);
int EditarTransporte(struct Transporte *transporte, int id);
int CopiarLista(struct NodeTransporte *head, struct NodeTransporte **copiedHead);
int OrdenarListaDecrescente(struct NodeTransporte *head);
int MostrarTransportes(struct NodeTransporte *head);
int MostrarTransportesOrdenados(struct NodeTransporte *head);
struct NodeTransporte* ProcurarTransportesPorLocal(struct NodeTransporte* headTransportes, const char* local);
float CustoTotalAluguer(struct Transporte* transporte, int tempoAluguer);
int AlugarTransporteDisponivel(struct Transporte* transporte);
int EditarTransporteID(struct NodeTransporte *headTransporte, int id);


#endif