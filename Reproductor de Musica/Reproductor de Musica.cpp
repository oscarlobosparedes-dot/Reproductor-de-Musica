#include <iostream>
#include <string>
#include <conio.h> 

using namespace std;

// Nodo de la lista circular
struct Cancion {
    string nombre;
    string artista;
    string duracion;
    Cancion* siguiente;
    Cancion* anterior;
};

Cancion* cabeza = NULL;
int total = 0;

// Insertar cancion al final de la lista circular
void agregarCancion() {
    Cancion* nueva = new Cancion();

    cout << "\nNombre de la cancion: ";
    cin.ignore();
    getline(cin, nueva->nombre);

    cout << "Artista: ";
    getline(cin, nueva->artista);

    cout << "Duracion (mm:ss): ";
    getline(cin, nueva->duracion);

    nueva->siguiente = NULL;
    nueva->anterior = NULL;

    if (cabeza == NULL) {
        cabeza = nueva;
        nueva->siguiente = nueva;
        nueva->anterior = nueva;
    }
    else {
        Cancion* ultimo = cabeza->anterior;
        ultimo->siguiente = nueva;
        nueva->anterior = ultimo;
        nueva->siguiente = cabeza;
        cabeza->anterior = nueva;
    }

    total++;
    cout << "\nCancion agregada correctamente!\n";
}

// Mostrar todas las canciones
void mostrarLista() {
    if (cabeza == NULL) {
        cout << "\nLa playlist esta vacia.\n";
        return;
    }

    cout << "\n--- LISTA DE CANCIONES ---\n";

    Cancion* actual = cabeza;
    int i = 1;

    do {
        cout << i << ". " << actual->nombre << " - " << actual->artista
            << " (" << actual->duracion << ")\n";
        actual = actual->siguiente;
        i++;
    } while (actual != cabeza);

    cout << "Total: " << total << " cancion(es)\n";
}

// Calcular la posicion de un nodo en la lista
int calcularPosicion(Cancion* nodo) {
    Cancion* tmp = cabeza;
    int pos = 1;
    while (tmp != nodo) {
        tmp = tmp->siguiente;
        pos++;
    }
    return pos;
}

// Mostrar la cancion que se esta reproduciendo
void mostrarCancion(Cancion* actual) {
    int pos = calcularPosicion(actual);
    cout << "\n[" << pos << "/" << total << "] Reproduciendo: " << actual->nombre << "\n";
    cout << "    Artista  : " << actual->artista << "\n";
    cout << "    Duracion : " << actual->duracion << "\n";
    cout << "Controles: flecha derecha = siguiente | flecha izquierda = anterior | ESC = salir\n";
}

// Modo reproduccion con flechas y ESC
void reproducirPlaylist() {
    if (cabeza == NULL) {
        cout << "\nLa playlist esta vacia. Agrega canciones primero.\n";
        return;
    }

    Cancion* actual = cabeza;
    int tecla;

    cout << "\n--- MODO REPRODUCCION ---\n";
    mostrarCancion(actual);

    while (true) {
        tecla = _getch();

        // Las teclas especiales (flechas) devuelven 0 o 224 primero,
        // luego un segundo valor que identifica la tecla
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();

            if (tecla == 77) {  // Flecha derecha
                actual = actual->siguiente;
                mostrarCancion(actual);

            }
            else if (tecla == 75) {  // Flecha izquierda
                actual = actual->anterior;
                mostrarCancion(actual);
            }

        }
        else if (tecla == 27) {  // ESC
            cout << "\nVolviendo al menu principal...\n";
            break;
        }
    }
}

// Menu principal
void mostrarMenu() {
    cout << "\n============================\n";
    cout << "   REPRODUCTOR DE MUSICA\n";
    cout << "============================\n";
    cout << "1. Agregar cancion\n";
    cout << "2. Mostrar lista completa\n";
    cout << "3. Reproducir playlist\n";
    cout << "4. Salir\n";
    cout << "Opcion: ";
}

int main() {
    int opcion;

    cout << "Bienvenido al Reproductor de Musica\n";

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
        case 1:
            agregarCancion();
            break;
        case 2:
            mostrarLista();
            break;
        case 3:
            reproducirPlaylist();
            break;
        case 4:
            cout << "\nHasta luego!\n";
            break;
        default:
            cout << "\nOpcion invalida. Intenta de nuevo.\n";
        }

    } while (opcion != 4);

    return 0;
}