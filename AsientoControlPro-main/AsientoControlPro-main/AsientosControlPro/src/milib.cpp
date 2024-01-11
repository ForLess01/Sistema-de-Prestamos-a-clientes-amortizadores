#include <iostream>
#include <conio.h>  // para clrscr( ) .. . cprint
#include <string>   // para strlen() .. .
#include <stdlib.h> // para atoi( ) ...
#include <ctype.h>  // para toupper( ) ...
// #include <dos.h>     // para sound() y delay() .. .
#include <Windows.h>
#include <thread>
#include <chrono>
#include <stdio.h>   // para sprintf() .. .
#include "milib.h"   // para prototipos
#include <windows.h> //

#include <cstring>
#include <ctime>
#include "Parche.h"
using namespace std;

void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void EscribeCad(int columna, int fila, const char *cadena)
{
    gotoxy(columna, fila);
    // cprintf("%s", cadena); // para que respete atributo de color
    cout << cadena;
}
//
void EscribeCad(int columna, int fila, const unsigned char *cadena)
{
    gotoxy(columna, fila);
    // cprintf("%s", cadena); // para que respete atributo de color
    cout << cadena;
}

// ---------------------------------------------------------------------------------------------
void EscribeFecha(int columna, int fila, int dia, int mes, int anio)
{
    char *nombremes[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul",
                         "Ago", "Set", "Oct", "Nov", "Dic"};
    gotoxy(columna, fila);
    // cprintf("%2d/%s/%4d", dia, nombremes[mes - 1], anio);
    printf("%2d/%s/%4d", dia, nombremes[mes - 1], anio);
}

// -------------------------------------------------------------------------------------------
void CentraCad(int fila, const char *cadena)
{
    int columna_central;
    columna_central = (80 - strlen(cadena)) / 2;
    EscribeCad(columna_central, fila, cadena);
}

// --------------------------------------------------------------------------
char *RepiteCad(int longitud, char caracter)
{
    char *cadena = new char[longitud + 1];
    memset(cadena, 'O', longitud + 1);
    memset(cadena, caracter, longitud);

    return cadena;
}

// --------------------------------------------------------------------------

void PintaFila(int fila, int colini, int colfin, char caracter)
{
    EscribeCad(colini, fila, RepiteCad(colfin - colini + 1, caracter));
}

// --------------------------------------------------------------------------

void PintaCol(int col, int filaini, int filafin, char caracter)
{
    for (int fila = filaini; fila <= filafin; fila++)
    {
        gotoxy(col, fila);
        // cprintf("%c ", caracter);
        // Reemplaza cprintf("%c ", caracter); con std::cout
        std::cout << caracter << ' ';
    }
}

// --------------------------------------------------------------------------

void DibujaCuadro(int col_ini, int fila_ini, int col_term, int fila_term, const char *bordes)
{
    // pinta esquinas
    gotoxy(col_ini, fila_ini);
    cout << bordes[0];
    gotoxy(col_term, fila_ini);
    cout << bordes[1];
    gotoxy(col_term, fila_term);
    cout << bordes[2];
    gotoxy(col_ini, fila_term);
    cout << bordes[3];

    // pinta filas
    PintaFila(fila_ini, col_ini + 1, col_term - 1, bordes[4]);
    PintaFila(fila_term, col_ini + 1, col_term - 1, bordes[4]);

    // pinta columnas
    PintaCol(col_ini, fila_ini + 1, fila_term - 1, bordes[5]);
    PintaCol(col_term, fila_ini + 1, fila_term - 1, bordes[5]);
}

// --------------------------------------------------------------------------

void BorraCuadro(int col_ini, int fila_ini, int col_term, int fila_term)
{
    const char blanco = ' ';
    // borra filas
    EscribeCad(col_ini, fila_ini, RepiteCad(col_term - col_ini + 1, blanco));
    EscribeCad(col_ini, fila_term, RepiteCad(col_term - col_ini + 1, blanco));

    // borra columnas
    for (int fila = fila_ini + 1; fila < fila_term; fila++)
    {
        gotoxy(col_ini, fila);
        cout << blanco;
        gotoxy(col_term, fila);
        cout << blanco;
    }
}

