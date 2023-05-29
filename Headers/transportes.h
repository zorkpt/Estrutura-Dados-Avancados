#ifndef TRANSPORTES_HEADER_GUARD
#define TRANSPORTES_HEADER_GUARD
#pragma once
#include "grafo.h"
#include "viagem.h"
#define MAX_TIPOS_TRANSPORTE 100


typedef struct TipoTransporte {
    int idTipo;
    char nome[MAX_CHAR];
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



// Funções relacionadas à estrutura Transporte
struct Transporte EscreveTransporte(struct NodeTipoTransporte** headTipoTransporte, int id, int tipo, int nivelBateria, int localizacao, int estado);
struct Transporte* ProcurarTransporte(struct NodeTransporte* headRef, int id );
int EditarTransporte(struct Transporte *transporte, int id, int estado, int nivelBateria, float preco, int localizacao);
int EdtarEstadoTransporte(struct NodeTransporte *headTransporte, int id);
int InserirViagem(Viagem** headViagem, Viagem viagem);
void LimparCamposTransportes(NodeTransporte *transporte);

// Funções relacionadas à estrutura NodeTransporte
int InserirTransporte(struct NodeTransporte** headRef, struct Transporte transporte);
int RemoverTransporte(struct NodeTransporte **head, int id);
NodeTransporte* ProcurarTransportesPorLocal(struct NodeTransporte* headTransportes, int local);
struct NodeTransporte *ProcuraTransporteMaisProximo(NodeTransporte *listaTransportes, Vertice *grafo, int localCliente);

// Funções relacionadas a mostrar/ordenar listas de transportes
int MostrarTransportes(struct NodeTransporte* head);
int MostrarTransportesOrdenados(struct NodeTransporte *head);
int VerTransportesDisponiveis(struct NodeTransporte* headTransporte, struct Vertice* headGrafo, int localizacaoCliente);

// Funções relacionadas à estrutura Camiao
int PodeAdicionarTransporte(Camiao *camiao, Transporte *transporte);
void AdicionarTransporte(Camiao *camiao, Transporte *transporte);
Camiao* InicializarCamiao(float capacidadeMaxima);

// Funções de operação de lista
int CopiarLista(struct NodeTransporte *head, struct NodeTransporte **copiedHead);
int OrdenarListaDecrescente(struct NodeTransporte *head);

// Funções de operação de algoritmo de pesquisa
void RecarregarTransportes(NodeTransporte* transportesARecolher, NodeTransporte* transportesOriginais);
void MoverTransportesParaCentro(NodeTransporte *transportesARecolher, NodeTransporte* transportesOriginais, int centroRecolha);

// Outras funções de transporte
float CustoTotalAluguer(struct Transporte* transporte, int tempoAluguer);
int AlugarTransporteDisponivel(struct Transporte* transporte);
void ListarTransportesPorTipoERaio(struct NodeTransporte* headTransportes, struct Vertice* headGrafo, int localCliente, const char* tipo, float raio);


// Funções relacionadas à estrutura TipoTransporte
TipoTransporte* ProcuraTipoTransporte(NodeTipoTransporte** head, int idTipo);
int InserirTipoTransporte(struct NodeTipoTransporte** headRef, TipoTransporte tipoTransporte);
void ListarTiposTransporte(NodeTipoTransporte* tiposTransporte);
int AlterarPrecoTransporte(NodeTipoTransporte* tiposTransporte, int idTipo, float novoPreco);
TipoTransporte* EncontrarTipoPorId(NodeTipoTransporte** headTiposTransporte, int idTipo);


#endif