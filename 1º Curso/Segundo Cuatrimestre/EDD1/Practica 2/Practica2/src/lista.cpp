//FICHERO TADLista.cpp
#include "lista.h"
#include <iostream>
#include <cstring>

lista::lista() {
    primero = nullptr;
    n = 0;
}

lista::~lista() {
    Nodo *aux;
    while (primero != nullptr) {
        aux = primero;
        primero = primero->sig;
        delete aux;
    }
    n = 0;
}

bool lista::obtenerPrimero(Jugador &j) {
    if (primero != nullptr) {
        j = primero->info;
        return true;
    }
    return false;
}

bool lista::esvacia() {
    return n == 0;
}

int lista::longitud() {
    return n;
}

void lista::insertarOrdenado(Jugador j) {
    Nodo *nuevo = new Nodo;
    nuevo->info = j;
    nuevo->sig = nullptr;

    if (primero == nullptr || j.puntuacion < primero->info.puntuacion) {
        nuevo->sig = primero;
        primero = nuevo;
    } else {
        Nodo *act = primero;
        while (act->sig != nullptr && act->sig->info.puntuacion <= j.puntuacion)
            act = act->sig;
        nuevo->sig = act->sig;
        act->sig = nuevo;
    }
    n++;
}

void lista::eliminarPorNombre(cadena nombre, bool &encontrado) {
    encontrado = false;
    Nodo *act = primero, *ant = nullptr;

    while (act != nullptr && strcmp(act->info.nombreJugador, nombre) != 0) {
        ant = act;
        act = act->sig;
    }

    if (act != nullptr) {
        encontrado = true;
        if (ant == nullptr)
            primero = act->sig;
        else
            ant->sig = act->sig;
        delete act;
        n--;
    }
}

bool lista::obtenerPorNombre(cadena nombre, Jugador &j) {
    Nodo *act = primero;
    while (act != nullptr) {
        if (strcmp(act->info.nombreJugador, nombre) == 0) {
            j = act->info;
            return true;
        }
        act = act->sig;
    }
    return false;
}

void lista::mostrar() {
    Nodo *act = primero;
    while (act != nullptr) {
        Jugador j = act->info;
        std::cout << "Nombre: " << j.nombreJugador
                  << ", ID: " << j.ID
                  << ", Ping: " << j.latencia
                  << ", Puntuacion: " << j.puntuacion
                  << ", Pais: " << j.pais << std::endl;
        act = act->sig;
    }
}

int lista::getLatenciaMedia() {
    if (n == 0) return 0;
    int suma = 0;
    Nodo *act = primero;
    while (act != nullptr) {
        suma += act->info.latencia;
        act = act->sig;
    }
    return suma / n;
}

void lista::exportar(Jugador *destino) {
    Nodo *act = primero;
    int i = 0;
    while (act != nullptr) {
        destino[i++] = act->info;
        act = act->sig;
    }
}
