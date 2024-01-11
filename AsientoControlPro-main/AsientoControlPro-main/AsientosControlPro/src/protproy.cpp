//--------
// desarrollo de los prototipos del proyecto
// protproy.cpp
//---
#include <iostream>
#include <iomanip> // std::setprecision
#include <fstream> // std::fstream
#include <conio.h>
#include <stdlib.h> // para itoa()...
#include <string.h> // para strcat()...
#include <stdio.h>  // para putchar()...
#include "milib.h"
#include "protproy.h"
#include "Parche.h"

using namespace std;
// variables globales--------------------------------------------------

// arreglos para los indexamientos
sRegIndiceRutas RUTAS[MaximoRutas];
sRegIndiceTurnos TURNOS[MaximoTurnos];
sRegIndicePasajero PASAJEROS[MaximoPasajeros];

// variables para el manejo de los archivos
fstream ArchRutas;                               // archivo de rutas
sRegistroRutas RegRuta;                          // registro de trabajo para rutas
int NumRutas,                                    // numero de Rutas
    IndRuta,                                     // �ndice de rutas
    TamRegRuta = sizeof(sRegistroRutas);         // tama�o de registro ruta
fstream ArchTurnos;                              // archivo de turnos
sRegistroTurnos RegTurno;                        // registro de trabajo para turnos
int NumTurnos,                                   // numero de turnos
    IndTurno,                                    // �ndice de turnos
    TamRegTurno = sizeof(sRegistroTurnos);       // tama�o de registro turno
fstream ArchPasaj;                               // archivo de pasajeros
sRegistroPasajeros RegPasaj;                     // registro de trabajo para pasajeros
int NumPasaj,                                    // numero de pasajeros
    IndPasaj,                                    // �ndice de pasajeros
    TamRegPasajero = sizeof(sRegistroPasajeros); // tama�o de registro pasajero
// indicador de t�rmino de un proceso
char Termina;
//--------------------------------------------------
void Presentacion()
{
    // //clrscr();
    system("cls");
    DibujaCuadro(1, 1, 35, 17);

    EscribeCad(13, 3, "SISTEMA DE");
    EscribeCad(10, 4, "CONTROL DE VIAJE");
    EscribeCad(6, 5, "EN UN TERMINAL TERRESTRE");
    DibujaCuadro(6, 8, 32, 11);
    EscribeCad(7, 9, "SISTEMA PROTOTIPO");
    EscribeCad(7, 10, "con ARCHIVOS o STREAMS");

    EscribeCad(6, 13, "@ Julio V�squez Paragulla");
    EscribeCad(13, 15, "1998");
}
//--------------------------------------------------
// MODULO DE RUTAS
//--------------------------------------------------
// menu de opciones de rutas.........................
int MenuRutas()
{
    const int columna = 55;
    const int fila = 10;
    char *opciones[] = {"Ingresos ",
                        "Modificacion",
                        "Anulacion",
                        "Listado",
                        "Retorno"};
    Presentacion();
    EscribeCad(columna, fila - 2, "RUTAS");
    return MenuPopUp(columna, fila, opciones, 5);
}

// pantalla para el mantenimiento de rutas...............
void PantallaRutas(char forma)
{
    const char *titulol = "INGRESO de RUTAS";
    const char *tituloM = "MODIFICACION de RUTAS";
    const char *tituloA = "ANULACION/ACTIVACION de RUTAS";
    ////clrscr();
    system("cls");
    DibujaCuadro(1, 1, 65, 10);
    switch (forma)
    {
    case 'T':
        CentraCad(2, titulol);
        break;
    case 'M':
        CentraCad(2, tituloM);
        break;
    case 'A':
        CentraCad(2, tituloA);
        break;
    }
    EscribeCad(3, 4, "CODIGO :");
    EscribeCad(3, 6, "CIUDAD :");
    EscribeCad(3, 7, "TARIFA :");
    EscribeCad(3, 8, "STATUS :");
    if (forma == 'T') // ingresos
        EscribeCad(45, 6, "<Enter= termina>");
    else
        EscribeCad(20, 4, "<Enter = termina>");
}
// autogenera el codigo de una ruta..............................
char *GeneraCodigoRuta()
{
    char *cadena = new char[4];
    itoa(NumRutas + 1, cadena, 10);
    cadena = strcat(RepiteCad(2 - strlen(cadena), '0'), cadena);
    cadena = Insertar("R", cadena, 0);
    return cadena;
}
// busqueda binaria de una ciudad en el arreglo indice de rutas......
int BuscarClaveRutas()
{
    int Primero, Ultimo, Medio;
    Primero = 0;
    Ultimo = NumRutas - 1;
    while (Primero <= Ultimo)
    {
        Medio = (Primero + Ultimo) / 2;
        if (!strcmp(RegRuta.Ciudad, RUTAS[Medio].Ciudad))
            return RUTAS[Medio].Posicion;
        else if (strcmp(RegRuta.Ciudad, RUTAS[Medio].Ciudad) < 0)
            // se encontrar�a en la primera mitad
            Ultimo = Medio - 1;
        else
            // se encontrar�a en la segunda mitad
            Primero = Medio + 1;
    }
    return -1; // no lo encontro
}
// ingresa ciudad como clave de ruta...
void IngresaClaveRutas()
{
    strcpy(RegRuta.Ciudad, IngresaCad(13, 6, 30));
    if (strlen(RegRuta.Ciudad) > 0 && NumRutas < MaximoRutas)
        Termina = Falso;
    else
        Termina = Verdad;
}
// ingresa otros datos de una ruta..................
void IngresaOtrosDatosRutas()
{
    strcpy(RegRuta.CodigoRuta, GeneraCodigoRuta());
    EscribeCad(13, 4, RegRuta.CodigoRuta);
    RegRuta.Tarifa = IngresaReal(13, 7, 9);
    // inicializa campos no ingresados
    RegRuta.Status = Verdad; // activo
    RegRuta.Turnos = 0;
    RegRuta.ImporteRuta = 0;
    RegRuta.TotalLibresR = 0;
    RegRuta.TotalVendidosR = 0;
}
// intercambia registros de ruta....................
void IntercambioRuta(sRegIndiceRutas &RegAct, sRegIndiceRutas &RegSig)
{
    sRegIndiceRutas RegAux;
    RegAux = RegAct;
    RegAct = RegSig;
    RegSig = RegAux;
}
// ordena arreglo indice de rutas por ciudad...................
void OrdenaPorCiudad()
{
    int okey;
    do
    {
        okey = Verdad;
        for (IndRuta = 0; IndRuta < NumRutas - 1; IndRuta++)
            if (strcmp(RUTAS[IndRuta].Ciudad, RUTAS[IndRuta + 1].Ciudad) > 0)
            {
                IntercambioRuta(RUTAS[IndRuta], RUTAS[IndRuta + 1]);
                okey = Falso;
            }
    } while (!okey);
}

