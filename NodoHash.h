#pragma once
template <typename T, typename K>
class NodoHash {
public:
    K clave;
    T dato;
    NodoHash<T, K>* sig;

    NodoHash(T data, K pass, NodoHash<T, K>* next = nullptr) : dato(data), clave(pass), sig(next) {}
};