/*

1. Determinar la cantidad de términos que son multiplos de 3 en los 200 primeros
términos de la siguiente serie:
6, 8, 10, 12, 14, ...
*/

#include <iostream>
using namespace std;

class Serie
{
public:
    int r;
    int t_1;

    Serie(int r, int t_1)
    {
        this->r = r;
        this->t_1 = t_1; // Agregar punto y coma aquí
    }

    int getTermino(int n)
    {
        return (this->t_1 + this->r * (n - 1)); // Corregir la expresión
    }
};

int main()
{
    system("cls");
    Serie pares(2, 6);
    int multiplos = 0;
    int n = 1;
    while (n <= 200)
    {
        if (pares.getTermino(n) % 3 == 0)
            multiplos += 1;
        n += 1;
    }
    cout<<"la cantidad de multiplos de 3 es: "<< multiplos<<endl;

    return 0;
}