// adiciona registro de rutas en el archivo y en el arreglo indice...
void AgregaRegistroRutas()
{
    // almacena registro al final del archivo
    ArchRutas.seekp(0, ios::end);
    ArchRutas.write((char *)&RegRuta, TamRegRuta);
    // almacena clave y posici�n en el arreglo �ndice
    strcpy(RUTAS[NumRutas].Ciudad, RegRuta.Ciudad);
    RUTAS[NumRutas].Posicion = NumRutas;
    // incrementa numero de rutas
    NumRutas++;
    // ordena arreglo �ndice de rutas
    OrdenaPorCiudad();
}
// ingreso de rutas..................................................
void IngresoRutas()
{
    do
    {
        PantallaRutas('T');
        IngresaClaveRutas();
        if (!Termina)
        {
            IndRuta = BuscarClaveRutas();
            if (IndRuta == -1) // no existe
            {
                IngresaOtrosDatosRutas();
                AgregaRegistroRutas();
            }
            else
                Mensaje(24, "CIUDAD YA REGISTRADA");
        }
    } while (!Termina);
}
// busqueda secuencial de un codigo de ruta en el archivo de rutas...
int BuscarCodigoRuta()
{
    sRegistroRutas RegRutaLeido;

    // ubica el puntero de registro al inicio del archivo
    ArchRutas.seekg(0, ios::beg);

    // recorre el archivo secuencialemente
    for (int indice = 0; indice < NumRutas; indice++)
    {
        // lee el registro del archivo
        ArchRutas.read((char *)&RegRutaLeido, TamRegRuta);

        // compara codigos
        if (!strcmp(RegRuta.CodigoRuta, RegRutaLeido.CodigoRuta))
            return indice;
    }
    return -1;
}
// corrige campos de una ruta............................................
void CorrigeCamposdeRuta()
{
    int existe;
    char campo;
    do
    {
        EscribeCad(13, 6, RegRuta.Ciudad);
        EscribeCad(13, 7, FormatoNum(RegRuta.Tarifa, 2));
        if (RegRuta.Status)
            EscribeCad(13, 8, "ACTIVO ");
        else
            EscribeCad(13, 8, "ANULADO");

        campo = Respuesta(24, "[1] Ciudad, [2] Tarifa, [3] Ninguno", "123");
        switch (campo)
        {
        case '1':
            do
            {
                strcpy(RegRuta.Ciudad, IngresaCad(13, 6, 30));
                existe = BuscarClaveRutas();
                if (existe != -1)
                    Mensaje(24, "CIUDAD YA REGISTRADA");
            } while (existe != -1);
            break;
        case '2':
            RegRuta.Tarifa = IngresaReal(13, 7, 9);
        }
    } while (campo != '3');
}
// ingresa codigo de ruta................................................
void IngresaCodigoRutas()
{
    strcpy(RegRuta.CodigoRuta, IngresaCad(13, 4, 3));
    if (strlen(RegRuta.CodigoRuta) > 0)
        Termina = Falso;
    else
        Termina = Verdad;
}
// recupera registro de ruta desde su archivo........
void RecuperaRegDeRutas(int indice)
{
    ArchRutas.seekg(indice * TamRegRuta, ios::beg);
    ArchRutas.read((char *)&RegRuta, TamRegRuta);
}
// actualiza registro de ruta en su archivo..............
void ActualizaRegEnRutas(int indice)
{
    ArchRutas.seekp(indice * TamRegRuta, ios::beg);
    ArchRutas.write((char *)&RegRuta, TamRegRuta);
}
// determina si una ruta esta activa o anulada............
int RegRutaesActivo()
{
    return RegRuta.Status;
}
// modificacion de rutas..........
void ModificaRutas()
{
    do
    {
        PantallaRutas('M');
        IngresaCodigoRutas();
        if (!Termina)
        {
            IndRuta = BuscarCodigoRuta();
            if (IndRuta != -1)
            {
                RecuperaRegDeRutas(IndRuta);
                if (RegRutaesActivo())
                {
                    CorrigeCamposdeRuta();
                    ActualizaRegEnRutas(IndRuta);
                }
                else
                    Mensaje(24, "CODIGO de RUTA esta ANULADA");
            }
            else
                Mensaje(24, "Codigo de RUTA NO existe");
        }
    } while (!Termina);
}
// muestra registro de ruta.......
void MuestraRegRutas()
{
    EscribeCad(13, 6, RegRuta.Ciudad);
    EscribeCad(13, 7, FormatoNum(RegRuta.Tarifa, 2));
    if (RegRuta.Status)
        EscribeCad(13, 8, "ACTIVO");
    else
        EscribeCad(13, 8, "ANULADO");
}
// anulacion logica de una ruta....
void AnulaRegRuta()
{
    RegRuta.Status = Falso;
}
// activacion logica de una ruta...
void ActivaRegRuta()
{
    RegRuta.Status = Verdad;
}
// determina si anula o activa resgistro de ruta...
char AnuloOActivoRuta()
{
    if (RegRutaesActivo())
    {
        if (Respuesta(24, "Esta Seguro de Anularlo?", "SN") == 'S')
        {
            AnulaRegRuta();
            return Verdad;
        }
    }
    else
    {
        if (Respuesta(24, "Esta Seguro de Activarlo?", "SN") == 'S')
        {
            ActivaRegRuta();
            return Verdad;
        }
    }
    return Falso;
}
// anula o activa una ruta...
void AnuloOActivoRutas()
{
    do
    {
        PantallaRutas('A');
        IngresaCodigoRutas();
        if (!Termina)
        {
            IndRuta = BuscarCodigoRuta();
            if (IndRuta != -1)
            {
                RecuperaRegDeRutas(IndRuta);
                MuestraRegRutas();
                if (AnuloOActivoRuta())
                    ActualizaRegEnRutas(IndRuta);
            }
            else
                Mensaje(24, "CODIGO de RUTA NO EXISTE");
        }
    } while (!Termina);
}
// pantalla para listado de rutas...
void Pantalla_ListadoRutas()
{
    // clrscr();
    system("cls");
    DibujaCuadro(1, 1, 70, 15);
    CentraCad(2, "<LISTADO de RUTAS por CIUDAD>");
    EscribeCad(3, 3, "STATUS");
    EscribeCad(12, 3, "CODIGO");
    EscribeCad(20, 3, "CIUDAD");
    EscribeCad(59, 3, "TARIFA");
}
// lista una ruta incrementando el contador de filas..................
void ListaRegRuta(int &fila)
{
    fila++;
    EscribeCad(12, fila + 3, RegRuta.CodigoRuta);
    EscribeCad(20, fila + 3, RegRuta.Ciudad);
    EscribeCad(50, fila + 3, AlineaDer(15, FormatoNum(RegRuta.Tarifa, 2)));
    if (RegRuta.Status)
        EscribeCad(3, fila + 3, "ACTIVO");
    else
        EscribeCad(3, fila + 3, "ANULADO");
}
// determina si se produce un cambio de pantalla en el listado........
char CambiaPantA(int numero)
{
    if (numero % LineasPorPag == 0)
        return Verdad;
    else
        return Falso;
}
// listado de rutas ordenado segun su arreglo indice...
void ListaRutas()
{
    int fila = 0;
    Pantalla_ListadoRutas();
    for (IndRuta = 0; IndRuta < NumRutas; IndRuta++)
    {
        RecuperaRegDeRutas(RUTAS[IndRuta].Posicion);
        ListaRegRuta(fila);
        if (CambiaPantA(fila))
        {
            Mensaje(24, "Para continuar");
            Pantalla_ListadoRutas();
            fila = 0;
        }
    }
    Mensaje(24, "Para continuar");
}
//................
// MODULO DE TURNOS
//.........................
// menu de opciones para turnos........
int MenuTurnos()
{
    const int columna = 55;
    const int fila = 11;
    char *opciones[] = {"Ingreso",
                        "Modificacion",
                        "Anulacion ",
                        "Listado",
                        "Retorno"};
    Presentacion();
    EscribeCad(columna, fila - 2, "TURNOS");
    return MenuPopUp(columna, fila, opciones, 5);
}
//...................
// pantalla para el mantenimiento de turnos..
void PantallaTurnos(char forma)
{
    const char *titulol = "INGRESO de TURNOS";
    const char *tituloM = "MODIFICACION de TURNOS";
    const char *tituloA = "ANULACION/ACTIVACION de TURNOS";

    // clrscr();
    system("cls");
    DibujaCuadro(1, 1, 65, 10);
    switch (forma)
    {
    case 'l':
        CentraCad(2, titulol);
        break;
    case 'M':
        CentraCad(2, tituloM);
        break;
    case 'A':
        CentraCad(2, tituloA);
        break;
    }
    EscribeCad(3, 4, "Codigo RUTA     : <Enter = ternina>");
    EscribeCad(3, 5, "CIUDAD         : ");
    EscribeCad(3, 6, "Codigo TURNO   : ");
    EscribeCad(3, 7, "Horade Partida :   hh:mm");
    EscribeCad(3, 8, "Frecuencia     :   0123456 <7=fin, 8=diario>");
    EscribeCad(3, 9, "STATUS        : ");
    EscribeCad(33, 9, "LMMJVSD");
    if (forma == 'l') // ingresos
        EscribeCad(41, 7, "<Enter = ternina>");
    else
        EscribeCad(41, 6, "<Enter = termina>");
}
//.......................................
// autogenera codigo de turno..
char *GeneraCodigoTurno()
{
    char *cadena = new char[4];

    itoa((RegRuta.Turnos + 1), cadena, 10);

    cadena = strcat(RepiteCad(2 - strlen(cadena), '0'), cadena);
    cadena = Insertar("T", cadena, 0);

    return cadena;
}
//............................................
// busqueda binaria de hora de partida en el arreglo �ndice de TURNOS
int BuscarRutaHora()
{
    int Primero, Ultimo, Medio;
    Primero = 0;
    Ultimo = NumTurnos - 1;
    while (Primero <= Ultimo)
    {
        Medio = (Primero + Ultimo) / 2;
        if (strcmp(TURNOS[Medio].CodigoRuta, RegTurno.CodigoRuta) == 0 && strcmp(TURNOS[Medio].HoraPartida, RegTurno.HoraPartida) == 0)
            return TURNOS[Medio].Posicion;
        else if (strcmp(TURNOS[Medio].CodigoRuta, RegTurno.CodigoRuta) == 0 && strcmp(TURNOS[Medio].HoraPartida, RegTurno.HoraPartida) > 0)
            // se encontrar�a en la primera mitad
            Ultimo = Medio - 1;
        else
            // se encontrar�a en la segunda mitad
            Primero = Medio + 1;
    }
    return -1; // no lo encontro
}
/*****************************************************************************
INGRESAR FRECUENCIA DE VIAJE
******************************************************************************/
char *IngresaFrec()
{
    char *cadena = new char[8];
    int dia;
    EscribeCad(33, 9, "LMMJVSD");
    cadena = RepiteCad(7, Blanco);
    // cadena = RepiteCad(7, ' ');
    do
    {
        do
        {
            gotoxy(22, 8);
            dia = getche() - 48;
        } while (dia < 0 || dia > 8);
        if (dia >= 0 && dia <= 6)
        {
            cadena[dia] = Asterisco;
            gotoxy(33 + dia, 9);
            // cprintf("%c", '.');
            std::cout << '.';
        }
        else if (dia == 8) // todos los dias
            strcpy(cadena, RepiteCad(7, Asterisco));
    } while (dia >= 0 && dia <= 6);
    cadena[7] = 0;
    return cadena;
}
/******************************************************************************
INGRESA CLAVE DE TURNO
******************************************************************************/
void IngresaClaveTurnos()
{
    strcpy(RegTurno.CodigoRuta, IngresaCad(22, 4, 3));
    Termina = (!(strlen(RegTurno.CodigoRuta) > 0 && NumTurnos < MaximoTurnos));
    // asignar codigo de ruta para la b�squeda en RUTAS
    strcpy(RegRuta.CodigoRuta, RegTurno.CodigoRuta);
}
/******************************************************************************
INGRESA OTROS DATOS DE TURNO
******************************************************************************/
void IngresaOtrosDatosTurnos()
{
    EscribeCad(22, 5, RegRuta.Ciudad); // nombre de ciudad
    strcpy(RegTurno.HoraPartida, IngresaCad(22, 7, 5));
    if (strlen(RegTurno.HoraPartida) > 0)
    {
        IndTurno = BuscarRutaHora();
        if (IndTurno == -1) // turno no existe
        {
            strcpy(RegTurno.CodigoTurno, GeneraCodigoTurno());
            EscribeCad(22, 6, RegTurno.CodigoTurno);
            strcpy(RegTurno.Frecuencia, IngresaFrec());

            // inicializa campos no ingresados
            RegTurno.Status = Verdad; // activo
            RegTurno.TotalLibresT = CapacidadOmnibus;
            RegTurno.TotalVendidosT = 0;
            RegTurno.ImporteTurno = 0;
            memset(RegTurno.Asientos, 0, sizeof(RegTurno.Asientos));
        }
        else
        {
            Mensaje(24, "HORA YA REGISTRADA");
            memset(RegTurno.HoraPartida, 0, sizeof(RegTurno.HoraPartida));
        }
    }
}
/******************************************************************************
DETERMINA SI CONTINUA INGRESANDO TURNOS
******************************************************************************/
char ContinualngTurnos()
{
    return (strlen(RegTurno.HoraPartida) > 0);
}
/******************************************************************************
INTERCAMBIA REGISTROS de TURNOS
******************************************************************************/
void IntercambioTurno(sRegIndiceTurnos &RegAct, sRegIndiceTurnos &RegSig)
{
    sRegIndiceTurnos RegAux;

    RegAux = RegAct;
    RegAct = RegSig;
    RegSig = RegAux;
}
/******************************************************************************
ORDENA TURNOS por HORA de PARTIDA
******************************************************************************/
void OrdenaTurnosPorHora()
{
    int okey;
    do
    {
        okey = Verdad;
        for (IndTurno = 0; IndTurno < NumTurnos - 1; IndTurno++)
            if (strcmp(TURNOS[IndTurno].HoraPartida, TURNOS[IndTurno + 1].HoraPartida) > 0)
            {
                IntercambioTurno(TURNOS[IndTurno], TURNOS[IndTurno + 1]);
                okey = Falso;
            }
    } while (!okey);
}
/******************************************************************************
AGREGA REGISTRO DE TURNOS
******************************************************************************/
void AgregaRegTurno()
{
    // almacena registro al final del archivo
    ArchTurnos.seekp(0, ios::end);
    ArchTurnos.write((char *)&RegTurno, TamRegTurno);

    // almacena clave y posici�n en el arreglo �ndice
    strcpy(TURNOS[NumTurnos].CodigoRuta, RegTurno.CodigoRuta);
    strcpy(TURNOS[NumTurnos].HoraPartida, RegTurno.HoraPartida);
    TURNOS[NumTurnos].Posicion = NumTurnos;

    // incrementa numero de registros de turnos
    NumTurnos++;

    // ordena arreglo �ndice de turnos
    OrdenaTurnosPorHora();
}
/******************************************************************************
ACTUALIZA CAMPOS EN REGISTRO DE RUTA
******************************************************************************/
void ActualizaCamposEnRuta()
{
    RegRuta.Turnos++;
    RegRuta.TotalLibresR += CapacidadOmnibus;
}
/******************************************************************************
INGRESA VARIOS TURNOS
******************************************************************************/
void IngresaVariosTurnos()
{
    do
    {
        IngresaOtrosDatosTurnos();
        if (ContinualngTurnos())
        {
            AgregaRegTurno();
            ActualizaCamposEnRuta();
        }
    } while (ContinualngTurnos());
}
/******************************************************************************
INGRESO de TURNOS
******************************************************************************/
void IngresoTurnos()
{
    do
    {
        PantallaTurnos('I');
        IngresaClaveTurnos();
        if (!Termina)
        {
            IndRuta = BuscarCodigoRuta();
            if (IndRuta != -1)
            {
                RecuperaRegDeRutas(IndRuta);
                if (RegRutaesActivo())
                {
                    IngresaVariosTurnos();
                    ActualizaRegEnRutas(IndRuta);
                }
                else
                    Mensaje(24, "Codigo de RUTA est� ANULADA");
            }
            else
                Mensaje(24, "CODIGO DE RUTA NO EXISTE");
        }
    } while (!Termina);
}
/******************************************************************************
BUSCAR CODIGO de RUTA y TURNO
Esta b�squeda se realiza en el archivo de turnos debido a que en el
arreglo �ndice no se tiene el c�digo de turno como parte de la clave
de ordenamiento. Esta b�squeda es secuencial.
******************************************************************************/
int BuscarRutaTurno()
{
    sRegistroTurnos RegTurnoLeido;

    // ubica el puntero de registro al inicio del archivo
    ArchTurnos.seekg(0, ios::beg);
    for (int indice = 0; indice < NumTurnos; indice++)
    {
        // lee registro del archvivo
        ArchTurnos.read((char *)&RegTurnoLeido, TamRegTurno);
        if (strcmp(RegTurnoLeido.CodigoRuta, RegTurno.CodigoRuta) == 0 &&
            strcmp(RegTurnoLeido.CodigoTurno, RegTurno.CodigoTurno) == 0)
            return indice;
    }
    return -1;
}
/******************************************************************************
MUESTRA REGISTRO DE TURNO
******************************************************************************/
void MuestraRegTurno()
{
    EscribeCad(22, 7, RegTurno.HoraPartida);
    EscribeCad(22, 8, RegTurno.Frecuencia);
    if (RegTurno.Status)
        EscribeCad(22, 9, "ACTIVO ");
    else
        EscribeCad(22, 9, "ANULADO");
}
/******************************************************************************
CORRIGE CAMPOS de un TURNO
******************************************************************************/
void CorrigeCamposdeTurno()
{
    char campo;
    int dia;
    int OtroIndTurno;

    do
    {
        MuestraRegTurno();
        campo = Respuesta(24, "[1] Hora, [2] Frecuencia, [3] Ninguno", "123");
        switch (campo)
        {
        case 'I':
            do
            {
                strcpy(RegTurno.HoraPartida, IngresaCad(22, 7, 5));
                OtroIndTurno = BuscarRutaHora();
                if (OtroIndTurno != -1)
                    Mensaje(24, "HORA de PARTIDA YA REGISTRADA en ESTA RUTA");
            } while (OtroIndTurno != -1);
            break;
        case '2':
            strcpy(RegTurno.Frecuencia, IngresaFrec());
        }
    } while (campo != '3');
}
/******************************************************************************
INGRESA CODIGO DE UN TURNO
******************************************************************************/
void IngresaCodigoTurno()
{
    strcpy(RegTurno.CodigoTurno, IngresaCad(22, 6, 3));
}
/******************************************************************************
DETERMINA SI CONTINUA MODIFICACION DE TURNO
******************************************************************************/
char ContinuaModTurno()
{
    return (strlen(RegTurno.CodigoTurno) > 0);
}
/******************************************************************************
RECUPERA REGISTRO DE TURNOS
******************************************************************************/
void RecuperaRegDeTurnos(int indice)
{
    ArchTurnos.seekg(indice * TamRegTurno, ios::beg);
    ArchTurnos.read((char *)&RegTurno, TamRegTurno);
}
/******************************************************************************
ACTUALIZA REGISTRO DE TURNOS
******************************************************************************/
void ActualizaRegEnTurnos(int indice)
{
    ArchTurnos.seekp(indice * TamRegTurno, ios::beg);
    ArchTurnos.write((char *)&RegTurno, TamRegTurno);
}
/******************************************************************************
DETERMINA SI REGISTRO DETURNO ESTA ACTIVO
******************************************************************************/
char RegTurnoesActivo()
{
    return RegTurno.Status;
}
/******************************************************************************
CORRIGE TURNOS
******************************************************************************/
void CorrigeTurnos()
{
    EscribeCad(22, 5, RegRuta.Ciudad); // nombre de ciudad
    do
    {
        IngresaCodigoTurno();
        if (ContinuaModTurno())
        {
            IndTurno = BuscarRutaTurno();
            if (IndTurno != -1)
            {
                RecuperaRegDeTurnos(IndTurno);
                if (RegTurnoesActivo())
                {
                    CorrigeCamposdeTurno();
                    ActualizaRegEnTurnos(IndTurno);
                }
                else
                    Mensaje(24, "CODIGO de TURNO esta ANULADO");
            }
            else
                Mensaje(24, "CODIGO de TURNO NO REGISTRADO en esta RUTA");
        }
    } while (ContinuaModTurno());
}
/******************************************************************************
MODIFICA TURNOS
******************************************************************************/
void ModificaTurnos()
{
    do
    {
        PantallaTurnos('M');
        IngresaClaveTurnos();
        if (!Termina)
        {
            IndRuta = BuscarCodigoRuta();
            if (IndRuta != -1)
            {
                RecuperaRegDeRutas(IndRuta);
                if (RegRutaesActivo())
                    CorrigeTurnos();
                else
                    Mensaje(24, "CODIGO de RUTA esta ANULADO");
            }
            else
                Mensaje(24, "CODIGO de RUTA NO REGISTRADO");
        }
    } while (!Termina);
}
/******************************************************************************
ANULA REGISTRO DE TURNO
******************************************************************************/
void AnulaRegTurno()
{
    RegTurno.Status = Falso;
}
/******************************************************************************
ACTIVA REGISTRO DE TURNO
******************************************************************************/
void ActivaRegTurno()
{
    RegTurno.Status = Verdad;
}
/******************************************************************************
DETERMINA SI ANULA O ACTIVA REGISTRO DE TURNO
******************************************************************************/
char AnulaoActivaTurnos()
{
    if (RegTurnoesActivo())
    {
        if (Respuesta(24, "Esta Seguro de Anularlo?", "SN") == 'S')
        {
            AnulaRegTurno();
            return Verdad;
        }
    }
    else
    {
        if (Respuesta(24, "Esta Seguro de Activarlo ?", "SN") == 'S')
        {
            ActivaRegTurno();
            return Verdad;
        }
    }
    return Falso;
}
/******************************************************************************
ANULA O ACTIVA REGISTRO DE TURNO
******************************************************************************/
void AnulaActivaRegTurno()
{
    EscribeCad(22, 5, RegRuta.Ciudad); // nombre de ciudad
    IngresaCodigoTurno();
    if (ContinuaModTurno())
    {
        IndTurno = BuscarRutaTurno();
        if (IndTurno != -1)
        {
            RecuperaRegDeTurnos(IndTurno);
            MuestraRegTurno();
            if (AnulaoActivaTurnos())
                ActualizaRegEnTurnos(IndTurno);
        }
        else
            Mensaje(24, "CODIGO de TURNO NO REGISTRADO");
    }
}
/******************************************************************************
ANULA TURNOS
******************************************************************************/
void AnulaActivaTurnos()
{
    do
    {
        PantallaTurnos('A');
        IngresaClaveTurnos();
        if (!Termina)
        {
            IndRuta = BuscarCodigoRuta();
            if (IndRuta != -1)
            {
                RecuperaRegDeRutas(IndRuta);
                AnulaActivaRegTurno();
            }
            else
                Mensaje(24, "CODIGO de RUTA NO REGISTRADO");
        }
    } while (!Termina);
}
/******************************************************************************
PANTALLA para LISTADO de TURNOS
******************************************************************************/
void PantallaListadoTurnos()
{
    // clrscr();
    system("cls");
    DibujaCuadro(1, 1, 70, 15);
    CentraCad(2, "< LISTADO de TURNOS por RUTA >");
    EscribeCad(3, 4, "CODIGO RUTA:");
    EscribeCad(22, 4, "CIUDAD:");
    EscribeCad(22, 5, "TARIFA:");

    EscribeCad(3, 6, "STATUS");
    EscribeCad(10, 6, "TURNO");
    EscribeCad(20, 6, "HORA PARTIDA");
    EscribeCad(34, 6, "FRECUENCIA");
    EscribeCad(34, 7, "LMMJVSD");
}
/******************************************************************************
LISTA REGISTRO DE TURNO INCREMENTANDO EL NUMERO DE FILA
******************************************************************************/
void ListaRegTurno(int &fila)
{
    fila++;
    EscribeCad(12, fila + 7, RegTurno.CodigoTurno);
    EscribeCad(20, fila + 7, RegTurno.HoraPartida);
    EscribeCad(34, fila + 7, RegTurno.Frecuencia);
    if (RegTurno.Status)
        EscribeCad(3, fila + 7, "ACTIVO ");
    else
        EscribeCad(3, fila + 7, "ANULADO");
}
/******************************************************************************
DETERMINA SI CODIGO DE RUTA ES EL MISMO EN RUTA Y EN TURNO
******************************************************************************/
char RutaenAesRutaenB()
{
    return (strcmp(RegRuta.CodigoRuta, RegTurno.CodigoRuta) == 0);
}
/******************************************************************************
LISTADO de TURNOS por RUTA
observe la forma de recuperar el registro de turno, de acuerdo a su
arreglo �ndice ya que los turnos deben mostrarse ordenados.
******************************************************************************/
void ListaTurnosdeRuta()
{
    int fila = 0;
    for (IndTurno = 0; IndTurno < NumTurnos; IndTurno++)
    {
        RecuperaRegDeTurnos(TURNOS[IndTurno].Posicion);
        if (RutaenAesRutaenB())
        {
            ListaRegTurno(fila);
            if (CambiaPantA(fila))
            {
                Mensaje(24, "Para continuar");
                BorraArea(2, 8, 69, 20);
                fila = 0;
            }
        }
    }
    Mensaje(24, "Para continuar");
}
/******************************************************************************
INGRESA CLAVE PARA EL LISTADO DE TURNOS
******************************************************************************/
void IngresaClaveListaTurnos()
{
    strcpy(RegTurno.CodigoRuta, IngresaCad(16, 4, 3));
    if (strlen(RegTurno.CodigoRuta) > 0)
        Termina = Falso;
    else
        Termina = Verdad;

    // asigna codigo de ruta para la b�squeda en RUTAS
    strcpy(RegRuta.CodigoRuta, RegTurno.CodigoRuta);
}
/******************************************************************************
LISTADO DE TURNOS DE UNA RUTA
******************************************************************************/
void ListadoDeTurnos()
{
    EscribeCad(30, 4, RegRuta.Ciudad);
    EscribeCad(30, 5, FormatoNum(RegRuta.Tarifa, 2));
    if (RegRuta.Turnos > 0)
    {
        OrdenaTurnosPorHora();
        ListaTurnosdeRuta();
    }
    else
        Mensaje(24, "RUTA no tiene TURNOS establecidos");
}
/******************************************************************************
LISTADO de TURNOS
******************************************************************************/
void ListaTurnos()
{
    IndRuta = -1;
    do
    {
        PantallaListadoTurnos();
        IngresaClaveListaTurnos();
        if (!Termina)
        {
            IndRuta = BuscarCodigoRuta();
            if (IndRuta != -1)
            {
                RecuperaRegDeRutas(IndRuta);
                if (RegRutaesActivo())
                    ListadoDeTurnos();
                else
                    Mensaje(24, "Codigo de RUTA est� ANULADA");
            }
            else
                Mensaje(24, "CODIGO de RUTA NO REGISTRADO");
        }
    } while (!Termina && IndRuta == -1);
}
/******************************************************************************
MODULO DE PASAJES
******************************************************************************/
/******************************************************************************
ESCRIBE NUMEROS DE ASIENTO
******************************************************************************/
void EscribeNumeroAsiento(int fila, int inicio, int fin)
{
    int asiento, y = 1;
    for (asiento = inicio; asiento <= fin; asiento++)
    {
        y += 4;
        EscribeCad(25 + y, fila, FormatoNum(asiento, 0));
    }
}
/******************************************************************************
PANTALLA de PASAJES
******************************************************************************/
void PantallaPasajes()
{
    // clrscr();
    system("cls");
    // textbackground(WHITE);
    // textcolor(BLACK);
    //  clrscr();
    system("cls");
    // textbackground(BLACK);
    // textcolor(WHITE);
    DibujaCuadro(1, 1, 70, 21);

    // pinta filas para dar forna del omnibus
    PintaFila(3, 28, 68, 196);
    PintaFila(6, 28, 68, 196);
    PintaFila(9, 28, 68, 196);
    PintaFila(13, 28, 68, 196);
    PintaFila(16, 28, 68, 196);
    PintaFila(19, 28, 68, 196);

    // pinta columnas para dar forna al omnibus
    int c = 28;
    while (c <= 68)
    {
        PintaCol(c, 4, 8, 179);
        PintaCol(c, 14, 18, 179);
        c += 4;
    }
    DibujaCuadro(28, 3, 68, 19);

    // empata los cruces de las filas con las columnas
    c = 32;

    while (c <= 64)
    {
        gotoxy(c, 3);
        putchar(203);
        gotoxy(c, 6);
        putchar(197);
        gotoxy(c, 9);
        putchar(193);
        gotoxy(c, 13);
        putchar(194);
        gotoxy(c, 16);
        putchar(197);
        gotoxy(c, 19);
        putchar(202);
        c += 4;
    }

    // escribe numeros de asiento
    EscribeNumeroAsiento(2, 1, 10);
    EscribeNumeroAsiento(10, 11, 20);
    EscribeNumeroAsiento(12, 21, 30);
    EscribeNumeroAsiento(20, 31, 40);

    // escribe ruta de viaje
    // highvideo();
    EscribeCad(3, 2, "RUTA: ");
    EscribeCad(9, 2, RegRuta.Ciudad);
    // nornvideo();

    // escribe titulos de los datos por ingresar por cada asiento
    EscribeCad(3, 4, "TURNO :");
    EscribeCad(3, 6, "DIA :");
    EscribeCad(3, 8, "ASIENTO: <99=fin>");
    EscribeCad(3, 10, "A.PATERNO");
    EscribeCad(3, 12, "AMATERNO:");
    EscribeCad(3, 14, "NOMBRES :");
    EscribeCad(3, 16, "EDAD :");
    EscribeCad(3, 18, "L. E. :");
}
/******************************************************************************
INGRESA DIA DE VIAJE
******************************************************************************/
int IngresarDia()
{
    int dia;
    do
    {
        dia = IngresaEnt(13, 6, 2);
    } while (dia < 1 || dia > 31);
    return dia;
}
// INGRESA NUMERO DE ASIENTO
int IngresarAsiento()
{
    int asiento;
    do
    {
        asiento = IngresaEnt(13, 8, 2);
    } while ((asiento != 99) && (asiento < 1 || asiento > 40));
    return asiento;
}

