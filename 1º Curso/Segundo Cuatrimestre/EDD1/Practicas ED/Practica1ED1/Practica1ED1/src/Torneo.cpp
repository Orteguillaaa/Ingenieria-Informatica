#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int PAR_CAMPO = 72;

struct Golfista {
    char licencia[20];
    float handicap;
    char nombre[30];
    char apellidos[50];
    int golpes;
    int resultado;
};

class Torneo {
private:
    fstream fichero;
    int numGolfistas;
    string nomFichero;
    string nomTorneo;

public:
    ~Torneo() {
        if (fichero.is_open())
            fichero.close();
    }

    Torneo() {
        numGolfistas = 0;
        nomFichero = "";
        nomTorneo = "";
    }

    int getNumGolfistas() {
        return numGolfistas;
    }

    void putNumGolfistas(int n) {
        numGolfistas = n;
    }

    void getNomTorneo(string& nombre) {
        nombre = nomTorneo;
    }

    void putNomTorneo(const string& nombre) {
        nomTorneo = nombre;
    }

    void getNomFichero(string& nombre) {
        nombre = nomFichero;
    }

    void putNomFichero(const string& nombre) {
        nomFichero = nombre;
    }

    void crearFichero(const char nombreFichero[]) {
        nomFichero = nombreFichero;
        fichero.open(nomFichero, ios::in | ios::out | ios::binary);

        if (!fichero) {
            // Fichero no existe, lo creamos vacío con 0 golfistas
            fichero.open(nomFichero, ios::out | ios::binary);
            int cero = 0;
            fichero.write(reinterpret_cast<char*>(&cero), sizeof(int));
            fichero.close();
            fichero.open(nomFichero, ios::in | ios::out | ios::binary);
            numGolfistas = 0;
        } else {
            // Leer número de golfistas existente
            fichero.seekg(0, ios::beg);
            fichero.read(reinterpret_cast<char*>(&numGolfistas), sizeof(int));
        }
    }

    Golfista consultar(int posicion) {
        Golfista g;
        if (posicion < 1 || posicion > numGolfistas) {
            cerr << "Posición no válida.\n";
            return g;
        }

        fichero.seekg(sizeof(int) + (posicion - 1) * sizeof(Golfista), ios::beg);
        fichero.read(reinterpret_cast<char*>(&g), sizeof(Golfista));
        return g;
    }

    int buscar(const string& licencia) {
        Golfista g;
        for (int i = 0; i < numGolfistas; ++i) {
            fichero.seekg(sizeof(int) + i * sizeof(Golfista), ios::beg);
            fichero.read(reinterpret_cast<char*>(&g), sizeof(Golfista));
            if (strcmp(g.licencia, licencia.c_str()) == 0) {
                return i + 1;
            }
        }
        return -1;
    }

    void mostrar(float hdcp) {
        Golfista g;
        for (int i = 0; i < numGolfistas; ++i) {
            fichero.seekg(sizeof(int) + i * sizeof(Golfista), ios::beg);
            fichero.read(reinterpret_cast<char*>(&g), sizeof(Golfista));
            if (hdcp == -1 || g.handicap == hdcp) {
                cout << "Licencia: " << g.licencia
                     << ", Nombre: " << g.nombre << " " << g.apellidos
                     << ", HCP: " << g.handicap
                     << ", Golpes: " << g.golpes
                     << ", Resultado: " << g.resultado << endl;
            }
        }
    }

    void insertar(Golfista g) {
        if (buscar(g.licencia) != -1) {
            cout << "Ya existe un golfista con esa licencia.\n";
            return;
        }

        vector<Golfista> lista;

        // Leer todos los golfistas
        for (int i = 0; i < numGolfistas; ++i) {
            Golfista temp;
            fichero.seekg(sizeof(int) + i * sizeof(Golfista), ios::beg);
            fichero.read(reinterpret_cast<char*>(&temp), sizeof(Golfista));
            lista.push_back(temp);
        }

        // Insertar el nuevo en orden de handicap
        lista.push_back(g);
        sort(lista.begin(), lista.end(), [](Golfista a, Golfista b) {
            return a.handicap < b.handicap;
        });

        // Escribir de nuevo el fichero
        fichero.close();
        fichero.open(nomFichero, ios::out | ios::binary);
        numGolfistas++;
        fichero.write(reinterpret_cast<char*>(&numGolfistas), sizeof(int));
        for (const auto& golfista : lista) {
            fichero.write(reinterpret_cast<const char*>(&golfista), sizeof(Golfista));
        }

        fichero.close();
        fichero.open(nomFichero, ios::in | ios::out | ios::binary);
    }

    void modificar(Golfista c, int posicion) {
        if (posicion < 1 || posicion > numGolfistas) {
            cout << "Golfista no encontrado.\n";
            return;
        }

        Golfista actual = consultar(posicion);
        c.handicap = actual.handicap; // No se puede modificar el handicap

        fichero.seekp(sizeof(int) + (posicion - 1) * sizeof(Golfista), ios::beg);
        fichero.write(reinterpret_cast<char*>(&c), sizeof(Golfista));
    }

    void eliminar(int posicion) {
        if (posicion < 1 || posicion > numGolfistas) {
            cout << "Posición inválida.\n";
            return;
        }

        vector<Golfista> lista;

        for (int i = 0; i < numGolfistas; ++i) {
            if (i != posicion - 1) {
                Golfista g;
                fichero.seekg(sizeof(int) + i * sizeof(Golfista), ios::beg);
                fichero.read(reinterpret_cast<char*>(&g), sizeof(Golfista));
                lista.push_back(g);
            }
        }

        numGolfistas--;
        fichero.close();
        fichero.open(nomFichero, ios::out | ios::binary);
        fichero.write(reinterpret_cast<char*>(&numGolfistas), sizeof(int));
        for (const auto& g : lista) {
            fichero.write(reinterpret_cast<const char*>(&g), sizeof(Golfista));
        }

        fichero.close();
        fichero.open(nomFichero, ios::in | ios::out | ios::binary);
    }

    void Clasificar() {
        vector<Golfista> lista;

        for (int i = 0; i < numGolfistas; ++i) {
            Golfista g;
            fichero.seekg(sizeof(int) + i * sizeof(Golfista), ios::beg);
            fichero.read(reinterpret_cast<char*>(&g), sizeof(Golfista));

            g.resultado = g.golpes - PAR_CAMPO;
            lista.push_back(g);
        }

        sort(lista.begin(), lista.end(), [](Golfista a, Golfista b) {
            return a.resultado < b.resultado;
        });

        cout << "\n--- Clasificación Final del Torneo ---\n";
        for (const auto& g : lista) {
            cout << g.nombre << " " << g.apellidos
                 << " | Golpes: " << g.golpes
                 << " | Resultado: " << (g.resultado == 0 ? "PAR" : to_string(g.resultado))
                 << endl;
        }
    }
};
