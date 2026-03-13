#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

struct reg1 {
	int codigo;
	int cantidad;
	int precio;
};

struct reg2 {
	int codigo;
	int cantidad;
	int peso;
};

void creapesos();
void creaprecios();

int main() {
	char opcion;
	
	do {
		system("cls");
		cout << "Este programa crea los ficheros \n";
		cout << "Los codigos ordenados \n";
		cout << " Elija opcion\n";
		cout << " 1 - Crear fichero de pesos\n";
		cout << " 2 - Crear fichero de precios\n";
		cout << " 3 - Salir\n";
		opcion = getch();
		switch (opcion) {
			case '1': creapesos(); break;
			case '2': creaprecios(); break;
			case '3': break;
			default: cout<<"Opcion incorrecta\n"; break;
		}
	} while (opcion!='3');
	
	return 0;
}

void creaprecios() {
	reg1 r1;
	int ultimo = -1;
	char seguir;
	
	ofstream f1("precios.dat", ios::binary);
	if (f1) {
		cout << "Se crea fichero de precios\n";
		do {
			do {
				cout <<"Deme codigo\n ";
				cin >> r1.codigo;
			} while (r1.codigo <= ultimo);
			
			ultimo = r1.codigo;
			
			cout <<"Deme cantidad\n ";
			cin >> r1.cantidad;
			cout <<"Deme precio\n ";
			cin >> r1.precio;
			
			f1.write((char*) &r1, sizeof(reg1));
			
			cout << "Desea mas datos (s/n)?\n";
			seguir = getch();
		} while (seguir != 'n');
		f1.close();
	}
	else
		cout << "Error en la apertura del fichero\n";
}

void creapesos() {
	reg2 r2;
	int ultimo = -1;
	char seguir;
	
	ofstream f2("pesos.dat", ios::binary);
	if (f2) {
		cout << "Se crea fichero de pesos\n";
		do {
			do {
				cout <<"Deme codigo\n ";
				cin >> r2.codigo;
			} while (r2.codigo <= ultimo);
			
			ultimo = r2.codigo;
			
			cout <<"Deme cantidad\n ";
			cin >> r2.cantidad;
			cout <<"Deme peso\n ";
			cin >> r2.peso;
			
			f2.write((char*) &r2, sizeof(reg2));
			
			cout << "Desea mas datos (s/n)?\n";
			seguir = getch();
		} while (seguir != 'n');
		f2.close();
	}
	else
		cout << "Error en la apertura del fichero\n";
}

