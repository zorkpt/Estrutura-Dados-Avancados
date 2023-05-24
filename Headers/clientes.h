#ifndef CLIENTES_HEADER_GUARD
#define CLIENTES_HEADER_GUARD
#pragma once
#include "viagem.h"

#define MAX_CHAR 50

// ESTRUTURA LISTA CLIENTES
typedef struct Clientes {
    int nif;
    char nome[MAX_CHAR];
    char morada[MAX_CHAR];
    float saldo;
    char login[MAX_CHAR];
    char password[MAX_CHAR];
    int localCliente;
    Viagem* historicoViagens;
} Clientes;

typedef struct NodeClientes {
    Clientes cliente;
    struct NodeClientes *proximo;
}NodeClientes;

// Funções associadas à estrutura Clientes
int MostrarClientes( NodeClientes* head);
NodeClientes* CriarNodeCliente(Clientes cliente);
int InserirCliente(struct NodeClientes** headRef, Clientes cliente);
int RemoverCliente(struct NodeClientes **head, int nif);
int EditarCliente(Clientes *cliente, char *nome, char *morada, char *login, char *password);
Clientes AdicionarCliente(NodeClientes* headRef, char* nome, char* morada, int nif, float saldo, char* login, char* password, int localCliente);
Clientes* ProcuraCliente(NodeClientes* headRef, int nif);
int TemSaldoSuficiente(Clientes* cliente, float custoTotal);
int AlterarSenha(Clientes* cliente, char novaSenha[]);
int RealizarDeposito(Clientes* cliente, float valor);
void MostrarHistoricoViagens(struct Clientes* cliente);


#endif
