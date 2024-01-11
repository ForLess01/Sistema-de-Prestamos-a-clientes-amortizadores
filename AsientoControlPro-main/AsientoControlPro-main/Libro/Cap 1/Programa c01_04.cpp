//------------------------------------------------------------------------
// Programa c01_04.cpp
// Procesos Secuenciales
// ----------------------------------------------------------------------
// inclusion de librerías
#include <iostream>
#include <conio.h>
using namespace std;
// funcion principal
int main()
{
    // declaracion de variables
    float Cantidad, Decimal;
    long PartEnt, PartDec;
    unsigned int b20, b10, b05, b01, m50, m20, m10, m05, m01;
    // ingreso de cantidad
    system("cls");
    cout << "Ingrese Cantidad : ";
    cin >> Cantidad;
    // Separar parte entera de parte decimal
    PartEnt = int(Cantidad);
    Decimal = Cantidad - PartEnt;
    // Distribucion de La parte entera
    b20 = PartEnt / 20;
    PartEnt = PartEnt % 20;
    b10 = PartEnt / 10; // 1O soles
    PartEnt = PartEnt % 10;
    b05 = PartEnt / 5;
    PartEnt = PartEnt % 5;
    b01 = PartEnt; // 1 sol
    // Distribucion de La parte decimal

    PartDec = int(Decimal * 1000);
    m50 = PartDec / 500;
    PartDec = PartDec % 500;
    m20 = PartDec / 200;
    PartDec = PartDec % 200;
    m10 = PartDec / 100;
    PartDec = PartDec % 100;
    m05 = PartDec /50;
    PartDec = PartDec % 50;
    m01 = PartDec / 10;
    // Escribir resultados
    cout<< "Billetes de 20 soles : " << b20 << endl
        << "Billetes de 10 soles : " << b10 << endl
        << "Billetes de 5 soles : " << b05 << endl
        << "Billetes de 1 sol : " << b01 << endl
        << endl
        << "Monedas de 50 centimos: " << m50 << endl
        << "Monedas de 20 centimos: " << m20 << endl
        << "Monedas de 10 centimos: " << m10 << endl
        << "Monedas de 5 centimos: " << m05 << endl
        << "Monedas de 1 centimo : " << m01 << endl;
    // pausa para ver los resultados
    getch();
    return 0;
}