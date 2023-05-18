#ifndef VIAGEM_HEADER_GUARD
#define VIAGEM_HEADER_GUARD
#define CHAR_MAX 100

typedef struct Viagem {
    int idTransporte;
    int origem;
    char tipoTransporte[CHAR_MAX];
    int destino;
    float valorPago;
    float custoPorKm;
    float distancia;
    struct Viagem* proxima;
} Viagem;

#endif
