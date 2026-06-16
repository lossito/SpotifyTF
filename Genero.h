#pragma once
#include <iostream>
#include <string>
#include <iomanip>

class Genero {
private:
    int id;
    std::string nombre;

public:
    Genero(int id, std::string nombre) : id(id), nombre(nombre) {};

    int getId() { return id; };
    std::string getNombre() { return nombre; };

    void imprimirInfo() {
        std::cout << std::left << std::setw(5) << id << std::setw(20) << nombre << std::endl;
    }
};