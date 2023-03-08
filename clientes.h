#ifndef CLIENTES_HEADER_GUARD
#define CLIENTES_HEADER_GUARD

#include "estruturas.h"

int EscreverCliente(Clientes *clientes, int totalClientes, int nif, char nome[], char morada[], float saldo, char nomeUtilizador[], char palavraPass[]);
int LerCliente(Clientes *clientes, int totalClientes);
int verificarInt(int valor);
int EditarCliente(Clientes *clientes, int totalClientes);
int ProcurarCliente(Clientes *clientes, int totalClientes);
int limpaSTDIN();
int VerTodosClientes(Clientes *cliente, int totalClientes);
int EliminarCliente(Clientes *cliente, int totalCliente);
#endif