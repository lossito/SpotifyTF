#pragma once
#include <functional>
#include "NodoHash.h"
template <typename T, typename K>
class TablaHash
{
private:
	int capacidad;
	NodoHash<T, K>** tabla;
	std::function<int(K)> funcionHash;

public:
	TablaHash(int tam, std::function<int(K)> hash) : capacidad(tam), funcionHash(hash) {
		tabla = new NodoHash<T, K>*[tam];
		for (int i = 0; i < capacidad; i++) { tabla[i] = nullptr; }
	};

	void insertar(T dato, K clave) {
		NodoHash<T, K>* aux = new NodoHash<T, K>(dato, clave);
		int pos = funcionHash(clave) % capacidad; 
		aux->sig = tabla[pos];
		tabla[pos] = aux;
	}

	T buscar(K clave) {
		int pos = funcionHash(clave) % capacidad;
		NodoHash<T, K>* aux = tabla[pos];
		while (aux != nullptr) {
			if (clave == aux->clave) { return aux->dato; }
			aux = aux->sig;
		}
		return nullptr;
	}
};