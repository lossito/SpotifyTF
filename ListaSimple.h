#pragma once
#include "Nodo.h"
#include <iostream>
#include <functional>

template <typename T>
class ListaSimple {
private:
    Nodo<T>* ini;
    unsigned int lon;

public:
    ListaSimple() {
        ini = nullptr;
        lon = 0;
    };

    ~ListaSimple() {
        Nodo<T>* aux = ini;
        while (aux != nullptr) {
            Nodo<T>* temp = aux;
            aux = aux->sig;
            delete temp;
        }
    }

    void vaciar() {
        Nodo<T>* aux = ini;
        while (aux != nullptr) {
            Nodo<T>* temp = aux;
            aux = aux->sig;
            delete temp;
        }
        ini = nullptr;
        lon = 0;
    }

    unsigned int getLon() { return lon; }

    void anadirItem(T item) {
        Nodo<T>* nuevoNodo = new Nodo<T>(item);
        if (ini == nullptr) {
            ini = nuevoNodo;
        }
        else {
            Nodo<T>* aux = ini;
            while (aux->sig != nullptr) { aux = aux->sig; }
            aux->sig = nuevoNodo;
        }
        lon++;
    }

    void recorrer(std::function<void(T&)> accion) {
        if (ini == nullptr) {
            return;
        }
        Nodo<T>* aux = ini;
        while (aux != nullptr) {
            accion(aux->dato);
            aux = aux->sig;
        }
    }

    bool existeNodo(std::function<bool(T&)> accion) {
        Nodo<T>* aux = ini;
        while (aux != nullptr) {
            if (accion(aux->dato)) return true;
            aux = aux->sig;
        }
        return false;
    }
};