// INGRESA EDAD del PASAJERO
int IngresarEdad()
{
    return IngresaEnt(13, 16, 2);
}

// VERIFICA DISPONIBILIDAD DEL DIA Y ASIENTO
char AsientoDisponible()
{
    return (RegTurno.Asientos[RegPasaj.DiaDeViaje]
                             [RegPasaj.NumeroDeAsiento] != Ocupado);
}

// MARCA ASIENTO ELEGIDO para EL DIA DE VIAJE
void OcuparAsiento()
{
    RegTurno.Asientos[RegPasaj.DiaDeViaje]
                     [RegPasaj.NumeroDeAsiento] = Ocupado;
}

// ACUMULA TOTALES POR TURNO Y POR RUTA
void AcumulaTotales(int PasajesVendidos)
{
    RegTurno.TotalVendidosT += PasajesVendidos;
    RegTurno.TotalLibresT = CapacidadOmnibus - RegTurno.TotalVendidosT;
    RegTurno.ImporteTurno = RegRuta.Tarifa * RegTurno.TotalVendidosT;

    RegRuta.TotalVendidosR += PasajesVendidos;
    RegRuta.TotalLibresR = CapacidadOmnibus * RegRuta.Turnos -
                           RegRuta.TotalVendidosR;
    RegRuta.ImporteRuta += RegRuta.Tarifa * PasajesVendidos;
}

