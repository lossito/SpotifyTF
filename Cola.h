#pragma once
#include "Nodo.h"
#include <functional>
#include <iostream>
template <typename T>
class Cola { 
private:
    Nodo<T>* frente; 
    Nodo<T>* fin;
    unsigned int lon;

public:
    Cola() {
        frente = nullptr;
        fin = nullptr;
        lon = 0;
    }

    ~Cola() {
        Nodo<T>* aux = frente;
        while (aux != nullptr) {
            Nodo<T>* temp = aux;
            aux = aux->sig;
            delete temp;
        }
    }

    void vaciar() {
        Nodo<T>* aux = frente;
        while (aux != nullptr) {
            Nodo<T>* temp = aux;
            aux = aux->sig;
            delete temp;
        }
        frente = nullptr;
        fin = nullptr;
        lon = 0;
    }

    unsigned int getLon() { return lon; }

    void enqueue(T item) { 
        Nodo<T>* nuevoNodo = new Nodo<T>(item);
        if (fin == nullptr) {
            frente = nuevoNodo;
            fin = nuevoNodo;
        }
        else {
            fin->sig = nuevoNodo;
            fin = nuevoNodo;
        }
        lon++;
    }

    void dequeue() { 
        if (frente == nullptr) return;
        Nodo<T>* temp = frente;
        frente = frente->sig;
        if (frente == nullptr) fin = nullptr; //por si solo habia 1 nodo en tu kola
        delete temp;
        lon--;
    }

    void recorrer(std::function<void(T&)> accion) {
        Nodo<T>* aux = frente;
        while (aux != nullptr) {
            accion(aux->dato);
            aux = aux->sig;
        }
    }

    T front() {
        return frente->dato;
    }

    bool esVacia() {
        return frente == nullptr;
    }
};