// --------------------------------------------------------------------------
void window(int colini, int filaini, int colfin, int filafin)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD topLeft = {static_cast<SHORT>(colini - 1), static_cast<SHORT>(filaini - 1)};
    COORD bottomRight = {static_cast<SHORT>(colfin), static_cast<SHORT>(filafin)};
    SMALL_RECT winRect = {topLeft.X, topLeft.Y, bottomRight.X, bottomRight.Y};

    SetConsoleWindowInfo(hConsole, TRUE, &winRect);
}

void BorraArea(int colini, int filaini, int colfin, int filafin)
{
    window(colini, filaini, colfin, filafin);
    // clrscr();
    system("cls");
    window(1, 1, 80, 25);
}

// --------------------------------------------------------------------------

int ValidaFecha(int dia, int mes, int anio)
{
    int UltimoDia; // dias m�ximos de acuerdo al mes
    switch (mes)
    {

    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        UltimoDia = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        UltimoDia = 30;
        break;
    case 2:
        if (anio % 4 == 0)
            UltimoDia = 29;
        else
            UltimoDia = 28;
    }
    return (dia >= 1 && dia <= UltimoDia &&
            mes >= 1 && mes <= 12 &&
            anio > 1900);
}

// --------------------------------------------------------------------------

char *IngresaCad(int columna, int fila, int longitud, unsigned char atributo)
{
    const char blanco = ' ';
    const char nulo = '\0';
    const char enter = 13;
    int posicion = 0;
    unsigned char caracter;
    unsigned char *cadena = new unsigned char[longitud + 1];

    // Inicializar contenido de cadena con espacios en blanco
    memset(cadena, blanco, longitud);
    cadena[longitud] = nulo;

    // Establecer colores de la consola
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(atributo));

    do
    {
        EscribeCad(columna, fila, reinterpret_cast<const char *>(cadena));
        caracter = static_cast<unsigned char>(getch());

        if (caracter >= 32 && posicion < longitud) // Caracter imprimible y espacio disponible
        {
            cadena[posicion] = caracter;
            posicion++;
        }
        else if (caracter == 8 && posicion > 0) // Backspace
        {
            posicion--;
            cadena[posicion] = blanco;
        }
    } while (caracter != enter);

    // Restablecer colores de la consola
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);

    return reinterpret_cast<char *>(cadena);
}

// --------------------------------------------------------------------------

int IngresaEnt(int columna, int fila, int longitud)
{
    int Numero;
    char *cadena = new char[longitud + 1];
    strcpy(cadena, IngresaCad(columna, fila, longitud));
    Numero = atoi(cadena);
    return Numero;
}

// --------------------------------------------------------------------------

float IngresaReal(int columna, int fila, int longitud)
{
    float Numero;
    char *cadena = new char[longitud + 1];
    strcpy(cadena, IngresaCad(columna, fila, longitud));
    Numero = atof(cadena);
    return Numero;
}

// --------------------------------------------------------------------------

void lngresaFecha(int columna, int fila, int &dia, int &mes, int &anio)
{
    do
    {
        EscribeCad(columna, fila, ".. /../.... ");
        dia = IngresaEnt(columna, fila, 2);
        mes = IngresaEnt(columna + 3, fila, 2);
        anio = IngresaEnt(columna + 6, fila, 4);
    } while (!ValidaFecha(dia, mes, anio));
}

// --------------------------------------------------------------------------

void Mensaje(int fila, const char *texto)
{
    const char *presionaenter = ", Presione [ENTER]";
    char *cadena = new char[80];
    strcpy(cadena, texto);
    strcat(cadena, presionaenter);
    if (strlen(cadena) > 79)
        cadena[79] = '\0';
    CentraCad(fila, cadena);
    // sound(300); delay(50);
    // sound( 120); delay(50);
    // sound(450); delay(50);
    // nosound();
    while (getch() != 13)
        ;
    gotoxy(1, fila);
    clreol();
    delete[] cadena;
}

// --------------------------------------------------------------------------

char Respuesta(int fila, const char *pregunta, const char *respuestas)
{
    char caracter;
    char *poscar;
    CentraCad(fila, pregunta);
    do
    {
        caracter = toupper(getch());
        poscar = strchr(respuestas, caracter);
    } while (!poscar);
    return caracter;
}

// --------------------------------------------------------------------------

char EnterOEsc(int fila, const char *pregunta)
{
    char caracter;
    CentraCad(fila, pregunta);
    do
    {
        caracter = getch();
    } while (caracter != 13 && caracter != 27);
    return caracter;
}

// --------------------------------------------------------------------------

