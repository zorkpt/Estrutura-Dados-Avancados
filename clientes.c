#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int limpaSTDIN(){
    int valor;
    while((valor = getchar()) != '\n' && valor != EOF);    
}

int verificarInt(int valor){
        while (scanf("%d",&valor)== 0) {
        printf("Insere um número válido.\n");
        limpaSTDIN();
    }   
    return valor;
}

int verificarFloat(float valor){
        while (scanf("%f",&valor)== 0) {
        printf("Insere um número válido.\n");
        limpaSTDIN();
    }   
    return valor;
}

char VerificarNomeUtilizador(Clientes *clientes, int totalClientes,char nomeUtilizador[]){
    
    for(int i = 0 ; i < totalClientes ; i++){
        if(strcmp(clientes[i].login,nomeUtilizador)==0){
            printf("Já existe um nome de utilizador com esse nome.\nEscolha outro: ");
            return 0;
        }
    } 
        return 1;

}

int LerCliente(Clientes *clientes, int totalClientes){
    int escolha;
    int nif,res;
    float saldo;

    char nome[50], morada[50], nomeUtilizador[50], palavraPasse[50];
    printf("A adicionar novo cliente.\n");
    printf("NIF: ");
    nif = verificarInt(nif);
    printf("\nNome: ");
    scanf("%s",nome);
    printf("\nMorada: ");
    scanf("%s",morada);
    printf("\nEfetuar carremento de saldo?\n1.Sim\n2.Não\n");
    escolha = verificarInt(escolha);

    if(escolha == 1){
        printf("\nQuantidade? ");
        saldo = verificarFloat(saldo);
    }else saldo=0;

    printf("Nome de Utilizador? \n");

    while(1){
        limpaSTDIN();
        scanf("%s",nomeUtilizador); 
        if(VerificarNomeUtilizador(clientes, totalClientes,nomeUtilizador)) break;
    }

    printf("Palavra-Passe? ");
    scanf("%s",palavraPasse);

    totalClientes = (EscreverCliente(clientes, totalClientes, nif, nome, morada, saldo, nomeUtilizador, palavraPasse));
    return totalClientes;
    
}

int EscreverCliente(Clientes *clientes, int totalClientes, int nif, char nome[], char morada[], float saldo, char nomeUtilizador[], char palavraPass[]) {
    clientes[totalClientes].nif = nif;
    strcpy(clientes[totalClientes].nome,nome);
    strcpy(clientes[totalClientes].morada,morada);
    clientes[totalClientes].saldo = saldo;
    strcpy(clientes[totalClientes].login,nomeUtilizador);
    strcpy(clientes[totalClientes].password,palavraPass);
    totalClientes++;
    return totalClientes;
}

int EscreveClienteEditado(Clientes *clientes, int indexCliente, char nome[], char morada[], float saldo){
    strcpy(clientes[indexCliente].nome,nome);
    strcpy(clientes[indexCliente].morada,morada);
    clientes[indexCliente].saldo = saldo;
    return 1;
}


int VerificaNif(Clientes *clientes, int totalClientes, int nif){
    scanf("%d",&nif);
    int indexCliente;
    for(int i=0; i< totalClientes; i++){
        if(nif==clientes[i].nif){
            indexCliente = i;
            return indexCliente;
        }
    }
    return -1;
}

int EditarCliente(Clientes *clientes, int totalClientes){
    int nif, indexCliente;
    char nome[50], morada[50],username[50],password[50];
    float saldo;

    printf("Inserir NIF do cliente a editar: ");
    indexCliente = VerificaNif(clientes,totalClientes,nif);
    if(indexCliente==-1){
        return 0;
    }

    printf("A editar o cliente:\nNIF:%d\nNome:%s\nMorada:%s\nSaldo:%f",clientes[indexCliente].nif,clientes[indexCliente].nome,clientes[indexCliente].morada,clientes[indexCliente].saldo);
    printf("\nNome:\n");
    scanf("%s",nome);
    printf("Morada?\n");
    scanf("%s",morada);
    printf("Saldo?\n");
    saldo = verificarFloat(saldo);
    printf("Nome de utlizador?\n");

    if(EscreveClienteEditado(clientes,indexCliente,nome,morada,saldo)) return 1;
    
}

int ProcurarCliente(Clientes *clientes, int totalClientes){
    int nif,indexCliente;
    printf("Inserir NIF do cliente: ");
    indexCliente = VerificaNif(clientes,totalClientes,nif);
    if(indexCliente==-1){
        return 0;
    }
    
    printf("\nNome:%s\nNIF:%d\nMorada:%s\nSaldo:%f",clientes[indexCliente].nome,clientes[indexCliente].nif,clientes[indexCliente].morada,clientes[indexCliente].saldo);

}


int VerTodosClientes(Clientes *cliente, int totalClientes){
        for(int i = 0 ; i<totalClientes; i++){
        printf("%d\t%s\t%s\t\t%.2f\tlogin: %s\t\tpass: %s\n",cliente[i].nif,cliente[i].nome,cliente[i].morada,cliente[i].saldo,cliente[i].login,cliente[i].password);
    }
}

int EliminarCliente(Clientes *cliente, int totalCliente){
int nif,index;
int novoTamanhoArray = totalCliente-1;
    printf("Introduza o NIF do cliente que pretende eliminar: ");
    nif = verificarInt(nif);

    for(int i = 0 ; i < totalCliente ; i++){
        if(cliente[i].nif == nif){
            index=i;
            break;
        }
    }
        cliente[index] = cliente[totalCliente-1];
        totalCliente--;
        return totalCliente;

    printf("Não foi encontrado nenhum cliente com o NIF introduzido.\n");
    return totalCliente;    
}