#pragma once
#include <iostream>
#include <fstream>
#include "ListaSimple.h"
#include "Cancion.h"
#include "Genero.h"
#include "Artista.h"
#include "Usuario.h"
#include "Playlist.h"

class GestorArchivos {
public:
    GestorArchivos() {};
    void cargarCancion(std::string filePath, ListaSimple<Cancion*>& lista) {
        std::ifstream file(filePath);
        std::string line;
        if (!file) {
            std::cout << "Error de archivo" << std::endl;
            return;
        }
        std::cout << "Cargando canciones de : " << filePath << std::endl;
        while (getline(file, line)) {
            std::string temp = "";
            int contadorEspacios = 0, id = 0, artistaId = 0, reproducciones = 0;
            std::string nombre = "", generosStr = "";
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '@') {
                    if (contadorEspacios == 0) id = stoi(temp);
                    else if (contadorEspacios == 1) nombre = temp;
                    else if (contadorEspacios == 2) artistaId = stoi(temp);
                    else if (contadorEspacios == 3) reproducciones = stoi(temp);
                    temp = "";
                    contadorEspacios++;
                }
                else {
                    temp += line[i]; // concatenar chars 
                }
            }
            if (contadorEspacios == 4) {
                generosStr = temp;
                Cancion* cancion = new Cancion(id, nombre, artistaId, reproducciones);
                std::string tempGenero = "";
                for (int i = 0; i < generosStr.length(); i++) {
                    if (generosStr[i] == ',') {
                        cancion->agregarGenero(stoi(tempGenero));
                        tempGenero = "";
                    }
                    else {
                        tempGenero += generosStr[i];
                    }
                }
                if (!tempGenero.empty()) {
                    cancion->agregarGenero(stoi(tempGenero));
                }
                lista.anadirItem(cancion);
            }
        }
        file.close();
    };
    void guardarCanciones(std::string filePath, ListaSimple<Cancion*>& lista) {
        std::ofstream file(filePath);
        if (!file) {
            std::cout << "Error de archivo" << std::endl;
            return;
        }
        lista.recorrer([&file](Cancion*& c) {
            file << c->getId() << "@" << c->getNombre() << "@" << c->getArtistaId() << "@" << c->getReproducciones() << "@";
            int totalGeneros = c->getGenerosId().getLon();
            int contador = 0;
            c->getGenerosId().recorrer([&file, &contador, &totalGeneros](int& generoId) {
                file << generoId;
                if (contador < totalGeneros - 1) { file << ","; }
                contador++;
                });
            file << "\n";
            });
        file.close();
    }
    void cargarGenero(std::string filePath, ListaSimple<Genero*>& lista) {
        std::ifstream file(filePath);
        std::string line;
        if (!file) {
            std::cout << "Error de archivo" << std::endl;
            return;
        }
        std::cout << "Cargando generos de : " << filePath << std::endl;
        while (getline(file, line)) {
            std::string temp = "";
            int contadorEspacios = 0, id = 0;
            std::string nombre = "";
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '@') {
                    if (contadorEspacios == 0) id = stoi(temp);
                    temp = "";
                    contadorEspacios++;
                }
                else {
                    temp += line[i];
                }
            }
            if (contadorEspacios == 1) {
                nombre = temp;
                Genero* genero = new Genero(id, nombre);
                lista.anadirItem(genero);
            }
        }
        file.close();
    };
    void cargarArtista(std::string filePath, ListaSimple<Artista*>& lista) {
        std::ifstream file(filePath);
        std::string line;
        if (!file) {
            std::cout << "Error de archivo" << std::endl;
            return;
        }
        std::cout << "Cargando artistas de : " << filePath << std::endl;
        while (getline(file, line)) {
            std::string temp = "";
            int contadorEspacios = 0, id = 0;
            std::string nombre = "";
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '@') {
                    if (contadorEspacios == 0) id = stoi(temp);
                    temp = "";
                    contadorEspacios++;
                }
                else {
                    temp += line[i];
                }
            }
            if (contadorEspacios == 1) {
                nombre = temp;
                Artista* artista = new Artista(id, nombre);
                lista.anadirItem(artista);
            }
        }
        file.close();
    };
    void cargarUsuario(std::string filePath, ListaSimple<Usuario*>& lista) {
        std::ifstream file(filePath);
        std::string line;
        if (!file) {
            std::cout << "Error de archivo" << std::endl;
            return;
        }
        std::cout << "Cargando usuarios de : " << filePath << std::endl;
        while (getline(file, line)) {
            std::string temp = "";
            int contadorEspacios = 0, id = 0;
            std::string nombre = "", username = "", password = "";
            std::string generosStr = "";
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '@') {
                    if (contadorEspacios == 0) id = stoi(temp);
                    else if (contadorEspacios == 1) nombre = temp;
                    else if (contadorEspacios == 2) username = temp;
                    else if (contadorEspacios == 3) password = temp;
                    temp = "";
                    contadorEspacios++;
                }
                else {
                    temp += line[i];
                }
            }
            if (contadorEspacios == 4) {
                generosStr = temp;
                Usuario* nuevoUsuario = new Usuario(id, nombre, username, password);
                std::string tempGenero = "";
                for (int i = 0; i < generosStr.length(); i++) {  // parsear los generos separados por coma
                    if (generosStr[i] == ',') {
                        nuevoUsuario->agregarGenero(stoi(tempGenero));
                        tempGenero = "";
                    }
                    else {
                        tempGenero += generosStr[i];
                    }
                }
                if (!tempGenero.empty()) {
                    nuevoUsuario->agregarGenero(stoi(tempGenero));
                }
                lista.anadirItem(nuevoUsuario);
            }
        }
        file.close();
    };
    void guardarUsuario(std::string filePath, Usuario* u) {
        std::ofstream file(filePath, std::ios::app);
        if (!file) {
            std::cout << "Error de archivo" << std::endl;
            return;
        }
        file << u->getId() << "@" << u->getNombre() << "@" << u->getUsername() << "@" << u->getPassword() << "@";
        int total = u->getGenerosPreferidos().getLon();
        int contador = 0;
        u->getGenerosPreferidos().recorrer([&file, &contador, &total](int& generoId)
            { file << generoId; if (contador < total - 1) { file << ","; } contador++; });
        file << "\n";
        file.close();
    }
    void cargarPlaylist(std::string filePath, ListaSimple<Playlist*>& lista, ListaSimple<Cancion*>& catalogo) {
        std::ifstream file(filePath);
        std::string line;
        if (!file) {
            std::cout << "Error de archivo" << std::endl;
            return;
        }
        std::cout << "Cargando playlists de : " << filePath << std::endl;
        while (getline(file, line)) {
            std::string temp = "";
            int contadorEspacios = 0, id = 0, usuarioId = 0;
            std::string nombre = "", cancionesStr = "";
            bool esAutomatica = false;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '@') {
                    if (contadorEspacios == 0) id = stoi(temp);
                    else if (contadorEspacios == 1) nombre = temp;
                    else if (contadorEspacios == 2) usuarioId = stoi(temp);
                    else if (contadorEspacios == 3) esAutomatica = (stoi(temp) == 1);
                    temp = "";
                    contadorEspacios++;
                }
                else {
                    temp += line[i];
                }
            }
            if (contadorEspacios == 4) {
                cancionesStr = temp;
                Playlist* nuevaPlaylist = new Playlist(id, nombre, usuarioId, esAutomatica);
                std::string tempCancion = "";
                for (int i = 0; i < cancionesStr.length(); i++) {
                    if (cancionesStr[i] == ',') {
                        int cancionId = stoi(tempCancion);
                        catalogo.recorrer([&nuevaPlaylist, cancionId](Cancion*& c)
                            { if (c->getId() == cancionId) nuevaPlaylist->agregarCancion(c); });
                        tempCancion = "";
                    }
                    else {
                        tempCancion += cancionesStr[i];
                    }
                }
                if (!tempCancion.empty()) {
                    int cancionId = stoi(tempCancion);
                    catalogo.recorrer([&nuevaPlaylist, cancionId](Cancion*& c)
                        { if (c->getId() == cancionId) nuevaPlaylist->agregarCancion(c); });
                }
                lista.anadirItem(nuevaPlaylist);
            }
        }
        file.close();
    };
    void guardarPlaylist(std::string filePath, Playlist* p) {
        std::ofstream file(filePath, std::ios::app);
        if (!file) {
            std::cout << "Error de archivo" << std::endl;
            return;
        }
        file << p->getId() << "@" << p->getNombre() << "@" << p->getUsuarioId() << "@" << (p->getEsAutomatica() ? 1 : 0) << "@";
        int total = p->getCanciones().getLon();
        int contador = 0;
        p->getCanciones().recorrer([&file, &contador, &total](Cancion*& c)
            { file << c->getId(); if (contador < total - 1) { file << ","; } contador++; });
        file << "\n";
        file.close();
    }
};
