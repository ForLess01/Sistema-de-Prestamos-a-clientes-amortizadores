#include <iostream>
#include <conio.h> //para getch()
#include <math.h> // para pow()

using namespace std;
int main(){
    float Capital, Tasa, Monto, Interes;
    int NumPer;
    system("cls");
    cout << "Ingrese Capital: "; cin >> Capital;
    cout << "% de Tasa de interes: "; cin >> Tasa;
    cout << "Numero periodos: "; cin >> NumPer;

    // Calculamos Monto de acuerdo a la formula
    Monto = Capital * pow(1 + Tasa / 100 ,  NumPer);

    // Calculamos el valor del interes
    Interes = Monto - Capital;
    
    // Escribir resultado
    cout << endl;
    cout << "Intereses ganados: " << Interes;


    getch();
    return 0;
}

