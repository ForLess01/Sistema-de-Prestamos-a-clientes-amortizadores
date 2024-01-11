/*
1. Los dias de la semana se identifican por un número de la siguiente forma: O para
Domingo, 1 para Lunes, 2 para Martes, etc. Determinar el día que corresponda a un
número ingresado dando un mensaje adecuado para el caso que el número dado no
corresponda a ningún dia de la semana.
*/

#include <iostream>
using namespace std;

string getDia(int x)
{
    switch (x)
    {
    case 0:
        return "Domingo";
    case 1:
        return "Lunes";
    case 2:
        return "Martes";
    case 3:
        return "Miercoles";
    case 4:
        return "Jueves";
    case 5:
        return "Viernes";
    case 6:
        return "Sabado";

    default:
        return "Dia fuera del rango";
    }
}

int main()
{
    system("cls");
    int dia;
    cout << "ingresa un numero del dia: ";
    cin >> dia;

    string nombre = getDia(dia);

    cout << nombre;

    return 0;
}