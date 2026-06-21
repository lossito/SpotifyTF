#pragma once
#include <iostream>
class Busqueda
{
private:
	std::string tipo;
	std::string dato;
	bool encontrado;
public:
	Busqueda(std::string type, std::string data, bool found) : tipo(type), dato(data), encontrado(found) {};

	std::string getTipo() { return tipo; }
	std::string getDato() { return dato; }
	bool getEncontrado() { return encontrado; }

	void imprimirInfo() {
		std::cout << tipo << " | " << dato << " | " << encontrado << std::endl;
	}
};
