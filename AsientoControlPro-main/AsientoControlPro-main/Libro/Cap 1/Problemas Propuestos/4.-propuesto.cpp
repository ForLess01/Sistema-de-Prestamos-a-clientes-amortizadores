


/*4. De acuerdo a un principio aritmético, un número es múltiplo de 5 si termina en
O ó en 5. Aplicando este principio determinar si un numero entero es múltiplo de
5.  */
#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

bool esMultiploDe5(int numero) {
    return numero % 5 == 0;
}

int main() {
    int numero;
    cout << "Ingrese un numero entero: ";
    cin >> numero;

    if (esMultiploDe5(numero)) {
        cout << numero << " es multiplo de 5." << endl;
    } else {
        cout << numero << " no es multiplo de 5." << endl;
    }
 
    return 0;
}
