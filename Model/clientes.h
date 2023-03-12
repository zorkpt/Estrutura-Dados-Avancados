#ifndef CLIENTES_HEADER_GUARD
#define CLIENTES_HEADER_GUARD

// ESTRUTURA LISTA CLIENTES
typedef struct Clientes{
    int nif;
    char nome[50];
    char morada[100];
    float saldo;
    char login[50];
    char password[50];
} Clientes;
typedef struct NodeClientes
{
    struct Clientes cliente;
    struct NodeClientes *proximo;
}NodeClientes;


// // VERIFICAÇÕES
// int VerificaNif(struct NodeClientes* head, int nif);
// int VerificarInt();
// float VerificarFloat();
// int limpaSTDIN();

// FUNCOES CONFIRMADAS E A FUNCIONAR:
void MostrarClientes(struct NodeClientes* head);
int InserirCliente(struct NodeClientes** headRef, struct Clientes cliente);
int RemoverCliente(struct NodeClientes **head, int nif);
int EditarCliente(struct NodeClientes *head, int nif);
int AdicionarCliente(struct NodeClientes* headRef);
int ProcuraCliente(struct NodeClientes* headRef, int nif);
#endif