// pagina 305
// MARCA ASIENTOS VENDIDOS
void MarcaAsientosVendidos()
{
    int asiento;

    for (asiento = 1; asiento < CapacidadOmnibus; asiento++)
        if (RegTurno.Asientos[RegPasaj.DiaDeViaje][asiento] == Ocupado)
            switch (asiento)
            {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                gotoxy(asiento * 4 + 26, 5);
                putchar(Ocupado);
                break;
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
                gotoxy(asiento * 4 - 14, 8);
                putchar(Ocupado);
                break;
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
                gotoxy(asiento * 4 - 54, 15);
                putchar(Ocupado);
                break;
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 38:
            case 39:
            case 40:
                gotoxy(asiento * 4 - 94, 18);
                putchar(Ocupado);
            }
}

// INGRESA CLAVE DE PASAJEROS
void IngresaClavePasajeros()
{
    RegPasaj.DiaDeViaje = IngresarDia();
}

// INGRESA NUMERO DE ASIENTO
void IngresaNumeroAsiento()
{
    RegPasaj.NumeroDeAsiento = IngresarAsiento();
}

// DETERMINA SI VALE EL NUMERO DE ASIENTO
char ValeNumeroAsiento()
{
    return (RegPasaj.NumeroDeAsiento >= 1 &&
            RegPasaj.NumeroDeAsiento <= 40);
}
// 306
// INGRESA DATOS PASAJES
void IngresarOtrosDatosPasajes()
{
    strcpy(RegPasaj.ApellidoPaterno, IngresaCad(13, 10, 15));
    strcpy(RegPasaj.ApellidoMaterno, IngresaCad(13, 12, 15));
    strcpy(RegPasaj.Nombres, IngresaCad(13, 14, 15));
    RegPasaj.Edad = IngresarEdad();
    strcpy(RegPasaj.LibretaElectoral, IngresaCad(13, 18, 8));
}