char *Extraer(const char *cadena, int inicio, int cantidad)
{
    char *auxiliar = new char[cantidad + 1];
    if (inicio < 0)
        inicio = 0;
    if (inicio > strlen(cadena))
    {
        cantidad = 0;
        inicio = strlen(cadena);
    }
    if ((inicio + cantidad) > strlen(cadena))
        cantidad = strlen(cadena) - inicio;

    strncpy(auxiliar, cadena + inicio, cantidad);
    auxiliar[cantidad] = '\0';
    return auxiliar;
}

// --------------------------------------------------------------------------

char *Insertar(const char *cadena, const char *cadena2, int posicion)
{
    char *auxiliar = new char[strlen(cadena) + strlen(cadena2) + 1];
    if (posicion > strlen(cadena2))
        posicion = strlen(cadena2);
    if (posicion < 0)
        posicion = 0;
    strncpy(auxiliar, cadena2, posicion);
    auxiliar[posicion] = '\0';
    strcat(auxiliar, cadena);
    if (posicion < strlen(cadena2))
        strcat(auxiliar, cadena2 + posicion);
    else
        auxiliar[strlen(cadena) + strlen(cadena2)] = '\0';
    return auxiliar;
}

// --------------------------------------------------------------------------

char *Suprimir(const char *cadena, int posicion, int cantidad)
{
    char *auxiliar = new char[strlen(cadena) + 1];
    if (posicion > strlen(cadena))
        cantidad = 0;
    if ((posicion + cantidad) > strlen(cadena))
        cantidad = strlen(cadena) - posicion;
    strncpy(auxiliar, cadena, posicion);
    auxiliar[posicion] = '\0';
    strcat(auxiliar, cadena + posicion + cantidad);
    return auxiliar;
}

// --------------------------------------------------------------------------

int PosCad(const char *cadena, char *cadena2)
{
    if (strstr(cadena2, cadena))
        return (strstr(cadena2, cadena) - cadena2);
    else
        return -1;
}

// --------------------------------------------------------------------------

char *FormatoNum(float numero, int ndec)
{
    const char coma = '.';
    const char apostrofe = '"';
    const char cadena_vacia = '\0';
    int longitud, esnegativo, decimales, signo;
    char *parte_entera, *parte_decimal, *resultado;
    if (numero < 0) // es negativo
    {
        esnegativo = 1;
        numero = numero * (-1);
    }
    else
        esnegativo = 0; // es positivo
    // inicializa la parte entera y la parte decimal como vac�as
    parte_entera = new char[1];
    parte_entera[0] = cadena_vacia;
    // separa la parte entera de la parte decimal
    resultado = fcvt(numero, ndec, &decimales, &signo);
    parte_entera = Extraer(resultado, 0, decimales);
    parte_decimal = Extraer(resultado, decimales, ndec);
    // inserta en la parte entera, los miles y millones
    longitud = strlen(parte_entera);
    switch (longitud)
    {
    case 4:
    case 5:
    case 6:
    {
        char *aux = new char[15];
        strncpy(aux, parte_entera, longitud - 3);
        aux[longitud - 3] = apostrofe;
        aux[longitud - 3 + 1] = coma;
        aux[longitud - 2] = '\0';
        strcat(aux, parte_entera + (longitud - 3));
        strcpy(parte_entera, aux);
        break;
    }
    case 7:
    case 8:
    case 9:
    {
        char *aux = new char[15];
        strncpy(aux, parte_entera, longitud - 6);
        aux[longitud - 6] = '\0';
        aux[longitud - 6] = apostrofe;
        aux[longitud - 5] = '"';
        strcat(aux, parte_entera + (longitud - 6));
        strncpy(aux, parte_entera, longitud - 2);
        aux[longitud - 2] = '\0';
        aux[longitud - 2] = coma;
        aux[longitud - 1] = apostrofe;
        strcat(aux, parte_entera + (longitud - 2));
        strcpy(parte_entera, aux);
        break;
    }
    }
    // junta la parte entera con la parte decimal
    strcpy(resultado, parte_entera);
    // inserta el signo negativo si el numero fue negativo
    if (esnegativo)
    {
        char *aux = new char[15];
        strcpy(aux, "-");
        strcat(aux, resultado);
        strcpy(resultado, aux);
    }
    // asigna el resultado al nombre de la funci�n
    if (strlen(parte_decimal) > 0)
        return strcat(resultado, Insertar(".", parte_decimal, 0));
    else
        return resultado;
}
// ------------------------------------------------------------------------

