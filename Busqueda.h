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
		std::cout << std::left << std::setw(11) << tipo << std::setw(20) << dato << std::setw(20);
		if (encontrado) { std::cout << "Resultado: Encontrado" << std::endl; }
		else { std::cout << "Resultado: No encontrado" << std::endl; }
	}
};
