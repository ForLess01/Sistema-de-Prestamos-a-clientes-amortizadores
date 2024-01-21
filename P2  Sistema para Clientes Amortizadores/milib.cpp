#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctype.h>
#include <dos.h>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <random>
#include <sstream>
#include <cstring>
#include "milib.h"

void EscribeCad(int columna, int fila, const char*cadena){
    std::cout<<"\033[" << fila<<";"<<columna<<"H"<<cadena;
}

void EscribeFecha(int columna, int fila, int dia, int mes, int anio){
    const char *nombremes[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul",
                        "Ago", "Set", "Oct", "Nov", "Dic"};

    std::cout << std::setw(2) << std::setfill('0') << dia << "/";
    std::cout << nombremes[mes - 1] << "/";
    std::cout << std::setw(4) << anio << std::setfill(' ');

    // Mueve el cursor a la posición deseada en la consola
    std::cout << "\033[" << fila << ";" << columna << "H";

}

void CentraCad(int fila, const char*cadena){
    int columna_central;
    columna_central = (80 - strlen(cadena))/2;
    EscribeCad(columna_central, fila, cadena);
}

char *RepiteCad(int longitud, char caracter){
    char *cadena = new char[longitud+1];

    memset(cadena, 0, longitud + 1);
    memset(cadena, caracter, longitud);

    return cadena;
}

void PintaFila(int fila, int colini, int colfin, char caracter){
    EscribeCad(colini, fila, RepiteCad(colfin-colini+1, caracter));
}

void PintaCol(int col, int filaini, int filafin, char caracter){
    for(int fila = filaini; fila <= filafin; fila++){
        std::cout << "\033[" << fila << ";" << col << "H";

        // Imprime el carácter
        std::cout << caracter;
    }
}

void DibujaCuadrado(int col_ini, int fila_ini, int col_term, int fila_term, const char*bordes){
    gotoxy(col_ini, fila_ini); std::cout<<bordes[0];
    gotoxy(col_term, fila_ini); std::cout<<bordes[1];
    gotoxy(col_term, fila_term); std::cout<<bordes[2];
    gotoxy(col_ini, fila_term); std::cout<<bordes[3];

    PintaFila(fila_ini, col_ini+1, col_term-1, bordes[4]);
    PintaFila(fila_term, col_ini+1, col_term-1, bordes[4]);

    PintaCol(col_ini, fila_ini+1, fila_term-1, bordes[5]);
    PintaCol(col_term, fila_ini+1, fila_term-1, bordes[5]);
}


void BorraCuadrado(int col_ini, int fila_ini, int col_term, int fila_term){
    const char blanco = ' ';

    EscribeCad(col_ini, fila_ini, RepiteCad(col_term-col_ini+1, blanco));
    EscribeCad(col_ini, fila_term, RepiteCad(col_term - col_ini+1, blanco));

    for(int fila=fila_ini+1; fila<fila_term; fila++){
        gotoxy(col_ini, fila); std::cout<<blanco;
        gotoxy(col_term, fila); std::cout<<blanco;
    }
}

void BorraArea(int colini, int filaini, int colfin, int filafin){
    window(colini, filafin, colfin,filafin);
    clrscr();
    window(1, 1, 80, 25);
}

int ValidaFecha(int dia, int mes, int anio){
    int UltimoDia;

    switch(mes){
        case 1: case 3: case 5: case 7: case 8: case 10:
        case 12: UltimoDia = 31; break;
        case 4: case 6: case 9: case 11: UltimoDia = 30; break;
        case 2: if(anio%4==0)
                    UltimoDia =29;
                else
                    UltimoDia = 28;
    }
    return (dia >= 1 && dia <= UltimoDia &&
            mes >= 1 && mes <= 12 &&
            anio > 1900);
}

unsigned char*IngresaCad(int columna, int fila, int longitud,
                         unsigned char atributo){
    const unsigned char blanco = ' ';
    const unsigned char nulo = '\0';
    const unsigned char enter = 13;
    int posicion = 0;
    unsigned char caracter;
    unsigned char* cadena = new unsigned char[longitud + 1];
    CONSOLE_SCREEN_BUFFER_INFO ventana;
    unsigned char colort = (atributo << 5) >> 5;
    unsigned char colorf = (atributo << 1) >> 5;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ventana);

    textcolor(colort);
    textbackground(colorf);

    memset(cadena, blanco, longitud);  // Llenar la cadena con caracteres blancos

    do {
        EscribeCad(columna, fila, reinterpret_cast<const char*>(cadena));
        gotoxy(columna + posicion, fila);
        caracter = getch();
        if (caracter >= 32) {
            cadena[posicion] = caracter;
            posicion++;
        }
        if (caracter == 8 && posicion > 0) {
            posicion--;
            cadena[posicion] = blanco;
        }
    } while (caracter != enter && posicion != longitud);

    if (posicion == longitud) {
        EscribeCad(columna, fila, reinterpret_cast<const char*>(cadena));
    }

    cadena[posicion] = nulo;

    textattr(ventana.wAttributes);
    return cadena;

}

