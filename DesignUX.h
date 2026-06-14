#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>

void configurarVentana() {
    HWND consola = GetConsoleWindow();
    MoveWindow(consola, 100, 50, 900, 700, TRUE);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;
    cursor.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursor);
}

void moverCursor(int columna, int fila) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD posicion = { (SHORT)columna, (SHORT)fila };
    SetConsoleCursorPosition(hConsole, posicion);
}

void establecerColor(int color_codigo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (color_codigo) {
    case 0:  SetConsoleTextAttribute(hConsole, 1);  break;  // Azul oscuro
    case 1:  SetConsoleTextAttribute(hConsole, 7);  break;  // Gris claro
    case 2:  SetConsoleTextAttribute(hConsole, 9);  break;  // Azul claro
    case 3:  SetConsoleTextAttribute(hConsole, 2);  break;  // Verde oscuro
    case 4:  SetConsoleTextAttribute(hConsole, 4);  break;  // Rojo oscuro
    case 5:  SetConsoleTextAttribute(hConsole, 6);  break;  // Amarillo oscuro / marrón
    case 6:  SetConsoleTextAttribute(hConsole, 0);  break;  // Negro
    case 7:  SetConsoleTextAttribute(hConsole, 3);  break;  // Cian oscuro
    case 8:  SetConsoleTextAttribute(hConsole, 8);  break;  // Gris oscuro
    case 9:  SetConsoleTextAttribute(hConsole, 5);  break;  // Morado oscuro
    case 10: SetConsoleTextAttribute(hConsole, 10); break;  // Verde claro
    case 11: SetConsoleTextAttribute(hConsole, 11); break;  // Cian claro
    case 12: SetConsoleTextAttribute(hConsole, 12); break;  // Rojo claro
    case 13: SetConsoleTextAttribute(hConsole, 13); break;  // Morado claro
    case 14: SetConsoleTextAttribute(hConsole, 14); break;  // Amarillo claro
    case 15: SetConsoleTextAttribute(hConsole, 15); break;  // Blanco
    default: SetConsoleTextAttribute(hConsole, 7);  break;  // Gris claro por defecto
    }
}

void usarColor(short colorIndex) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorIndex);
}

std::string acortar(std::string texto, int cantidadAcortar) {
    if (texto.size() <= cantidadAcortar) { return texto; }
    return texto.substr(0, cantidadAcortar - 3) + "...";
}

