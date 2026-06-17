#pragma once
#include <iostream>
#include <conio.h>
#include <ctime>
#include "GestorArchivos.h"
#include "DesignUX.h"
#include "ArbolBinario.h"
#include "TablaHash.h"
#include "Playlist.h"

class Sistema {
private:
    Usuario* usuarioActual;
    GestorArchivos fm;
    DesignUX ui;
    ListaSimple<Cancion*> canciones;
    ListaSimple<Artista*> artistas;
    ListaSimple<Genero*>  generos;
    ListaSimple<Usuario*> usuarios;
    ListaSimple<Playlist*> playlists;
    ArbolBinario<Cancion*> catalogoNombre;
    ArbolBinario<Cancion*> catalogoId;
    ArbolBinario<Cancion*> catalogoReproducciones;
    TablaHash<Cancion*, int> busquedasId;
    //TablaHash<Cancion*, std::string> busquedasArtista;
    //TablaHash<Cancion*, std::string> busquedasNombre;

    void cargarDatos() {
        fm.cargarCancion("archivos/canciones.txt", canciones);
        fm.cargarArtista("archivos/artistas.txt", artistas);
        fm.cargarGenero("archivos/generos.txt", generos);
        fm.cargarUsuario("archivos/usuarios.txt", usuarios);
        fm.cargarPlaylist("archivos/playlists.txt", playlists, canciones);
    }

    void preLogin() {
        int opc = 0;
        while (opc != 3) {
            system("cls");
            ui.pantallaBienvenida();
            std::cin >> opc;
            switch (opc) {
            case 1: {
                if (iniciarSesion()) {
                    postLogin();
                }
                break;
            }
            case 2: {
                registrar();
                break;
            }
            case 3: {
                cerrarPrograma();
                break;
            }
            default: {
                std::cout << "  No valido";
                (void)_getch();
                break;
            }
            }
        }
    }

    bool iniciarSesion() {
        system("cls");
        ui.marcoIniciarSesion();
        std::string user, pass;
        std::cin >> user;
        establecerColor(8);  std::cout << "  |  ";
        establecerColor(14); std::cout << "Password";
        establecerColor(8);  std::cout << "  |  >> ";
        establecerColor(7);
        std::cin >> pass;
        establecerColor(8);
        std::cout << "  +--------------------------------------------------+\n\n";
        Usuario* encontrado = nullptr;
        usuarios.recorrer([&encontrado, &user, &pass](Usuario*& u) {
            if (u->validarCredenciales(user, pass)) {
                encontrado = u;
            }
            });
        if (encontrado != nullptr) {
            usuarioActual = encontrado;
            establecerColor(14);
            std::cout << "\n  [+] Bienvenido de vuelta, " << usuarioActual->getNombre() << "!\n";
            std::cout << "  Presiona cualquier tecla para continuar...";
            establecerColor(7);
            (void)_getch();
            return true;
        }
        else {
            establecerColor(12);
            std::cout << "\n  [!] Username o password incorrectos.\n";
            establecerColor(8);
            std::cout << "  Presiona cualquier tecla para volver...";
            establecerColor(7);
            (void)_getch();
            return false;
        }
    }

    void advertenciaRegistro() {
        std::cout << "ADVERTENCIA: Por favor, al registrar nombre y password, no haga uso de espacios.\n";
        std::cout << "Ademas, al momento de registrar generos, solo se le registraran validos.\n";
        std::cout << "Presione para continuar.\n";
    }

    void cerrarPrograma() {
        system("cls");
        std::cout << "Gracias por usar Spotify! Hasta luego.\n";
        (void)_getch();
    }

