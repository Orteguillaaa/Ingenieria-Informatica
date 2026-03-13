#include "Clasificacion.h"
#include <iostream>

#define SALTO 4

Clasificacion::Clasificacion() {
    elementos = new Jugador[SALTO];
    tamano = SALTO;
    Jugadores = 0;
}

void Clasificacion::anadirjugador(Jugador a) {
    if (Jugadores == tamano) {
        Jugador* nuevo = new Jugador[tamano + SALTO];
        for (int i = 0; i < Jugadores; ++i)
            nuevo[i] = elementos[i];
        delete[] elementos;
        elementos = nuevo;
        tamano += SALTO;
    }
    elementos[Jugadores++] = a;
}

void Clasificacion::eliminar(int i) {
    if (i >= 0 && i < Jugadores) {
        for (int j = i; j < Jugadores - 1; ++j)
            elementos[j] = elementos[j + 1];
        --Jugadores;
    }
}

Jugador Clasificacion::consultar(int n) {
    return elementos[n];
}

bool Clasificacion::vacio() {
    return Jugadores == 0;
}

int Clasificacion::numjugadores() {
    return Jugadores;
}

void Clasificacion::ordenar() {
    for (int i = 0; i < Jugadores - 1; ++i) {
        for (int j = 0; j < Jugadores - i - 1; ++j) {
            if (elementos[j].resultado > elementos[j + 1].resultado) {
                Jugador temp = elementos[j];
                elementos[j] = elementos[j + 1];
                elementos[j + 1] = temp;
            }
        }
    }
}

Clasificacion::~Clasificacion() {
    delete[] elementos;
}
