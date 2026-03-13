#include "GestorServidores.h"
#include <cstring>
#include <iostream>
using namespace std;

GestorServidores::GestorServidores() {
    primerServidor = nullptr;
    numServidores = 0;
}

GestorServidores::~GestorServidores() {
    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        Servidor* siguiente = actual->getSiguienteServidor();
        delete actual;
        actual = siguiente;
    }
    primerServidor = nullptr;
    numServidores = 0;
}

int GestorServidores::getNumServidores() {
    return numServidores;
}

bool GestorServidores::desplegarServidor(cadena dS, cadena nJ, int i, int mxL, int mxC, int p, cadena lG) {
    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        cadena direccion;
        actual->getDireccionServidor(direccion);
        if (strcmp(direccion, dS) == 0 || actual->getId() == i)
            return false;
        actual = actual->getSiguienteServidor();
    }

    Servidor* nuevo = new Servidor(dS, nJ, i, mxL, mxC, p, lG);
    if (!nuevo) return false;

    if (!primerServidor || strcmp(lG, primerServidor->localizacionGeografica) < 0) {
        nuevo->setSiguienteServidor(primerServidor);
        primerServidor = nuevo;
    } else {
        Servidor* ant = nullptr;
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
    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        cadena direccion;
        actual->getDireccionServidor(direccion);
        if (strcmp(direccion, dS) == 0) {
            return actual->activar();
        }
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::realizarMantenimiento(cadena dS) {
    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        cadena direccion;
        actual->getDireccionServidor(direccion);
        if (strcmp(direccion, dS) == 0) {
            return actual->ponerEnMantenimiento();
        }
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::eliminarServidor(cadena dS) {
    Servidor* actual = primerServidor;
    Servidor* anterior = nullptr;
    while (actual != nullptr) {
        cadena direccion;
        actual->getDireccionServidor(direccion);
        if (strcmp(direccion, dS) == 0) {
            if (!actual->estaActivo()) {
                if (anterior == nullptr) {
                    primerServidor = actual->getSiguienteServidor();
                } else {
                    anterior->setSiguienteServidor(actual->getSiguienteServidor());
                }
                delete actual;
                numServidores--;
                return true;
            } else {
                return false;
            }
        }
        anterior = actual;
        actual = actual->getSiguienteServidor();
    }
    return false;
}

int GestorServidores::getPosicionServidor(cadena dS) {
    int pos = 1;
    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        cadena direccion;
        actual->getDireccionServidor(direccion);
        if (strcmp(direccion, dS) == 0) return pos;
        actual = actual->getSiguienteServidor();
        pos++;
    }
    return -1;
}

void GestorServidores::mostrarInformacionServidores(int pos) {
    if (pos == -1) {
        Servidor* actual = primerServidor;
        while (actual != nullptr) {
            actual->mostrarInformacion();
            cout << "------------------------------------------\n";
            actual = actual->getSiguienteServidor();
        }
    } else {
        if (pos < 1 || pos > numServidores) {
            cout << "Error: posición fuera de rango.\n";
            return;
        }
        Servidor* actual = primerServidor;
        int contador = 1;
        while (actual && contador < pos) {
            actual = actual->getSiguienteServidor();
            contador++;
        }
        if (actual)
            actual->mostrarInformacion();
    }
}

bool GestorServidores::alojarJugador(Jugador j, cadena nomJuego, cadena host, bool &enEspera) {
    Servidor* mejorServidor = nullptr;
    int maxEspacio = -1;

    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        cadena juego;
        actual->getNombreJuego(juego);
        if (actual->estaActivo() && strcmp(juego, nomJuego) == 0) {
            int espacioDisponible = actual->getMaxJugadoresConectados() - actual->getNumJugadoresConectados();
            if (espacioDisponible > maxEspacio) {
                mejorServidor = actual;
                maxEspacio = espacioDisponible;
            }
        }
        actual = actual->getSiguienteServidor();
    }

    if (mejorServidor != nullptr) {
        if (mejorServidor->conectarJugador(j)) {
            mejorServidor->getDireccionServidor(host);
            enEspera = false;
            return true;
        }
    }

    // Si no hay hueco, buscamos cola de espera con más espacio
    Servidor* mejorCola = nullptr;
    int maxEspera = -1;

    actual = primerServidor;
    while (actual != nullptr) {
        cadena juego;
        actual->getNombreJuego(juego);
        if (actual->estaActivo() && strcmp(juego, nomJuego) == 0) {
            int espacioCola = actual->getMaxJugadoresEnEspera() - actual->getNumJugadoresEnEspera();
            if (espacioCola > maxEspera) {
                mejorCola = actual;
                maxEspera = espacioCola;
            }
        }
        actual = actual->getSiguienteServidor();
    }

    if (mejorCola != nullptr) {
        if (mejorCola->ponerJugadorEnEspera(j)) {
            mejorCola->getDireccionServidor(host);
            enEspera = true;
            return false;
        }
    }

    enEspera = false;
    return false;
}

bool GestorServidores::expulsarJugador(cadena nJ, cadena host) {
    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        if (actual->expulsarJugador(nJ)) {
            actual->getDireccionServidor(host);
            return true;
        }
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::jugadorConectado(cadena nJ, cadena dS) {
    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        cadena direccion;
        actual->getDireccionServidor(direccion);
        if (strcmp(direccion, dS) == 0) {
            Jugador j;
            return actual->jugadoresConectados.obtenerPorNombre(nJ, j);
        }
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::jugadorEnEspera(cadena nJ, cadena dS) {
    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        cadena direccion;
        actual->getDireccionServidor(direccion);
        if (strcmp(direccion, dS) == 0) {
            int len = actual->getNumJugadoresEnEspera();
            for (int i = 0; i < len; i++) {
                Jugador j = actual->jugadoresEnEspera.primero();
                actual->jugadoresEnEspera.desencolar();
                actual->jugadoresEnEspera.encolar(j);
                if (strcmp(j.nombreJugador, nJ) == 0) return true;
            }
            return false;
        }
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::jugadorConectado(cadena nJ) {
    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        Jugador j;
        if (actual->jugadoresConectados.obtenerPorNombre(nJ, j))
            return true;
        actual = actual->getSiguienteServidor();
    }
    return false;
}

bool GestorServidores::jugadorEnEspera(cadena nJ) {
    Servidor* actual = primerServidor;
    while (actual != nullptr) {
        int len = actual->getNumJugadoresEnEspera();
        for (int i = 0; i < len; i++) {
            Jugador j = actual->jugadoresEnEspera.primero();
            actual->jugadoresEnEspera.desencolar();
            actual->jugadoresEnEspera.encolar(j);
            if (strcmp(j.nombreJugador, nJ) == 0) return true;
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
