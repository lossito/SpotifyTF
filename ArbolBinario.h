#pragma once
#include "NodoArbol.h"
#include <functional>
template <typename T>
class ArbolBinario {
private:
    NodoArbol<T>* raiz;
    std::function<bool(T, T)> comparar;
    
    NodoArbol<T>* insert(T item, NodoArbol<T>* actual) {
        if (actual == nullptr) return new NodoArbol<T>(item);
        if (comparar(item, actual->dato)) {
            actual->izquierda = insert(item, actual->izquierda);
        }
        else {
            actual->derecha = insert(item, actual->derecha);
        }
        return actual;
    }

    int countNodos(NodoArbol<T>* raiz) {
        if (raiz == nullptr) return 0;
        return 1 + countNodos(raiz->izquierda) + countNodos(raiz->derecha);
    }

    void inOrden(NodoArbol<T>* nodo, std::function<void(T)> criterio) {
        if (nodo == nullptr) return;
        inOrden(nodo->izquierda, criterio);
        criterio(nodo->dato);
        inOrden(nodo->derecha, criterio);
    }

public:
    ArbolBinario() : raiz(nullptr) {}
    ArbolBinario(std::function<bool(T, T)> criterio) : raiz(nullptr), comparar(criterio) {}
    
    void insertar(T item) {
        raiz = insert(item, raiz);
    }

    void enOrden(std::function<void(T)> criterio) {
        inOrden(raiz, criterio);
    }

    int contarNodos() {
        return countNodos(raiz);
    }
};