#include <iostream>
#include <math.h>
/*
5. Determinar el valor de la HIPOTENUSA de un triángulo rectangulo aplicando el
teorema de pitágoras, el perímetro y el área que representa conociendo solamente
el valor de sus catetos.
*/
using namespace std;
int main()
{
    float a, b, h, p, area;
    cout << "Introduce los catetos de del triangulo Rectangulo: ";
    cin >> a >> b;
    h = sqrt(pow(a, 2) + pow(b, 2));
    p = a + b + h;
    area = (a * b) / 2;

    cout << "La hipotenusa es: " << h << endl;
    cout << "La area es: " << area << endl;
    cout << "La perimetro es: " << p << endl;

    return 0;
}