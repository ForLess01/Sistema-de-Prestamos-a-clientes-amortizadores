#include "Parche.h"
#include <cstring>
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

int random(int max)
{
    // Inicializar la semilla para generar n�meros realmente aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generar un n�mero aleatorio entre 0 y max-1
    return std::rand() % max;
}

void strcpy(char destino[], const unsigned char origen[])
{
    strcpy(reinterpret_cast<char *>(destino), reinterpret_cast<const char *>(origen));
}
void strcpy(char unsigned destino[], const char origen[])
{
    strcpy(reinterpret_cast<char *>(destino), reinterpret_cast<const char *>(origen));
}

void clreol()
{
    // Obtener la posici�n actual del cursor en la consola
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    // Calcular el n�mero de caracteres para borrar en la l�nea actual
    int charsToClear = csbi.dwSize.X - csbi.dwCursorPosition.X;

    // Llenar la l�nea con espacios para borrarla
    std::cout << std::string(charsToClear, ' ');
}
