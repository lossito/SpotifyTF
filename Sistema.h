#pragma once
#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>
#include "GestorArchivos.h"
#include "Algoritmos.h"
#include "DesignUX.h"
#include "Busqueda.h"
#include "Cola.h"
#include "Arbol.h"
#include "ArbolAVL.h"
#include "TablaHash.h"
#include "Grafo.h"

class Sistema {
private:
    Usuario* usuarioActual;
    GestorArchivos fm;
    DesignUX ui;
    ListaSimple<Cancion*> canciones;
    ListaSimple<Artista*> artistas;
    ListaSimple<Genero*>  generos;
    ListaSimple<Usuario*> usuarios;
    Cola<Cancion*> fila;
    Arbol<Cancion*> catalogoNombre;
    ArbolAVL<Cancion*> catalogoId;
    ArbolAVL<Cancion*> catalogoReproducciones;
    TablaHash<Cancion*, int> busquedaId;
    TablaHash<Cancion*, std::string> busquedaNombre;
    TablaHash<ListaSimple<Cancion*>*, std::string> busquedaArtista;
    TablaHash<ListaSimple<Cancion*>*, std::string> busquedaGenero;
    std::vector<Cancion*> historialCancion;
    std::vector<Busqueda> historialBusqueda;
    Grafo<int> grafoCanciones;
    char ajusteReproducciones = '0', ajusteBusquedas = '0';
    bool ordenAscendente = true;
    
    void cargarDatos() {
        fm.cargarCancion("archivos/canciones.txt", canciones);
        fm.cargarArtista("archivos/artistas.txt", artistas);
        fm.cargarGenero("archivos/generos.txt", generos);
        fm.cargarUsuario("archivos/usuarios.txt", usuarios);
    }