class DesignUX
{
public:
    DesignUX() {};
    void imprimirTitulo(int color) {
        establecerColor(color);
        std::cout << R"(
                 %#********++++++++++**#%
              +============================+
           *==================================*
          =======================================
         #=========+*#%@@@@@@@%#*+================# 
        %====+@@@@@@@@@@@@@@@@@@@@@@@@@@#+=========#
       +====#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+======+
      #=======*%#*=================+*%@@@@@@@@#=====#
      =========+#%@@@@@@@@@@@@@@%#*+========+========
      =========@@@@@@@@@@@@@@@@@@@@@@@@@+============
      *==========+*##%%@@@@@%%#*+========+==========*
       ========@@@@@@@@@@@@@@@@@@@@@#===============
       *=============================%@@===========*
         %========================================#
            +==================================+
               ==============================%
                    +====================+
                        %*+========+*#
                        )";
    }

    void imprimirLogoSpotify(int color) {
        establecerColor(color);
        std::cout << "\n";
        std::cout << "  $$$$$$\\  $$$$$$$\\   $$$$$$\\ $$$$$$$$\\ $$$$$$\\ $$$$$$$$\\ $$\\   $$\\\n";
        std::cout << " $$  __$$\\ $$  __$$\\ $$  __$$\\\\__$$  __|\_$$  _|$$  _____|$$ |  $$ |\n";
        std::cout << " $$ /  \\__|$$ |  $$ |$$ /  $$ |  $$ |    $$ |  $$ |      $$ |  $$ |\n";
        std::cout << " \\$$$$$$\\  $$$$$$$  |$$ |  $$ |  $$ |    $$ |  $$$$$\\    \\$$$$$$$ |\n";
        std::cout << "  \\____$$\\ $$  ____/ $$ |  $$ |  $$ |    $$ |  $$  __|    \\_____$$ |\n";
        std::cout << " $$\\  $$ | $$ |      $$ |  $$ |  $$ |    $$ |  $$ |             $$ |\n";
        std::cout << " \\$$$$$$  | $$ |     \\$$$$$$  |  $$ |  $$$$$$\\ $$ |             $$ |\n";
        std::cout << "  \\______/  \\__|      \\______/   \\__|  \\______|\\__|             \\__|\n";

    }

    void animarTitulo() {
        int colores[] = { 1, 2, 3, 4, 5, 9, 11, 12, 13, 14, 15 };
        for (int i = 0; i < 14; i++) {
            int color = colores[rand() % 11];
            moverCursor(0, 0);
            imprimirTitulo(color);
            std::cout << std::endl;
            Sleep(57);
        }
        moverCursor(0, 0);
        imprimirTitulo(10);
        std::cout << std::endl;
    }

    void pantallaBienvenida() {
        animarTitulo();
        //imprimirLogoSpotify(10);
        establecerColor(8);
        std::cout << "  +-------------------------------------------------+\n";
        establecerColor(10);
        std::cout << "  |             Bienvenido a Spotify!               |\n";
        establecerColor(8);
        std::cout << "  +-------------------------------------------------+\n";
        establecerColor(8);  std::cout << "  |    ";
        establecerColor(11); std::cout << "[1]";
        establecerColor(7);  std::cout << "  Iniciar sesion                          ";
        establecerColor(8);  std::cout << "|\n";
        establecerColor(8);  std::cout << "  |    ";
        establecerColor(11); std::cout << "[2]";
        establecerColor(7);  std::cout << "  Registrarse                             ";
        establecerColor(8);  std::cout << "|\n";
        establecerColor(8);
        std::cout << "  |                                                 |\n";
        establecerColor(8);  std::cout << "  |    ";
        establecerColor(12); std::cout << "[3]";
        establecerColor(12); std::cout << "  Salir                                   ";
        establecerColor(8);  std::cout << "|\n";
        std::cout << "  +-------------------------------------------------+\n";
        establecerColor(8);
        std::cout << "  >> ";
    }

    void tituloFicha(const std::string titulo, int xPos, int yPos) {
        system("cls");
        establecerColor(10);
        int x = xPos;
        int y = yPos;
        int ancho = titulo.length() + 4;

        moverCursor(x, y);
        for (int i = 0; i < ancho; i++) {
            std::cout << "=";
        }
        moverCursor(x, y + 1);
        std::cout << "/";
        moverCursor(x + ancho - 1, y + 1);
        std::cout << "\\";

        moverCursor(x, y + 2);
        std::cout << "|";
        moverCursor(x + ancho - 1, y + 2);
        std::cout << "|";

        moverCursor(x, y + 3);
        std::cout << "\\";
        moverCursor(x + ancho - 1, y + 3);
        std::cout << "/";

        moverCursor(x + 2, y + 2);
        std::cout << titulo;
        establecerColor(1);
    }

    void marco() {
        establecerColor(10);
        int x = 33;
        int y = 10;
        int ancho = 55;
        int alto = 13;

        moverCursor(x, y);
        for (int i = 0; i < ancho; i++) std::cout << "=";

        for (int i = 1; i < alto; i++) {
            moverCursor(x, y + i);
            std::cout << "|";
            moverCursor(x + ancho - 1, y + i);
            std::cout << "|";
        }

        moverCursor(x, y + alto);
        for (int i = 0; i < ancho; i++) std::cout << "=";

        establecerColor(1);
    }
    void marcoIniciarSesion() {
        establecerColor(10);
        std::cout << "\n  +==================================================+\n";
        std::cout << "  |             *** INICIAR SESION ***              |\n";
        std::cout << "  +==================================================+\n\n";
        establecerColor(8);
        std::cout << "  +--------------------------------------------------+\n";
        establecerColor(8);  std::cout << "  |  ";
        establecerColor(14); std::cout << "Username";
        establecerColor(8);  std::cout << "  |  >> ";
        establecerColor(7);
    }

    void marco2() {

        establecerColor(10);
        std::cout << "\n";
        std::cout << "  $$$$$$\\  $$$$$$$\\   $$$$$$\\ $$$$$$$$\\ $$$$$$\\ $$$$$$$$\\ $$\\   $$\\\n";
        std::cout << " $$  __$$\\ $$  __$$\\ $$  __$$\\\\__$$  __|\_$$  _|$$  _____|$$ |  $$ |\n";
        std::cout << " $$ /  \\__|$$ |  $$ |$$ /  $$ |  $$ |    $$ |  $$ |      $$ |  $$ |\n";
        std::cout << " \\$$$$$$\\  $$$$$$$  |$$ |  $$ |  $$ |    $$ |  $$$$$\\    \\$$$$$$$ |\n";
        std::cout << "  \\____$$\\ $$  ____/ $$ |  $$ |  $$ |    $$ |  $$  __|    \\_____$$ |\n";
        std::cout << " $$\\  $$ | $$ |      $$ |  $$ |  $$ |    $$ |  $$ |             $$ |\n";
        std::cout << " \\$$$$$$  | $$ |     \\$$$$$$  |  $$ |  $$$$$$\\ $$ |             $$ |\n";
        std::cout << "  \\______/  \\__|      \\______/   \\__|  \\______|\\__|             \\__|\n";

        establecerColor(8);
        std::cout << "\n  ================================================\n";
        establecerColor(14);
        std::cout << "    Bienvenido, ";

        establecerColor(8);
        std::cout << "\n  ================================================\n";
        establecerColor(8);
        std::cout << "\n  +---------+-------------------------------+\n";
        std::cout << "  |  tecla  |  accion                       |\n";
        std::cout << "  +---------+-------------------------------+\n";
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(11); std::cout << "[1]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(7);  std::cout << "Ver catalogo                 ";
        establecerColor(8);  std::cout << "|\n";
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(11); std::cout << "[2]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(7);  std::cout << "Mis playlists                ";
        establecerColor(8);  std::cout << "|\n";
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(11); std::cout << "[3]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(7);  std::cout << "Fila de reproduccion         ";
        establecerColor(8);  std::cout << "|\n";
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(11); std::cout << "[4]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(7);  std::cout << "Historial                    ";
        establecerColor(8);  std::cout << "|\n";
        establecerColor(8);
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(11); std::cout << "[5]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(7);  std::cout << "Top 10 global                ";
        establecerColor(8);  std::cout << "|\n";
        establecerColor(8);
        std::cout << "  +---------+-------------------------------+\n";
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(12); std::cout << "[6]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(12); std::cout << "Cerrar sesion                ";
        establecerColor(8);  std::cout << "|\n";
        std::cout << "  +---------+-------------------------------+\n\n";
        establecerColor(7);
    }

    void marcoPlaylists() {
        establecerColor(10);
        establecerColor(8);
        std::cout << "  +----+------------------------+-------------+-----------+\n";
        establecerColor(14);
        std::cout << "  | ID | Nombre                 | Tipo        | Canciones |\n";
        establecerColor(8);
        std::cout << "  +----+------------------------+-------------+-----------+\n";
        establecerColor(7);
    }

    void marcoPlaylistsOpciones() {
        establecerColor(8);
        std::cout << "  +----+------------------------+-------------+-----------+\n";
        std::cout << "\n";
        std::cout << "  +---------+-------------------------------+\n";
        establecerColor(14);
        std::cout << "  |  tecla  |  accion                       |\n";
        establecerColor(8);
        std::cout << "  +---------+-------------------------------+\n";
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(11); std::cout << "[1]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(7);  std::cout << "Crear playlist manual        ";
        establecerColor(8);  std::cout << "|\n";
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(11); std::cout << "[2]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(7);  std::cout << "Crear playlist automatica    ";
        establecerColor(8);  std::cout << "|\n";
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(11); std::cout << "[3]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(7);  std::cout << "Abrir playlist               ";
        establecerColor(8);  std::cout << "|\n";
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(11); std::cout << "[4]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(7);  std::cout << "Cambiar orden                ";
        establecerColor(8);  std::cout << "|\n";
        std::cout << "  |                                         |\n";
        establecerColor(8);  std::cout << "  |   ";
        establecerColor(12); std::cout << "[Q]";
        establecerColor(8);  std::cout << "   |  ";
        establecerColor(12); std::cout << "Volver                       ";
        establecerColor(8);  std::cout << "|\n";
        std::cout << "  +---------+-------------------------------+\n";
        establecerColor(7);
    }
    void marcoRegistro() {
        establecerColor(10);
        std::cout << "\n  +==================================================+\n";
        std::cout << "  |               *** REGISTRO ***                  |\n";
        std::cout << "  +==================================================+\n\n";
        establecerColor(8);
        std::cout << "  +--------------------------------------------------+\n";
        establecerColor(8);  std::cout << "  |  ";
        establecerColor(14); std::cout << "Nombre   ";
        establecerColor(8);  std::cout << "|  >> ";
        establecerColor(7);
    }

    void marcoRegistroExito() {
        establecerColor(10);
        std::cout << "\n  +==================================================+\n";
        std::cout << "  |          *** CUENTA CREADA CON EXITO ***         |\n";
        std::cout << "  +==================================================+\n\n";
        establecerColor(8);
        std::cout << "  +--------------------------------------------------+\n\n";
        establecerColor(14);
        std::cout << "  Ahora puedes iniciar sesion con tu username y password.\n";
        std::cout << "  Presiona cualquier tecla para volver al menu...";
        establecerColor(7);
    }
};

