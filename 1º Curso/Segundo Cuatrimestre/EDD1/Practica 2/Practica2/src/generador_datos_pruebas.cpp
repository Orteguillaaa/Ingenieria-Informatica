#include "generador_datos_pruebas.h"
#include <cstring>

// Crea y devuelve un jugador con los parámetros dados
Jugador creaJugador(cadena n, int id, bool c, int l, long p, cadena pa) {
    Jugador r;
    strcpy(r.nombreJugador, n);
    r.ID = id;
    r.activo = c;
    r.latencia = l;
    r.puntuacion = p;
    strcpy(r.pais, pa);
    return r;
}

// Inicializa servidores y jugadores en el objeto gestor pasado como argumento
void inicializarDatosPruebas(GestorServidores &gS) {
    // Jugadores
    Jugador j1 = creaJugador("Jan27", 23002, false, 25, 23000, "Italia");
    Jugador j2 = creaJugador("Rocio_Roma", 34011, false, 32, 27000, "Francia");
    Jugador j3 = creaJugador("LuisG", 33007, false, 15, 21000, "Reino Unido");
    Jugador j4 = creaJugador("Maria005", 45055, false, 28, 24400, "Francia");
    Jugador j5 = creaJugador("PacoRomero", 35054, false, 18, 14445, "España");
    Jugador j6 = creaJugador("Carmen56", 35062, false, 42, 12305, "Estonia");
    Jugador j7 = creaJugador("LouisX_23", 25022, false, 65, 45405, "Estonia");
    Jugador j8 = creaJugador("O-O_Yep", 33121, false, 12, 11345, "Italia");
    Jugador j9 = creaJugador("PacoPePe", 22012, false, 32, 23422, "España");
    Jugador j10 = creaJugador("Wilson2001", 21252, false, 23, 4345, "Reino Unido");

    // Servidores
    gS.desplegarServidor("175.23.34.66", "DemonSlayer 2", 320002, 2, 3, 4, "Moldavia");
    gS.conectarServidor("175.23.34.66");

    gS.desplegarServidor("systemrs.server0092.fr", "DemonSlayer 2", 320004, 2, 2, 6, "Francia");
    gS.conectarServidor("systemrs.server0092.fr");

    gS.desplegarServidor("systemrs.server0042.es", "Quake Heroes", 320082, 2, 2, 6, "España");
    gS.conectarServidor("systemrs.server0042.es");

    // Alojar jugadores
    cadena h;
    bool es;

    gS.alojarJugador(j1, "DemonSlayer 2", h, es);
    gS.alojarJugador(j2, "DemonSlayer 2", h, es);
    gS.alojarJugador(j3, "DemonSlayer 2", h, es);
    gS.alojarJugador(j4, "DemonSlayer 2", h, es);
    gS.alojarJugador(j5, "DemonSlayer 2", h, es);
    gS.alojarJugador(j6, "DemonSlayer 2", h, es);
    gS.alojarJugador(j7, "Quake Heroes", h, es);
    gS.alojarJugador(j8, "Quake Heroes", h, es);
    gS.alojarJugador(j9, "Quake Heroes", h, es);
    gS.alojarJugador(j10, "Quake Heroes", h, es);
}
