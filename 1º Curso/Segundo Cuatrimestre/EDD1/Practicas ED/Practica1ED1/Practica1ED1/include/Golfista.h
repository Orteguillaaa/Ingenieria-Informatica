#ifndef GOLFISTA_H
#define GOLFISTA_H

const int TAM_CADENA = 30;
typedef char cadena[TAM_CADENA];

struct Golfista {
    cadena licencia;
    float handicap;
    cadena nombre;
    cadena apellidos;
    int golpes;
    int resultado;
};

#endif