int IngresaEnt(int columna, int fila, int longitud){
    int Numero;
    unsigned char* cadena = IngresaCad(columna, fila, longitud);
    Numero = atoi(reinterpret_cast<const char*>(cadena));
    delete[] cadena;  // Liberar la memoria asignada para la cadena
    return Numero;
}


float IngresaReal(int columna, int fila, int longitud){
    float Numero;
    unsigned char* cadena = IngresaCad(columna, fila, longitud);
    Numero = atof(reinterpret_cast<const char*>(cadena));
    delete[] cadena;  // Liberar la memoria asignada para la cadena
    return Numero;

}


void IngresaFecha(int columna, int fila, int &dia, int &mes, int &anio){
    do{
        EscribeCad(columna, fila, "../../....");
        dia = IngresaEnt(columna, fila, 2);
        mes = IngresaEnt(columna + 3, fila, 2);
        anio = IngresaEnt(columna+6, fila, 4);
    } while (!ValidaFecha(dia, mes, anio));
}


void Mensaje(int fila, const char *texto){
    const char * presionaenter = ", Presione[ENTER]";
    char *cadena = new char[100];

    strcpy(cadena, texto);
    strcat(cadena, presionaenter);
    if(strlen(cadena)>79)
        cadena[79] = 0;

    CentraCad(fila, cadena);
    //sound(300);
    delay(50);
    //sound(120);
    delay(50);
    //sound(450);
    delay(50);
    //nosound();
    while(getch() != 13);
    gotoxy(1, fila); clreol();
    delete[] cadena;
}


char Respuesta(int fila, const char*pregunta, const char*respuestas){
    char caracter;
    const char *poscar;

    CentraCad(fila, pregunta);
    do{
        caracter = toupper(getch());
        poscar = strchr(respuestas, caracter);
    } while(!poscar);
    return caracter;
}


char EnterOEsc(int fila, const char*pregunta){
    char caracter;

    CentraCad(fila, pregunta);
    do{
        caracter = getch();
    } while(caracter !=13 && caracter != 27);
    return caracter;
}


char *Extraer(const char*cadena, int inicio, int cantidad){
    char *auxiliar = new char[cantidad+1];

    if(inicio<0) inicio = 0;
    if(inicio>strlen(cadena)) {cadena = 0; inicio=strlen(cadena);}
    if((inicio+cantidad)>strlen(cadena))
        cantidad = strlen(cadena)-inicio;

    strcpy(auxiliar, cadena + inicio);
    auxiliar[cantidad] = 0;

    return auxiliar;
}


char *Insertar(const char*cadena1, const char*cadena2, int posicion){
    char *auxiliar = new char(strlen(cadena1)+strlen(cadena2)+1);

    if(posicion > strlen(cadena2)) posicion = strlen(cadena2);
    if(posicion < 0) posicion = 0;
    strncpy(auxiliar, cadena2, posicion);
    auxiliar[posicion] = 0;
    strcat(auxiliar, cadena1);
    if(posicion < strlen(cadena2))
        strcat(auxiliar, cadena2 + posicion);
    else
        auxiliar[strlen(cadena1 + strlen(cadena2)+1)] = 0;

    return auxiliar;
}


char *Suprimir(const char*cadena, int posicion, int cantidad){
    char *auxiliar = new char[strlen(cadena)+1];

    if(posicion>strlen(cadena)) cantidad = 0;
    if((posicion + cantidad) > strlen(cadena))
        cantidad = strlen(cadena) - posicion;

    strncpy(auxiliar, cadena, posicion);
    auxiliar[posicion] = 0;
    strcat(auxiliar, cadena+posicion+cantidad);
    return auxiliar;
}


int PosCad(const char *cadena1, char *cadena2){
    if(strstr(cadena2, cadena1))
        return(strstr(cadena2, cadena1) - cadena2);
    else
        return -1;
}


