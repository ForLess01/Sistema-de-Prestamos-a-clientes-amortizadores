// ....................................................... .
// Programa c01_01.cpp
// Procesos Secuenciales
// ..................................... ···-···············

#include <conio.h>  // apra clrscr(), getch()
#include <iostream> // para cin, cout
/*
Para sustituir getch(), solo necesitamos: cin.get(); la cual está en <stdio.h>. Si no funciona entonces tendremos que ponerla dos veces: cin.get();cin.get();, la cuestión es algo complicada de explicar.
Para sustituir clrscr(), solo necesitamos escribir system("cls"); la cual está en <iostream> (es sin .h, se definiría así: #include<iostream>).
Gotoxy() es algo vanal, y además se puede sustituir usando n (espacio hacia abajo) y t (espacio hacia la derecha) dentro de un printf();
Y la verdad es que cualquiera te agradecerá que no le pongas fondo rosa y letras amarillas a tus programas
*/

/*
GPT
El uso de void main() como punto de entrada en un programa en C o C++ no es una práctica estándar y puede llevar a comportamientos indefinidos en algunos compiladores. La forma correcta y estándar de declarar la función principal en C es int main(), y en C++ puedes usar tanto int main() como int main(int argc, char *argv[]).
*/
using namespace std;
int main()
{
    long N, Suma;
    system("cls");
    cout << "Ingresar un numero entero: ";
    cin >> N;

    Suma = N * (N + 1) / 2;
    cout << "La suma de los " << N
            << " primeros numeros enteros es: " << Suma;
    // pausa para verl los resultados
    getch();   // Lee un carácter directamente de la consola sin hacer uso del buffer, y sin mostrar salida
    return 0;
}
/*
Referencias:
https://ccodigo.help/tag/conio-h/
*/