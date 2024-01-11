/*La nota final de un curso de programación se obtiene de acuerdo a las siguientes
formulas:
PF=(Ep+2Ef+Pp)/4
Ef=(2Pe + Py) /3
Pp=(2Pa+ Pc) /3

donde:

PF, Promedio final
Ep, Examen parcial
Ef, Examen final
Pp, Promedio de prácticas
Pe, Prueba escrita del examen final
Py, proyecto
Pa, Promedio de practicas de aula
Pe, Promedio de notas de concepto del profesor
Según reglamento, la nota minima aprobatoria es l0.5 y los promedios parciales
no se redondean. Un alumno, sumamente preocupado, desea saber cuánto deberá
sacar como nota en la prueba escrita del examen final para aprobar dicho curso si ya
sabe todas las demás notas.*/
#include <iostream>

using namespace std;

int main() {
    double Ep, Ef, Pp, Pe, Py, Pa, Pc, Pf, nota_minima;
    cout << "Ingrese la nota del examen parcial (Ep): ";
    cin >> Ep;

    cout << "Ingrese el promedio de practicas de aula (Pa): ";
    cin >> Pa;

    cout << "Ingrese el promedio de notas de concepto del profesor (Pc): ";
    cin >> Pc;

    cout << "Ingrese la nota de proyectos (Py): ";
    cin >> Py;

    Pp = (2 * Pa + Pc) / 3;

    nota_minima = max((10.5 * 4 - Ep - 2 * Pp) / 3, 0.0);

    Ef = (3 * nota_minima + Py) / 2;

    Pf = (Ep + 2 * Ef + Pp) / 4;
    
    cout << "\nResultados de las formulas:" << endl;
    cout << "Promedio de prácticas (Pp): " << Pp << endl;
    cout << "Examen final (Ef): " << Ef << endl;
    cout << "Promedio final (PF): " << Pf << endl;
    cout << "Nota necesaria en la prueba escrita del examen final (Pe) para aprobar con 10.5: " << nota_minima << endl;

    return 0;
}