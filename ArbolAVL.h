#pragma once
#include "NodoAVL.h"
#include <functional>

template <typename T>
class ArbolAVL {
private:
    NodoAVL<T>* raiz;
    std::function<bool(T, T)> comparar;

    int altura(NodoAVL<T>* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->altura;
    }

    int factorBalance(NodoAVL<T>* nodo) {
        if (nodo == nullptr) return 0;
        return altura(nodo->derecha) - altura(nodo->izquierda);
    }

    void actualizarAltura(NodoAVL<T>* nodo) {
        int izq = altura(nodo->izquierda);
        int der = altura(nodo->derecha);

        if (izq > der) nodo->altura = izq + 1;
        else nodo->altura = der + 1;
    }

    NodoAVL<T>* rotarDerecha(NodoAVL<T>* nodo) {
        NodoAVL<T>* aux = nodo->izquierda;
        NodoAVL<T>* temp = aux->derecha;

        aux->derecha = nodo;
        nodo->izquierda = temp;

        actualizarAltura(nodo);
        actualizarAltura(aux);

        return aux;
    }

    NodoAVL<T>* rotarIzquierda(NodoAVL<T>* nodo) {
        NodoAVL<T>* aux = nodo->derecha;
        NodoAVL<T>* temp = aux->izquierda;

        aux->izquierda = nodo;
        nodo->derecha = temp;

        actualizarAltura(nodo);
        actualizarAltura(aux);

        return aux;
    }

    NodoAVL<T>* insert(T item, NodoAVL<T>* actual) {
        if (actual == nullptr) return new NodoAVL<T>(item);
        if (comparar(item, actual->dato)) { actual->izquierda = insert(item, actual->izquierda); }
        else { actual->derecha = insert(item, actual->derecha); }

        actualizarAltura(actual);
        int balance = factorBalance(actual);

        if (balance < -1 && comparar(item, actual->izquierda->dato)) { return rotarDerecha(actual); }
        if (balance > 1 && !comparar(item, actual->derecha->dato)) { return rotarIzquierda(actual); }
        if (balance < -1 && !comparar(item, actual->izquierda->dato)) {
            actual->izquierda = rotarIzquierda(actual->izquierda);
            return rotarDerecha(actual);
        }
        if (balance > 1 && comparar(item, actual->derecha->dato)) {
            actual->derecha = rotarDerecha(actual->derecha);
            return rotarIzquierda(actual);
        }
        return actual;
    }

    int countNodos(NodoAVL<T>* raiz) {
        if (raiz == nullptr) return 0;
        return 1 + countNodos(raiz->izquierda) + countNodos(raiz->derecha);
    }

    void inOrden(NodoAVL<T>* nodo, std::function<void(T)> criterio) {
        if (nodo == nullptr) return;
        inOrden(nodo->izquierda, criterio);
        criterio(nodo->dato);
        inOrden(nodo->derecha, criterio);
    }

public:
    ArbolAVL() : raiz(nullptr) {}
    ArbolAVL(std::function<bool(T, T)> criterio) : raiz(nullptr), comparar(criterio) {}

    void insertar(T item) {
        raiz = insert(item, raiz);
    }

    void enOrden(std::function<void(T)> criterio) {
        inOrden(raiz, criterio);
    }

    int contarNodos() {
        return countNodos(raiz);
    }

    int alturaArbol() {
        return altura(raiz);
    }
};