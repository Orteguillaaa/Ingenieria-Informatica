// FICHERO TADLista.h
#ifndef TADLISTA_H
#define TADLISTA_H

#include "comun.h"

struct Nodo {
    Jugador info;
    Nodo *sig;
};

class lista {
private:
    Nodo *primero;
    int n;

public:
    lista();
    ~lista();

    bool obtenerPrimero(Jugador &j);
    bool esvacia();
    int longitud();
    void insertarOrdenado(Jugador j); // por puntuación ascendente
    void eliminarPorNombre(cadena nombre, bool &encontrado);
    bool obtenerPorNombre(cadena nombre, Jugador &j);
    void mostrar();
    int getLatenciaMedia();
    void exportar(Jugador *destino);
};

#endif
