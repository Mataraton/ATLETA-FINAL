#include <iostream>
#include <stdlib.h>
#include <queue>

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
};

promedio* cabp = nullptr;
promedio* auxp = nullptr;
promedio* aux2p = nullptr;

int numerocorredor = 1;

struct nodo_arbol {
    float promedio;
    corredor* atleta;
    nodo_arbol* izquierdo;
    nodo_arbol* derecho;
};

nodo_arbol* raiz = nullptr;

void agregarCorredor() {
    corredor* nuevoCorredor = new corredor;
    nuevoCorredor->numero = numerocorredor;
    numerocorredor++;
    std::cout << "Ingrese el nombre del corredor: ";
    std::cin >> nuevoCorredor->nombre;

    if (cab == nullptr) {
        cab = nuevoCorredor;
        aux = cab;
    } else {
        aux->sig = nuevoCorredor;
        aux = nuevoCorredor;
    }
}

void mostrarCorredoresPorRonda() {
    if (cab == nullptr) {
        std::cout << "No hay corredores en la lista." << std::endl;
    } else {
        aux = cab;
        while (aux != nullptr) {
            std::cout << "Número: " << aux->numero << ", Nombre: " << aux->nombre << ", Ronda: " << aux->ronda << std::endl;
            aux = aux->sig;
        }
    }
}

void mostrarArbolInOrden(nodo_arbol* nodo) {
    if (nodo == nullptr)
        return;

    mostrarArbolInOrden(nodo->izquierdo);
    std::cout << "Promedio: " << nodo->promedio << ", Nombre: " << nodo->atleta->nombre << std::endl;
    mostrarArbolInOrden(nodo->derecho);
}

void mostrarCorredoresPorPromedioAscendente() {
    if (raiz == nullptr) {
        std::cout << "No hay corredores en el árbol." << std::endl;
    } else {
        std::cout << "Corredores por promedio ascendente:" << std::endl;
        mostrarArbolInOrden(raiz);
    }
}

void mostrarArbolInOrdenDescendente(nodo_arbol* nodo) {
    if (nodo == nullptr)
        return;

    mostrarArbolInOrdenDescendente(nodo->derecho);
    std::cout << "Promedio: " << nodo->promedio << ", Nombre: " << nodo->atleta->nombre << std::endl;
    mostrarArbolInOrdenDescendente(nodo->izquierdo);
}

void mostrarArbolPorNiveles(nodo_arbol* nodo) {
    std::queue<nodo_arbol*> cola;
    cola.push(nodo);
    while (!cola.empty()) {
        nodo_arbol* actual = cola.front();
        cola.pop();

        std::cout << "Promedio: " << actual->promedio << ", Nombre: " << actual->atleta->nombre<< std::endl;
    if (actual->izquierdo != nullptr)
        cola.push(actual->izquierdo);

    if (actual->derecho != nullptr)
        cola.push(actual->derecho);
}
}

void mostrarCorredoresPorNiveles() {
if (raiz == nullptr) {
std::cout << "No hay corredores en el árbol." << std::endl;
} else {
std::cout << "Corredores por niveles:" << std::endl;
mostrarArbolPorNiveles(raiz);
}
}

void mostrarMenu() {
std::cout << "======= MENÚ =======" << std::endl;
std::cout << "1. Agregar corredor" << std::endl;
std::cout << "2. Mostrar corredores por ronda" << std::endl;
std::cout << "3. Mostrar corredores por promedio ascendente" << std::endl;
std::cout << "5. Mostrar corredores por niveles" << std::endl;
std::cout << "6. Salir" << std::endl;
std::cout << "====================" << std::endl;
}

int main() {
int opcion;
do {
mostrarMenu();
std::cout << "Seleccione una opción: ";
std::cin >> opcion;
    switch (opcion) {
        case 1:
            agregarCorredor();
            break;
        case 2:
            mostrarCorredoresPorRonda();
            break;
        case 3:
            mostrarCorredoresPorPromedioAscendente();
            break;
        case 5:
            mostrarCorredoresPorNiveles();
            break;
        case 6:
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opción inválida. Por favor, seleccione una opción válida." << std::endl;
            break;
    }
} while (opcion != 6);

return 0;
}