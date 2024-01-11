/*
2. Mostrar los N primeros términos de la siguiente serie, indicando además la suma
de los mismos:
7,9, 12, 16,21, ...
*/
#include <iostream>
using namespace std;
class Serie
{
public:
    int r;
    int t_1;

    Serie(int t_1, int r)
    {
        this->r = r;
        this->t_1 = t_1; // Agregar punto y coma aquí
    }

    int getTermino(int n)
    {
        return (this->t_1 + this->r * (n - 1)); // Corregir la expresión
    }
    int sumaTermino(int inico, int final)
    {
        if (final < inico){
            return 0;
        }

        float n = final - inico + 1;
        float suma = (getTermino(inico) + getTermino(final)) * (n / 2);
       
        return suma;
    }
};
class SeriCuadatica : public Serie
{
public:
    int t_1;
    int m_1;
    int r;
    SeriCuadatica(int t_1, int m_1, int r);

    int getTermino(int n)
    {
        if (n == 1){
            return this->t_1;
        }
        int suma = sumaTermino(1, n - 1);

        return suma + this->t_1;
    }
};

SeriCuadatica::SeriCuadatica(int t_1, int m_1, int r) : Serie(m_1, r)
{
    this->t_1 = t_1;
}

int main()
{
    system("cls");
    int n;
    cout << "Ingrese la cantidad de datos" << endl;
    cin>>n;
    cout << "Mostramos los " << n << " primros datos la serie" << endl;

    SeriCuadatica serie(7, 2, 1);
    int ini = 1;
    while (ini != n)
    {
        cout << serie.getTermino(ini) << ", ";
        ini += 1;
    }
    return 0;
}