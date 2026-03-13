#include <iostream>
#include <conio.h>

using namespace std;

int main() {
	float *Tabla;
	char respuesta;
	float suma = 0;
	int fila, col;
	
	float **Datos = new float*[100];
  
	if (Datos != NULL) {
		for (int i=0; i<100; i++) {
			Datos[i] = new float[100-i];
			Tabla = Datos[i];
			for (int j=0; j<100-i; j++)
				Tabla[j] = 0;
				//Datos[i][j] = 0;
			}
	}
	
	do {
		cout << "Deme fila (1 a 100)\n";
		cin >> fila;
		Tabla = Datos[fila-1];
		cout << "Deme columna (1 a " << 100-fila+1 << ")\n";
		cin >> col;
		cout << "Deme valor\n";
		cin >> Tabla[col-1];
		cout << "\n Desea continuar (S/N)\n";
		respuesta = toupper(getch());
   } while (respuesta != 'N');                    
  
	for (int i=0; i<100; i++) {
		Tabla = Datos[i];
		for (int j=0; j<100-i; j++) 
			suma += Tabla[j];
			//suma += Datos[i][j]; 
		delete [] Tabla;
		//delete [] Datos[i];
	}   
  
	cout << "La suma vale " << suma << endl << endl;

	delete [] Datos;

	system("pause");
	return 0;
} 

  
  
  