// INTERCAMBIA REGISTROS DE PASAJEROS
void IntercambioPasajeros(sRegIndicePasajero &RegAct,
                          sRegIndicePasajero &RegSig)
{
    sRegIndicePasajero RegAux;
    RegAux = RegAct;
    RegAct = RegSig;
    RegSig = RegAux;
}

// ORDENA PASAJEROS POR APELLIDOS
void OrdenaPorApellidos()
{
    int okey;
    char *clave1 = new char[35], *clave2 = new char[50];

    do
    {
        okey = Verdad;
        for (IndPasaj = 0; IndPasaj < NumPasaj - 1; IndPasaj++)
        {
            strcpy(clave1, PASAJEROS[IndPasaj].ApellidoPaterno);
            strcpy(clave1, PASAJEROS[IndPasaj].ApellidoMaterno);

            strcpy(clave2, PASAJEROS[IndPasaj + 1].ApellidoPaterno);
            strcpy(clave2, PASAJEROS[IndPasaj + 1].ApellidoMaterno);

            if (strcmp(clave1, clave2) > 0)
            {
                IntercambioPasajeros(PASAJEROS[IndPasaj], PASAJEROS[IndPasaj + 1]);
                okey = Falso;
            }
        }
    } while (!okey);
    delete[] clave1;
    delete[] clave2;
}

