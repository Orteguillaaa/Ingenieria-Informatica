#include <iostream>
#include "Torneo.h"
#include"Comun.h"
#include <fstream>
#include <cstring>
#include"Clasificacion.h"

using namespace std;

int main()
{
    Torneo tor;
        TorneoAux tabla[N], torneoActual;
        int elec, nTorneos, elecTorneos,general;
        cadena copiar;
        fstream fichTorneo;
        bool valido=false;
        Golfista pasar;
        fichTorneo.open("TORNEOS.dat", ios::binary|ios::in|ios::out);
        if(!fichTorneo){
        cout<<"Error al abrir el fichero";
                                            }
    fichTorneo.seekg(0, ios::end);
    nTorneos=(fichTorneo.tellg())/(sizeof(TorneoAux));
    cout<<"Bienvenido:\n\n";

    do{
        fichTorneo.seekg(0, ios::beg);
        for(int i=0;i<nTorneos;i++){
            fichTorneo.read((char*) &tabla[i], sizeof(TorneoAux));
        }
                cout<<"CLUB DE GOLF\n--------------------------------\nTorneos: "<<nTorneos<<"\n\n1) Listado de Torneos Abiertos\n2) Alta Torneo\n3) Elegir Torneo\n4) Salir\n\Indique la opcion deseada :\n";
        cin>>elec;
        cout<<endl;
        switch (elec){
            case 1:{
                for(int i=0;i<nTorneos;i++){
                    cout<<"Numero de golfistas: "<<tabla[i].nGolfistas<<endl;
                    cout<<"Nombre del torneo: "<<tabla[i].nTorneo<<endl;
                    cout<<"Nombre del fichero: "<<tabla[i].nFichero<<endl<<endl;
                }
                break;}
            case 2:{
                    if(nTorneos<N){
                    cout<<"Nombre del torneo: ";
                    cin>>copiar;
                    strcpy(tabla[nTorneos+1].nTorneo, copiar);
                    cout<<"Nombre del fichero: ";
                    cin>>copiar;
                    strcpy(tabla[nTorneos+1].nFichero, copiar);
                    tabla[nTorneos+1].nGolfistas=0;
                    fichTorneo.seekg(nTorneos * sizeof(TorneoAux), ios::beg);
                    fichTorneo.write((char*) &tabla[nTorneos+1], sizeof(TorneoAux));
                    nTorneos++;
                    }
                    else{cout<<"Este es el numero maximo,no se pueden anadir mas\n\n";}
                break;}
            case 3:{
                valido=false;
                do{
                    cout<<"Numero del torneo: ";
                    cin>>elecTorneos;
                    cout<<endl<<endl;
                    if(elecTorneos<=nTorneos&&elecTorneos>0){
                        valido=true;
                        elecTorneos--;
                        torneoActual=tabla[elecTorneos];}
                    else{
                        cout<<"Torneo no valido, intentelo de nuevo\n\n";
                }}while(!valido);
                tor.crearFichero(torneoActual.nFichero);
                tor.putNomFichero(torneoActual.nFichero);
                tor.putNomTorneo(torneoActual.nTorneo);
                tor.putNumGolfistas(torneoActual.nGolfistas);
                do{
                        cout << "Torneo "<<torneoActual.nTorneo << endl;
                        cout << "--------------------------------------------" << endl;
                        cout << "Golfistas: " << torneoActual.nGolfistas << endl << endl;
                        cout << "1) Consulta de inscripciones" << endl;
                        cout << "2) Inscripcion al torneo" << endl;
                        cout << "3) Busqueda de una inscripcion" << endl;
                        cout << "4) Modificar datos de una inscripcion" << endl;
                        cout << "5) Eliminar una inscripcion" << endl;
                        cout << "6) Mostrar Resultados del Torneo" << endl;
                        cout << "7) Salir" << endl << endl;
                        cin>>elecTorneos;
                    switch (elecTorneos){
                        case 1:{
                            cout<<"Indique el handicap: ";
                            cin>>general;
                            cout<<"\n\n";
                            tor.mostrar(general);
                            break;
                        }
                        case 2:{
                            cout<<"Indique la licencia: ";
                            do{
                                cin>>pasar.licencia;
                                general=tor.buscar(pasar.licencia);
                                if(general!=-1){
                                    cout<<"\n\nError, existen dos licencias iguales, introduzca otra licencia diferente: ";
                                }
                            }while(general!=-1);
                            cout<<"\n\nHandicap: ";
                            cin>>pasar.handicap;
                            cout<<"\n\nNombre: ";
                            cin>>pasar.nombre;
                            cout<<"\n\nApellido: ";
                            cin>>pasar.apellidos;
                            pasar.golpes=0;
                            pasar.resultado=0;
                            tor.insertar(pasar);
                            cout<<"\n\n";
                            break;
                        }
                        case 3:{
                            cout<<"Licencia: ";
                            cin>>copiar;
                            general=tor.buscar(copiar);
                            if(general==-1){
                                cout<<"\n\nError, no existe el golfista \n\n";
                            }
                            else{
                                cout<<"\n\n";
                                tor.consultar(general);
                                cout<<"\n\n";
                            }
                            break;
                        }
                        case 4:{
                            cout<<"Licencia: ";
                            cin>>pasar.licencia;
                            general=tor.buscar(pasar.licencia);
                            if(general==-1){
                                cout<<"\n\nError, no existe el golfista \n\n";
                            }
                            else{
                            cout<<"\n\nNombre: ";
                            cin>>pasar.nombre;
                            cout<<"\n\nApellido: ";
                            cin>>pasar.apellidos;
                            pasar.golpes=0;
                            pasar.resultado=0;
                            pasar.handicap=0;
                            tor.modificar(pasar, general);
                            }
                            break;
                        }
                        case 5:{
                            cout<<"Licencia: ";
                            cin>>copiar;
                            general=tor.buscar(copiar);
                            if(general==-1){
                                cout<<"\n\nError, no existe el golfista \n\n";
                            }
                            tor.eliminar(general);
                            break;
                        }
                        case 6:{

                        }
                        case 7:{
                            tor.Cerrar();
                            break;
                        }
                        default:{
                            cout<<"Opcion no valida\n\n";
                            break;}
                    }
                }while(elecTorneos!=7);
                break;}
            case 4:{
                cout<<"Adios";
                break;}
            default:{
                cout<<"Opcion no valida\n\n";
                break;}
        }
    }while(elec!=4);
    fichTorneo.close();
    return 0;
}



