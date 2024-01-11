#include <iostream>
#include <conio.h> //para getch()
#include <math.h> // para pow()

using namespace std;
int main(){
    float NumReal;
    int Hor, Min, Seg, Dseg;
    system("cls");
    cout<<"Ingrese un numero real: "; cin >> NumReal;
    Hor = int(NumReal);
    NumReal = (NumReal - Hor) * 60;
    Min = int(NumReal);
    NumReal = (NumReal - Min)*60;
    Seg = int(NumReal);
    NumReal = (NumReal - Seg)*60;
    Dseg = int(NumReal);

    cout << "Horas: "<<Hor <<endl;
    cout << "Minutos: "<<Min <<endl;
    cout << "Segundos: "<<Seg <<endl;
    cout << "Decimos: "<<Dseg <<endl;

    getch();
    return 0;
}

