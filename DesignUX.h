#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
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

    void imprimirSpotifyTexto(int color) {
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

    void animarTexto(std::string texto) {
        int tam = texto.length();
        for (int i = 0; i < tam; i++)
        {
            std::cout << texto[i];
            Sleep(70);
        }
    }

    void pantallaBienvenida() {
        animarTitulo();
        establecerColor(10); moverCursor(16, 21); animarTexto("Bienvenido a Spotify!");
        establecerColor(8); moverCursor(0, 20); std::cout << "  +-------------------------------------------------+";
        moverCursor(2, 21); std::cout << "|";
        moverCursor(52, 21); std::cout << "|";
        moverCursor(0, 22); std::cout << "  +-------------------------------------------------+\n";
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

    void tituloFicha(const std::string titulo, int xPos, int yPos, int color) {
        system("cls");
        establecerColor(color);
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
        establecerColor(11);
        std::cout << "\n  +==================================================+\n";
        std::cout << "  |             *** INICIAR SESION ***               |\n";
        std::cout << "  +==================================================+\n\n";
        establecerColor(8);
        std::cout << "  +--------------------------------------------------+\n";
        establecerColor(8);  std::cout << "  |  ";
        establecerColor(14); std::cout << "Username";
        establecerColor(8);  std::cout << "  |  >> ";
        establecerColor(7);
    }

    void marcoGenerosDisponibles() {
        establecerColor(11);
        std::cout << "  +-----------------------------------+\n";
        establecerColor(11);
        std::cout << "  |        GENEROS DISPONIBLES        |\n";
        establecerColor(11);
        std::cout << "  +-----------------------------------+\n";
    }
    void marcoPostLogin() {
        establecerColor(10);
        imprimirSpotifyTexto(10);
        establecerColor(14); std::cout << "\n  ================================================\n";
        establecerColor(11); std::cout << "    Bienvenido, ";
        establecerColor(14); std::cout << "\n  ================================================\n";
        std::cout << "\n  +---------+-------------------------------+\n";
        std::cout << "  |"; establecerColor(11); std::cout << "  tecla  "; establecerColor(14); std::cout << "|";  establecerColor(11); 
        std::cout << "  accion"; establecerColor(14); std::cout << "                       |\n";
        std::cout << "  +---------+-------------------------------+\n";
        establecerColor(14);  std::cout << "  |   ";
        establecerColor(7); std::cout << "[1]";
        establecerColor(14);  std::cout << "   |  ";
        establecerColor(11);  std::cout << "Ver catalogo                 ";
        establecerColor(14);  std::cout << "|\n";
        establecerColor(14);  std::cout << "  |   ";
        establecerColor(7); std::cout << "[2]";
        establecerColor(14);  std::cout << "   |  ";
        establecerColor(11);  std::cout << "Realizar busquedas           ";
        establecerColor(14);  std::cout << "|\n";
        establecerColor(14);  std::cout << "  |   ";
        establecerColor(7); std::cout << "[3]";
        establecerColor(14);  std::cout << "   |  ";
        establecerColor(11);  std::cout << "Fila de reproduccion         ";
        establecerColor(14);  std::cout << "|\n";
        establecerColor(14);  std::cout << "  |   ";
        establecerColor(7); std::cout << "[4]";
        establecerColor(14);  std::cout << "   |  ";
        establecerColor(11);  std::cout << "Historial                    ";
        establecerColor(14);  std::cout << "|\n";
        establecerColor(14);
        establecerColor(14);  std::cout << "  |   ";
        establecerColor(7); std::cout << "[5]";
        establecerColor(14);  std::cout << "   |  ";
        establecerColor(11);  std::cout << "Recomendacion semanal        ";
        establecerColor(14);  std::cout << "|\n";
        establecerColor(14);
        std::cout << "  +---------+-------------------------------+\n";
        establecerColor(14);  std::cout << "  |   ";
        establecerColor(12); std::cout << "[6]";
        establecerColor(14);  std::cout << "   |  ";
        establecerColor(12); std::cout << "Cerrar sesion                ";
        establecerColor(14);  std::cout << "|\n";
        std::cout << "  +---------+-------------------------------+\n\n";
        establecerColor(7);
    }

    void marcoRegistro() {
        establecerColor(11);
        std::cout << "\n  +==================================================+\n";
        std::cout << "  |               *** REGISTRO ***                   |\n";
        std::cout << "  +==================================================+\n\n";
        establecerColor(8);
        std::cout << "  +--------------------------------------------------+\n";
        establecerColor(8);  std::cout << "  |  ";
        establecerColor(14); std::cout << "Nombre   ";
        establecerColor(8);  std::cout << "|  >> ";
        establecerColor(7);
    }

    void marcoRegistroExito() {
        establecerColor(11);
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

    void titulo(const std::string& titulo, int anchoTotal = 43) {
        establecerColor(14);
        std::cout << "\n  +" << std::string(anchoTotal, '=') << "+\n";
        std::string texto = "*** " + titulo + " ***";
        int hueco = anchoTotal - texto.length();
        if (hueco < 0) hueco = 0;
        int izq = hueco / 2, der = hueco - izq; establecerColor(14);
        std::cout << "  |" << std::string(izq, ' '); establecerColor(11); std::cout << texto; establecerColor(14); std::cout << std::string(der, ' ') << "|\n";
        std::cout << "  +" << std::string(anchoTotal, '=') << "+\n\n";
    }

    void marcoTexto(const std::string& titulo, int anchoTotal = 43) {
        establecerColor(14);
        std::cout << "\n  +" << std::string(anchoTotal, '=') << "+\n";
        std::string texto = titulo;
        int hueco = anchoTotal - texto.length();
        if (hueco < 0) hueco = 0;
        int izq = hueco / 2, der = hueco - izq;
        std::cout << "  |" << std::string(izq, ' '); establecerColor(11); std::cout << texto; establecerColor(14); std::cout << std::string(der, ' ') << "|\n";
        std::cout << "  +" << std::string(anchoTotal, '=') << "+\n\n";
    }

    void bordeOpciones(int anchoAccion = 33) {
        establecerColor(14);
        std::cout << "  +---------+" << std::string(anchoAccion, '-') << "+\n";
    }

    void cabeceraOpciones(int anchoAccion = 33) {
        bordeOpciones(anchoAccion);
        establecerColor(14);
        std::cout << "  |  tecla  |";
        establecerColor(11); std::cout << "  ";
        establecerColor(14); std::cout << std::left << std::setw(anchoAccion - 2) << "accion";
        establecerColor(11); std::cout << "|\n";
        bordeOpciones(anchoAccion);
    }

    void imprimirOpcion(const std::string& tecla, const std::string& accion, int colorTecla = 11, int anchoAccion = 33) {
        std::string t = "[" + tecla + "]";
        int hueco = 9 - t.length();
        if (hueco < 0) hueco = 0;
        int izq = hueco / 2, der = hueco - izq;
        establecerColor(14);  std::cout << "  |" << std::string(izq, ' ');
        establecerColor(colorTecla); std::cout << t;
        establecerColor(14);  std::cout << std::string(der, ' ') << "|  ";
        establecerColor(colorTecla == 12 ? 12 : 7);
        std::cout << std::left << std::setw(anchoAccion - 2) << accion;
        establecerColor(14);  std::cout << "|\n";
    }

    void menuBusqueda() {
        titulo("REALIZAR BUSQUEDA");
        cabeceraOpciones();
        imprimirOpcion("1", "Buscar por Id");
        imprimirOpcion("2", "Buscar por Nombre");
        imprimirOpcion("3", "Buscar por Artista");
        imprimirOpcion("4", "Buscar por Genero");
        bordeOpciones();
        imprimirOpcion("Q", "Salir", 12);
        bordeOpciones();
        establecerColor(7);
    }

    void menuHistorial() {
        titulo("HISTORIAL");
        cabeceraOpciones();
        imprimirOpcion("1", "Mostrar por reproducciones");
        imprimirOpcion("2", "Mostrar por busqueda");
        imprimirOpcion("3", "Ajustes");
        bordeOpciones();
        imprimirOpcion("Q", "Salir", 12);
        bordeOpciones();
        establecerColor(7);
    }

    void menuAjustes(char ajusteReproducciones, char ajusteBusquedas, bool ordenAscendente) {
        establecerColor(8);
        std::cout << "  +-------------------------------------------------------------+\n";
        establecerColor(14); std::cout << "  |  General        -- ";
        establecerColor(11); std::cout << "[0]"; establecerColor(7); std::cout << " Restablecer";
        std::cout << std::string(15, ' '); establecerColor(8); std::cout << "           |\n";

        establecerColor(14); std::cout << "  |  Reproducciones -- ";
        establecerColor(11); std::cout << "[N]"; establecerColor(7); std::cout << " Nombre  ";
        establecerColor(11); std::cout << "[I]"; establecerColor(7); std::cout << " Id  ";
        establecerColor(11); std::cout << "[R]"; establecerColor(7); std::cout << " Rep  ";
        establecerColor(11); std::cout << "[X]"; establecerColor(7); std::cout << " Artista";
        establecerColor(8); std::cout << " |\n";

        establecerColor(14); std::cout << "  |  Busqueda       -- ";
        establecerColor(11); std::cout << "[T]"; establecerColor(7); std::cout << " Tipo  ";
        establecerColor(11); std::cout << "[B]"; establecerColor(7); std::cout << " Busqueda  ";
        establecerColor(11); std::cout << "[E]"; establecerColor(7); std::cout << " Encontrado";
        establecerColor(8); std::cout << "   |\n";

        establecerColor(14); std::cout << "  |  Direccion      -- ";
        establecerColor(11); std::cout << "[A]"; establecerColor(7); std::cout << " Ascendente  ";
        establecerColor(11); std::cout << "[D]"; establecerColor(7); std::cout << " Descendiente";
        establecerColor(8); std::cout << "         |\n";
        std::cout << "  +-------------------------------------------------------------+\n";

        establecerColor(14); std::cout << "  Ajuste actual -> ";
        establecerColor(11); std::cout << ajusteReproducciones << "  " << ajusteBusquedas;
        establecerColor(14); std::cout << "  --  ";
        establecerColor(11); std::cout << (ordenAscendente ? "Ascendente" : "Descendiente");
    }
};

