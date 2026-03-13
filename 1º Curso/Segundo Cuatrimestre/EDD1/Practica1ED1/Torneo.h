#ifndef TORNEO_H_INCLUDED
#define TORNEO_H_INCLUDED
#include"Comun.h"
#include"Golfistas.h"
#include <fstream>

using namespace std;

class Torneo
{
fstream fichero;
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
void crearFichero(cadena nombreFichero);
void mostrar(float hdcp);
Golfista consultar(int posicion);
int buscar(cadena licencia);
void insertar(Golfista g);
void modificar(Golfista c, int posicion);
void eliminar(int posicion);
void Clasificar();
void Cerrar();
};

#endif // TORNEO_H_INCLUDED
