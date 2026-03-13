#ifndef CLASIFICACION_H
#define CLASIFICACION_H

#include "Jugador.h"

class Clasificacion {
    Jugador* elementos;
    int Jugadores;
    int tamano;
public:
    Clasificacion();
    void anadirjugador(Jugador a);
    void eliminar(int i);
    Jugador consultar(int n);
    bool vacio();
    int numjugadores();
    void ordenar();
    ~Clasificacion();
};

#endif
