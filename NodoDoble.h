#pragma once
template <class T>
class NodoDoble {
public:
    T dato;
    NodoDoble<T>* sig;
    NodoDoble<T>* ant;

    NodoDoble(T data, NodoDoble<T>* next = nullptr, NodoDoble<T>* prev = nullptr) : dato(data), sig(next), ant(prev) {}
};