    void registrar() {
        system("cls");
        advertenciaRegistro();
        (void)_getch();
        system("cls");
        std::string nombre, username, password;
        ui.marcoRegistro();
        std::cin.ignore();
        std::getline(std::cin, nombre);
        establecerColor(8);  std::cout << "  |  ";
        establecerColor(14); std::cout << "Username ";
        establecerColor(8);  std::cout << "|  >> ";
        establecerColor(7); std::cin >> username;
        if (existeUsername(username)) {
            establecerColor(8);
            std::cout << "  +--------------------------------------------------+\n\n";
            establecerColor(12);
            std::cout << "  [!] El username '" << username << "' ya esta en uso.\n";
            establecerColor(7);
            std::cout << "  Presiona cualquier tecla para volver...";
            (void)_getch();
            return;
        }
        establecerColor(8);  std::cout << "  |  ";
        establecerColor(14); std::cout << "Password ";
        establecerColor(8);  std::cout << "|  >> ";
        establecerColor(7);
        std::cin >> password;
        establecerColor(8);
        std::cout << "  +--------------------------------------------------+\n\n";
        system("cls");
        mostrarGenerosDisponibles();
        establecerColor(14);
        std::cout << "\n  Ingresa los Ids separados por coma ";
        std::cout << "(ej: 1,2,3)";
        establecerColor(8);
        std::cout << ": ";
        establecerColor(7);
        std::string generosInput;
        std::cin >> generosInput;
        int nuevoId = generarNuevoId<Usuario>(usuarios);
        Usuario* nuevoUsuario = new Usuario(nuevoId, nombre, username, password);
        int generosAgregados = agregarGenerosValidos(generosInput, nuevoUsuario);
        system("cls");
        if (generosAgregados == 0) {
            establecerColor(12);
            std::cout << "\n  [!] Ningun genero ingresado fue valido. Registro cancelado.\n";
            establecerColor(7);
            delete nuevoUsuario;
            std::cout << "  Presiona cualquier tecla para volver...";
            (void)_getch();
            return;
        }
        usuarios.anadirItem(nuevoUsuario);
        fm.guardarUsuario("archivos/usuarios.txt", nuevoUsuario);
        ui.marcoRegistroExito();
        (void)_getch();
    }