char *FormatoNum(float numero, int ndec){
    const char coma = ',';
    const char apostrofe = '`';
    const char cadena_vacia = '\()';
    int longitud, esnegativo, decimales, signo;
    char *parte_entera, *parte_decimal, *resultado;

    if(numero<0){
        esnegativo = 1;
        numero = numero*(-1);
    }
    else
        esnegativo = 0;

    parte_entera[0] = cadena_vacia;

    resultado = fcvt(numero, ndec, &decimales, &signo);

    parte_entera = Extraer(resultado, 0, decimales);
    parte_decimal = Extraer(resultado, decimales, ndec);

    longitud = strlen(parte_entera);
    switch(longitud){
        case 4: case 5: case 6:
            {   char *aux = new char[15];
                strncpy(aux, parte_entera, longitud-3);
                aux[longitud-3] = '\0';
                aux[longitud-3] = coma;
                aux[longitud-2] = '\0';
                strcat(aux, parte_entera+(longitud-3));
                strcpy(parte_entera, aux);
                break;
            }
        case 7: case 8: case 9:
            {   char *aux = new char[15];
                strncpy(aux, parte_entera, longitud-6);
                aux[longitud-6] = '\0';
                aux[longitud-6] = apostrofe;
                aux[longitud-5] = '\0';
                strcat(aux, parte_entera+(longitud-6));
                strcpy(parte_entera, aux);

                strncpy(aux, parte_entera, longitud-2);
                aux[longitud-2] = '\0';
                aux[longitud-2] = coma;
                aux[longitud-1] = '\0';

                strcat(aux, parte_entera+(longitud-2));
                strcpy(parte_entera, aux);
                break;
            }
    }

    strcpy(resultado, parte_entera);

    if(esnegativo){
        char *aux = new char[15];
        strcpy(aux, "-");
        strcat(aux, resultado);
        strcpy(resultado, aux);
    }

    if(strlen(parte_decimal)>0)
        return strcat(resultado, Insertar(".", parte_decimal, 0));
    else
        return resultado;
}


unsigned char *MensajeSecreto(const char* mensaje) {
    size_t longitud = strlen(mensaje);
    unsigned char* resultado = new unsigned char[longitud * 2 + 1];
    short valdig;
    char chrdig;

    strcpy(reinterpret_cast<char*>(resultado), mensaje);

    for (size_t p = 0; p < longitud; p++) {
        if (p % 2 == 0) {
            valdig = random(0, 9);
            chrdig = valdig + '0';
            resultado[p * 2] = chrdig;
        }
        else {
            resultado[p * 2] = mensaje[p];
        }
    }

    resultado[longitud * 2] = '\0';

    return resultado;
}


unsigned char *AlineaDer(int longitud, char *cadena){
    const char blanco = ' ';

    unsigned char* resultado = new unsigned char[longitud + 1];

    // Llenar el principio con caracteres en blanco
    memset(resultado, blanco, longitud);

    // Copiar la cadena al final del array
    strcpy(reinterpret_cast<char*>(resultado) + longitud - strlen(cadena), cadena);

    // Asegurarse de que el resultado est� terminado con '\0'
    resultado[longitud] = '\0';

    return resultado;

}


int MenuPopUp(int col, int fil, const char**TextoMenu, int NumOpciones,
              int ConMarco, unsigned char Atributo){
    const char Enter = 13;
    const char Esc = 27;
    const char *mensaje1 = "Use flechas direccionales,";
    const char *mensaje2 = "<ENTER> para seleccionar, <ESC> para abandonar";

    char Tecla;
    char *auxiliar = new char[80];
    int IndOpcion, LongMayor;

    unsigned char ColorCaract, ColorFondo;
    CONSOLE_SCREEN_BUFFER_INFO infopantalla;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),  & infopantalla);

    ColorCaract = (Atributo<<5)>>5;
    ColorFondo = (Atributo<<2)>>5;

    strcpy(auxiliar, mensaje1); strcat(auxiliar, mensaje2);

    EscribeCad(2,25,auxiliar);

    LongMayor = strlen(TextoMenu[0]);

    if(ConMarco)
        DibujaCuadrado(col-1, fil-1, col+LongMayor, fil+NumOpciones, "++++/");

    textcolor(ColorCaract); textbackground(ColorFondo);
    for(IndOpcion = 0; IndOpcion<NumOpciones; IndOpcion++)
        EscribeCad(col, fil+IndOpcion, TextoMenu[IndOpcion]);

    IndOpcion = 0;
    textcolor(ColorFondo); textbackground(ColorCaract);
    EscribeCad(col, fil, TextoMenu[IndOpcion]);

    _setcursortype(false);

    do{
        Tecla = getch();
        switch(Tecla){
            case 77: case 80:
                textcolor(ColorCaract); textbackground(ColorFondo);
                EscribeCad(col, fil+IndOpcion, TextoMenu[IndOpcion]);
                IndOpcion++;
                if(IndOpcion > NumOpciones - 1)
                    IndOpcion = 0;
                textcolor(ColorFondo); textbackground(ColorCaract);
                EscribeCad(col, fil+IndOpcion, TextoMenu[IndOpcion]);
                break;
            case 75: case 72:
                textcolor(ColorCaract); textbackground(ColorFondo);
                EscribeCad(col, fil+IndOpcion, TextoMenu[IndOpcion]);
                IndOpcion--;
                if(IndOpcion<0)
                    IndOpcion = NumOpciones - 1;
                textcolor(ColorFondo); textbackground(ColorCaract);
                EscribeCad(col, fil+IndOpcion, TextoMenu[IndOpcion]);
                break;
        }
    } while(Tecla != Enter && Tecla != Esc);

    textattr(infopantalla.wAttributes);
    _setcursortype(true);

    delete[] auxiliar;

    if(Tecla == Enter)
        return IndOpcion + 1;
    else
        return 0;
}


