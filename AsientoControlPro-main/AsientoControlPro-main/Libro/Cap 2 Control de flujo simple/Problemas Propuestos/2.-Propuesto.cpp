/*
2 Determinar el MENOR valor de 5 números ingresados desde el teclado. (utilizando solo condicionales)
*/
 #include <iostream>
 using namespace std;
 
 int main() {
    system("cls");
     float a,b,c,d,e;
     cout<< "Ingresa los 5 numeros: "; cin>>a>>b>>c>>d>>e;
     float MENOR = a;
     if (b < MENOR) MENOR = b;
     if (c < MENOR) MENOR = c;
     if (d < MENOR) MENOR = d;
     if (e < MENOR) MENOR = e;

     cout<<"El menor es: "<< MENOR;
     return 0;
 }