    void postLogin() {
        char opc = ' ';
        while (opc != '6' && usuarioActual != nullptr) {
            establecerColor(10);
            system("cls");
            //ui.marco2();
            establecerColor(14);
            //moverCursor(15, 11);
            //std::cout << " " << usuarioActual->getNombre() << "!\n\n";
            std::cout << "---SPOTIFY TB2---" << std::endl; //menu temporal
            std::cout << "1. Ver catalogo musical" << std::endl;
            std::cout << "2. Realizar busquedas" << std::endl;
            std::cout << "6. Cerrar sesion" << std::endl;
            opc = _getch();
            switch (opc) {
            case '1': {
                alternarOrdenCanciones();
                break;
            }
            case '2': {
                realizarBusqueda();
                break;
            }
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6': {

                break;
            }
            default: {
                moverCursor(2, 26);
                establecerColor(12);
                std::cout << "Opcion no valida\n";
                (void)_getch();
                break;
            }
            }
        }
    }

    void alternarOrdenCanciones() {
        char tecla = ' '; int contadorImprimir = 0;
        while (tecla != 'Q' && tecla != 'q')
        {
            if (tecla == 'E' || tecla == 'e') { contadorImprimir++; }
            if (contadorImprimir > 2) { contadorImprimir = 0; }
            switch (contadorImprimir)
            {
            case 0: {
                system("cls");
                tecla = catalogoCanciones(catalogoNombre, "Nombre");
                break;
            }
            case 1: {
                system("cls");
                tecla = catalogoCanciones(catalogoId, "Id");
                break;
            }
            case 2: {
                system("cls");
                tecla = catalogoCanciones(catalogoReproducciones, "Reproducciones");
                break;
            }
            default:
                break;
            }
        }
    }

    char catalogoCanciones(ArbolBinario<Cancion*>& catalogo, std::string tipoOrden) {
        int contador = 0, paginaActual = 0, rangoMaximo = 10, rangoMinimo = 0; char tecla = ' ';
        while (true) {
            contador = 0; system("cls");
            establecerColor(14); std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << "NOMBRE" << std::setw(18) << "ARTISTA" << std::setw(8) << "REP" << "GENEROS" << std::endl;
            establecerColor(1); std::cout << std::string(80, '-') << std::endl;
            catalogo.enOrden([&](Cancion* aux) {
                if (contador >= rangoMinimo && contador < rangoMaximo) {
                    aux->imprimirInfo(devolverNombreArtista(aux->getArtistaId())); ListaSimple<int>& temp = aux->getGenerosId(); bool first = true;
                    temp.recorrer([&](int id) { if (first != true) { std::cout << ", "; }
                    std::cout << devolverNombreGenero(id); first = false;
                        });
                    std::cout << std::endl;
                }
                contador++;
                });
            std::cout << std::string(80, '-') << std::endl;
            establecerColor(11); std::cout << "   [A] Anterior   [D] Siguiente   [E] Cambiar Orden";
            establecerColor(12); std::cout << "   [Q] Cancelar\n\n"; establecerColor(14); std::cout << "   Tipo de Orden: " << tipoOrden;
            tecla = _getch();
            if (tecla == 'D' || tecla == 'd') {
                if (contador <= rangoMaximo) continue;
                paginaActual++;
                rangoMinimo += 10; rangoMaximo += 10;
                system("cls");
            }
            else if (tecla == 'A' || tecla == 'a') {
                if (paginaActual <= 0) continue;
                paginaActual--;
                rangoMinimo -= 10; rangoMaximo -= 10;
                system("cls");
            }
            else if (tecla == 'Q' || tecla == 'q' || tecla == 'E' || tecla == 'e') {
                system("cls");
                return tecla;
            }
        }
    }

    char catalogoSinCambio(ArbolBinario<Cancion*>& catalogo) {
        int contador = 0, paginaActual = 0, rangoMaximo = 10, rangoMinimo = 0; char tecla = ' ';
        while (true) {
            contador = 0; system("cls");
            establecerColor(14); std::cout << std::left << std::setw(5) << "Id" << std::setw(30) << "NOMBRE" << std::setw(18) << "ARTISTA" << std::setw(8) << "REP" << "GENEROS" << std::endl;
            establecerColor(1); std::cout << std::string(80, '-') << std::endl;
            catalogo.enOrden([&](Cancion* aux) {
                if (contador >= rangoMinimo && contador < rangoMaximo) {
                    aux->imprimirInfo(devolverNombreArtista(aux->getArtistaId())); ListaSimple<int>& temp = aux->getGenerosId(); bool first = true;
                    temp.recorrer([&](int id) { if (first != true) { std::cout << ", "; }
                    std::cout << devolverNombreGenero(id); first = false;
                        });
                    std::cout << std::endl;
                }
                contador++;
                });
            std::cout << std::string(80, '-') << std::endl;
            establecerColor(11); std::cout << "   [A] Anterior   [D] Siguiente";
            establecerColor(12); std::cout << "   [Q] Cancelar\n\n"; establecerColor(14);
            std::cout << "  +-------REALIZAR BUSQUEDA-------+\n";
            std::cout << "  1. Realizar busqueda por Id\n";
            std::cout << "  2. Realizar busqueda por Artista\n";
            std::cout << "  3. Realizar busqueda por Nombre\n";
            tecla = _getch();
            if (tecla == 'D' || tecla == 'd') {
                if (contador <= rangoMaximo) continue;
                paginaActual++;
                rangoMinimo += 10; rangoMaximo += 10;
                system("cls");
            }
            else if (tecla == 'A' || tecla == 'a') {
                if (paginaActual <= 0) continue;
                paginaActual--;
                rangoMinimo -= 10; rangoMaximo -= 10;
                system("cls");
            }
            else if (tecla == 'Q' || tecla == 'q' || tecla == '1' || tecla == '2' || tecla == '3') {
                system("cls");
                return tecla;
            }
        }
    }
    
    void realizarBusqueda() {
        char tecla = ' ';
        while (tecla != 'Q' && tecla != 'q')
        {
            tecla = catalogoSinCambio(catalogoId);
            switch (tecla)
            {
            case '1': {
                int id = 0; std::cout << "ingrese el Id de la cancion que desea buscar: "; std::cin >> id;
                establecerColor(14); std::cout << std::endl << std::left << std::setw(5) << "ID" << std::setw(30) << "NOMBRE" << std::setw(18) << "ARTISTA" << std::setw(8) << "REP" << "GENEROS" << std::endl;
                establecerColor(1); std::cout << std::string(80, '-') << std::endl;
                Cancion* aux = busquedasId.buscar(id);
                if (aux != nullptr) {
                    aux->imprimirInfo(devolverNombreArtista(aux->getArtistaId())); ListaSimple<int>& temp = aux->getGenerosId(); bool first = true;
                    temp.recorrer([&](int id) { if (first != true) { std::cout << ", "; }
                    std::cout << devolverNombreGenero(id); first = false; });
                }
                else { establecerColor(12); std::cout << "No se encontro informacion." << std::endl; }
                (void)_getch();
                break;
            }
            case '2': {
                std::cout << "prueba";
                (void)_getch();
                break;
            }
            case '3': {
                std::cout << "prueba";
                (void)_getch();
                break;
            }
            default:
                break;
            }
        }
    }

    void mostrarGenerosDisponibles() {
        establecerColor(10);
        std::cout << "  +-----------------------------------+\n";
        establecerColor(14);
        std::cout << "  |        GENEROS DISPONIBLES        |\n";
        establecerColor(10);
        std::cout << "  +-----------------------------------+\n";
        generos.recorrer([](Genero*& g) {
            establecerColor(8);  std::cout << "  |  ";
            establecerColor(11); std::cout << std::left << std::setw(3) << g->getId();
            establecerColor(8);  std::cout << "|  ";
            establecerColor(7);  std::cout << std::setw(27) << g->getNombre();
            establecerColor(8);  std::cout << "|\n";
            });
        establecerColor(10);
        std::cout << "  +-----------------------------------+\n";
        establecerColor(7);
    }

    int agregarGenerosValidos(std::string generosInput, Usuario* nuevoUsuario) {
        std::string tempGenero = ""; int generosAgregados = 0;
        for (int i = 0; i < generosInput.length(); i++) {
            if (generosInput[i] == ',') {
                if (tempGenero != "") {
                    int genId = stoi(tempGenero);
                    if (existeGenero(genId)) {
                        nuevoUsuario->agregarGenero(genId);
                        generosAgregados++;
                    }
                }
                tempGenero = "";
            }
            else {
                tempGenero += generosInput[i];
            }
        }
        if (!tempGenero.empty()) {
            int genId = stoi(tempGenero);
            if (existeGenero(genId)) {
                nuevoUsuario->agregarGenero(genId);
                generosAgregados++;
            }
        }
        return generosAgregados;
    }

    bool existeUsername(std::string username) {
        return usuarios.existeNodo([&](Usuario* u) { return u->getUsername() == username; });
    }

    bool existeGenero(int generoId) {
        return generos.existeNodo([&](Genero* g) { return g->getId() == generoId; });
    }

    template<typename T>
    int generarNuevoId(ListaSimple<T*>& lista) {
        int max = 0;
        lista.recorrer([&max](T* item) { if (item->getId() > max) max = item->getId(); });
        return max + 1;
    }

    std::string devolverNombreGenero(int id) {
        std::string nombre = "Desconocido";
        generos.recorrer([&nombre, &id](Genero* genero) { if (genero->getId() == id) nombre = genero->getNombre(); });
        return nombre;
    }

    std::string devolverNombreArtista(int id) {
        std::string nombre = "Desconocido";
        artistas.recorrer([&nombre, &id](Artista* artista) { if (artista->getId() == id) nombre = artista->getNombre(); });
        return nombre;
    }
public:
    Sistema() : usuarioActual(nullptr), busquedasId(101, [](int clave) { return clave; }) {
        catalogoNombre = ArbolBinario<Cancion*>([](Cancion* a, Cancion* b) {
            return a->getNombre() < b->getNombre();
            });
        catalogoId = ArbolBinario<Cancion*>([](Cancion* a, Cancion* b) {
            return a->getId() < b->getId();
            });
        catalogoReproducciones = ArbolBinario<Cancion*>([](Cancion* a, Cancion* b) {
            return a->getReproducciones() > b->getReproducciones();
            });
    };

    void ejecutar() {
        configurarVentana();
        srand(time(NULL));
        cargarDatos();
        canciones.recorrer([&](Cancion* aux) {
            catalogoNombre.insertar(aux);
            catalogoId.insertar(aux);
            catalogoReproducciones.insertar(aux);
            busquedasId.insertar(aux, aux->getId());
            });
        preLogin();
    }
};