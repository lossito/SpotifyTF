#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "ListaSimple.h"

class Usuario {
private:
    int id;
    std::string nombre;
    std::string username;
    std::string password;
    ListaSimple<int> generosPreferidos;

public:
    Usuario(int id, std::string nombre, std::string username, std::string password)
        : id(id), nombre(nombre), username(username), password(password) {
    };

    int getId() { return id; };
    std::string getNombre() { return nombre; };
    std::string getUsername() { return username; };
    std::string getPassword() { return password; };
    ListaSimple<int>& getGenerosPreferidos() { return generosPreferidos; };

    void setPassword(std::string nuevoPassword) { password = nuevoPassword; };
    void agregarGenero(int generoId) {
        generosPreferidos.anadirItem(generoId);
    };

    bool validarCredenciales(std::string user, std::string pass) {
        return username == user && password == pass;
    };

    void imprimirInfo() {
        std::cout << std::left << std::setw(8) << id << std::setw(20) << nombre << std::setw(20) << username << std::endl;
        std::cout << "Generos preferidos: ";
        generosPreferidos.recorrer([](int& generoId) { std::cout << generoId << " "; });
        std::cout << std::endl;
    }
};