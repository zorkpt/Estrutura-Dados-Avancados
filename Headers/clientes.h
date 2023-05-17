#ifndef CLIENTES_HEADER_GUARD
#define CLIENTES_HEADER_GUARD
#define MAX_CHAR 50
#pragma once
// ESTRUTURA LISTA CLIENTES
typedef struct Clientes{
    int nif;
    char nome[MAX_CHAR];
    char morada[MAX_CHAR];
    float saldo;
    char login[MAX_CHAR];
    char password[MAX_CHAR];
    int localCliente;
} Clientes;
typedef struct NodeClientes
{
    Clientes cliente;
    struct NodeClientes *proximo;
}NodeClientes;


// FUNCOES CONFIRMADAS E A FUNCIONAR:
int MostrarClientes( NodeClientes* head);
NodeClientes* criarNodeCliente(Clientes cliente);
int InserirCliente(struct NodeClientes** headRef, struct Clientes cliente);
int RemoverCliente(struct NodeClientes **head, int nif);
int EditarCliente(struct Clientes *cliente, char *nome, char *morada, char *login, char *password);
struct Clientes AdicionarCliente(struct NodeClientes* headRef, char* nome, char* morada, int nif, float saldo, char* login, char* password, int localCliente);
struct Clientes* ProcuraCliente(struct NodeClientes* headRef, int nif);
int TemSaldoSuficiente(struct Clientes* cliente, float custoTotal);
int AlterarSenha(struct Clientes* cliente, char novaSenha[]);
int RealizarDeposito(struct Clientes* cliente, float valor);
#endif

