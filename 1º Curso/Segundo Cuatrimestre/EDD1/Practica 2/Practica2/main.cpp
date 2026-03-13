#include <iostream>
#include "GestorServidores.h"
#include "generador_datos_pruebas.h"

using namespace std;

int main() {
    GestorServidores gestor;
    inicializarDatosPruebas(gestor);
    int opcion;

    do {
        cout << "\nGESTOR DE SERVIDORES v1.0" << endl;
        cout << "--------------------------------------------------------------------------------------------------" << endl;
        cout << "1. Mostrar servidor." << endl;
        cout << "2. Crear servidor." << endl;
        cout << "3. Eliminar servidor." << endl;
        cout << "4. Activar servidor." << endl;
        cout << "5. Desactivar servidor." << endl;
        cout << "6. Programar mantenimiento de servidor." << endl;
        cout << "7. Conectar jugador." << endl;
        cout << "8. Expulsar jugador." << endl;
        cout << "9. Salir." << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        cadena dir, juego, pais, nombreJugador;
        int id, maxC, maxE, puerto;
        Jugador j;
        bool resultado, enEspera;

        switch(opcion) {
            case 1:
                int pos;
                cout << "Introduzca posicion del servidor (-1 para todos): ";
                cin >> pos;
                gestor.mostrarInformacionServidores(pos);
                break;

            case 2:
                cout << "Direccion servidor: "; cin >> dir;
                cout << "Nombre del juego: "; cin >> juego;
                cout << "ID del servidor: "; cin >> id;
                cout << "Max jugadores conectados: "; cin >> maxC;
                cout << "Max jugadores en espera: "; cin >> maxE;
                cout << "Puerto: "; cin >> puerto;
                cout << "Pais: "; cin >> pais;
                if (gestor.desplegarServidor(dir, juego, id, maxC, maxE, puerto, pais))
                    cout << "Servidor creado exitosamente." << endl;
                else
                    cout << "Error al crear servidor (puede que ya exista o haya fallo de memoria)." << endl;
                break;

            case 3:
                cout << "Direccion del servidor a eliminar: "; cin >> dir;
                resultado = gestor.eliminarServidor(dir);
                cout << (resultado ? "Servidor eliminado." : "No se puede eliminar (no existe o esta activo).") << endl;
                break;

            case 4:
                cout << "Direccion del servidor a activar: "; cin >> dir;
                resultado = gestor.conectarServidor(dir);
                cout << (resultado ? "Servidor activado." : "No se puede activar.") << endl;
                break;

            case 5:
                cout << "Direccion del servidor a desactivar: "; cin >> dir;
                resultado = gestor.desconetarServidor(dir);
                cout << (resultado ? "Servidor desactivado y jugadores redistribuidos." : "No se puede desactivar.") << endl;
                break;

            case 6:
                cout << "Direccion del servidor a poner en mantenimiento: "; cin >> dir;
                resultado = gestor.realizarMantenimiento(dir);
                cout << (resultado ? "Servidor en mantenimiento." : "No se puede poner en mantenimiento.") << endl;
                break;

            case 7:
                cout << "Nombre jugador: "; cin >> j.nombreJugador;
                cout << "ID: "; cin >> j.ID;
                cout << "Latencia: "; cin >> j.latencia;
                cout << "Puntuacion: "; cin >> j.puntuacion;
                cout << "Pais: "; cin >> j.pais;
                cout << "Juego destino: "; cin >> juego;
                if (gestor.alojarJugador(j, juego, dir, enEspera)) {
                    cout << "Jugador conectado en servidor: " << dir << endl;
                } else if (enEspera) {
                    cout << "Jugador en espera en servidor: " << dir << endl;
                } else {
                    cout << "No se pudo conectar ni encolar al jugador." << endl;
                }
                break;

            case 8:
                cout << "Nombre del jugador a expulsar: "; cin >> nombreJugador;
                if (gestor.expulsarJugador(nombreJugador, dir)) {
                    cout << "Jugador expulsado del servidor: " << dir << endl;
                } else {
                    cout << "Jugador no encontrado en el sistema." << endl;
                }
                break;

            case 9:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opcion no valida." << endl;
        }

    } while (opcion != 9);

    return 0;
}