// 307
// AGREGAR REGISTRO DE PASAJEROS
void AgregarRegPasaj()
{
    // almacena registro de pasajero al final del archivo
    ArchPasaj.seekp(0, ios::end);
    ArchPasaj.write((char *)&RegPasaj, TamRegPasajero);

    // almacena clave y posici n en el arreglo  ndice
    strcpy(PASAJEROS[NumPasaj].ApellidoPaterno, RegPasaj.ApellidoPaterno);
    strcpy(PASAJEROS[NumPasaj].ApellidoMaterno, RegPasaj.ApellidoMaterno);
    PASAJEROS[NumPasaj].Posicion = NumPasaj;

    // incrementa numero de registros de pasajeros
    NumPasaj++;
    // ordena arreglo  ndice de pasajeros
    OrdenaPorApellidos();
}

// PROCESO DE VENTA DE PASAJES
void VendePasajes()
{
    int ContPasajesVend = 0;

    IngresaClavePasajeros();
    do
    {
        MarcaAsientosVendidos();
        IngresaNumeroAsiento();
        if (ValeNumeroAsiento())
        {
            if (AsientoDisponible())
            {
                OcuparAsiento();
                IngresarOtrosDatosPasajes();
                AgregarRegPasaj();
                ContPasajesVend++;
            }
        }
        else
            Mensaje(24, "ASIENTO OCUPADO");
    } while (ValeNumeroAsiento());
    AcumulaTotales(ContPasajesVend);
}

// 308
// INGRESA TURNO PARA VENTA DE PASAJES
void IngresaTurnoPasajes()
{
    strcpy(RegPasaj.CodigoRuta, RegRuta.CodigoRuta);
    strcpy(RegPasaj.CodigoTurno, IngresaCad(13, 4, 3));
    if (strlen(RegPasaj.CodigoTurno) > 0)
        Termina = Falso;
    else
        Termina = Verdad;
    // asigna codigo de ruta y turno para la b squeda en TURNOS
    strcpy(RegTurno.CodigoRuta, RegPasaj.CodigoRuta);
    strcpy(RegTurno.CodigoTurno, RegPasaj.CodigoTurno);
}

// EJECUTA PROCESO DE PASAJES
void EjecutaPasajes()
{
    ListaTurnos();
    if (!Termina && RegRutaesActivo())
        do
        {
            PantallaPasajes();
            IngresaTurnoPasajes();
            if (!Termina)
            {
                IndTurno = BuscarRutaTurno();
                if (IndTurno != -1)
                {
                    RecuperaRegDeTurnos(IndTurno);
                    if (RegTurnoesActivo())
                    {
                        VendePasajes();
                        ActualizaRegEnTurnos(IndTurno);
                        ActualizaRegEnRutas(IndRuta);
                    }
                    else
                        Mensaje(24, "Codigo de TURNO est  ANULADO");
                }
                else
                    Mensaje(24, "TURNO NO CORRESPONDE A RUTA INGRESADA");
            }
        } while (!Termina);
}

// 309
// MODULO de CONSULTAS

// PANTALLA DE OPCIONES DE CONSULTA.
int Consultas()
{
    const int columna = 55;
    const int fila = 13;
    char *opciones[] =
        {"Rutas",
         "Turnos",
         "Pasajeros",
         "Retorno"};
    Presentacion();
    EscribeCad(columna, fila - 2, "CONSULTAS");
    return MenuPopUp(columna, fila, opciones, 4);
}

// PANTALLA para CONSULTA de todas las RUTAS..
void PantallaConsultaRutas()
{
    // clrscr();
    system("cls");
    DibujaCuadro(1, 1, 70, 21);

    CentraCad(2, "< CONSULTA RUTAS>");
    EscribeCad(3, 4, "RUTA");
    EscribeCad(8, 4, "CIUDAD");
    EscribeCad(36, 4, "TARIFA");
    EscribeCad(45, 4, "LIBRES");
    EscribeCad(52, 4, "VENDIDOS");
    EscribeCad(62, 4, "IMPORTE");
    EscribeCad(3, 20, "TOTALES");
}

// MUESTRA REGISTRO DE RUTA EN CONSULTA DE RUTAS.
void MuestraConsRegRuta(int &fila, int &Libres, int &Vendidos,
                        float &Importe)
{
    fila++;
    EscribeCad(3, fila + 4, RegRuta.CodigoRuta);
    EscribeCad(8, fila + 4, RegRuta.Ciudad);
    EscribeCad(35, fila + 4, AlineaDer(7, FormatoNum(RegRuta.Tarifa, 2)));
    EscribeCad(46, fila + 4, AlineaDer(5, FormatoNum(RegRuta.TotalLibresR, 0)));
    EscribeCad(55, fila + 4, AlineaDer(5, FormatoNum(RegRuta.TotalVendidosR, 0)));
    EscribeCad(61, fila + 4, AlineaDer(8, FormatoNum(RegRuta.ImporteRuta, 2)));

    Libres += RegRuta.TotalLibresR;
    Vendidos += RegRuta.TotalVendidosR;
    Importe += RegRuta.ImporteRuta;
}
// 310
//  CONSULTA de todas las RUTAS..
/* observe la forma de recuperar el registro de rutas, debido a que las rutas deben aparecer ordenadas de acuerdo a su arreglo  ndice.
 */
void ConsultaRutas()
{
    int Libres = 0, Vendidos = 0, fila = 0;
    float Importe = 0;

    PantallaConsultaRutas();
    for (IndRuta = 0; IndRuta < NumRutas; IndRuta++)
    {
        RecuperaRegDeRutas(RUTAS[IndRuta].Posicion);
        if (RegRutaesActivo())
        {
            MuestraConsRegRuta(fila, Libres, Vendidos, Importe);
            if (CambiaPantA(fila))
            {
                MuestraConsRegRuta(fila, Libres, Vendidos, Importe);
                if (CambiaPantA(fila))
                {
                    Mensaje(24, "Para continuar");
                    PantallaConsultaRutas();
                    fila = 0;
                }
            }
        }
        EscribeCad(46, 20, AlineaDer(5, FormatoNum(Libres, 0)));
        EscribeCad(55, 20, AlineaDer(5, FormatoNum(Vendidos, 0)));
        EscribeCad(61, 20, AlineaDer(8, FormatoNum(Importe, 2)));
        Mensaje(24, "Para continuar");
    }
}

// MUESTRA TOTALES DEL REGISTRO DE RUTA
void MuestraTotalesRegRuta()
{
    EscribeCad(29, 20, AlineaDer(5, FormatoNum(RegRuta.TotalLibresR, 0)));
    EscribeCad(46, 20, AlineaDer(5, FormatoNum(RegRuta.TotalVendidosR, 0)));
    EscribeCad(59, 20, AlineaDer(8, FormatoNum(RegRuta.ImporteRuta, 2)));

    Mensaje(24, "Para continuar");
}

