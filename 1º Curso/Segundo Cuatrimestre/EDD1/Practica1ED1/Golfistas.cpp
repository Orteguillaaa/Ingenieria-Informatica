/*
#include "Golfistas.h"
#include <iostream>
#include <cstring>

// Constructor por defecto
Golfista::Golfista() {
    strcpy(licencia, "");  // Inicializa la licencia como una cadena vacía
    handicap = 0.0;
    strcpy(nombre, "");
    strcpy(apellidos, "");
    golpes = 0;
    resultado = 0;
}

// Constructor con parámetros
Golfista::Golfista(const char* lic, float hcp, const char* nom, const char* ape) {
    strcpy(licencia, lic);
    handicap = hcp;
    strcpy(nombre, nom);
    strcpy(apellidos, ape);
    golpes = 0;
    resultado = 0;
}

// Método para mostrar información del golfista
void Golfista::mostrar() const {
    std::cout << "Licencia: " << licencia << std::endl;
    std::cout << "Nombre: " << nombre << " " << apellidos << std::endl;
    std::cout << "Handicap: " << handicap << std::endl;
    std::cout << "Golpes: " << golpes << std::endl;
    std::cout << "Resultado: " << resultado << std::endl;
}

// Método para modificar el golfista (excluyendo el hándicap)
void Golfista::modificar(const char* nom, const char* ape) {
    strcpy(nombre, nom);
    strcpy(apellidos, ape);
}

// Método para actualizar los golpes
void Golfista::actualizarGolpes(int nuevosGolpes) {
    golpes = nuevosGolpes;
    resultado = golpes - 72;  // Se asume que el par del campo es 72
}








MEJORAS CODIGO

Mejoras y correcciones sugeridas:
1. buscar(): no actualiza cont
cpp
Copiar
Editar
int cont=0; // pero nunca se incrementa
✅ Solución:

cpp
Copiar
Editar
for (int i = 0; i < numGolfistas; i++) {
    fichero.read((char*)&infoGolfistas, sizeof(Golfista));
    if (strcmp(licen, infoGolfistas.licencia) == 0) {
        return i;
    }
}
return -1;
2. En consultar(), el return está ausente
Aunque se imprimen los datos del golfista, la función debe devolver el objeto:

cpp
Copiar
Editar
Golfista Torneo::consultar(int pos) {
    // ...
    return infoGolfistas; // <--- Falta esto
}
3. modificar(): error en el desplazamiento
La posición se calcula mal, estás escribiendo en pos en vez de pos - 1:

cpp
Copiar
Editar
fichero.seekp(((pos - 1) * sizeof(Golfista)) + sizeof(int), ios::beg);
4. eliminar(): falta un continue si no se encuentra licencia
En main(), opción 5, si el golfista no existe, se intenta eliminar igualmente:

cpp
Copiar
Editar
if(general==-1){
    cout<<"\n\nError, no existe el golfista \n\n";
    continue; // <- añadir esto
}
5. Clasificar() escribe resultados aleatorios en golpes, pero no resetea si se corre dos veces.
Podrías añadir una validación para evitar que se re-clasifique si ya se hizo.

6. Clasificacion::~Clasificacion() vacío
Podrías liberar la memoria dinámica:

cpp
Copiar
Editar
Clasificacion::~Clasificacion(){
    delete[] elementos;
}
7. Menú: Opción 6 del torneo no ejecuta nada
Le falta el cuerpo al case 6:

cpp
Copiar
Editar
case 6: {
    tor.Clasificar();
    break;
}





MODIFICACION

🛠️ 1. Modificar el método eliminar de Torneo
En lugar de eliminar directamente, guardaremos una copia del golfista eliminado en un vector<Golfista> (para eso necesitaremos <vector> en el .cpp).

🛠️ 2. Añadir opción en el menú del torneo
Una nueva opción que, al seleccionarla, guarde todos los golfistas eliminados en un fichero binario nuevo, por ejemplo, llamado "ELIMINADOS.dat".

✅ Cambios detallados paso a paso:
1. En Torneo.h, añade:
cpp
Copiar
Editar
#include <vector>

class Torneo
{
    fstream fichero;
    int numGolfistas;
    cadena nomFichero;
    cadena nomTorneo;

    std::vector<Golfista> eliminados; // <-- Añadido

public:
    ...
    void guardarEliminados(); // <-- Nuevo método
};
2. En Torneo.cpp, modifica el método eliminar así:
cpp
Copiar
Editar
void Torneo::eliminar(int pos){
    if(pos > numGolfistas || pos < 1){
        cout << "Opcion no valida\n";
        return;
    }

    fichero.clear();
    Golfista g;

    // Leer el golfista que se va a eliminar
    fichero.seekg(((pos - 1) * sizeof(Golfista)) + sizeof(int), ios::beg);
    fichero.read((char*)&g, sizeof(Golfista));
    eliminados.push_back(g); // Guardarlo en el vector

    // Desplazar el resto
    Golfista siguiente;
    for (int i = pos; i < numGolfistas; i++) {
        fichero.seekg((i * sizeof(Golfista)) + sizeof(int), ios::beg);
        fichero.read((char*)&siguiente, sizeof(Golfista));

        fichero.seekp(((i - 1) * sizeof(Golfista)) + sizeof(int), ios::beg);
        fichero.write((char*)&siguiente, sizeof(Golfista));
    }

    numGolfistas--;
    fichero.seekp(0, ios::beg);
    fichero.write((char*)&numGolfistas, sizeof(int));
}
3. Implementar guardarEliminados:
cpp
Copiar
Editar
void Torneo::guardarEliminados() {
    if (eliminados.empty()) {
        cout << "No hay golfistas eliminados para guardar.\n";
        return;
    }

    ofstream archivo("ELIMINADOS.dat", ios::binary | ios::app);
    if (!archivo) {
        cout << "Error al crear/abrir el archivo de eliminados.\n";
        return;
    }

    for (const auto& g : eliminados) {
        archivo.write((char*)&g, sizeof(Golfista));
    }

    archivo.close();
    eliminados.clear(); // Limpiar después de guardar
    cout << "Golfistas eliminados guardados en ELIMINADOS.dat\n";
}
4. En el main(), dentro del menú de torneo, añade una nueva opción:
Después de la opción 6:

cpp
Copiar
Editar
cout << "7) Guardar eliminados en fichero" << endl;
cout << "8) Salir" << endl << endl;
Y ajusta el switch:

cpp
Copiar
Editar
case 7: {
    tor.guardarEliminados();
    break;
}
case 8: {
    tor.Cerrar();
    break;
}
Y ajusta también el do-while para que termine con elecTorneos != 8

🧩 Cambios en el Menú del Torneo:
🔁 Antes:
cpp
Copiar
Editar
                        cout << "6) Mostrar Resultados del Torneo" << endl;
                        cout << "7) Salir" << endl << endl;
✅ Ahora:
cpp
Copiar
Editar
                        cout << "6) Mostrar Resultados del Torneo" << endl;
                        cout << "7) Guardar eliminados en fichero" << endl;
                        cout << "8) Salir" << endl << endl;
🧠 Cambios en el switch:
🔁 Antes:
cpp
Copiar
Editar
case 6: {
    tor.Clasificar();
    break;
}
case 7: {
    tor.Cerrar();
    break;
}
✅ Ahora:
cpp
Copiar
Editar
case 6: {
    tor.Clasificar();
    break;
}
case 7: {
    tor.guardarEliminados();
    break;
}
case 8: {
    tor.Cerrar();
    break;
}
🔄 Y finalmente, ajusta el do-while:
🔁 Antes:
cpp
Copiar
Editar
} while(elecTorneos != 7);
✅ Ahora:
cpp
Copiar
Editar
} while(elecTorneos != 8);

Con estos cambios, ahora puedes eliminar golfistas como antes, y en cualquier momento usar la opción 7 del menú para guardar todos los eliminados en un fichero binario llamado ELIMINADOS.dat.
*/
