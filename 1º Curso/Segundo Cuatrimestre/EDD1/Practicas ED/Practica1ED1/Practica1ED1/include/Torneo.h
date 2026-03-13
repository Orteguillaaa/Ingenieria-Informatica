#ifndef TORNEO_H
#define TORNEO_H

#include <fstream>
#include "Golfista.h"
#include "Clasificacion.h"

class Torneo {
    std::fstream fichero;
    int numGolfistas;
    cadena nomFichero;
    cadena nomTorneo;

public:
    ~Torneo();
    Torneo();
    int getNumGolfistas();
    void putNumGolfistas(int n);
    void getNomTorneo(cadena nombre);
    void getNomFichero(cadena nombre);
    void putNomTorneo(cadena nombre);
    void putNomFichero(cadena nombre);
    void CrearFichero(char nombreFichero[]);
    void mostrar(float hdcp);
    Golfista consultar(int posicion);
    int buscar(cadena licencia);
    void insertar(Golfista g);
    void modificar(Golfista c, int posicion);
    void eliminar(int posicion);
    void Clasificar();
};

#endif
