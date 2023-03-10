#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int menu(){
    int escolha;
    printf("\nSoftware de Gestão frota Smart City.\n");
    printf("1. Registar Cliente\n");
    printf("2. Alterar Cliente\n");
    printf("3. Eliminar Cliente\n");    
    printf("4. Localizar Cliente\n");
    printf("5. Ver todos Clientes\n");
    printf("6. Ver Trasportes\n");  
    printf("7. Ver Transportes Activos\n");
    printf("8. Histórico Transacções\n");
    printf("9. Exportar Dados\n");   
    printf("0. Sair\n");
    printf("Escolhe uma opção: ");
    
    escolha = verificarInt(escolha);

    return escolha;
}