// PANTALLA para CONSULTA de TURNOS.
void PantallaConsultaTurnos()
{
    // clrscr();
    system("cls");
    DibujaCuadro(1, 1, 70, 21);
    CentraCad(2, "< CONSULTA TURNOS >");
    EscribeCad(7, 4, "CODIGO RUTA: ");
    EscribeCad(32, 4, "CIUDAD: ");
    EscribeCad(7, 5, "TARIFA S/.: ");
    EscribeCad(3, 6, "TURNO ");
    EscribeCad(17, 6, "HORA ");
    EscribeCad(28, 6, "LIBRES ");
    EscribeCad(43, 6, "VENDIDOS ");
    EscribeCad(60, 6, "IMPORTE ");
    EscribeCad(3, 20, "TOTALES");
}
// 311
//  MUESTRA REGISTRO DE TURNO EN CONSULTA DE TURNOS..
void MuestraConsRegTurno(int &fila)
{
    fila++;
    EscribeCad(3, fila + 7, RegTurno.CodigoTurno);
    EscribeCad(17, fila + 7, RegTurno.HoraPartida);
    EscribeCad(29, fila + 7, AlineaDer(5, FormatoNum(RegTurno.TotalLibresT, 0)));
    EscribeCad(46, fila + 7, AlineaDer(5, FormatoNum(RegTurno.TotalVendidosT, 0)));
    EscribeCad(59, fila + 7, AlineaDer(8, FormatoNum(RegTurno.ImporteTurno, 2)));
}

// CONSULTA DE TURNOS POR RUTA...
/* observe que no es necesario ordenar debido a que el arreglo  ndice siempre se mantiene ordenado.
observe la forma de recuperar el registro de turnos, debido a que la consulta debe mostrar los registros ordenados seg n su arreglo  ndice.
*/
void ConsultaTurnosDeRuta()
{
    int fila = 0;
    // Ordena TurnosporHora();
    for (IndTurno = 0; IndTurno < NumTurnos; IndTurno++)
    {
        RecuperaRegDeTurnos(TURNOS[IndTurno].Posicion);
        if (RutaenAesRutaenB() && RegTurnoesActivo())
        {
            MuestraConsRegTurno(fila);
            if (CambiaPantA(fila))
            {
                Mensaje(24, "Para continuar");
                BorraArea(2, 8, 69, 20);
                fila = 0;
            }
        }
    }
}

// 312
//  INGRESA CLAVE DE TURNO EN CONSULTA DE TURNOS.
void IngresaClaveConsTurnos()
{
    strcpy(RegTurno.CodigoRuta, IngresaCad(20, 4, 3));
    if (strlen(RegTurno.CodigoRuta) > 0)
        Termina = Falso;
    else
        Termina = Verdad;
    // asigna codigo de ruta para la b squeda en RUTAS
    strcpy(RegRuta.CodigoRuta, RegTurno.CodigoRuta);
}

// MUESTRA REGISTRO DE RUTA EN CONSULTA DE TURNO.
void MuestraConsTurnoRegRuta()
{
    EscribeCad(40, 4, RegRuta.Ciudad);
    EscribeCad(20, 5, FormatoNum(RegRuta.Tarifa, 2));
}
// CONSULTA DE TURNOS.
void ConsultaTurnos()
{
    do
    {
        PantallaConsultaTurnos();
        IngresaClaveConsTurnos();
        if (!Termina)
        {
            IndRuta = BuscarCodigoRuta();
            if (IndRuta != -1)
            {
                RecuperaRegDeRutas(IndRuta);
                if (RegRutaesActivo())
                {
                    MuestraConsTurnoRegRuta();
                    ConsultaTurnosDeRuta();
                    MuestraTotalesRegRuta();
                }
                else
                    Mensaje(24, "Codigo de RUTA est  ANULADO");
            }
            else
                Mensaje(24, "CODIGO de RUTA NO REGISTRADO");
        }

    } while (!Termina);
}

// 313
//  PANTALLA PARA CONSULTA de PASAJEROS....
void PantallaConsultaPasajeros()
{
    // clrscr();
    system("cls");
    DibujaCuadro(1, 1, 70, 21);

    CentraCad(2, "< CONSULTA PASAJEROS>");
    EscribeCad(5, 4, "CODIGO RUTA: ");
    EscribeCad(32, 4, "CIUDAD: ");
    EscribeCad(5, 5, "CODIGO TURNO: ");
    EscribeCad(32, 5, "HORA :");
    EscribeCad(3, 7, "DIA ");
    EscribeCad(7, 7, "ASIENTO");
    EscribeCad(15, 7, "APELLIDOS");
    EscribeCad(37, 7, "NOMBRES");
    EscribeCad(50, 7, "EDAD");
    EscribeCad(60, 7, "L.E.");
}

// DETERMINA SI CODIGO DE RUTA ES IGUAL AL DEL PASAJERO
char RutaTurnoenCesRutaTurnoenB()
{
    return (strcmp(RegPasaj.CodigoRuta, RegTurno.CodigoRuta) == 0 &&
            strcmp(RegPasaj.CodigoTurno, RegTurno.CodigoTurno) == 0);
}

// LISTA REGISTRO DE PASAJEROS.
void ListaRegPasaj(int &fila)
{
    fila++;
    EscribeCad(3, fila + 7, AlineaDer(3, FormatoNum(RegPasaj.DiaDeViaje, 0)));
    EscribeCad(7, fila + 7, AlineaDer(4, FormatoNum(RegPasaj.NumeroDeAsiento, 0)));
    EscribeCad(15, fila + 7, strcat(strcat(RegPasaj.ApellidoPaterno, ""), RegPasaj.ApellidoMaterno));
    EscribeCad(37, fila + 7, RegPasaj.Nombres);
    EscribeCad(50, fila + 7, AlineaDer(4, FormatoNum(RegPasaj.Edad, 0)));
    EscribeCad(60, fila + 7, RegPasaj.LibretaElectoral);
}

// RECUPERA REGISTRO DE PASAJEROS..
void RecuperaRegdePASAJEROS(int indice)
{
    ArchPasaj.seekg(indice * TamRegPasajero, ios::beg);
    ArchPasaj.read((char *)&RegPasaj, TamRegPasajero);
}

// 314
//  LISTADO DE VIAJEROS..
/* observe que no es necesario ordenar por apellidos debido a que su arreglo  ndice siempre se mantiene ordenado.
tambi n observe la forma de recuperar el registro de pasajero. Esto para que el listado salga ordenado de acuerdo a su arreglo indice.
*/
void ListarViajeros()
{
    int fila = 0;

    EscribeCad(40, 4, RegRuta.Ciudad);
    EscribeCad(40, 5, RegTurno.HoraPartida);

    // OrdenaporApellidos();
    for (IndPasaj = 0; IndPasaj < NumPasaj; IndPasaj++)
    {
        RecuperaRegdePASAJEROS(PASAJEROS[IndPasaj].Posicion);
        if (RutaTurnoenCesRutaTurnoenB())
        {
            ListaRegPasaj(fila);
            if (CambiaPantA(fila))
            {
                Mensaje(24, "Para continuar");
                BorraArea(3, 8, 69, 20);
                fila = 0;
            }
        }
    }
    Mensaje(24, "Para continuar");
    BorraArea(3, 8, 69, 20);
}

// INGRESA CLAVE DE PASAJEROS.
void IngresaClaveConsPasajeros()
{
    strcpy(RegPasaj.CodigoRuta, IngresaCad(20, 4, 3));
    if (strlen(RegPasaj.CodigoRuta) > 0)
        Termina = Falso;
    else
        Termina = Verdad;

    // asigna codigo de ruta para la b squeda en RUTAS
    strcpy(RegRuta.CodigoRuta, RegPasaj.CodigoRuta);
    // asigna codigo de ruta para la b squeda en TURNOS
    strcpy(RegTurno.CodigoRuta, RegPasaj.CodigoRuta);
}

// 315
//  INGRESA CODIGO DE TURNO EN CONSULTA DE PASAJEROS..........
void IngresaTurnoConsPasajeros()
{
    strcpy(RegPasaj.CodigoTurno, IngresaCad(20, 5, 3));
    // asigna codigo de turno para la b squeda en TURNOS
    strcpy(RegTurno.CodigoTurno, RegPasaj.CodigoTurno);
}
// DETERMINA SI CONSULTA OTRO TURNO DE PASAJEROS.
char OtroTurnoConsPasajeros()
{
    return (strlen(RegPasaj.CodigoTurno) > 0);
}

// CONTINUA CON LA CONSULTA DE PASAJEROS.
void ContinuaConsultaPasajeros()
{
    do
    {
        IngresaTurnoConsPasajeros();
        if (OtroTurnoConsPasajeros())
        {
            IndTurno = BuscarRutaTurno();
            if (IndTurno != -1)
            {
                RecuperaRegDeTurnos(IndTurno);
                if (RegTurnoesActivo())
                    ListarViajeros();
                else
                    Mensaje(24, "Codigo de TURNO est  ANULADO");
            }
            else
                Mensaje(24, "CODIGO de TURNO NO corresponde a la RUTA");
        }

    } while (OtroTurnoConsPasajeros());
}

