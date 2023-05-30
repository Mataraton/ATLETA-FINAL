#include <iostream>
#include <stdlib.h>

using namespace std;

struct corredor {
    int numero;
    char nombre[30];
    int tiempo = 0;
    int tiempototal = 0;
    int ronda = 0;
    corredor* sig;
};

corredor* cab = nullptr;
corredor* aux = nullptr;
corredor* aux2 = nullptr;

struct promedio {
    float prom;
    promedio* sig;
    corredor* apunta;
    promedio* izq;
    promedio* der;
};

promedio* cabp = nullptr;
promedio* auxp = nullptr;
promedio* aux2p = nullptr;
int numerocorredor = 1;

// Obtener la altura de un nodo en el árbol AVL
int obtenerAltura(promedio* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return 1 + max(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));
}

// Obtener el factor de balance de un nodo en el árbol AVL
int obtenerFactorBalance(promedio* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return obtenerAltura(nodo->izq) - obtenerAltura(nodo->der);
}

// Rotación simple a la derecha en el árbol AVL
promedio* rotacionDerecha(promedio* nodo) {
    promedio* nuevoPadre = nodo->izq;
    nodo->izq = nuevoPadre->der;
    nuevoPadre->der = nodo;
    return nuevoPadre;
}

// Rotación simple a la izquierda en el árbol AVL
promedio* rotacionIzquierda(promedio* nodo) {
    promedio* nuevoPadre = nodo->der;
    nodo->der = nuevoPadre->izq;
    nuevoPadre->izq = nodo;
    return nuevoPadre;
}

// Realizar el balanceo del árbol AVL después de insertar un nodo
promedio* balancearArbolAVL(promedio* nodo) {
    int factorBalance = obtenerFactorBalance(nodo);
    if (factorBalance > 1) {
        // El subárbol izquierdo es más alto, se requiere rotación a la derecha
        if (obtenerFactorBalance(nodo->izq) < 0) {
            // Rotación doble a la derecha
            nodo->izq = rotacionIzquierda(nodo->izq);
        }
        // Rotación simple a la derecha
        return rotacionDerecha(nodo);
    }
    else if (factorBalance < -1) {
        // El subárbol derecho es más alto, se requiere rotación a la izquierda
        if (obtenerFactorBalance(nodo->der) > 0) {
            // Rotación doble a la izquierda
            nodo->der = rotacionDerecha(nodo->der);
        }
        // Rotación simple a la izquierda
        return rotacionIzquierda(nodo);
    }
    return nodo;
}

// Insertar un nodo en el árbol AVL
promedio* insertarNodo(promedio* nodo, promedio* nuevoNodo) {
    if (nodo == nullptr) {
        return nuevoNodo;
    }
    if (nuevoNodo->prom < nodo->prom) {
        nodo->izq = insertarNodo(nodo->izq, nuevoNodo);
    }
    else {
        nodo->der = insertarNodo(nodo->der, nuevoNodo);
    }
    return balancearArbolAVL(nodo);
}

// Recorrer y mostrar el árbol AVL en orden ascendente
void mostrarArbolAVL(promedio* nodo) {
    if (nodo == nullptr) {
        return;
    }
    mostrarArbolAVL(nodo->izq);
    cout << "Número: " << nodo->apunta->numero << " | Nombre: " << nodo->apunta->nombre << " | Promedio: " << nodo->prom << endl;
    mostrarArbolAVL(nodo->der);
}

// Insertar un corredor en la lista
void insertarCorredor() {
    corredor* n = new corredor;
    n->numero = numerocorredor;
    cout << "Ingrese el nombre del corredor: ";
    cin >> n->nombre;
    if (cab == nullptr) {
        cab = n;
        cab->sig = nullptr;
        aux = cab;
    }
    else {
        aux->sig = n;
        n->sig = nullptr;
        aux = n;
    }
    numerocorredor++;
}

// Registrar el tiempo de vuelta de un corredor
void registrarTiempoVuelta() {
    int numCorredor;
    cout << "Ingrese el número de corredor: ";
    cin >> numCorredor;

    corredor* corredorActual = cab;
    while (corredorActual != nullptr) {
        if (corredorActual->numero == numCorredor) {
            int tiempo;
            cout << "Ingrese el tiempo de vuelta: ";
            cin >> tiempo;

            corredorActual->tiempototal += tiempo;
            corredorActual->ronda++;
            corredorActual->tiempo = corredorActual->tiempototal / corredorActual->ronda;

            promedio* nuevoPromedio = new promedio;
            nuevoPromedio->prom = corredorActual->tiempo;
            nuevoPromedio->apunta = corredorActual;
            nuevoPromedio->izq = nullptr;
            nuevoPromedio->der = nullptr;

            cabp = insertarNodo(cabp, nuevoPromedio);

            cout << "Tiempo registrado correctamente." << endl;
            return;
        }
        corredorActual = corredorActual->sig;
    }

    cout << "No se encontró un corredor con ese número." << endl;
}

// Mostrar los corredores y sus promedios ordenados de menor a mayor
void mostrarPromediosOrdenados() {
    cout << "Promedios ordenados de menor a mayor:" << endl;
    mostrarArbolAVL(cabp);
}

int main() {
    int opcion;
    while (opcion != 4) {
        cout << endl;
        cout << "===== Registro de Corredores =====" << endl;
        cout << "1. Registrar corredor" << endl;
        cout << "2. Registrar tiempo de vuelta" << endl;
        cout << "3. Mostrar promedios ordenados" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                insertarCorredor();
                break;
            case 2:
                registrarTiempoVuelta();
                break;
            case 3:
                mostrarPromediosOrdenados();
                break;
            case 4:
                cout << "¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
        }
    }

    return 0;
}
