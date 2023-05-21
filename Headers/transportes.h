#ifndef TRANSPORTES_HEADER_GUARD
#define TRANSPORTES_HEADER_GUARD
#pragma once
#include "grafo.h"
#include "viagem.h"
#define MAX_TIPOS_TRANSPORTE 100


typedef struct TipoTransporte {
    int idTipo;
    char nome[50];
    float peso;
    float precoPorKm;
} TipoTransporte;

typedef struct NodeTipoTransporte {
    TipoTransporte tipo;
    struct NodeTipoTransporte* proximo;
}NodeTipoTransporte;

typedef struct Transporte{
    int id;
    int idTipo;
    TipoTransporte* tipo;
    int nivelBateria;
    int localizacao;
    int estado;
    int visitado;
} Transporte;

typedef struct NodeTransporte
{
    struct Transporte transporte;
    struct NodeTransporte *proximo;
}NodeTransporte;

typedef struct Camiao {
    float capacidadeMaxima; // Capacidade máxima do camião em kg
    float cargaAtual; // Carga atual do camião em kg
    float cargaMaxima; // Carga maxima do camião
} Camiao;



int InserirTransporte(struct NodeTransporte** headRef, struct Transporte transporte);
int MostrarTransportes(struct NodeTransporte* head);
int VerTransportesDisponiveis(struct NodeTransporte* headTransporte, struct Vertice* headGrafo, int localizacaoCliente);
struct Transporte EscreveTransporte(struct NodeTipoTransporte** headTipoTransporte, int id, int tipo, int nivelBateria, int localizacao, int estado);
struct Transporte* ProcurarTransporte(struct NodeTransporte* headRef, int id );    
int RemoverTransporte(struct NodeTransporte **head, int id);
int EditarTransporte(struct Transporte *transporte, int id, int estado, int nivelBateria, float preco, int localizacao);
int CopiarLista(struct NodeTransporte *head, struct NodeTransporte **copiedHead);
int OrdenarListaDecrescente(struct NodeTransporte *head);
int MostrarTransportes(struct NodeTransporte *head);
int MostrarTransportesOrdenados(struct NodeTransporte *head);
struct NodeTransporte* ProcurarTransportesPorLocal(struct NodeTransporte* headTransportes, int local);
float CustoTotalAluguer(struct Transporte* transporte, int tempoAluguer);
int AlugarTransporteDisponivel(struct Transporte* transporte);
int EditarTransporteID(struct NodeTransporte *headTransporte, int id);
NodeTransporte* TransportesParaRecolher(NodeTransporte *transportes);
void LimparCamposTransportes(NodeTransporte *transporte);
NodeTransporte *ProcuraTransporteMaisProximo(NodeTransporte *listaTransportes, Vertice *grafo, int localCliente);
void ListarTransportesPorTipoERaio(struct NodeTransporte* headTransportes, struct Vertice* headGrafo, int localCliente, const char* tipo, float raio);
TipoTransporte* ProcuraTipoTransporte(NodeTipoTransporte** head, int idTipo);
int InserirTipoTransporte(struct NodeTipoTransporte** headRef, TipoTransporte tipoTransporte);
void RecarregarTransportes(NodeTransporte* transportes);
void MoverTransportesParaCentro(NodeTransporte* transportes, int centroRecolha);
void ListarTiposTransporte(NodeTipoTransporte* tiposTransporte);
int AlterarPrecoTransporte(NodeTipoTransporte* tiposTransporte, int idTipo, float novoPreco);

//funcs camiao
int PodeAdicionarTransporte(Camiao *camiao, Transporte *transporte);
void AdicionarTransporte(Camiao *camiao, Transporte *transporte);
void DescarregarCamiao(Camiao *camiao);
Camiao* InicializarCamiao(float capacidadeMaxima);
Viagem* CriarNovaViagem(int idTransporte, int origem, int destino, float valorPago, float custoPorKm, float distancia,char tipoTransporte[]);
int InserirViagem(Viagem** headViagem, Viagem viagem);
#endif