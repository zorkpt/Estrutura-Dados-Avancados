#ifndef STRUCT_HEADER_GUARD
#define STRUCT_HEADER_GUARD

typedef struct ClientesTesteLista
{
    int nif;
    char nome[50];
    char morada[100];
    float saldo;
    char login[50];
    char password[50];
    int tipoUser;
}ClientesTesteLista;

typedef struct nodeClientes
{
    struct ClientesTesteLista data;
    struct nodeClientes *next;
}nodeClientes;






typedef struct {
    int id;
    char tipo[50];
    int nivelBateria;
    float preco;
    char localizacao[50];
    int estado;
} Transporte;

typedef struct {
    int nif;
    char nome[50];
    char morada[100];
    float saldo;
    char login[50];
    char password[50];
    int tipoUser;
} Clientes;

typedef struct {
    char nome[50];
    char password[50];
} Gestores;

typedef struct {
    int idClienteAAlugar;
    int idTransporte;
    int tempoAluguerDecorrido;
} Transacoes;

enum Estrutura { CLIENTES, TRANSPORTE, GESTORES, TRANSACOES, TESTE };
enum TipoUser { GESTOR, CLIENTE };

#endif