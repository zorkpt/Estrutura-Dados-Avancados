#ifndef TRANSACOES_HEADER_GUARD
#define TRANSACOES_HEADER_GUARD


typedef struct Transacoes{
    int idTransacao;
    int idClienteAAlugar;
    int idTransporte;
    int tempoAlugado;
} Transacoes;

typedef struct NodeTransacoes
{
    struct Transacoes transacoes;
    struct NodeTransacoes *proximo;
}NodeTransacoes;


int InserirTransacoes(struct NodeTransacoes** headRef, struct Transacoes transacoes);
int MostrarTransacoes(struct NodeTransacoes* head);
int MostrarTransacoesCliente(struct NodeTransacoes* head, int idCliente);
int EditarTransacao(struct Transacoes * transacao);
int RemoverTransacao(struct NodeTransacoes **head, int idTransacao);
struct Transacoes* ProcurarTransacao(struct NodeTransacoes* head, int idTransacao);

#endif