#ifndef GESTORSERVIDORES_H
#define GESTORSERVIDORES_H
#include "comun.h"
#include "Servidor.h"
#include "lista.h"
#include "cola.h"

class GestorServidores
{


GestorServidores::GestorServidores() {
    primerServidor = nullptr;
    numServidores = 0;
}

GestorServidores::~GestorServidores() {
    Servidor *aux;
    while (primerServidor != nullptr) {
        aux = primerServidor;
        primerServidor = primerServidor->getSiguienteServidor();
        delete aux;
    }
    numServidores = 0;
}

int GestorServidores::getNumServidores() {
    return numServidores;
}

bool GestorServidores::desplegarServidor(cadena dS, cadena nJ, int i, int mxL, int mxC, int p, cadena lG) {
    Servidor *actual = primerServidor;
    while (actual != nullptr) {
        cadena dir;
        actual->getDireccionServidor(dir);
        if (strcmp(dir, dS) == 0 || actual->getId() == i) return false;
        actual = actual->getSiguienteServidor();
    }

    Servidor *nuevo = new Servidor(dS, nJ, i, mxL, mxC, p, lG);
    if (!nuevo) return false;

    if (!primerServidor || strcmp(lG, primerServidor->localizacionGeografica) < 0) {
        nuevo->setSiguienteServidor(primerServidor);
        primerServidor = nuevo;
    } else {
        Servidor *ant = nullptr;
        actual = primerServidor;
        cadena paisActual;
        actual->getLocalizacionGeografica(paisActual);
        while (actual && strcmp(lG, paisActual) >= 0) {
            ant = actual;
            actual = actual->getSiguienteServidor();
            if (actual) actual->getLocalizacionGeografica(paisActual);
        }
        ant->setSiguienteServidor(nuevo);
        nuevo->setSiguienteServidor(actual);
    }

    numServidores++;
    return true;
}

bool GestorServidores::conectarServidor(cadena dS) {
    Servidor *actual = primerServidor;
    while (actual) {
        cadena dir;
        actual->getDireccionServidor(dir);
        if (strcmp(dir, dS) == 0)
            return actual->activar();
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::realizarMantenimiento(cadena dS) {
    Servidor *actual = primerServidor;
    while (actual) {
        cadena dir;
        actual->getDireccionServidor(dir);
        if (strcmp(dir, dS) == 0)
            return actual->ponerEnMantenimiento();
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::eliminarServidor(cadena dS) {
    Servidor *actual = primerServidor, *ant = nullptr;
    while (actual) {
        cadena dir;
        actual->getDireccionServidor(dir);
        if (strcmp(dir, dS) == 0) {
            if (!actual->estaActivo()) {
                if (ant == nullptr)
                    primerServidor = actual->getSiguienteServidor();
                else
                    ant->setSiguienteServidor(actual->getSiguienteServidor());
                delete actual;
                numServidores--;
                return true;
            } else {
                return false; // no se puede eliminar si está ACTIVO
            }
        }
        ant = actual;
        actual = actual->getSiguienteServidor();
    }
    return false;
}

int GestorServidores::getPosicionServidor(cadena dS) {
    int pos = 1;
    Servidor *actual = primerServidor;
    while (actual) {
        cadena dir;
        actual->getDireccionServidor(dir);
        if (strcmp(dir, dS) == 0)
            return pos;
        actual = actual->getSiguienteServidor();
        pos++;
    }
    return -1;
}

void GestorServidores::mostrarInformacionServidores(int pos) {
    if (pos == -1) {
        Servidor *actual = primerServidor;
        int i = 1;
        while (actual) {
            cout << "Servidor #" << i << ":\n";
            actual->mostrarInformacion();
            actual = actual->getSiguienteServidor();
            i++;
        }
    } else {
        if (pos <= 0 || pos > numServidores) {
            cout << "Posicion fuera de rango.\n";
            return;
        }
        Servidor *actual = primerServidor;
        for (int i = 1; i < pos; i++)
            actual = actual->getSiguienteServidor();
        actual->mostrarInformacion();
    }
}

bool GestorServidores::jugadorConectado(cadena nJ, cadena dS) {
    Servidor *actual = primerServidor;
    while (actual) {
        cadena dir;
        actual->getDireccionServidor(dir);
        if (strcmp(dir, dS) == 0) {
            Jugador j;
            return actual->jugadoresConectados.obtenerPorNombre(nJ, j);
        }
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::jugadorEnEspera(cadena nJ, cadena dS) {
    Servidor *actual = primerServidor;
    while (actual) {
        cadena dir;
        actual->getDireccionServidor(dir);
        if (strcmp(dir, dS) == 0) {
            int len = actual->jugadoresEnEspera.longitud();
            for (int i = 0; i < len; i++) {
                Jugador j = actual->jugadoresEnEspera.primero();
                actual->jugadoresEnEspera.desencolar();
                actual->jugadoresEnEspera.encolar(j);
                if (strcmp(j.nombreJugador, nJ) == 0)
                    return true;
            }
            return false;
        }
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::jugadorConectado(cadena nJ) {
    Servidor *actual = primerServidor;
    while (actual) {
        Jugador j;
        if (actual->jugadoresConectados.obtenerPorNombre(nJ, j))
            return true;
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::jugadorEnEspera(cadena nJ) {
    Servidor *actual = primerServidor;
    while (actual) {
        int len = actual->jugadoresEnEspera.longitud();
        for (int i = 0; i < len; i++) {
            Jugador j = actual->jugadoresEnEspera.primero();
            actual->jugadoresEnEspera.desencolar();
            actual->jugadoresEnEspera.encolar(j);
            if (strcmp(j.nombreJugador, nJ) == 0)
                return true;
        }
        actual = actual->getSiguienteServidor();
    }
    return false;
}


bool GestorServidores::alojarJugador(Jugador j, cadena nomJuego, cadena host, bool &enEspera) {
    Servidor *mejorOpcion = nullptr;
    int maxEspacios = -1;
    Servidor *actual = primerServidor;

    while (actual) {
        if (actual->estaActivo()) {
            cadena juego;
            actual->getNombreJuego(juego);
            if (strcmp(juego, nomJuego) == 0) {
                int disponibles = actual->getMaxJugadoresConectados() - actual->getNumJugadoresConectados();
                if (disponibles > maxEspacios) {
                    maxEspacios = disponibles;
                    mejorOpcion = actual;
                }
            }
        }
        actual = actual->getSiguienteServidor();
    }

    if (mejorOpcion) {
        if (mejorOpcion->conectarJugador(j)) {
            mejorOpcion->getDireccionServidor(host);
            enEspera = false;
            return true;
        }
    }

    // Si no pudo conectarse, intentamos cola de espera
    maxEspacios = -1;
    actual = primerServidor;
    while (actual) {
        if (actual->estaActivo()) {
            cadena juego;
            actual->getNombreJuego(juego);
            if (strcmp(juego, nomJuego) == 0) {
                int libres = actual->getMaxJugadoresEnEspera() - actual->getNumJugadoresEnEspera();
                if (libres > maxEspacios) {
                    maxEspacios = libres;
                    mejorOpcion = actual;
                }
            }
        }
        actual = actual->getSiguienteServidor();
    }

    if (mejorOpcion && mejorOpcion->ponerJugadorEnEspera(j)) {
        mejorOpcion->getDireccionServidor(host);
        enEspera = true;
        return false;
    }

    // No se pudo conectar ni encolar
    enEspera = false;
    return false;
}

bool GestorServidores::expulsarJugador(cadena nJ, cadena host) {
    Servidor *actual = primerServidor;
    while (actual) {
        if (actual->expulsarJugador(nJ)) {
            actual->getDireccionServidor(host);
            return true;
        }
        actual = actual->getSiguienteServidor();
    }
    return false;
}

};
#endif // GESTORSERVIDORES_H
