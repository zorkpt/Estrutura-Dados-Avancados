/**
 * @file menu.c
 * @author Hugo Poças
 * @brief 
 * @version 0.1
 * @date 18-03-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../Headers/verificacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/// @brief Mostra o menu do gestor
/// @return Retorna a escolha do gestor
int listaMenuGestor(){
    int escolha;
    printf("\nSoftware de Gestão frota Smart City.\n");
    printf("======================================\n");
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
    printf("17. Ver todos Transportes Sorted por Autonomia\n");
    printf("19. Editar Preço de Tipo de Transporte\n");
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

/// @brief Mostra o menu do cliente
/// @return Retorna a escolha do cliente
int ListaMenuCliente(){
    int escolha;
    printf("\nSmart City\n");
    printf("======================================\n");
    printf("1. Visualizar meios de mobilidade elétrica disponíveis por ordem decrescente de autonomia\n");
    printf("2. Visualizar meios de mobilidade elétrica disponíveis por geocódigo\n");
    printf("3. Alugar um meio de mobilidade elétrica\n");
    printf("4. Terminar Viagem\n");    
    printf("5. Visualizar histórico de alugueres\n");
    printf("6. Ver transportes mais perto\n");
    printf("7. Realizar depósito\n");
    printf("8. Alterar Senha\n");
    printf("9. Procurar Transportes por Tipo/Raio\n");
    printf("10. Sair\n");
    escolha = VerificarInt(escolha);
    return escolha;
}

