#ifndef TRANSPORTES_HEADER_GUARD
#define TRANSPORTES_HEADER_GUARD
#pragma once
#include "clientes.h"

typedef struct Transporte{
    int id;
    char tipo[50];
    int nivelBateria;   
    float preco;
    int localizacao;
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
struct Transporte EscreveTransporte(struct NodeTransporte* headTransporte, int id, char* tipo, int nivelBateria, float preco, int localizacao, int estado);
struct Transporte* ProcurarTransporte(struct NodeTransporte* headRef, int id );    
int RemoverTransporte(struct NodeTransporte **head, int id);
int EditarTransporte(struct Transporte *transporte, int id, int estado, int nivelBateria, float preco, int localizacao, char *tipo);
int CopiarLista(struct NodeTransporte *head, struct NodeTransporte **copiedHead);
int OrdenarListaDecrescente(struct NodeTransporte *head);
int MostrarTransportes(struct NodeTransporte *head);
int MostrarTransportesOrdenados(struct NodeTransporte *head);
struct NodeTransporte* ProcurarTransportesPorLocal(struct NodeTransporte* headTransportes, int local);
float CustoTotalAluguer(struct Transporte* transporte, int tempoAluguer);
int AlugarTransporteDisponivel(struct Transporte* transporte);
int EditarTransporteID(struct NodeTransporte *headTransporte, int id);


#endif