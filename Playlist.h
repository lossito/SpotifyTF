#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "ListaDoble.h"
#include "Cancion.h"

class Playlist {
private:
    int id;
    std::string nombre;
    int usuarioId;
    bool esAutomatica;
    ListaDoble<Cancion*> canciones;

public:
    Playlist(int id, std::string nombre, int usuarioId, bool esAutomatica = false) : id(id), nombre(nombre), usuarioId(usuarioId), esAutomatica(esAutomatica) {};

    int getId() { return id; };
    std::string getNombre() { return nombre; };
    int getUsuarioId() { return usuarioId; };
    bool getEsAutomatica() { return esAutomatica; };
    ListaDoble<Cancion*>& getCanciones() { return canciones; };

    void setNombre(std::string nuevoNombre) { nombre = nuevoNombre; };

    void agregarCancion(Cancion* c) { canciones.anadirItem(c); };

    int getCantidad() { return canciones.getLon(); };

    void imprimirInfo() {
        std::string tipo = esAutomatica ? "Automatica" : "Manual"; std::cout << std::left << std::setw(5)
            << id << std::setw(25) << nombre << std::setw(12) << tipo << std::setw(10) << canciones.getLon() << std::endl;
    };
};