int MenuBarra(int col, int fil, const char**TextoMenu, int NumOpciones,
              int espaciado, unsigned char Atributo){
    const char Enter = 13;
    const char Esc = 27;
    char Tecla;
    int IndOpcion, *ColDesp = new int[NumOpciones];

    unsigned char ColorCaract, ColorFondo;
    CONSOLE_SCREEN_BUFFER_INFO infopantalla;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &infopantalla);

    ColorCaract = 2;
    ColorFondo = 4;

    ColDesp[0] = col;
    for(IndOpcion=1; IndOpcion < NumOpciones; IndOpcion++){
        ColDesp[IndOpcion] = ColDesp[IndOpcion - 1]+
                                strlen(TextoMenu[IndOpcion])+
                                espaciado;
    }

    textcolor(ColorCaract); textbackground(ColorFondo);
    for(IndOpcion = 0; IndOpcion<NumOpciones; IndOpcion++)
        EscribeCad(ColDesp[IndOpcion], fil, TextoMenu[IndOpcion]);

    IndOpcion = 0;
    textcolor(ColorFondo); textbackground(ColorCaract);
    EscribeCad(col, fil, TextoMenu[IndOpcion]);

    _setcursortype(false);

    do{
        Tecla = getch();
        switch(Tecla){
            case 77: case 80:
                textcolor(ColorCaract); textbackground(ColorFondo);
                EscribeCad(ColDesp[IndOpcion], fil, TextoMenu[IndOpcion]);
                IndOpcion++;
                if(IndOpcion > NumOpciones-1)
                    IndOpcion = 0;
                textcolor(ColorFondo); textbackground(ColorCaract);
                EscribeCad(ColDesp[IndOpcion], fil, TextoMenu[IndOpcion]);
                break;
            case 75: case 72:
                textcolor(ColorCaract); textbackground(ColorFondo);
                EscribeCad(ColDesp[IndOpcion], fil, TextoMenu[IndOpcion]);
                IndOpcion--;
                if(IndOpcion < 0)
                    IndOpcion = NumOpciones-1;
                textcolor(ColorFondo); textbackground(ColorCaract);
                EscribeCad(ColDesp[IndOpcion], fil, TextoMenu[IndOpcion]);
                break;
        }
    } while(Tecla != Enter && Tecla != Esc);

    textattr(infopantalla.wAttributes);
    _setcursortype(true);

    delete[] ColDesp;

    if(Tecla == Enter)
        return IndOpcion + 1;
    else
        return 0;
}


void FechaSistema(int &DiaDeSem, int &Dia, int &Mes, int &Anio){
    SYSTEMTIME fecha;
    GetSystemTime(&fecha);

    DiaDeSem = int (fecha.wDayOfWeek);
    Dia = int(fecha.wDay);
    Mes = int(fecha.wMonth);
    Anio = fecha.wYear;
}


char *FormatoFecha(int d, int m, int a){
    char *cadena = new char[12];

    char std[3], stm[3], sta[5];

    sprintf(std, "%2d", d); if(std[0]==' ') std[0] = '0';
    sprintf(stm, "%2d", m); if(stm[0]==' ') stm[0] = '0';

    sprintf(sta, "%4d", a);

    strcpy(cadena, std);
    strcat(cadena, "/");
    strcat(cadena, stm);
    strcat(cadena, "/");
    strcat(cadena, sta);

    cadena[10] = '\0';

    return cadena;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int wherex() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}

int wherey() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}

void clrscr() {
    system("cls");
}

void delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void textattr(int color) {
    std::cout << "\033[" << color << "m";
}

void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void textbackground(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void window(int x, int y, int width, int height) {
    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, 0, x, y, width, height, SWP_NOZORDER | SWP_NOSIZE);
}

void clreol() {
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    coord.X = info.dwCursorPosition.X;
    coord.Y = info.dwCursorPosition.Y;

    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', info.dwSize.X - info.dwCursorPosition.X, coord, &written);
}

int random(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void _setcursortype(bool visible) {
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
