/*
1. Un restaurant ofrece un descuento del 20% para un Consumo mayor a S/30.00
y aplica un impuesto de 15% para todo Consumo. Determinar el importe a pagar por
lo consumido, mostrando todos los importes.
*/
#include <iostream>
#include <iomanip>
using namespace std;

#define Pimpuesto 0.15
#define Pdescuento 0.20

int main() {
    system("cls");

    float Consumo, Descuento, Impuesto, Importe;

    cout << "Ingrese el Consumo: ";
    cin >> Consumo;

    if (Consumo > 30) {
        Descuento = Consumo * Pdescuento; // Aplicar descuento para consumo mayor a S/30.00
    } else {
        Descuento = 0; // Sin descuento si el consumo es S/30.00 o menos
    }

    Impuesto = Consumo * Pimpuesto;
    Importe = Consumo - Descuento + Impuesto;

    cout << fixed << setprecision(2);
    cout << "Consumo: " << setw(10) << Consumo << endl
         << "Descuento: " << setw(10) << Descuento << endl
         << "Impuesto: " << setw(10) << Impuesto << endl
         << endl
         << "Importe a Pagar: " << setw(10) << Importe << endl;

    cin.ignore();
    cin.get();

    return 0;
}

