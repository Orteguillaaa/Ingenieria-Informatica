// FICHERO TADCola.h
#ifndef COLA_H
#define COLA_H

#include "comun.h"

class cola
{
    Jugador *elementos; //elementos de la cola
    int inicio, fin; //principio y fin de la cola
    int Tama; //Capacidad de la tabla
    int ne; //Nº de elementos
public:
    cola(); // constructor de la clase
    ~cola(); // destructor de la clas
    void encolar(Jugador e);
    void desencolar();
    bool esvacia();
    Jugador primero() ;
    int longitud();
};
#endif // COLA_H
