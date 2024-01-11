#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;
int main()
{
    system("cls");
    float a, b, c, area, p;
    cout << "ingrese los 3 lados del triangulo: ";
    cin >> a >> b >> c;
    p = (a + b + c) / 2;
    area = sqrt(p * (p - a) * (p - b) * (p - c));
    cout << "El area el triangulo es: " << area;
    return 0;
}