#include <iostream>
#include <conio.h>

using namespace std;
int main()
{
    system("cls");
    float Farenheit, Centigrado;
    cout << "Ingrese los grados Centigrados: ";
    cin >> Centigrado;

    Farenheit = 1.8 * Centigrado + 32;
    cout << "En grados Farenheit es: " << Farenheit << endl;
    return 0;
}