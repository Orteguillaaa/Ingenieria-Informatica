#include <iostream>
#include <fstream>
#include <cstring>
#include "Torneo.h"

using namespace std;

void menuTorneo(Torneo &t);

void menuPrincipal(Torneo torneos[], int &numTorneos) {
    int opcion;
    do {
        cout << "\n------ MENU PRINCIPAL: CLUB DE GOLF ------" << endl;
        cout << "1. Mostrar torneos abiertos" << endl;
        cout << "2. Abrir nuevo torneo" << endl;
        cout << "3. Operar con torneo" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                bool alguno = false;
                for (int i = 0; i < numTorneos; i++) {
                    cadena nombre;
                    torneos[i].getNomTorneo(nombre);
                    cout << "Torneo: " << nombre << endl;
                    alguno = true;
                }
                if (!alguno) cout << "No hay torneos abiertos." << endl;
                break;
            case 2: {
                if (numTorneos < N) {
                    cadena nombre, fichero;
                    cout << "Nombre del torneo: ";
                    cin.ignore(); cin.getline(nombre, TAM_CADENA);
                    cout << "Nombre del fichero: ";
                    cin.getline(fichero, TAM_CADENA);

                    torneos[numTorneos].putNomTorneo(nombre);
                    torneos[numTorneos].putNomFichero(fichero);
                    torneos[numTorneos].putNumGolfistas(0);
                    torneos[numTorneos].CrearFichero(fichero);

                    fstream fTorneos("TORNEOS.dat", ios::binary | ios::app);
                    if (fTorneos) {
                        TorneoAux aux;
                        strcpy(aux.nT, nombre);
                        strcpy(aux.nF, fichero);
                        aux.nG = 0;
                        fTorneos.write((char*)&aux, sizeof(TorneoAux));
                        fTorneos.close();
                    }
                    numTorneos++;
                } else {
                    cout << "Se ha alcanzado el maximo de torneos." << endl;
                }
                break;
            }
            case 3:
                if (numTorneos > 0) {
                    cout << "Seleccione torneo (0 a " << numTorneos - 1 << "): ";
                    int idx;
                    cin >> idx;
                    if (idx >= 0 && idx < numTorneos) {
                        menuTorneo(torneos[idx]);
                    } else {
                        cout << "Indice fuera de rango." << endl;
                    }
                } else {
                    cout << "No hay torneos disponibles." << endl;
                }
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 4);
}

void menuTorneo(Torneo &t) {
    int opcion;
    do {
        cout << "\n------ MENU TORNEO ------" << endl;
        cout << "1. Mostrar golfistas por handicap o todos" << endl;
        cout << "2. Inscribir golfista" << endl;
        cout << "3. Consultar golfista" << endl;
        cout << "4. Modificar golfista" << endl;
        cout << "5. Eliminar golfista" << endl;
        cout << "6. Mostrar clasificacion" << endl;
        cout << "7. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                float hdcp;
                cout << "Introduce handicap a consultar (-1 para todos): ";
                cin >> hdcp;
                t.mostrar(hdcp);
                break;
            }
            case 2: {
                Golfista g;
                cout << "Licencia: ";
                cin.ignore(); cin.getline(g.licencia, TAM_CADENA);
                cout << "Handicap: ";
                cin >> g.handicap;
                cin.ignore();
                cout << "Nombre: "; cin.getline(g.nombre, TAM_CADENA);
                cout << "Apellidos: "; cin.getline(g.apellidos, TAM_CADENA);
                g.golpes = 0; g.resultado = 0;
                if (t.buscar(g.licencia) == -1) {
                    t.insertar(g);
                } else {
                    cout << "Licencia duplicada." << endl;
                }
                break;
            }
            case 3: {
                cadena lic;
                cout << "Licencia: ";
                cin.ignore(); cin.getline(lic, TAM_CADENA);
                int pos = t.buscar(lic);
                if (pos != -1) {
                    Golfista g = t.consultar(pos);
                    cout << "Licencia: " << g.licencia << ", Nombre: " << g.nombre << " " << g.apellidos << ", Handicap: " << g.handicap << endl;
                } else {
                    cout << "No encontrado." << endl;
                }
                break;
            }
            case 4: {
                cadena lic;
                cout << "Licencia: ";
                cin.ignore(); cin.getline(lic, TAM_CADENA);
                int pos = t.buscar(lic);
                if (pos != -1) {
                    Golfista g;
                    strcpy(g.licencia, lic);
                    cout << "Nuevo nombre: "; cin.getline(g.nombre, TAM_CADENA);
                    cout << "Nuevos apellidos: "; cin.getline(g.apellidos, TAM_CADENA);
                    g.handicap = t.consultar(pos).handicap;
                    g.golpes = 0; g.resultado = 0;
                    t.modificar(g, pos);
                } else {
                    cout << "Licencia no encontrada." << endl;
                }
                break;
            }
            case 5: {
                cadena lic;
                cout << "Licencia: ";
                cin.ignore(); cin.getline(lic, TAM_CADENA);
                int pos = t.buscar(lic);
                if (pos != -1) {
                    t.eliminar(pos);
                } else {
                    cout << "No encontrado." << endl;
                }
                break;
            }
            case 6:
                t.Clasificar();
                break;
            case 7:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 7);
}

int main() {
    Torneo torneos[N];
    int numTorneos = 0;

    fstream fichero("TORNEOS.dat", ios::binary | ios::in);
    if (fichero) {
        TorneoAux aux;
        while (fichero.read((char*)&aux, sizeof(TorneoAux))) {
            if (numTorneos < N) {
                torneos[numTorneos].putNomTorneo(aux.nT);
                torneos[numTorneos].putNomFichero(aux.nF);
                torneos[numTorneos].putNumGolfistas(aux.nG);
                numTorneos++;
            }
        }
        fichero.close();
    }

    menuPrincipal(torneos, numTorneos);
    return 0;
}
