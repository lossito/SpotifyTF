#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "ListaSimple.h"
#include "DesignUX.h"

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

    void imprimirInfo(std::string nombreArtista) {
        std::cout << std::left << std::setw(5) << id << std::setw(30) << acortar(nombre, 29) << std::setw(18) << acortar(nombreArtista, 17) << std::setw(8) << reproducciones;
    }
};