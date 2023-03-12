#ifndef VERIFICACOES_HEADER_GUARD
#define VERIFICACOES_HEADER_GUARD
#include "../Model/transportes.h"
#include "../Model/clientes.h"

int VerificarInt();
int VerificaIdTransportes(struct NodeTransporte* head, int id);
int limpaSTDIN();
int VerificaNif(struct NodeClientes* head, int nif);
int VerificaUser(struct NodeClientes* head, char *login);
float VerificarFloat();

#endif