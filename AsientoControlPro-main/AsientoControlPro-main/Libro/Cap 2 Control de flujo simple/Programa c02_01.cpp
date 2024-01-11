//---------------------------------------------------------------------------------
// Programa c02_01.cpp
// Procesos Condicionales: if
// --------------------------------------------------------------------------------
#include <conio.h>
#include <iostream>
#include <iomanip> // para manipuladores setw, setiosflags, etc.
// Capítulo 02: Control de flujo simple
// definicion de constantes
#define Pdscto1 0.20 // 20% descuento
#define Pdscto2 0.10 // 10% descuento
#define Pimplo 0.15  // 15% impuesto
// Ju ncion principal
using namespace std;
int main()
{
    // declaracion de variables
    float Consumo, Dscto, Impuesto, Importe;
    // ingreso de consumo
    system("cls");
    cout << "Ingrese consumo : ";
    cin >> Consumo;
    // Calcular Descuento
    if (Consumo > 30)
        Dscto = Consumo * Pdscto1;
    else
        Dscto = Consumo * Pdscto2;
    // Calcular monto del impuesto
    Impuesto = (Consumo - Dscto) * Pimplo;
    // Calcular monto del importe a pagar
    Importe = Consumo - Dscto + Impuesto;
    // Escribir resultados
    cout << endl;
    cout << setiosflags(ios::fixed | ios::showpoint); // Format for floating-point numbers

    // Display information with setw and setprecision
    cout << "Consumo: " << setw(10) << setprecision(2) << Consumo << endl
         << "Descuento: " << setw(10) << setprecision(2) << Dscto << endl
         << "Impuesto: " << setw(10) << setprecision(2) << Impuesto << endl
         << endl
         << "Importe a Pagar: " << setw(10) << setprecision(2) << Importe << endl;

    getch(); // Assuming you are using getch() to pause the console

    return 0;
}