unsigned char *MensajeSecreto(const char *mensaje)
{
    unsigned char *resultado = new unsigned char[strlen(mensaje) + 1];
    short valdig, p;
    char chrdig;

    strcpy(resultado, mensaje);

    for (p = 0; p < strlen(reinterpret_cast<char *>(resultado)); p++)
        if (p % 2 == 0) // posicion impar
        {
            valdig = random(10); // aleatorio entre 0 y 9
            chrdig = valdig + 48;
            resultado[p] = chrdig;
        }
    return resultado;
}

// ------------------------------------------------------------------------

unsigned char *AlineaDer(int longitud, char *cadena)
{
    const char blanco = ' ';
    char *resultado = strcat(RepiteCad(longitud - strlen(cadena), blanco), cadena);
    return (unsigned char *)resultado;
}

// ------------------------------------------------------------------------

int MenuPopUp(int col, int fil, char **TextoMenu, int NumOpciones,
              int ConMarco, unsigned char Atributo)
{
    const char Enter = 13;
    const char Ese = 27;
    const char *mensaje = "Use flechas direccionales, ";
    const char *mensaje2 = " <ENTER> para seleccionar, <ESC> para abandonar ";
    char Tecla;
    int IndOpcion = 0;

    // Conserva atributos de pantalla actual
    CONSOLE_SCREEN_BUFFER_INFO infopantalla;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &infopantalla);

    // Determina colores de caracter y de fondo
    unsigned char ColorCaract = Atributo & 0x0F;
    unsigned char ColorFondo = (Atributo >> 4) & 0x0F;

    // Muestra un marco dentro del cual se mostrarán las opciones
    if (ConMarco)
        system("cls");

    // Muestra las opciones del arreglo con atributo normal
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Atributo);
    for (int i = 0; i < NumOpciones; i++)
        EscribeCad(col, fil + i, TextoMenu[i]);

    // Muestra el mensaje sobre el uso de las teclas
    EscribeCad(2, 25, mensaje);
    EscribeCad(2, 26, mensaje2);

    // Desaparece el cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // Maneja el índice de opción de acuerdo a la tecla direccional
    do
    {
        Tecla = getch();
        if (Tecla == 224) // Tecla especial
        {
            Tecla = getch();
            switch (Tecla)
            {
            case 77:
            case 80: // Flecha derecha o abajo
                EscribeCad(col, fil + IndOpcion, TextoMenu[IndOpcion]);
                IndOpcion = (IndOpcion + 1) % NumOpciones;
                break;
            case 75:
            case 72: // Flecha izquierda o arriba
                EscribeCad(col, fil + IndOpcion, TextoMenu[IndOpcion]);
                IndOpcion = (IndOpcion - 1 + NumOpciones) % NumOpciones;
                break;
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Atributo);
            EscribeCad(col, fil + IndOpcion, TextoMenu[IndOpcion]);
        }
    } while (Tecla != Enter && Tecla != Ese);

    // Restablecer colores de la consola
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), infopantalla.wAttributes);

    // Restablecer la visibilidad del cursor
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    if (Tecla == Enter)
        return IndOpcion + 1;
    else
        return 0;
}

// -------------------------------------------------------------------------
void FechaSistema(int &DiaDeSem, int &Dia, int &Mes, int &Anio)
{
    time_t now = time(0);
    tm *localTime = localtime(&now);

    DiaDeSem = localTime->tm_wday;    // Día de la semana (0=domingo, 1=lunes, ..., 6=sábado)
    Dia = localTime->tm_mday;         // Día del mes
    Mes = localTime->tm_mon + 1;      // Mes (0=enero, 1=febrero, ..., 11=diciembre)
    Anio = localTime->tm_year + 1900; // Año (se cuenta desde 1900)
}
// ------------------------------------- -------------------------------------
char *FonnatoFecha(int d, int m, int a)
{
    char *cadena = new char[12];
    char std[3], stm[3], sta[5];
    sprintf(std, "%2d", d);
    if (std[0] == ' ')
        std[0] = '0';
    sprintf(stm, "%2d", m);
    if (stm[0] == ' ')
        stm[0] = '0';
    sprintf(sta, "%4d", a);
    strcpy(cadena, std);
    strcat(cadena, "/");
    strcat(cadena, stm);
    strcat(cadena, "/");
    strcat(cadena, sta);
    cadena[10] = '\0';
    return cadena;
}
