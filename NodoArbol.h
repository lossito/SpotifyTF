#pragma once
template <typename T>
class NodoArbol {
public:
    T dato;
    NodoArbol<T>* izquierda;
    NodoArbol<T>* derecha;

    NodoArbol(T data, NodoArbol<T>* left = nullptr, NodoArbol<T>* right = nullptr) : dato(data), izquierda(left), derecha(right) {}
};