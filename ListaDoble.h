#pragma once
#include "NodoDoble.h"
#include <iostream>
#include <functional>

template <class T>
class ListaDoble {
private:
    NodoDoble<T>* ini;
    NodoDoble<T>* fin;
    NodoDoble<T>* actual;
    unsigned int lon;

public:
    ListaDoble() {
        ini = nullptr;
        actual = nullptr;
        fin = nullptr;
        lon = 0;
    }

    ~ListaDoble() {
        NodoDoble<T>* aux = ini;
        while (aux != nullptr) {
            NodoDoble<T>* temp = aux;
            aux = aux->sig;
            delete temp;
        }
    }

    void vaciar() {
        NodoDoble<T>* aux = ini;
        while (aux != nullptr) {
            NodoDoble<T>* temp = aux;
            aux = aux->sig;
            delete temp;
        }
        ini = nullptr;
        actual = nullptr;
        fin = nullptr;
        lon = 0;
    }

    unsigned int getLon() { return lon; }

    void anadirItem(T item) {
        NodoDoble<T>* nuevoNodo = new NodoDoble<T>(item);
        if (ini == nullptr) {
            ini = nuevoNodo;
            actual = nuevoNodo;
            fin = nuevoNodo;
        }
        else {
            nuevoNodo->ant = fin;
            fin->sig = nuevoNodo;
            fin = nuevoNodo;
        }
        lon++;
    }

    void recorrer(std::function<void(T&)> accion) {
        if (ini == nullptr) {
            return;
        }
        NodoDoble<T>* aux = ini;
        while (aux != nullptr) {
            accion(aux->dato);
            aux = aux->sig;
        }
    }

    void irAlInicio() { actual = ini; }
    void irAlFinal() { actual = fin; }

    T getActual() {
        return actual->dato;
    }

    T getPos(int pos) {
        if (ini == nullptr || pos < 0 || pos >= lon) {
            return T();
        }

        NodoDoble<T>* aux = ini;
        int i = 0;
        while (aux != nullptr && i < pos) {
            aux = aux->sig;
            i++;
        }
        return aux->dato;
    }

    NodoDoble<T>* getNodo(unsigned int pos) {
        if (ini == nullptr || pos >= lon) {
            return nullptr;
        }

        NodoDoble<T>* n = ini;
        int i = 0;
        while (n != nullptr && i < pos) {
            n = n->sig;
            i++;
        }
        return n;
    }

    void intercambiar(unsigned int pos1, unsigned int pos2) {
        NodoDoble<T>* nodo1 = getNodo(pos1);
        NodoDoble<T>* nodo2 = getNodo(pos2);

        if (nodo1 != nullptr && nodo2 != nullptr) {
            T aux = nodo1->dato;
            nodo1->dato = nodo2->dato;
            nodo2->dato = aux;
        }
    }

    void fisherYates() {
        int total = lon;
        for (int i = total - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            intercambiar(i, j);
        }
    }

    bool esValido() {
        return actual != nullptr;
    }

    bool tieneSiguiente() {
        return actual != nullptr && actual->sig != nullptr;
    }

    bool tieneAnterior() {
        return actual != nullptr && actual->ant != nullptr;
    }

    void avanzar() {
        if (actual != nullptr) {
            actual = actual->sig;
        }
    }

    void retroceder() {
        if (actual != nullptr) {
            actual = actual->ant;
        }
    }
};