/*
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "Torneo.h"
#include "Comun.h"
#include "Clasificacion.h"

using namespace std;

int main() {
    // 1) Cargar TORNEOS.dat solo al inicio
    vector<TorneoAux> torneosEnMemoria;
    {
        ifstream entrada("TORNEOS.dat", ios::binary);
        if (entrada) {
            TorneoAux temp;
            while (entrada.read(reinterpret_cast<char*>(&temp), sizeof(TorneoAux))) {
                torneosEnMemoria.push_back(temp);
            }
            entrada.close();
        }
    }

    Torneo gestor;
    Golfista participante;
    cadena buffer;
    int opcion, idxTorneo, filtro, pos;

    do {
        cout << "\n=== CLUB DE GOLF (MEMORIA) ===\n";
        cout << "1) Listar torneos (" << torneosEnMemoria.size() << ")\n";
        cout << "2) Alta de torneo\n";
        cout << "3) Operar en torneo\n";
        cout << "4) Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                for (size_t i = 0; i < torneosEnMemoria.size(); ++i) {
                    auto &t = torneosEnMemoria[i];
                    cout << i+1 << ") " << t.nTorneo
                         << "  |  Inscritos: " << t.nGolfistas
                         << "  |  Archivo: " << t.nFichero << "\n";
                }
                break;
            }
            case 2: {
                if (torneosEnMemoria.size() < N) {
                    TorneoAux nuevo{};
                    cout << "Nombre torneo: ";
                    cin >> buffer;
                    strcpy(nuevo.nTorneo, buffer);
                    cout << "Archivo datos: ";
                    cin >> buffer;
                    strcpy(nuevo.nFichero, buffer);
                    nuevo.nGolfistas = 0;
                    torneosEnMemoria.push_back(nuevo);
                } else {
                    cout << "Límite de torneos alcanzado.\n";
                }
                break;
            }
            case 3: {
                if (torneosEnMemoria.empty()) {
                    cout << "No hay torneos disponibles.\n";
                    break;
                }
                cout << "Elige torneo (1-" << torneosEnMemoria.size() << "): ";
                cin >> idxTorneo;
                if (idxTorneo < 1 || idxTorneo > (int)torneosEnMemoria.size()) {
                    cout << "Selección inválida.\n";
                    break;
                }

                // Inicializar gestor con ese torneo
                TorneoAux &sel = torneosEnMemoria[idxTorneo - 1];
                gestor.crearFichero(sel.nFichero);
                gestor.putNomTorneo(sel.nTorneo);
                gestor.putNomFichero(sel.nFichero);
                gestor.putNumGolfistas(sel.nGolfistas);

                int subop;
                do {
                    cout << "\n-- TORNEO: " << sel.nTorneo << " --\n";
                    cout << "1) Ver inscritos (-1 para todos)\n";
                    cout << "2) Inscribir golfista\n";
                    cout << "3) Buscar golfista\n";
                    cout << "4) Modificar golfista\n";
                    cout << "5) Eliminar golfista\n";
                    cout << "6) Mostrar clasificación\n";
                    cout << "7) Volver\n";
                    cout << "Opción: ";
                    cin >> subop;

                    switch (subop) {
                        case 1:
                            cout << "Handicap (-1 para todos): ";
                            cin >> filtro;
                            gestor.mostrar(filtro);
                            break;
                        case 2:
                            // Evitar duplicados
                            do {
                                cout << "Licencia: ";
                                cin >> participante.licencia;
                                pos = gestor.buscar(participante.licencia);
                                if (pos != -1)
                                    cout << "Licencia ya existe. Prueba otra.\n";
                            } while (pos != -1);
                            cout << "Handicap: ";   cin >> participante.handicap;
                            cout << "Nombre: ";     cin >> participante.nombre;
                            cout << "Apellidos: ";  cin >> participante.apellidos;
                            participante.golpes = participante.resultado = 0;
                            gestor.insertar(participante);
                            sel.nGolfistas = gestor.getNumGolfistas();
                            break;
                        case 3:
                            cout << "Licencia a buscar: ";
                            cin >> buffer;
                            pos = gestor.buscar(buffer);
                            if (pos == -1) cout << "No encontrado.\n";
                            else gestor.consultar(pos);
                            break;
                        case 4:
                            cout << "Licencia a modificar: ";
                            cin >> participante.licencia;
                            pos = gestor.buscar(participante.licencia);
                            if (pos == -1) cout << "No existe.\n";
                            else {
                                cout << "Nuevo nombre: ";    cin >> participante.nombre;
                                cout << "Nuevos apellidos: "; cin >> participante.apellidos;
                                participante.golpes = participante.resultado = 0;
                                gestor.modificar(participante, pos);
                            }
                            break;
                        case 5:
                            cout << "Licencia a eliminar: ";
                            cin >> buffer;
                            pos = gestor.buscar(buffer);
                            if (pos == -1) cout << "No existe.\n";
                            else {
                                gestor.eliminar(pos);
                                sel.nGolfistas = gestor.getNumGolfistas();
                            }
                            break;
                        case 6:
                            gestor.Clasificar();
                            break;
                        case 7:
                            gestor.Cerrar();
                            break;
                        default:
                            cout << "Opción inválida.\n";
                    }
                } while (subop != 7);
                break;
            }
            case 4:
                cout << "Saliendo. No se guardan cambios en disco.\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 4);

    return 0;
}
*/
