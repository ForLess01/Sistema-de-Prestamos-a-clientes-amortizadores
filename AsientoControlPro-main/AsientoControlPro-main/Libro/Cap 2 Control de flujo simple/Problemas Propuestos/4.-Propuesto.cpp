#include <iostream>
#include <cstring> // Necesario para usar la función strcpy
using namespace std;

struct Persona
{
    char nombre[20];
    int edad;
    char telefono[20];
};
void mostrardatos(Persona &persona)
{
    cout << "Nombre: " << persona.nombre << endl;
    cout << "Edad: " << persona.edad << endl;
    cout << "Telefono: " << persona.telefono << endl;
}

void datosPersona(Persona &persona)
{
    cout << "Ingresa los datos de la persona: " << endl;
    cout << "Nombre: ";
    cin.ignore(); // Ignorar el salto de línea pendiente en el buffer
    cin.getline(persona.nombre, 20, '\n');
    cout << "Edad: ";
    cin >> persona.edad;
    cin.ignore(); // Ignorar el salto de línea pendiente en el buffer
    cout << "Telefono: ";
    cin.getline(persona.telefono, 20, '\n');
}

void intercambiarIdentidades(Persona &persona1, Persona &persona2)
{
    if (persona1.edad > persona2.edad && persona1.edad - persona2.edad <= 4)
    {
        // Ocurre el intercambio solo si la diferencia de edades es menor o igual a 4
        swap(persona1, persona2);
        cout << "Intercambio exitoso:" << endl;
        mostrardatos(persona1);
        mostrardatos(persona2);
    }
    else
    {
        // Muestra un mensaje indicando la diferencia de edades que impide el intercambio
        cout << "La diferencia de edades impide el intercambio. Diferencia: " << abs(persona1.edad - persona2.edad) << " años." << endl;
    }
}


int main()
{
    Persona persona1, persona2;
    
    cout << "Datos para la persona 1" << endl;
    datosPersona(persona1);

    cout << "\nDatos para la persona 2" << endl;
    datosPersona(persona2);

    intercambiarIdentidades(persona1, persona2);

    return 0;
}
