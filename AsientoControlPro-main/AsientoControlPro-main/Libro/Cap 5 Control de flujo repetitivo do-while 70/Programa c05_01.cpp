/*
Un estudiante ha registrado I O instituciones que dictan un curso de computación de su interés, a
diferentes costos. Desea determinar el costo promedio del curso, el costo mas elevado, el costo mas
bajo y el nombre de la institución que ofrece el costo más bajo. Se sabe además que ningún costo llega
a tener 4 cifras.
DEFINICION DE E/S :

    Entradas:   nombre del instituto (nombre)
                costo del curso (costo)
    Salidas     costo promedio (costo_prom)
                costo mayor (costo_may)
                costo menor (costo_men)
                nombre de quien tiene costo menor (nombre_costomen)
*/

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
// Programa c05_01.cpp
// Procesos Repetitivos: do - while
// ·-------. --···-..... --. ---. ---------------------------. ----.. ·----.. --... --.
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
// definicion de constantes
#define NUMINST 2
#define Maxcosto 999
using namespace std;
// funcion principal
int main()
{
    // número de instituciones
    // máximo costo permitido
    // declaracion de variables
    char nombre[30], nombre_costomen[30];
    float costo, suma, costo_prom, costo_may, costo_men;
    int contador;
    // inicializar elementos
    contador = 1;
    suma = 0.0;
    costo_may = 0.0;
    costo_men = Maxcosto;
    // proceso repetitivo
    do
    {
        // contador de instituciones
        // acumulador de costos
        // supuesto falso del mayor costo
        // supuesto falso del menor costo
        // clrscr(); // clears the screen and move the cursor to upper left corner
        fflush(stdin);
        system("cls");
        cout << "Instituto Nro:" << setw(1) << contador << endl;
        cout << "Nombre: ";
        cin.getline(nombre, 30, '\n');
        cout << "Costo del curso: ";
        cin >> costo;
        // acumular costos
        suma += costo;
        // determina el costo mayor
        if (costo > costo_may)
            costo_may = costo;
        // determina el costo menor e identifica su nombre
        if (costo < costo_men)
        {
            costo_men = costo;
            strcpy(nombre_costomen, nombre);
        }
        // incrementa contador
        contador++;
    } while (contador <= NUMINST);
    // calcular costo promedio
    costo_prom = suma / NUMINST;
    // mostrar resultados
    cout << endl
         << "COSTO PROMEDIO : "
         << setw(10) << setprecision(2) << costo_prom << endl
         << "COSTO MAYOR : "
         << setw(10) << setprecision(2) << costo_may << endl
         << "COSTO MENOR : "
         << setw(10) << setprecision(2) << costo_men
         << ' ' << nombre_costomen
         << endl;
    getch();
    return 0;
}
