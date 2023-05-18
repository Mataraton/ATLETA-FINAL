#include <iostream>
#include <stdlib.h>

using namespace std;

// Para datos de tipo FIFO
struct corredor {
    int numero;
    char nombre[30];
    // Lo registro en la vuelta no en el registro inicial
    int tiempo = 0;
    int tiempototal = 0;
    int ronda = 0;
    corredor* sig;
};
corredor* cab = nullptr;
corredor* aux = nullptr;
corredor* aux2 = nullptr;

// Structur LIFO
struct promedio {
    float prom;
    promedio* sig;
    corredor* apunta;
};
promedio* cabp = nullptr;
promedio* auxp = nullptr;
promedio* aux2p = nullptr;
int numerocorredor = 1;

int registrar() {
    // Tipo FIFO: Creamos el nuevo corredor
    aux = new corredor;
    aux->sig = nullptr;
    cout << "Proporcione el nombre del corredor: ";
    cin >> aux->nombre;
    aux->numero = numerocorredor;
    aux->ronda = aux->tiempo = 0;
    numerocorredor++;
    cout << "El numero asignado al corredor es: " << aux->numero << endl;
    if (!cab) {
        cab = aux;
    }
    else {
        aux2 = cab;
        while (aux2->sig != nullptr) {
            aux2 = aux2->sig;
        }
        aux2->sig = aux;
    }
}

int mostrar() {
    if (cab == nullptr) {
        cout << "No hay corredores registrados." << endl;
        return 0;
    }
    cout << "Corredores registrados: " << endl;
    for (aux = cab; aux != nullptr; aux = aux->sig) {
        cout << "El numero " << aux->numero << " es el corredor: " << aux->nombre << " (" << aux->ronda << ") :: " << aux->tiempo << " segundos" << endl;
    }
}

int mostrartiempos() {
    aux2p = cabp;
    while (aux2p != nullptr) {
        cout << "Promedio " << aux2p->apunta->nombre << " " << aux2p->prom << endl;
        aux2p = aux2p->sig;
    }
}

int calcularpromedio() {
    float prom;
    int bandera = 0;
    prom = aux->tiempototal / aux->ronda;
    if (cabp == nullptr) {
        cabp = new promedio;
        cabp->prom = prom;
        cabp->sig = nullptr;
        cabp->apunta = aux;
    }
    else {
        // Comprobar si el usuario es apuntado (Si sí es apuntado solo actualizo el promedio, sino creo un apuntado a él)
        aux2p = cabp;
        while (aux2p != nullptr) {
            // Verifico si el nodo apunta al corredor
            if (aux2p->apunta == aux) {
                aux2p->prom = prom;
                bandera = 1;
            }
            aux2p = aux2p->sig;
        }
        if (bandera == 0) {
            auxp = new promedio;
            auxp->prom = prom;
            auxp->apunta = aux;
            auxp->sig = cabp;
            cabp = auxp;
        }
    }
}

int registrarvuelta() {
    int numcorredor;
    int bandera = 0;
    mostrar();
    cout << "Registre el número del corredor: ";
    cin >> numcorredor;
    aux = cab;
    while (aux != nullptr) {
        if (aux->numero == numcorredor) {
            bandera = 1; // Bandera para verificar que el corredor se encontró
            aux->ronda++;
            cout << "Es el corredor: " << aux->nombre << " (" << aux->ronda << ") :: " << aux->tiempo << " segundos" << endl;
            int tiempoAnterior = aux->tiempo;
            cout << "Registre el tiempo de la última vuelta: ";
            cin >> aux->tiempo;
            aux->tiempototal = aux->tiempototal - tiempoAnterior + aux->tiempo;
            if (aux->ronda >= 2) {
                calcularpromedio();
            }
            break;
        }
        aux = aux->sig;
    }
    if (bandera == 0) {
        cout << "El corredor no existe." << endl;
    }
}

// Función auxiliar para recorrer el árbol en orden ascendente
void inorderRecursivo(promedio* nodo) {
    if (nodo != nullptr) {
        inorderRecursivo(nodo->sig);
        cout << "Promedio " << nodo->apunta->nombre << " " << nodo->prom << endl;
        inorderRecursivo(nodo->sig);
    }
}

// Mostrar los datos de menor promedio a mayor recorriendo el árbol (LIFO)
void inorder() {
    if (cabp == nullptr) {
        cout << "No hay promedios registrados." << endl;
        return;
    }
    cout << "Promedios ordenados (de menor a mayor): " << endl;
    inorderRecursivo(cabp);
}

int balancear() {
    // Implementar aquí el algoritmo para balancear el árbol
    // ...
    cout << "El árbol se ha balanceado correctamente." << endl;
}

int main() {
    int opcion = 0;
    do {
        cout << endl << endl;
        cout << "1. Registrar corredor" << endl;
        cout << "2. Mostrar corredores" << endl;
        cout << "3. Registrar vuelta" << endl;
        cout << "4. Mostrar Clasificación (LIFO)" << endl;
        cout << "5. Mostrar Promedios Ordenados (Inorder)" << endl;
        cout << "6. Balancear el árbol" << endl;
        cout << "10. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;
        switch (opcion) {
        case 1:
            registrar();
            break;
        case 2:
            mostrar();
            break;
        case 3:
            registrarvuelta();
            break;
        case 4:
            mostrartiempos();
            break;
        case 5:
            inorder();
            break;
        case 6:
            balancear();
            break;
        }
    } while (opcion != 10);

    return 0;
}
