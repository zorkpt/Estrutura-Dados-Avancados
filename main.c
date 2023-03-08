#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define MAX_CLIENTES 100

int PrintListaClientesTeste(ClientesTesteLista *head){
    ClientesTesteLista *atual = head;
    int contadorNode = 0;

    while(atual){
        ++contadorNode;
        printf("%d",atual->nif);
        atual=atual->next;
    }
}


int main() {
    Clientes cliente[MAX_CLIENTES];
    Transporte transporte[MAX_CLIENTES];
    Gestores gestores[MAX_CLIENTES];
    Transacoes transacoes[MAX_CLIENTES];
    
    int totalClientes = CarregarDados(cliente,CLIENTES,"./Data/clients.csv");
    int totalTransportes = CarregarDados(transporte,TRANSPORTE,"./Data/transportes.csv");
    int totalGestores = CarregarDados(gestores,GESTORES,"./Data/gestores.csv");
    int totalTransacoes = CarregarDados(transacoes,TRANSACOES,"./Data/transacoes.csv");
    int tipoMenu;

    tipoMenu = IniciarLogin(cliente,totalClientes,gestores,totalGestores);



// TESTES LISTAS




struct nodeClientes *new_node = (struct nodeClientes*) malloc(sizeof(struct nodeClientes));
struct ClientesTesteLista *novoCliente = (struct ClientesTesteLista*) malloc(sizeof(struct ClientesTesteLista));



novoCliente->nif = 250223232;
strcpy(novoCliente->nome, "João");
strcpy(novoCliente->morada, "Rua 3");
novoCliente->saldo = 30;
strcpy(novoCliente->login, "admin1");
strcpy(novoCliente->password, "admin1");
novoCliente->tipoUser = 1;
new_node->data = *novoCliente;
new_node->next = NULL;


// FIM TESTES LISTAS







    switch (tipoMenu)
    {
    case 1:
        MenuUtilizador(cliente,totalClientes);
        break;
    case 2:
        MenuGestor(cliente,totalClientes,gestores,totalGestores,transporte,totalTransportes,transacoes,totalTransacoes);
        break;

    default:
        break;
    };
  
}
    