    void preLogin() {
        int opc = 0;
        while (opc != 3) {
            system("cls");
            ui.pantallaBienvenida(); std::cin >> opc;
            validadorNumeros(opc, "  >> ");
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
        std::string user, pass; std::cin >> user;
        establecerColor(8);  std::cout << "  |  ";
        establecerColor(14); std::cout << "Password";
        establecerColor(8);  std::cout << "  |  >> ";
        establecerColor(7);
        std::cin >> pass; std::cin.ignore();
        establecerColor(8);
        std::cout << "  +--------------------------------------------------+\n\n";
        Usuario* encontrado = nullptr;
        usuarios.recorrer([&](Usuario*& u) { if (u->validarCredenciales(user, pass)) { encontrado = u; }});
        if (encontrado != nullptr) {
            usuarioActual = encontrado;
            establecerColor(14); std::cout << "  [+] "; 
            establecerColor(11); std::cout << "Bienvenido de vuelta, " << usuarioActual->getNombre() << "!\n"; 
            establecerColor(14); std::cout << "  Presiona cualquier tecla para continuar.";
            establecerColor(7);
            (void)_getch();
            return true;
        }
        else {
            establecerColor(12);
            std::cout << "\n  [!] Username o password incorrectos.\n";
            establecerColor(8);
            std::cout << "  Presiona cualquier tecla para volver.";
            establecerColor(7);
            (void)_getch();
            return false;
        }
    }

    void advertenciaRegistro() {
        establecerColor(12); std::cout << "ADVERTENCIA:"; 
        establecerColor(8);  std::cout << " Por favor, al registrar nombre y password, no haga uso de espacios.\n";
        std::cout << "Ademas, al momento de registrar generos, solo se le registraran los validos.\n";
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
        std::getline(std::cin, nombre);
        establecerColor(8);  std::cout << "  |  ";
        establecerColor(14); std::cout << "Username ";
        establecerColor(8);  std::cout << "|  >> ";
        establecerColor(7); std::cin >> username; std::cin.ignore();
        if (existeUsername(username)) {
            establecerColor(8);
            std::cout << "  +--------------------------------------------------+\n\n";
            establecerColor(12);
            std::cout << "  [!] El username '" << username << "' ya esta en uso.\n";
            establecerColor(7);
            std::cout << "  Presiona cualquier tecla para volver.";
            (void)_getch();
            return;
        }
        establecerColor(8); std::cout << "  |  ";
        establecerColor(14); std::cout << "Password ";
        establecerColor(8); std::cout << "|  >> ";
        establecerColor(7); std::cin >> password; std::cin.ignore();
        establecerColor(8);
        std::cout << "  +--------------------------------------------------+\n\n";
        system("cls");
        mostrarGenerosDisponibles();
        establecerColor(14);
        std::cout << "\n  Ingresa los Ids separados por coma ";
        std::cout << "(ej: 1,2,3)";
        establecerColor(8); std::cout << ": ";
        establecerColor(7); std::string generosInput; std::cin >> generosInput; std::cin.ignore();
        int nuevoId = generarNuevoId<Usuario>(usuarios);
        Usuario* nuevoUsuario = new Usuario(nuevoId, nombre, username, password);
        int generosAgregados = agregarGenerosValidos(generosInput, nuevoUsuario);
        system("cls");
        if (generosAgregados == 0) {
            establecerColor(12);
            std::cout << "\n  [!] Ningun genero ingresado fue valido. Registro cancelado.\n";
            establecerColor(7);
            delete nuevoUsuario;
            std::cout << "  Presiona cualquier tecla para volver.";
            (void)_getch();
            return;
        }
        usuarios.anadirItem(nuevoUsuario);
        fm.guardarUsuario("archivos/usuarios.txt", nuevoUsuario);
        ui.marcoRegistroExito();
        (void)_getch();
    }

    void postLogin() {
        char opc = ' '; std::vector<Cancion*> enteras; canciones.recorrer([&](Cancion* c) { enteras.push_back(c); }); std::vector<Cancion*> recomendaciones; filtrarGustosRecursivo(enteras, recomendaciones);
        while (opc != '6' && usuarioActual != nullptr) {
            establecerColor(10);
            system("cls");
            ui.marcoPostLogin();
            establecerColor(11); moverCursor(15, 11); std::cout << " " << usuarioActual->getNombre() << "!\n\n"; establecerColor(14);
            opc = _getch();
            switch (opc) {
            case '1': {
                alternarCanciones();
                break;
            }
            case '2': {
                realizarBusqueda();
                break;
            }
            case '3': {
                filaReproduccion();
                break;
            }
            case '4': {
                mostrarHistorial();
                break;
            }
            case '5': {
                recomendacionSemanal(recomendaciones);
                break;
            }
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

    void alternarCanciones() {
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

    template <typename T>
    char catalogoCanciones(T& catalogo, std::string tipoOrden) {
        int contador = 0, paginaActual = 0, rangoMaximo = 10, rangoMinimo = 0; char tecla = ' ';
        while (true) {
            contador = 0; system("cls");
            imprimirCanciones(catalogo, contador, paginaActual, rangoMaximo, rangoMinimo);
            establecerColor(11); std::cout << "   [A] Anterior   [D] Siguiente   [E] Cambiar orden   [F] Agregar a fila";
            establecerColor(12); std::cout << "   [Q] Salir\n\n"; establecerColor(14); std::cout << "   Tipo de orden: " << tipoOrden;
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
            else if (tecla == 'F' || tecla == 'f') {
                agregarFila();
                system("cls");
            }
            else if (tecla == 'Q' || tecla == 'q' || tecla == 'E' || tecla == 'e') {
                system("cls");
                return tecla;
            }
        }
    }

    void realizarBusqueda() {
        char tecla = ' ';
        while (tecla != 'Q' && tecla != 'q')
        {
            system("cls");
            ui.menuBusqueda();
            tecla = _getch();
            switch (tecla)
            {
            case '1': {
                system("cls");
                int id = 0; establecerColor(14); std::cout << "\n  ingrese el Id de la cancion que desea buscar: "; establecerColor(11); std::cin >> id;
                validadorNumeros(id, "  Id invalido. Intente nuevamente: ");
                buscarCancionId(id);
                (void)_getch();
                break;
            }
            case '2': {
                system("cls");
                std::string nombreCancion; validadorTexto(nombreCancion, "\n  ingrese el nombre de la Cancion que desea buscar: "); 
                buscarCancionNombre(nombreCancion);
                (void)_getch();
                break;
            }
            case '3': {
                system("cls");
                std::string nombreArtista; validadorTexto(nombreArtista, "\n  ingrese el nombre del Artista que desea buscar: ");
                buscarPorArtista(nombreArtista);
                (void)_getch();
                break;
            }
            case '4': {
                system("cls");
                std::string nombreGenero; validadorTexto(nombreGenero, "\n  ingrese el nombre del Genero que desea buscar: "); 
                buscarPorGenero(nombreGenero);
                (void)_getch();
                break;
            }
            default:
                break;
            }
        }
    }

    void agregarFila() {
        establecerColor(14); int temp = 0; std::cout << "\n\n   Ingrese el Id de la cancion que desee agregar: "; 
        establecerColor(11); std::cin >> temp; establecerColor(14); validadorNumeros(temp, "   Id invalido. Intente nuevamente: ");
        Cancion* aux = busquedaId.buscar(temp);
        if (aux != nullptr) { fila.enqueue(aux); establecerColor(10); std::cout << "   -- Id agregado!\n"; }
        else { establecerColor(12); std::cout << "   -- Id no encontrado.\n"; };
        (void)_getch();
    }

    void buscarCancionId(int id) {
        Cancion* aux = busquedaId.buscar(id);
        historialBusqueda.push_back(Busqueda("Id", std::to_string(id), aux != nullptr));
        establecerColor(14); std::cout << std::endl << std::left << std::setw(5) << "Id" << std::setw(30) << "NOMBRE" << std::setw(18) << "ARTISTA" << std::setw(8) << "REP" << "GENEROS" << std::endl;
        establecerColor(1); std::cout << std::string(80, '-') << std::endl;
        if (aux != nullptr) {
            aux->imprimirInfo(devolverNombreArtista(aux->getArtistaId())); ListaSimple<int>& temp = aux->getGenerosId(); bool first = true;
            temp.recorrer([&](int id) { if (first != true) { std::cout << ", "; }
            std::cout << devolverNombreGenero(id); first = false; }); std::cout << std::endl;
        }
        else { establecerColor(12); std::cout << "No se encontro informacion." << std::endl; }
    }

    void buscarCancionNombre(std::string nombreCancion) {
        Cancion* aux = busquedaNombre.buscar(nombreCancion);
        historialBusqueda.push_back(Busqueda("Nombre", nombreCancion, aux != nullptr));
        establecerColor(14); std::cout << std::endl << std::left << std::setw(5) << "Id" << std::setw(30) << "NOMBRE" << std::setw(18) << "ARTISTA" << std::setw(8) << "REP" << "GENEROS" << std::endl;
        establecerColor(1); std::cout << std::string(80, '-') << std::endl;
        if (aux != nullptr) {
            aux->imprimirInfo(devolverNombreArtista(aux->getArtistaId())); ListaSimple<int>& temp = aux->getGenerosId(); bool first = true;
            temp.recorrer([&](int id) { if (first != true) { std::cout << ", "; }
            std::cout << devolverNombreGenero(id); first = false; }); std::cout << std::endl;
        }
        else { establecerColor(12); std::cout << "No se encontro informacion." << std::endl; }
    }

    void buscarPorArtista(std::string nombreArtista) {
        ListaSimple<Cancion*>* aux = busquedaArtista.buscar(nombreArtista);
        historialBusqueda.push_back(Busqueda("Artista", nombreArtista, aux != nullptr));
        establecerColor(14); std::cout << std::endl << std::left << std::setw(5) << "Id" << std::setw(30) << "NOMBRE" << std::setw(18) << "ARTISTA" << std::setw(8) << "REP" << "GENEROS" << std::endl;
        establecerColor(1); std::cout << std::string(80, '-') << std::endl;
        if (aux != nullptr) {
            aux->recorrer([&](Cancion* x) { x->imprimirInfo(nombreArtista); ListaSimple<int>& temp = x->getGenerosId(); bool first = true;
            temp.recorrer([&](int id) { if (first != true) { std::cout << ", "; }
            std::cout << devolverNombreGenero(id); first = false; }); std::cout << std::endl;; });
        }
        else { establecerColor(12); std::cout << "No se encontro informacion." << std::endl; }
    }

    void buscarPorGenero(std::string nombreGenero) {
        ListaSimple<Cancion*>* aux = busquedaGenero.buscar(nombreGenero);
        historialBusqueda.push_back(Busqueda("Genero", nombreGenero, aux != nullptr));
        establecerColor(14); std::cout << std::endl << std::left << std::setw(5) << "Id" << std::setw(30) << "NOMBRE" << std::setw(18) << "ARTISTA" << std::setw(8) << "REP" << "GENEROS" << std::endl;
        establecerColor(1); std::cout << std::string(80, '-') << std::endl;
        if (aux != nullptr) {
            aux->recorrer([&](Cancion* x) { x->imprimirInfo(devolverNombreArtista(x->getArtistaId())); ListaSimple<int>& temp = x->getGenerosId(); bool first = true;
            temp.recorrer([&](int id) { if (first != true) { std::cout << ", "; }
            std::cout << devolverNombreGenero(id); first = false; }); std::cout << std::endl;; });
        }
        else { establecerColor(12); std::cout << "No se encontro informacion." << std::endl; }
    }

    template <typename T>
    void imprimirCanciones(T& catalogo, int& contador, int& paginaActual, int& rangoMaximo, int& rangoMinimo) {
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
    }

    void filaReproduccion() {
        char tecla = ' ';
        while (tecla != 'Q' && tecla != 'q') {
            system("cls");
            ui.tituloFicha("Fila de reproduccion", 15, 0, 14); std::cout << "\n\n\n";
            if (fila.esVacia()) { std::cout << "La fila de reproduccion esta vacia.\n"; }
            else { std::cout << "Canciones en fila:\n\n"; int contador = 1;
                fila.recorrer([&](Cancion* c) { if (c != nullptr) { std::cout << contador << ". " << c->getNombre() << " | " << devolverNombreArtista(c->getArtistaId()) << "\n"; contador++; }}); }
            establecerColor(14); std::cout << "\n------------------------------------------------------------\n";
            establecerColor(11); std::cout << "   [R] Reproducir   [V] Vaciar fila   [G] Generar canciones";
            establecerColor(12); std::cout << "   [Q] Salir\n"; 
            tecla = _getch();
            if (tecla == 'V' || tecla == 'v') { fila.vaciar(); }
            if (tecla == 'G' || tecla == 'g') { generarCanciones(); }
            else if (tecla == 'R' || tecla == 'r') {
                if (fila.esVacia()) {
                    establecerColor(12); std::cout << "\n   La fila esta vacia.";
                    establecerColor(1);
                    (void)_getch(); continue;
                }
                Cancion* actual = fila.front(); fila.dequeue();
                registrarReproduccion(actual);
                int reproducidas = 1; 
                while (tecla != 'Q' && tecla != 'q') {
                    system("cls");
                    ui.tituloFicha("Reproduciendo desde fila", 15, 0, 11);
                    establecerColor(14); std::cout << "\n\n\n";
                    std::cout << "Cancion reproducida desde la fila: " << reproducidas << "\n";
                    std::cout << "Canciones restantes en fila: " << fila.getLon() << "\n";
                    std::cout << "------------------------------------------------------------\n\n";
                    if (actual != nullptr) {
                        std::string generos = ""; actual->getGenerosId().recorrer([&](int generoId) {
                            if (!generos.empty()) { generos += ", "; } generos += devolverNombreGenero(generoId); });
                        establecerColor(11); std::cout << "Cancion: " << actual->getNombre() << "\n";
                        establecerColor(14); std::cout << "Artista: " << devolverNombreArtista(actual->getArtistaId()) << "\n";
                        std::cout << "Genero: " << generos << "\n";
                        std::cout << "Reproducciones: " << actual->getReproducciones() << "\n";
                    }
                    std::cout << "\n------------------------------------------------------------\n";
                    if (fila.esVacia()) {
                        establecerColor(12); std::cout << "   [Q] Salir\n"; std::cout << "   Ya no quedan canciones en la fila.\n";
                    }
                    else {
                        establecerColor(11); std::cout << "   [D] Siguiente de la fila"; establecerColor(12); std::cout << "   [Q] Salir\n";
                    }
                    tecla = _getch();
                    if (tecla == 'D' || tecla == 'd') {
                        if (!fila.esVacia()) {
                            actual = fila.front();
                            fila.dequeue();
                            registrarReproduccion(actual);
                            reproducidas++;
                        }
                        else {
                            continue;
                        }
                    }
                }
            }
        }
    }

    void generarCanciones() {
        establecerColor(14);
        int n = 0; std::cout << "\n   Ingrese cuantas canciones desea generar: "; std::cin >> n; validadorNumeros(n, "   Numero invalido. Intente nuevamente: ");
        char tipo = ' '; std::cout << "   Desea incluir canciones fuera de su rango musical?: \n";
        establecerColor(11); std::cout << "   [1] Si"; establecerColor(12); std::cout << "   [0] No"; tipo = _getch();
        std::vector<Cancion*> aux;
        if (tipo == '1') { canciones.recorrer([&](Cancion* c) { aux.push_back(c); }); }
        else if (tipo == '0') { canciones.recorrer([&](Cancion* c) { if (generoCoincideUsuario(c)) { aux.push_back(c); }}); }
        else { establecerColor(12); std::cout << "\n   Respuesta invalida."; (void)_getch(); }
        if (n > aux.size()) { n = aux.size(); } recorridoGenerativoRecursivo(n, aux);
    }

    void recorridoGenerativoRecursivo(int max, std::vector<Cancion*>& aux) {
        if (max == 0) return;
        int indice = rand() % aux.size(); fila.enqueue(aux[indice]); aux.erase(aux.begin() + indice);
        recorridoGenerativoRecursivo(max - 1, aux);
    }

    template <typename T>
    void rellenarVectorRecursivo(int indice, int max, std::vector<T>& original, std::vector<T>& nuevo) {
        if (max == 0) return;
        nuevo.push_back(original[indice]); 
        rellenarVectorRecursivo(indice - 1, max - 1, original, nuevo);
    }

    template <typename T>
    void rellenarVectorAleatorioRecursivo(int max, std::vector<T>& original, std::vector<T>& nuevo) {
        if (max == 0) return;
        int indice = rand() % original.size();
        nuevo.push_back(original[indice]); original.erase(original.begin() + indice);
        rellenarVectorAleatorioRecursivo(max - 1, original, nuevo);
    }

    void filtrarGustosRecursivo(std::vector<Cancion*>& enteras, std::vector<Cancion*>& recomendaciones) {
        if (recomendaciones.size() == 10 || enteras.empty()) return;
        int i = rand() % enteras.size(); if (generoCoincideUsuario(enteras[i])) { recomendaciones.push_back(enteras[i]); }
        enteras.erase(enteras.begin() + i);
        filtrarGustosRecursivo(enteras, recomendaciones);
    }

    void mostrarHistorial() {
        char opc = ' ', ajuste = '0';
        while (opc != 'Q' && opc != 'q') {
            establecerColor(14);
            system("cls");
            ui.menuHistorial();
            opc = _getch();
            switch (opc) {
            case '1': {
                if (historialCancion.size() <= 0) { 
                    establecerColor(12); std::cout << "\n  No se ha reproducido nada esta sesion.\n";
                    (void)_getch(); break;
                }
                system("cls");
                std::cout << "+                    HISTORIAL                         +\n";
                establecerColor(1); std::cout << std::string(56, '-') << std::endl;
                establecerColor(14); std::cout << std::left << std::setw(5) << "Id" << std::setw(30) << "NOMBRE" << std::setw(18) << "ARTISTA" << std::setw(8) << "REP" << std::endl;
                establecerColor(1); std::cout << std::string(56, '-') << std::endl;
                int n = 10, paginado = 0; if (n >= historialCancion.size()) { n = historialCancion.size(); } paginado = (historialCancion.size() - 1) - n;
                std::vector<Cancion*> vistaReproducciones; 
                rellenarVectorRecursivo(historialCancion.size() - 1, n, historialCancion, vistaReproducciones);
                if (ajusteReproducciones == '0') { for (int i = historialCancion.size() - 1; i > paginado; i--) { historialCancion[i]->imprimirInfo(devolverNombreArtista(historialCancion[i]->getArtistaId())); std::cout << std::endl;; } 
                establecerColor(1); std::cout << std::string(56, '-') << std::endl;
                establecerColor(12); std::cout << "   Presione cualquier tecla para salir." << std::endl; }
                else {
                    std::function<bool(Cancion* a, Cancion* b)> comparar;
                    switch (ajusteReproducciones)
                    {
                    case 'N': {
                        comparar = [&](Cancion* a, Cancion* b) { if (ordenAscendente) { return a->getNombre() < b->getNombre(); } else return a->getNombre() > b->getNombre(); };
                        break;
                    }
                    case 'I': {
                        comparar = [&](Cancion* a, Cancion* b) { if (ordenAscendente) { return a->getId() < b->getId(); } else return a->getId() > b->getId(); };
                        break;
                    }
                    case 'R': {
                        comparar = [&](Cancion* a, Cancion* b) { if (ordenAscendente) { return a->getReproducciones() > b->getReproducciones(); } else return a->getReproducciones() < b->getReproducciones(); };
                        break;
                    }
                    case 'X': {
                        comparar = [&](Cancion* a, Cancion* b) { if (ordenAscendente) { return devolverNombreArtista(a->getArtistaId()) < devolverNombreArtista(b->getArtistaId()); } else return devolverNombreArtista(a->getArtistaId()) > devolverNombreArtista(b->getArtistaId()); };
                        break;
                    }
                    default:
                        break;
                    }
                    heapSort(vistaReproducciones, comparar);
                    for (int i = 0; i < n; i++) { vistaReproducciones[i]->imprimirInfo(devolverNombreArtista(vistaReproducciones[i]->getArtistaId())); std::cout << std::endl; }
                    establecerColor(1); std::cout << std::string(56, '-') << std::endl;
                    establecerColor(12); std::cout << "   Presione cualquier tecla para salir." << std::endl;
                }
                (void)_getch();
                break;
            }
            case '2': {
                if (historialBusqueda.size() <= 0) {
                    establecerColor(12); std::cout << "\n  No se ha realizado ninguna busqueda esta sesion.\n";
                    (void)_getch(); break;
                }
                system("cls");
                std::cout << "+                    HISTORIAL                        +\n";
                establecerColor(1); std::cout << std::string(55, '-') << std::endl;
                establecerColor(14); std::cout << std::left << std::setw(11) << "TIPO" << std::setw(20) << "BUSQUEDA" << std::setw(20) << "RESULTADO" << std::endl;
                establecerColor(1); std::cout << std::string(55, '-') << std::endl;
                int n = 10, paginado = 0; if (n >= historialBusqueda.size()) { n = historialBusqueda.size(); } paginado = (historialBusqueda.size() - 1) - n;
                std::vector<Busqueda> vistaBusqueda;
                rellenarVectorRecursivo(historialBusqueda.size() - 1, n, historialBusqueda, vistaBusqueda);
                if (ajusteBusquedas == '0') { for (int i = historialBusqueda.size() - 1; i > paginado; i--) { historialBusqueda[i].imprimirInfo(); } 
                establecerColor(1); std::cout << std::string(55, '-') << std::endl;
                establecerColor(12); std::cout << "   Presione cualquier tecla para salir." << std::endl;
                }
                else {
                    std::function<bool(Busqueda a, Busqueda b)> comparar;
                    switch (ajusteBusquedas)
                    {
                    case 'T': {
                        comparar = [&](Busqueda a, Busqueda b) { if (ordenAscendente) { return a.getTipo() < b.getTipo(); } else return a.getTipo() > b.getTipo(); };
                        break;
                    }
                    case 'B': {
                        comparar = [&](Busqueda a, Busqueda b) { if (ordenAscendente) { return a.getDato() < b.getDato(); } else return a.getDato() > b.getDato(); };
                        break;
                    }
                    case 'E': {
                        comparar = [&](Busqueda a, Busqueda b) { if (ordenAscendente) { return a.getEncontrado() > b.getEncontrado(); } else return a.getEncontrado() < b.getEncontrado(); };
                        break;
                    }
                    default:
                        break;
                    }
                    quickSort(vistaBusqueda, 0, n - 1, comparar);
                    for (int i = 0; i < n; i++) { vistaBusqueda[i].imprimirInfo(); }
                    establecerColor(1); std::cout << std::string(55, '-') << std::endl;
                    establecerColor(12); std::cout << "   Presione cualquier tecla para salir." << std::endl;
                }
                (void)_getch();
                break;
            }
            case '3': {
                establecerColor(14);
                ui.menuAjustes(ajusteReproducciones, ajusteBusquedas, ordenAscendente);
                establecerColor(14);
                ajuste = _getch(); ajuste = std::toupper(ajuste);
                switch (ajuste)
                {
                case '0': {
                    ajusteReproducciones = '0';
                    ajusteBusquedas = '0';
                    break;
                }
                case 'N': {
                    ajusteReproducciones = 'N';
                    break;
                }
                case 'I': {
                    ajusteReproducciones = 'I';
                    break;
                }
                case 'R': {
                    ajusteReproducciones = 'R';
                    break;
                }
                case 'X': {
                    ajusteReproducciones = 'X';
                    break;
                }
                case 'T': {
                    ajusteBusquedas = 'T';
                    break;
                }
                case 'B': {
                    ajusteBusquedas = 'B';
                    break;
                }
                case 'E': {
                    ajusteBusquedas = 'E';
                    break;
                }
                case 'A': {
                    ordenAscendente = true;
                    break;
                }
                case 'D': {
                    ordenAscendente = false;
                    break;
                }
                default:
                    break;
                }
                break;
            }
            default: {
                break;
            }
            }
        }
    }

    void recomendacionSemanal(std::vector<Cancion*> recomendaciones) {
       char opc = ' '; std::function<bool(Cancion* a, Cancion* b)> comparar = [&](Cancion* a, Cancion* b) { return a->getNombre() < b->getNombre(); };
       mergeSort(recomendaciones, 0, recomendaciones.size() - 1, comparar);
       while (opc != 'Q' && opc != 'q') {
            establecerColor(7);
            system("cls");
            std::cout << "+               RECOMENDACION SEMANAL                  +\n";
            establecerColor(1); std::cout << std::string(56, '-') << std::endl;
            establecerColor(14); std::cout << std::left << std::setw(5) << "Id" << std::setw(30) << "NOMBRE" << std::setw(18) << "ARTISTA" << std::setw(8) << "REP" << std::endl;
            establecerColor(1); std::cout << std::string(56, '-') << std::endl;
            for (int i = 0; i < recomendaciones.size(); i++) { recomendaciones[i]->imprimirInfo(devolverNombreArtista(recomendaciones[i]->getArtistaId())); std::cout << std::endl; } 
            establecerColor(1); std::cout << std::string(56, '-') << std::endl; establecerColor(11); std::cout << std::endl;
            std::cout << "   [1] Buscar canciones similares" << std::endl;
            std::cout << "   [2] Agregar a fila" << std::endl; establecerColor(12);
            std::cout << "   [Q] Salir" << std::endl;
            opc = _getch();
            switch (opc)
            {
            case '1': {
                explorarRelacionadas();
                break;
            }
            case '2': {
                agregarFila();
                break;
            }
            default:
                break;
            }
        }
    }

    void explorarRelacionadas() {
        system("cls"); char opc = ' ';
        int id = 0; establecerColor(14); std::cout << "\n  Ingrese el Id de una cancion: "; establecerColor(11); std::cin >> id;
        validadorNumeros(id, "  Id invalido. Intente nuevamente: "); 
        std::vector<Cancion*> relacionadasTotal; 
        Cancion* base = busquedaId.buscar(id);
        grafoCanciones.recorrerAmplitud(id, 1, [&](int id) { Cancion* c = busquedaId.buscar(id); if (c != nullptr) { relacionadasTotal.push_back(c); }});
        std::vector<Cancion*> relacionadas = relacionadasTotal; std::vector<Cancion*> vistaRelacionadas;
        int n = 10; if (n >= relacionadas.size()) { n = relacionadas.size(); } 
        rellenarVectorAleatorioRecursivo(n, relacionadas, vistaRelacionadas);
        if (base == nullptr) { establecerColor(12); std::cout << "No se encontro la cancion.\n"; establecerColor(7); (void)_getch(); return; }
        while (opc != 'Q' && opc != 'q') {
            establecerColor(14);
            system("cls");
            establecerColor(14); std::cout << "Canciones relacionadas con "; establecerColor(11); std::cout << base->getNombre(); establecerColor(14); std::cout << ":\n\n";
            std::cout << std::left << std::setw(5) << "Id" << std::setw(30) << "NOMBRE" << std::setw(18) << "ARTISTA" << std::setw(8) << "REP" << "GENEROS" << std::endl;
            std::cout << std::string(80, '-') << std::endl; establecerColor(1);
            for (int i = 0; i < n; i++) { vistaRelacionadas[i]->imprimirInfo(devolverNombreArtista(vistaRelacionadas[i]->getArtistaId())); 
            ListaSimple<int>& temp = vistaRelacionadas[i]->getGenerosId(); bool first = true; temp.recorrer([&](int id) { 
            if (first != true) { std::cout << ", "; } std::cout << devolverNombreGenero(id); first = false; }); std::cout << std::endl; }
            std::cout << std::string(80, '-') << std::endl; 
            establecerColor(11); std::cout << "   [1] Buscar otras   [2] Agregar a fila";
            establecerColor(12); std::cout << "   [Q] Salir\n\n"; establecerColor(14);
            opc = _getch();
            switch (opc)
            {
            case '1': {
                vistaRelacionadas.clear();
                relacionadas = relacionadasTotal;
                rellenarVectorAleatorioRecursivo(n, relacionadas, vistaRelacionadas);
                break;
            }
            case '2': {
                agregarFila();
                break;
            }
            default:
                break;
            }
        }
    }

    void mostrarGenerosDisponibles() {
        ui.marcoGenerosDisponibles();
        generos.recorrer([](Genero* g) {
            establecerColor(8);  std::cout << "  |  ";
            establecerColor(11); std::cout << std::left << std::setw(3) << g->getId();
            establecerColor(8);  std::cout << "|  ";
            establecerColor(7);  std::cout << std::setw(27) << g->getNombre();
            establecerColor(8);  std::cout << "|\n";
            });
        establecerColor(11);
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

    bool estanRelacionadas(Cancion* a, Cancion* b) {
        bool coincide = false;
        if (a->getArtistaId() == b->getArtistaId()) { coincide = true; }
        ListaSimple<int>& generosA = a->getGenerosId();
        ListaSimple<int>& generosB = b->getGenerosId();
        generosA.recorrer([&](int generoA) { if (generosB.existeNodo([&](int generoB) { return generoA == generoB;})) { coincide = true; }});
        return coincide;
    }

    void construirGrafoCanciones() {
        grafoCanciones = Grafo<int>();
        canciones.recorrer([&](Cancion* c) { grafoCanciones.agregarVertice(c->getId()); });
        canciones.recorrer([&](Cancion* a) { canciones.recorrer([&](Cancion* b) { if (a->getId() < b->getId() && estanRelacionadas(a, b)) { grafoCanciones.agregarArista(a->getId(), b->getId()); }}); });
    }

    void validadorNumeros(int& n, std::string texto) {
        while (std::cin.fail() || n <= 0 || std::cin.peek() != '\n') {
            establecerColor(14);
            std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << texto; establecerColor(11); std::cin >> n;
        } std::cin.ignore(); 
        establecerColor(14);
    }

    void validadorTexto(std::string& texto, std::string imprimir) {
        do
        {
            establecerColor(14); std::cout << imprimir;
            establecerColor(11); std::getline(std::cin, texto);
            while (!texto.empty() && texto.back() == ' ') { texto.pop_back(); }
        } while (texto.empty());
        establecerColor(14);
    }

    void registrarReproduccion(Cancion* c) {
        if (c != nullptr) { c->incrementarReproducciones(); };
        historialCancion.push_back(c);
        fm.guardarCanciones("archivos/canciones.txt", canciones);
    }

    bool existeUsername(std::string username) {
        return usuarios.existeNodo([&](Usuario* u) { return u->getUsername() == username; });
    }

    bool existeGenero(int generoId) {
        return generos.existeNodo([&](Genero* g) { return g->getId() == generoId; });
    }

    bool generoCoincideUsuario(Cancion* c) {
        bool coincide = false;
        ListaSimple<int>& auxCancion = c->getGenerosId(); ListaSimple<int>& auxUsuario = usuarioActual->getGenerosPreferidos();
        auxCancion.recorrer([&](int c) { if (auxUsuario.existeNodo([&](int u) { return c == u; })) { coincide = true; } });
        return coincide;
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
    Sistema() : usuarioActual(nullptr), busquedaId(101, [](int clave) { return clave; }), busquedaNombre(101, [](std::string clave) {
        int acumulador = 0; for (int i = 0; i < clave.length(); i++) { acumulador++; } return acumulador; }), busquedaArtista(101, [](std::string clave) { 
        int acumulador = 0; for (int i = 0; i < clave.length(); i++) { acumulador++; } return acumulador; }), busquedaGenero(101, [](std::string clave) {
        int acumulador = 0; for (int i = 0; i < clave.length(); i++) { acumulador++; } return acumulador; }) {
        catalogoNombre = Arbol<Cancion*>([](Cancion* a, Cancion* b) {
            return a->getNombre() < b->getNombre();
            });
        catalogoId = ArbolAVL<Cancion*>([](Cancion* a, Cancion* b) {
            return a->getId() < b->getId();
            });
        catalogoReproducciones = ArbolAVL<Cancion*>([](Cancion* a, Cancion* b) {
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
            busquedaId.insertar(aux, aux->getId());
            busquedaNombre.insertar(aux, aux->getNombre());
            std::string nombreArtista = devolverNombreArtista(aux->getArtistaId()); 
            ListaSimple<Cancion*>* cancionesArtista = busquedaArtista.buscar(nombreArtista);
            if (cancionesArtista == nullptr) { cancionesArtista = new ListaSimple<Cancion*>; busquedaArtista.insertar(cancionesArtista, nombreArtista); }
            cancionesArtista->anadirItem(aux);
            ListaSimple<Cancion*>* cancionesGenero;
            ListaSimple<int>& auxGeneros = aux->getGenerosId(); auxGeneros.recorrer([&](int x) { std::string nombreGenero = devolverNombreGenero(x); cancionesGenero = busquedaGenero.buscar(nombreGenero); 
            if (cancionesGenero == nullptr) { cancionesGenero = new ListaSimple<Cancion*>; busquedaGenero.insertar(cancionesGenero, nombreGenero); } cancionesGenero->anadirItem(aux); });
            });
        construirGrafoCanciones();
        preLogin();
    }
};