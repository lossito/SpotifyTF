#pragma once
template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* sig;

    Nodo(T data, Nodo<T>* next = nullptr) : dato(data), sig(next) {}
};