// CONSULTA PASAJEROS...
void ConsultaPasajeros()
{
    PantallaConsultaPasajeros();
    IngresaClaveConsPasajeros();
    if (!Termina)
    {
        IndRuta = BuscarCodigoRuta();
        if (IndRuta != -1)
        {
            RecuperaRegDeRutas(IndRuta);
            if (RegRutaesActivo())
                ContinuaConsultaPasajeros();
            else
                Mensaje(24, "Codigo de RUTA est  ANULADO");
        }
        else
            Mensaje(24, "CODIGO de RUTA NO REGISTRADO");
    }
}
// 316

// EJECUCION DE PROCESOS
//  EJECUTA CONSULTAS.
void EjecutaConsultas()
{
    int OpcionConsultas;

    do
    {
        OpcionConsultas = Consultas();
        switch (OpcionConsultas)
        {
        case 1:
            ConsultaRutas();
            break;
        case 2:
            ConsultaTurnos();
            break;
        case 3:
            ConsultaPasajeros();
            break;
        }
    } while (OpcionConsultas > 0 && OpcionConsultas < 4);
}

// EJECUTA TURNOS.
void EjecutaTurnos()
{
    int OpcionTurnos;
    do
    {
        OpcionTurnos = MenuTurnos();
        switch (OpcionTurnos)
        {
        case 1:
            IngresoTurnos();
            break;
        case 2:
            ModificaTurnos();
            break;
        case 3:
            AnulaActivaTurnos();
            break;
        case 4:
            ListaTurnos();
            break;
        }
    } while (OpcionTurnos > 0 && OpcionTurnos < 5);
}

// EJECUTA RUTAS...
void EjecutaRutas()
{
    int OpcionRutas;
    do
    {
        OpcionRutas = MenuRutas();
        switch (OpcionRutas)
        {
        case 1:
            IngresoRutas();
            break;
        case 2:
            ModificaRutas();
            break;
        case 3:
            AnuloOActivoRuta();
            break;
        case 4:
            ListaRutas();
            break;
        }
    } while (OpcionRutas > 0 && OpcionRutas < 5);
}

// 317
//  INICIALIZA MES.
void InicializaMes()
{
    // inicializa archivo de rutas
    for (IndRuta = 0; IndRuta < NumRutas; IndRuta++)
    {
        RecuperaRegDeTurnos(IndTurno);

        memset(RegTurno.Asientos, 0, sizeof(RegTurno.Asientos));
        RegTurno.TotalLibresT = CapacidadOmnibus;
        RegTurno.TotalVendidosT = 0;
        RegTurno.ImporteTurno = 0;

        ActualizaRegEnTurnos(IndTurno);
    }
    // inicializa archivo de rutas
    for (IndRuta = 0; IndRuta < NumRutas; IndRuta++)
    {
        RecuperaRegDeRutas(IndRuta);

        RegRuta.TotalLibresR = RegRuta.Turnos * CapacidadOmnibus;
        RegRuta.TotalVendidosR = 0;
        RegRuta.ImporteRuta = 0;

        ActualizaRegEnRutas(IndRuta);
    }
    // inicializa archivo de pasajeros
    ArchPasaj.open(NombreArchPasaj, ios::trunc);
    NumPasaj = 0;

    Mensaje(24, "TODO LISTO para el NUEVO MES");
}

// 318
//  MENU PRINCIPAL.
int Principal()
{
    const int columna = 50;
    const int fila = 9;
    char *opciones[] = {"Rutas",
                        "Turnos",
                        "Pasajes",
                        "Consultas",
                        "Otro Mes",
                        "Fin"};
    Presentacion();
    EscribeCad(columna, fila - 2, "PRINCIPAL");
    return MenuPopUp(columna, fila, opciones, 6);
}
// PROCESO DE EJECUCION DEL PROYECTO.
void Ejecutar()
{

    int OpcionPrincipal;
    do
    {
        OpcionPrincipal = Principal();
        switch (OpcionPrincipal)
        {
        case 1:
            EjecutaRutas();
            break;
        case 2:
            EjecutaTurnos();
            break;
        case 3:
            EjecutaPasajes();
            break;
        case 4:
            EjecutaConsultas();
            break;
        case 5:
            InicializaMes();
            break;
        }
    } while (OpcionPrincipal > 0 && OpcionPrincipal < 6);
}

// PROCESO DE FINALIZACION DEL PROYECTO.
void Finalizar()
{
    // cerrar archivos
    ArchRutas.close();
    ArchTurnos.close();
    ArchPasaj.close();
    // da un mensaje de despedida
    // clrscr();
    system("cls");
    Mensaje(10, "Muchas Gracias por todo...");
    // clrscr();
    system("cls");
}

// 319
//  DETERMINA EL NUMERO DE REGISTROS DE CADA ARCHIVO..........
void DeterminaNumeroDeRegistros()
{
    ArchRutas.seekg(0, ios::end);
    NumRutas = ArchRutas.tellg() / TamRegRuta;
    ArchTurnos.seekg(0, ios::end);
    NumTurnos = ArchTurnos.tellg() / TamRegTurno;
    ArchPasaj.seekg(0, ios::end);
    NumPasaj = ArchPasaj.tellg() / TamRegPasajero;
}

// CREA ARREGLO DE INDICE DE RUTAS..
void CreaArregloIndiceDeRutas()
{
    ArchRutas.seekg(0, ios::beg);

    for (IndRuta = 0; IndRuta < NumRutas; IndRuta++)
    {
        ArchRutas.read((char *)&RegRuta, TamRegRuta);
        strcpy(RUTAS[IndRuta].Ciudad, RegRuta.Ciudad);
        RUTAS[IndRuta].Posicion = IndRuta;
    }
    OrdenaPorCiudad();
}

// CREA ARREGLO DE INDICE DE TURNOS.
void CreaArregloIndiceDeTurnos()
{
    ArchTurnos.seekg(0, ios::beg);

    for (IndTurno = 0; IndTurno < NumTurnos; IndTurno++)
    {
        ArchTurnos.read((char *)&RegTurno, TamRegTurno);
        strcpy(TURNOS[IndTurno].CodigoRuta, RegTurno.CodigoRuta);
        strcpy(TURNOS[IndTurno].HoraPartida, RegTurno.HoraPartida);
        TURNOS[IndTurno].Posicion = IndTurno;
    }
    OrdenaTurnosPorHora();
}

// CREA ARREGLO DE INDICE DE PASAJEROS.
void CreaArregloIndiceDePasaj()
{
    ArchPasaj.seekg(0, ios::beg);

    for (IndPasaj = 0; IndPasaj < NumPasaj; IndPasaj++)
    {
        ArchPasaj.read((char *)&RegPasaj, TamRegPasajero);
        strcpy(PASAJEROS[IndPasaj].ApellidoPaterno, RegPasaj.ApellidoPaterno);
        strcpy(PASAJEROS[IndPasaj].ApellidoMaterno, RegPasaj.ApellidoMaterno);
        PASAJEROS[IndPasaj].Posicion = IndPasaj;
    }
    OrdenaPorApellidos();
}

// 320
// CREA ARREGLOS INDICE..
void CreaArreglosIndice()
{
    CreaArregloIndiceDeRutas();
    CreaArregloIndiceDeTurnos();
    CreaArregloIndiceDePasaj();
}
// PROCESO DE INICIALIZACION.
void Inicializar()
{
    // abre archivos
    ArchRutas.open(NombreArchRutas, ios::in | ios::out | ios::binary);
    if (!ArchRutas.is_open())
    {
        Mensaje(24, "ERROR. no puedo abrir el archivo de Rutas.");
        exit(1);
    }

    ArchTurnos.open(NombreArchTurnos, ios::in | ios::out | ios::binary);
    if (!ArchTurnos.is_open())
    {
        Mensaje(24, "ERROR. no puedo abrir el archivo de Turnos.");
        exit(1);
    }

    ArchPasaj.open(NombreArchPasaj, ios::in | ios::out | ios::binary);
    if (!ArchPasaj.is_open())
    {
        Mensaje(24, "ERROR. no puedo abrir el archivo de Pasajeros.");
        exit(1);
    }
    DeterminaNumeroDeRegistros();
    CreaArreglosIndice();
}
