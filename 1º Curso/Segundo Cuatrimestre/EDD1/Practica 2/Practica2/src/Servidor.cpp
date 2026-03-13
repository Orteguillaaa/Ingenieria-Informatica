#include "Servidor.h"
#include <iostream>
#include <cstring>

using namespace std;

Servidor::Servidor(cadena dS, cadena nJ, int i, int mxL, int mxC, int p, cadena lG) {
    strcpy(direccionServidor, dS);
    strcpy(nombreJuego, nJ);
    id = i;
    maxJugadoresConectados = mxL;
    maxJugadoresEnEspera = mxC;
    puerto = p;
    strcpy(localizacionGeografica, lG);
    strcpy(estado, "INACTIVO");
    siguienteServidor = nullptr;
}

Servidor::~Servidor() {
    // Recursos internos liberados automáticamente
}

int Servidor::getId() {
    return id;
}

void Servidor::getDireccionServidor(cadena dS) {
    strcpy(dS, direccionServidor);
}

void Servidor::setSiguienteServidor(Servidor *pS) {
    siguienteServidor = pS;
}

Servidor* Servidor::getSiguienteServidor() {
    return siguienteServidor;
}

bool Servidor::conectarJugador(Jugador j) {
    if (jugadoresConectados.longitud() < maxJugadoresConectados) {
        j.activo = true;
        jugadoresConectados.insertarOrdenado(j);
        return true;
    }
    return false;
}

bool Servidor::ponerJugadorEnEspera(Jugador j) {
    if (jugadoresConectados.longitud() >= maxJugadoresConectados &&
        jugadoresEnEspera.longitud() < maxJugadoresEnEspera) {
        jugadoresEnEspera.encolar(j);
        return true;
    }
    return false;
}

void Servidor::mostrarJugadoresConectados() {
    jugadoresConectados.mostrar();
}

void Servidor::mostrarJugadoresEnEspera() {
    int len = jugadoresEnEspera.longitud();
    for (int i = 0; i < len; i++) {
        Jugador j = jugadoresEnEspera.primero();
        cout << "Nombre: " << j.nombreJugador
             << ", ID: " << j.ID
             << ", Ping: " << j.latencia
             << ", Puntuacion: " << j.puntuacion
             << ", Pais: " << j.pais << endl;
        jugadoresEnEspera.desencolar();
        jugadoresEnEspera.encolar(j); // rotamos para no alterar el orden
    }
}

bool Servidor::estaActivo() {
    return strcmp(estado, "ACTIVO") == 0;
}

bool Servidor::activar() {
    if (!estaActivo()) {
        strcpy(estado, "ACTIVO");
        return true;
    }
    return false;
}

bool Servidor::desactivar() {
    if (strcmp(estado, "INACTIVO") == 0)
        return false;

    strcpy(estado, "INACTIVO");

    // Vaciar conectados
   Jugador j;
bool encontrado;
while (jugadoresConectados.obtenerPrimero(j)) {
    jugadoresConectados.eliminarPorNombre(j.nombreJugador, encontrado);
}



    // Vaciar espera
    while (!jugadoresEnEspera.esvacia()) {
        jugadoresEnEspera.desencolar();
    }

    return true;
}

bool Servidor::ponerEnMantenimiento() {
    if (strcmp(estado, "INACTIVO") == 0) {
        strcpy(estado, "MANTENIMIENTO");
        return true;
    }
    return false;
}

void Servidor::mostrarInformacion() {
    cout << "Servidor: " << direccionServidor << " (ID: " << id << ")\n";
    cout << "Juego: " << nombreJuego << "\n";
    cout << "Estado: " << estado << "\n";
    cout << "Puerto: " << puerto << "\n";
    cout << "Localizacion: " << localizacionGeografica << "\n";
    cout << "Jugadores conectados: " << jugadoresConectados.longitud()
         << "/" << maxJugadoresConectados << "\n";
    cout << "Jugadores en espera: " << jugadoresEnEspera.longitud()
         << "/" << maxJugadoresEnEspera << "\n";
    cout << "Latencia media: " << jugadoresConectados.getLatenciaMedia() << " ms\n";

    if (estaActivo()) {
        cout << "--- Conectados ---\n";
        mostrarJugadoresConectados();
        cout << "--- En espera ---\n";
        mostrarJugadoresEnEspera();
    }
}

bool Servidor::expulsarJugador(cadena nombre) {
    bool encontrado = false;
    jugadoresConectados.eliminarPorNombre(nombre, encontrado);

    if (!encontrado) {
        // Buscar en la cola de espera
        int len = jugadoresEnEspera.longitud();
        for (int i = 0; i < len; i++) {
            Jugador j = jugadoresEnEspera.primero();
            jugadoresEnEspera.desencolar();
            if (strcmp(j.nombreJugador, nombre) != 0)
                jugadoresEnEspera.encolar(j);
            else
                encontrado = true;
        }
    } else {
        // Si había alguien esperando, moverlo a conectados
        if (!jugadoresEnEspera.esvacia()) {
            Jugador siguiente = jugadoresEnEspera.primero();
            jugadoresEnEspera.desencolar();
            conectarJugador(siguiente);
        }
    }

    return encontrado;
}

void Servidor::getNombreJuego(cadena nJ) {
    strcpy(nJ, nombreJuego);
}

int Servidor::getPuerto() {
    return puerto;
}

void Servidor::getLocalizacionGeografica(cadena lG) {
    strcpy(lG, localizacionGeografica);
}

int Servidor::getMaxJugadoresConectados() {
    return maxJugadoresConectados;
}

int Servidor::getMaxJugadoresEnEspera() {
    return maxJugadoresEnEspera;
}

int Servidor::getNumJugadoresConectados() {
    return jugadoresConectados.longitud();
}

int Servidor::getNumJugadoresEnEspera() {
    return jugadoresEnEspera.longitud();
}

void Servidor::exportarJugadoresConectados(Jugador *conectados) {
    jugadoresConectados.exportar(conectados);
}

void Servidor::exportarJugadoresEnEspera(Jugador *enEspera) {
    int len = jugadoresEnEspera.longitud();
    for (int i = 0; i < len; i++) {
        Jugador j = jugadoresEnEspera.primero();
        enEspera[i] = j;
        jugadoresEnEspera.desencolar();
        jugadoresEnEspera.encolar(j); // rotamos
    }
}
