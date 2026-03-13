const int TAM_CADENA = 30;

typedef char cadena[TAM_CADENA];

#define N 10
#define SALTO 4

struct Golfista {
	cadena licencia;
	float handicap;
	cadena nombre;
	cadena apellidos;
	int golpes;
	int resultado;
};

struct Jugador {
    int indice;
	int resultado;
};


class Torneo
{
    fstream fichero;
    int numGolfistas;
    cadena nomFichero;
    cadena nomTorneo;

public:
    ~Torneo();
    Torneo();
    int getNumGolfistas();
    void putNumGolfistas(int n);
    void getNomTorneo(cadena nombre);
    void getNomFichero(cadena nombre);
    void putNomTorneo(cadena nombre);
    void putNomFichero(cadena nombre);
    void CrearFichero(char nombreFichero[]);
    void mostrar(float hdcp);
    Golfista consultar(int posicion);
    int buscar(cadena licencia);
    void insertar(Golfista g);
    void modificar(Golfista c, int posicion);
    void eliminar(int posicion);
    void Clasificar();
};



class Clasificacion {
    Jugador  *elementos; //elementos de la tabla
    int Jugadores;
    int tamano;
 public:
    Clasificacion(); // constructor de la clase
    void anadirjugador(Jugador a);
    void eliminar(int i);
    Jugador consultar(int n);//Devuelve la estructura en esa posicion
    bool vacio();
    int numjugadores();
    void ordenar();
    ~Clasificacion();
};


// METODO DE ORDENACION BURBUJA de una clase vector con los elementos en el atributo celda
void vector::Burbuja(int inicio, int fin)
        {
        int pos,ele;
        for (pos=inicio; pos<fin; pos++)
            for (ele=inicio+1; ele<fin ; ele++)
                if(celda[ele-1]>celda[ele])
                    intercambiar(celda[ele-1],celda[ele]);//Función genérica que tendrá que ser implementada
        }
