#include"Clasificacion.h"
#include"Comun.h"
#include <iostream>
#include <cstring>

using namespace std;

Clasificacion::Clasificacion(){
    elementos=new Jugador[SALTO];
    tamano=SALTO;
    Jugadores=0;
}

int Clasificacion::numjugadores(){
    return Jugadores;
}

void Clasificacion::anadirjugador(Jugador nuevo){
    if(Jugadores==tamano){
        tamano += SALTO;
        Jugador* nuevaTablilla=new Jugador[tamano];
        for(int i=0; i<Jugadores; i++){
            nuevaTablilla[i]=elementos[i];
        }
        delete[] elementos;
        elementos=nuevaTablilla;
    }
    elementos[Jugadores]=nuevo;
    Jugadores++;
}


void Clasificacion::eliminar(int borrar){
    //En las tablas la primera pocision es 0, por lo tanto si queremos la primera pocision, se escribe uno y se borra la primera
    borrar--;
    for(int i=borrar;i<=Jugadores;i++){
        elementos[i].indice=elementos[i+1].indice;
        elementos[i].resultado=elementos[i+1].resultado;
    }
    Jugadores--;
}

void Clasificacion::ordenar(){
    Jugador tmp;
    for(int i=0; i<Jugadores; i++){
        for(int j=i+1; j<Jugadores; j++){
            if (elementos[i].resultado>elementos[j].resultado){
                tmp=elementos[i];
                elementos[i]=elementos[j];
                elementos[j]=tmp;
            }
        }

    }
}

Jugador Clasificacion::consultar(int n){
    return elementos[n-1];
}

bool Clasificacion::vacio(){
    if(Jugadores==0){
        return true;
    }
    else{
        return false;
    }
}

Clasificacion::~Clasificacion(){}
