#pragma once
template <typename T>
class NodoAVL {
public:
    T dato;
    NodoAVL<T>* izquierda;
    NodoAVL<T>* derecha;
    int altura;

    NodoAVL(T data, NodoAVL<T>* left = nullptr, NodoAVL<T>* right = nullptr) : dato(data), izquierda(left), derecha(right), altura(1) {}
};