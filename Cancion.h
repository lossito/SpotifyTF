#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "ListaSimple.h"

class Cancion {
private:
    int id;
    std::string nombre;
    int artistaId;
    int reproducciones;
    ListaSimple<int> generosId;

public:
    Cancion(int id, std::string nombre, int artistaId, int reproducciones = 0)
        : id(id), nombre(nombre), artistaId(artistaId), reproducciones(reproducciones) {
    };

    int getId() { return id; };
    std::string getNombre() { return nombre; };
    int getArtistaId() { return artistaId; };
    int getReproducciones() { return reproducciones; };
    ListaSimple<int>& getGenerosId() { return generosId; };

    void agregarGenero(int generoId) { generosId.anadirItem(generoId); };
    void incrementarReproducciones() { reproducciones++; };

    void imprimirInfo() {
        std::cout << std::left << std::setw(5) << id << std::setw(20) << nombre << std::setw(12) << artistaId << std::setw(8) << reproducciones;
        std::cout << "Generos: ";
        generosId.recorrer([](int& g) { std::cout << g << " "; });
        std::cout << std::endl;
    }
};