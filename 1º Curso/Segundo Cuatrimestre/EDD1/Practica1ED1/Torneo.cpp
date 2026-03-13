#include <iostream>
#include"Torneo.h"
#include <cstring>
#include"Comun.h"
#include <fstream>
#include"Clasificacion.h"
#include <ctime>
#include<cstdlib>
using namespace std;

Torneo::Torneo(){
    numGolfistas=0;
    cadena vacio="";
    strcpy(nomFichero, vacio);
    strcpy(nomTorneo, vacio);
}

Torneo::~Torneo(){
    fichero.close();
}

void Torneo::crearFichero(cadena n){
    fichero.open(n, ios::binary|ios::in|ios::out);
    if (fichero.fail()){
        cout<<"Error al cargar el archivo, se va a crear otro con el nombre de fichero "<<n<<endl;
        fichero.close();
        fichero.open(n, ios::binary|ios::out);
        fichero.close();
        if(!fichero.fail()){
            fichero.open(n, ios::binary|ios::in|ios::out);
            numGolfistas=0;
            fichero.write((char*) &numGolfistas, sizeof(int));
       }
      }
     else{
        fichero.read((char*) &numGolfistas, sizeof(int));
    }
    strcpy(nomFichero, n);
}

Golfista Torneo::consultar(int pos){
    fichero.clear();
    fichero.seekg(sizeof(int), ios::beg);
    Golfista infoGolfistas;
    for (int i=0; i<numGolfistas; i++){
        fichero.read((char*) &infoGolfistas, sizeof(Golfista));
        if(pos==i+1){
        cout<<"Licencia: "<<infoGolfistas.licencia<<endl;
        cout<<"Handicap: "<<infoGolfistas.handicap<<endl;
        cout<<"Nombre: "<<infoGolfistas.nombre<<endl;
        cout<<"Apellidos: "<<infoGolfistas.apellidos<<endl;
        cout<<"Golpes: "<<infoGolfistas.golpes<<endl;
        cout<<"Resultado: "<<infoGolfistas.resultado<<"\n\n";}
        }
}




int Torneo::getNumGolfistas(){
 return numGolfistas;
}

void Torneo::putNumGolfistas(int nGolf){
    numGolfistas=nGolf;
    fichero.seekg(0, ios::beg);
    fichero.write((char*) &nGolf, sizeof(int));
}

void Torneo::getNomTorneo(cadena nom){
    strcpy(nom, nomTorneo);
}

void Torneo::getNomFichero(cadena nom){
    strcpy(nom, nomFichero);
}

void Torneo::putNomTorneo(cadena nom){
    strcpy(nomTorneo, nom);
}

void Torneo::putNomFichero(cadena nom){
    strcpy(nomFichero, nom);
}


int Torneo::buscar(cadena licen){
    fichero.clear();
    fichero.seekg(sizeof(int), ios::beg);
    Golfista infoGolfistas;
    bool encontrado=true;
    int cont=0, comparador;
    for (int i=0; i<numGolfistas; i++){
        fichero.read((char*) &infoGolfistas, sizeof(Golfista));
        comparador=strcmp(licen, infoGolfistas.licencia);
        if(comparador==0){
            encontrado=false;
        }
    }
    if(encontrado){
        return -1;
    }
    else{
        return cont;
    }
}

void Torneo::mostrar(float hd){
    fichero.clear();
    fichero.seekg(sizeof(int), ios::beg);
    cout <<"Numero de golfistas: "<<numGolfistas<<endl<<endl;
    Golfista infoGolfistas;
    for (int i=0; i<numGolfistas; i++){
        fichero.read((char*) &infoGolfistas, sizeof(Golfista));
        if(hd==-1){
        cout<<"Licencia: "<<infoGolfistas.licencia<<endl;
        cout<<"Handicap: "<<infoGolfistas.handicap<<endl;
        cout<<"Nombre: "<<infoGolfistas.nombre<<endl;
        cout<<"Apellidos: "<<infoGolfistas.apellidos<<endl;
        cout<<"Golpes: "<<infoGolfistas.golpes<<endl;
        cout<<"Resultado: "<<infoGolfistas.resultado<<endl<<endl;}
        else{
            if(hd==infoGolfistas.handicap){
            cout<<"Licencia: "<<infoGolfistas.licencia<<endl;
            cout<<"Handicap: "<<infoGolfistas.handicap<<endl;
            cout<<"Nombre: "<<infoGolfistas.nombre<<endl;
            cout<<"Apellidos: "<<infoGolfistas.apellidos<<endl;
            cout<<"Golpes: "<<infoGolfistas.golpes<<endl;
            cout<<"Resultado: "<<infoGolfistas.resultado<<endl<<endl;
            }
        }
    }
}



