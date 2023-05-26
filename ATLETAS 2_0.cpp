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
    promedio* izq;
    promedio* der;
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
        cabp->izq = cabp->der = nullptr;
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
            auxp->izq = auxp->der = nullptr;
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
        inorderRecursivo(nodo->izq);
        cout << "Promedio " << nodo->apunta->nombre << " " << nodo->prom << endl;
        inorderRecursivo(nodo->der);
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

// Obtener la altura de un nodo
int obtenerAltura(promedio* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return 1 + max(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));
}

// Obtener el factor de balance de un nodo
int obtenerFactorBalance(promedio* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return obtenerAltura(nodo->izq) - obtenerAltura(nodo->der);
}

// Rotación simple a la derecha
promedio* rotacionDerecha(promedio* nodo) {
    promedio* nuevoPadre = nodo->izq;
    nodo->izq = nuevoPadre->der;
    nuevoPadre->der = nodo;
    return nuevoPadre;
}

// Rotación simple a la izquierda
promedio* rotacionIzquierda(promedio* nodo) {
    promedio* nuevoPadre = nodo->der;
    nodo->der = nuevoPadre->izq;
    nuevoPadre->izq = nodo;
    return nuevoPadre;
}

// Realizar el balanceo del árbol AVL
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

// Reinsertar todos los nodos en el árbol AVL
promedio* reinsertarNodos(promedio* nodo, promedio* nuevoNodo) {
    if (nodo == nullptr) {
        return nuevoNodo;
    }
    if (nodo->izq != nullptr) {
        nodo->izq = reinsertarNodos(nodo->izq, nuevoNodo);
    }
    else {
        nodo->izq = nuevoNodo;
    }
    if (nodo->der != nullptr) {
        return reinsertarNodos(nodo->der, nuevoNodo);
    }
    else {
        nodo->der = nuevoNodo;
        return nodo;
    }
}

// Balancear el árbol AVL
void balancear() {
    if (cabp == nullptr) {
        cout << "No hay promedios registrados." << endl;
        return;
    }

    // Reinsertar todos los nodos en el árbol
    promedio* nodoActual = cabp;
    promedio* siguienteNodo = nodoActual->sig;
    promedio* nuevoArbol = nullptr;

    while (nodoActual != nullptr) {
        nodoActual->izq = nodoActual->der = nullptr;
        nuevoArbol = insertarNodo(nuevoArbol, nodoActual);
        nodoActual = siguienteNodo;
        if (siguienteNodo != nullptr) {
            siguienteNodo = siguienteNodo->sig;
        }
    }

    cabp = nuevoArbol;

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
        cout << "5. Mostrar Clasificación (AVL)" << endl;
        cout << "6. Balancear árbol AVL" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese la opción: ";
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
    } while (opcion != 0);
    return 0;
}
