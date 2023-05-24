#ifndef VERIFICACOES_HEADER_GUARD
#define VERIFICACOES_HEADER_GUARD
#pragma once
#include "transportes.h"
#include "clientes.h"
#include "gestores.h"
 
int VerificarInt();
int VerificaIdTransportes(struct NodeTransporte* head, int id);
int VerificaNif(struct NodeClientes* head, int nif);
int VerificaUser(struct NodeClientes* head, char *login);
float VerificarFloat();
int LerTextoInput(char *texto, char *resultado, int max_length);
int VerificaGestor(struct NodeGestores* head, char *login);


#endif