void Torneo::insertar(Golfista nuevo){
    fichero.clear();
    int cont=1;
    bool parar=true;
    Golfista infoGolfista, sig;
    fichero.seekg(sizeof(int), ios::beg);
    do{
    if(!fichero.read((char*) &infoGolfista, sizeof(Golfista))){
        cout <<"Error al leer el fichero en la posicion"<<cont<<endl;
        return;
    }
    if(infoGolfista.handicap<=nuevo.handicap){
    cont++;
    }
    else{
        parar=false;
    }
    }while(parar && cont <= numGolfistas);
    if(numGolfistas!=0){
        for (int i=numGolfistas; i>=cont;i--){
            fichero.seekp(((i-1) * sizeof(Golfista) + sizeof(int)), ios::beg);
            if(!fichero.read((char*) &sig, sizeof(Golfista))){
            cout <<"Error al leer el fichero en la posicion"<<i<<endl;
            return;
            }
            fichero.seekp((i * sizeof(Golfista) + sizeof(int)), ios::beg);
            if(!fichero.write((char*) &sig, sizeof(Golfista))){
            cout <<"Error al escribir el fichero en la posicion"<<i<<endl;
            return;
            }
        }
    }
    fichero.seekp((cont * sizeof(Golfista) + sizeof(int)), ios::beg);
    if(!fichero.write((char*)&nuevo,sizeof(Golfista))){
        cout <<"Error al escribir el nuevo golfista al fichero"<<endl;
        return;
    }
    numGolfistas++;
    fichero.seekp(0, ios::beg);
    if(!fichero.write((char*)&numGolfistas,sizeof(int))){
        cout <<"Error al actualizar el nuevo numero de golfistas"<<endl;
        return;
    }
}

void Torneo::eliminar(int pos){
    if(pos>numGolfistas){
        cout<<"Opcion no valida\n";
    }
    else{
    fichero.clear();
    bool parar=true;
    Golfista sig;
    fichero.seekg(sizeof(int), ios::beg);
    if(numGolfistas!=0){
        for (int i=pos; i<numGolfistas;i++){
            fichero.seekp((i * sizeof(Golfista) + sizeof(int)), ios::beg);
            if(!fichero.read((char*) &sig, sizeof(Golfista))){
            cout <<"Error al leer el fichero en la posicion"<<i<<endl;
            return;
            }
            fichero.seekp(((i-1) * sizeof(Golfista) + sizeof(int)), ios::beg);
            if(!fichero.write((char*) &sig, sizeof(Golfista))){
            cout <<"Error al escribir el fichero en la posicion"<<i<<endl;
            return;
            }
        }
    }
    numGolfistas--;
    fichero.seekp(0, ios::beg);
    if(!fichero.write((char*)&numGolfistas,sizeof(int))){
        cout <<"Error al actualizar el nuevo numero de golfistas"<<endl;
        return;
    }
    }
}

void Torneo::modificar(Golfista cambio, int pos){
    Golfista infoGolfistas;
    if((pos<=numGolfistas)&&(0<=pos)){
        fichero.seekg(((pos-1) * sizeof(Golfista)) + sizeof(int), ios::beg);
        fichero.read((char*) &infoGolfistas, sizeof(Golfista));
        cambio.handicap=infoGolfistas.handicap;
        fichero.seekp(((pos) * sizeof(Golfista)) + sizeof(int), ios::beg);
        fichero.write((char*) &cambio, sizeof(Golfista));
    }else{cout<<"\nEsa posicion no existe";}
}




void Torneo::Clasificar(){
    srand(time(NULL));
    Clasificacion clas;
    Jugador jug;
    Golfista gol;
    for(int i=0;i<numGolfistas;i++){
       gol=consultar(i+1);
       gol.golpes=rand()%100;
       gol.resultado=gol.golpes-72;
       clas.anadirjugador({i, gol.resultado});
       modificar(gol, i+1);
    }
    clas.ordenar();
    for(int i=0;i<clas.numjugadores();i++){
        jug=clas.consultar(i);
        gol=consultar(jug.indice+1);
        cout<<"Nombre: "<<gol.nombre<<" "<<gol.apellidos<<", Resultado: "<<gol.resultado<<endl;
    }
    cout<<"\n";
}

void Torneo::Cerrar(){
    fichero.close();
}
