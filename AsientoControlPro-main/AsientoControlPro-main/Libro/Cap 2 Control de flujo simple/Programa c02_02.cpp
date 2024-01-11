//----------------------------------------------------. -------------------------
// Programa c02_02.cpp
// Procesos Condicionales: if
// -------------------------------------------------·--------------------------
#include <iostream>
#include <iomanip>
// definicion de constantes
#define Pdsctol 0.30 // 30% descuento
#define Pdscto2 0.20 // 20% descuento
#define Pdscto3 0.15 // 15% descuento
#define Pdscto4 0.10 // 10% descuento
#define Pimpto 0.15  // 15% impuesto
// funcion principal
// Capítulo 02 : Control de flujo simple
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
    if (Consumo > 100)
        Dscto = Consumo * Pdsctol;
    else if (Consumo > 60)
        Dscto = Consumo * Pdscto2;
    else if (Consumo > 30)
        Dscto = Consumo * Pdscto3;
    else
        Dscto = Consumo * Pdscto4;
    // Calcular monto del impuesto
    Impuesto = (Consumo - Dscto) * Pimpto;
    // Calcular monto del importe a pagar
    Importe = Consumo - Dscto + Impuesto;
    // Escribir resultados
    cout << endl;

    // Display information with setw and setprecision
    cout << setiosflags(ios::fixed | ios::showpoint); // Format for floating-point numbers
    cout << "Consumo: " << setw(10) << setprecision(2) << Consumo << endl
         << "Descuento: " << setw(10) << setprecision(2) << Dscto << endl
         << "Impuesto: " << setw(10) << setprecision(2) << Impuesto << endl
         << endl
         << "Importe a Pagar: " << setw(10) << setprecision(2) << Importe << endl;

    // pausa para ver resultados
    // Assuming you want to pause to view the results
    // Note: getch() is platform-dependent, and its use may require including <conio.h>
    // It is recommended to use std::cin.get() for a more portable solution
    cin.get();
    return 0;
}