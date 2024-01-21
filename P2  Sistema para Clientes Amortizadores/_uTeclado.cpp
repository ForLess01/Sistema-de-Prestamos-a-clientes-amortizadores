#include <conio.h>
#include <cstring>
#include "_uTeclado.h"

void cCtrlTeclado::Ejecuta(){
    IniciaProcesoTeclas();
    do{
        LeerTecla();
        EvaluaTeclas(Tecla);
    } while (!Salir);
}

void cCtrlTeclado::LeerTecla(){
    Tecla.Normal = getch();
    if(Tecla.Normal == 0)
        Tecla.Extendida = getch();
    else
        Tecla.Extendida = 0;
}

void cCtrlTeclado::LimpiarTecla(){
    Tecla.Completo = 0;
}

void cCtrlTeclado::Leer(uRegTeclado &prTecla){
    prTecla.Normal = getch();
    if(prTecla.Normal == 0)
        prTecla.Extendida = getch();
    else
        prTecla.Extendida = 0;
}

unsigned char cCtrlTeclado::LeerCarNor(const uRegTeclado pvCarsValidos,
                                       int pvColumna, int pvFila){
    uRegTeclado voTecla;

    gotoxy(pvColumna, pvFila);
    do{
        Leer(voTecla);
    } while(voTecla.Normal < pvCarsValidos.Desde ||
            voTecla.Normal > pvCarsValidos.Hasta);
    return voTecla.Normal;
}

unsigned char cCtrlTeclado::LeerCarExt(const uRegTeclado pvCarsValidos){
    uRegTeclado voTecla;

    do{
        Leer(voTecla);
    } while(voTecla.Extendida < pvCarsValidos.Desde ||
            voTecla.Extendida > pvCarsValidos.Hasta);
    return voTecla.Extendida;
}

void cCtrlTeclado::gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

int cCtrlTeclado::wherex() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}

int cCtrlTeclado::wherey() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}
