#include "../Controller/verificacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int menu(){
    int escolha;
    printf("\nSoftware de Gestão frota Smart City.\n");
    printf(" ------- CLIENTES -------- \n");
    printf("1. Registar Cliente\n");
    printf("2. Alterar Cliente\n");
    printf("3. Eliminar Cliente\n");    
    printf("4. Localizar Cliente\n");
    printf("5. Ver todos Clientes\n");
    printf(" ------- TRANSPORTES -------- \n");
    printf("11. Adicionar Trasportes\n");  
    printf("12. Alterar Transporte\n");
    printf("13. Eliminar Transporte\n");
    printf("14. Localizar Transporte\n");
    printf("15. Ver todos Transportes\n");
    printf("16. Ver todos Transportes disponiveis\n");
    printf("17. Ver todos Transportes Sorted por Autonomia");
    printf(" ------- GESTORES -------- \n");
    printf("21. Adicionar Gestor\n");
    printf("22. Eliminar Gestor\n");
    printf(" ------- TRANSAÇÕES -------- \n");
    printf("31. Ver Todas Transações\n");
    printf("32. Ver Transações de Cliente\n");
    printf("33. Editar Transação\n");
    printf("34. Eliminar Transação\n");
    printf(" ------- RELATÓRIOS -------- \n");
    printf("0. Guardar Dados\n");
    printf("Escolhe uma opção: ");
    
    escolha = VerificarInt(escolha);

    return escolha;
}


