#include "uProPres.h"
#include "milib.h"
#include "uCadenas.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

cMantSecPre::cMantSecPre():
    cMantArchSec("MANTENIEMIENTO de PRESTAMOS", "Prestamo.DAT",
                 &RegPrestamo, sizeof(RegPrestamo), 4,1,23,80, ListadoConFiltro)
{
    if(mTodoCorrecto()){
        if(!ObjCliente.mTodoCorrecto())
            mRegistraError();
    }
    else
        mRegistraError();
}


int cMantSecPre::Menu(){
    int voOpcion;
    const char *opciones[] = {"Ingreso ",
                            "Anulacion",
                            "Consulta",
                            "Listado",
                            "Fin    "};
    cCadena voCadena;

    EscribeCad(1, 25, voCadena.Espacios(79));
    voOpcion = MenuBarra(1, 25, opciones, 5);
    EscribeCad(1, 25, voCadena.Espacios(79));
    if(voOpcion == 5)
        voOpcion = 0;
    return voOpcion;
}


void cMantSecPre::RealizaAcciones(int pvOpcion){
    switch(pvOpcion){
        case 1: Ingresos(); break;
        case 2: Anulacion(); break;
        case 3: Consulta(); break;
        case 4: Listado(); break;
    }
}


int cMantSecPre::IngresaClave(){
    int voClienteHabilitado, voSi;
    cCadena voCadena;

    if(mOpcionElegida() != cgOpcIngreso){
        CentraCad(22, "PARA TERMINAR, presione solo [ENTER] al ingresar Numero de Prestamo");
        NumeroPrest = IngresaEnt(40,8,3);
        voSi = NumeroPrest != 0;
        EscribeCad(1,22,voCadena.Espacios(79));
    }
    else{
        do{
            CentraCad(22,"PARA TERMINAR, presione solo [ENTER] al ingresar Libreta Electroal");
            voClienteHabilitado = 0;
            NumeroPrest = NumeroRegistros()+1;
            EscribeCad(40,8,FormatoNum(NumeroPrest,0));
            EscribeCad(40,10,voCadena.Espacios(41));
            strcpy(RegCliente.LibretaElec, voCadena.Espacios(8));
            strcpy(RegCliente.LibretaElec, reinterpret_cast<const char*>(IngresaCad(40,9,8)));
            if(strlen(RegCliente.LibretaElec)>0){
                EscribeCad(1,22,voCadena.Espacios(79));
                if(!ObjCliente.mObtieneReg(RegCliente.LibretaElec, RegCliente))
                    Mensaje(25,"CLIENTE NO REGISTRADO");
                else{
                    char apynomb[81];
                    strcpy(apynomb, voCadena.SinBlancosDer(RegCliente.Apellidos));
                    strcat(apynomb, " ");
                    strcat(apynomb, RegCliente.Nombres);
                    EscribeCad(10, 10, apynomb);
                    voClienteHabilitado = ClienteHabilitado();
                }
            }
        }while (!voClienteHabilitado && strlen(RegCliente.LibretaElec)>0);

        voSi = (strlen(RegCliente.LibretaElec)>0);
    }
    return voSi;
}


void cMantSecPre::IngresaOtrosCampos(){
    int voDiaSem, voDia, voMes, voAnio;
    char voFechaPrestamo[15];
    int voConfirma;

    FechaSistema(voDiaSem, voDia, voMes, voAnio);

    do{
        RegPrestamo.NumPrestamo = NumeroPrest;
        strcpy(RegPrestamo.LibretaElec, RegCliente.LibretaElec);

        do{
            RegPrestamo.NumCuotas = 12;
            RegPrestamo.NumCuotas = IngresaEnt(40, 16, 2);
        } while (RegPrestamo.NumCuotas < 12 || RegPrestamo.NumCuotas > 36);

        //calcula importes del prestamo
        RegPrestamo.MontoDePres = 10 * RegCliente.UltimoSaldo;
        RegPrestamo.MontoDeInt  = RegPrestamo.MontoDePres * 1.5 * RegPrestamo.NumCuotas/100;
        RegPrestamo.Mensualidad = (RegPrestamo.MontoDePres + RegPrestamo.MontoDeInt)/RegPrestamo.NumCuotas;
        RegPrestamo.TotalAmort  = 0;
        RegPrestamo.TotalInt    = 0;
        RegPrestamo.NumPagos    = 0;
        RegPrestamo.Estado      = 1; //activo

        //asigna campos de fecha del prestamo
        RegPrestamo.FechaDePres.dia = voDia;
        RegPrestamo.FechaDePres.mes = voMes;
        RegPrestamo.FechaDePres.anio = voAnio;

        //muestra campos de fecha del prestamo
        EscribeCad(40, 11, FormatoFecha(voDia, voMes, voAnio));

        //muestra campos de importes
        EscribeCad(10, 12, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.MontoDePres, 2))));
        EscribeCad(10, 13, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.MontoDeInt, 2))));
        EscribeCad(10, 17, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.Mensualidad, 2))));

        //Pide conformidad para el ingreso
        voConfirma = (Respuesta(25, "Esta de acuerdo con el ingreso?", "SN")== 'S');
        if(!voConfirma)
            BorraArea(40, 10, 80, 15);
        else{
            //actualiza registro del cliente
            RegCliente.PrestamoAct = 1;
            RegCliente.Prestamos++;
            ObjCliente.mActualizaCliente(RegCliente);
        }
    } while (!voConfirma);
}


void cMantSecPre::LimpiaEntrada(){ BorraArea(40, 8, 80, 17); }


void cMantSecPre::FormatoPantalla(const char *pvTitulo){
    BorraArea(1, 4, 80, 23);
    CentraCad(5, pvTitulo);
    EscribeCad(20, 8, "Numero de Prestammo: ");
    EscribeCad(20, 9, "Libreta Electoral: ");
    EscribeCad(20, 10, "Cliente: ");

    EscribeCad(20, 11, "Fecha de Prestamo: ");
    EscribeCad(20, 12, "Monto de Prestamo: ");
    EscribeCad(20, 13, "Monto de Intereses: ");
    EscribeCad(20, 14, "Total Amortizado: ");
    EscribeCad(20, 15, "Total Intereses: ");
    EscribeCad(20, 16, "Numero de Cuotas: ");
    EscribeCad(20, 17, "Mensualidad: ");
    EscribeCad(20, 18, "Numero de Pagos: ");
}


int cMantSecPre::ClienteHabilitado(){
    int voDiaSem, voDiaAct, voMesAct, voAnioAct, voAnioIng, voMesIng, voDiaIng, voError;

    int voSi;

    FechaSistema(voDiaSem, voDiaAct, voMesAct, voAnioAct);
    voDiaIng = RegCliente.FechaIng.dia;
    voMesIng = RegCliente.FechaIng.mes;
    voAnioIng = RegCliente.FechaIng.anio;

    voSi = 0;
    if(!RegCliente.Estado)
        Mensaje(25, "CLIENTE ESTA ANULADO");
    else
        if(RegCliente.PrestamoAct)
            Mensaje(25, "CLIENTE TIENE PRESTAMO POR CANCELAR");
        else
            if(RegCliente.UltimoSaldo < 100)
                Mensaje(25, "ULTIMO SALDO NO CUMPLE REQUISITO");
            else
                if(((voAnioAct - 1)*360 + (voMesAct - 1)*30 + (voDiaAct))-
                   ((voAnioIng - 1)*360 + (voMesIng - 1)*30 + (voDiaIng))<360)
                   Mensaje(25, "CLIENTE NO TIENE UN A�O DE ANTIGUEDAD");
                else
                    voSi=1;
    return voSi;
}


int cMantSecPre::ClaveEncontrada(){
    if(mOpcionElegida() != cgOpcIngreso)
        return (RegPrestamo.NumPrestamo == NumeroPrest);
    else
        return 0;
}


void cMantSecPre::MuestraInformacion(){
    cCadena voCadena;

    //obtiene informacion del cleinte correspondiente al prestamo en consulta
    ObjCliente.mObtieneReg(RegPrestamo.LibretaElec, RegCliente);

    EscribeCad(40, 9, RegPrestamo.LibretaElec);
    EscribeCad(40, 10, ObjCliente.mApellidosYNombres());
    EscribeCad(40, 11, FormatoFecha(RegPrestamo.FechaDePres.dia,
                                    RegPrestamo.FechaDePres.mes,
                                    RegPrestamo.FechaDePres.anio));
    EscribeCad(40, 12, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.MontoDePres, 2))));
    EscribeCad(40, 13, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.MontoDeInt, 2))));
    EscribeCad(40, 14, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.TotalAmort, 2))));
    EscribeCad(40, 15, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.TotalInt, 2))));
    EscribeCad(40, 16, reinterpret_cast<const char*>(AlineaDer(3, FormatoNum(RegPrestamo.NumCuotas, 0))));
    EscribeCad(40, 17, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.Mensualidad, 2))));
    EscribeCad(40, 18, reinterpret_cast<const char*>(AlineaDer(3, FormatoNum(RegPrestamo.NumPagos, 0))));
}


void cMantSecPre::CorrigeInformacion() {
    // Mostrar la informaci�n actual antes de la correcci�n
    LimpiaEntrada();
    FormatoPantalla("CORRECCI�N DE INFORMACI�N");
    MuestraInformacion();
    cCadena voCadena;

    char opcion;
    do {
        EscribeCad(1, 22, "Seleccione el campo a corregir (N: NumCuotas, M: MontoDePres, I: MontoDeInt, Q: Salir): ");
        opcion = toupper(getch());

        switch (opcion) {
        case 'N':
            do {
                EscribeCad(1, 23, "Ingrese el nuevo valor para NumCuotas: ");
                RegPrestamo.NumCuotas = IngresaEnt(41, 23, 2);
            } while (RegPrestamo.NumCuotas < 12 || RegPrestamo.NumCuotas > 36);
            break;

        case 'M':
            EscribeCad(1, 23, "Ingrese el nuevo valor para MontoDePres: ");
            RegPrestamo.MontoDePres = IngresaReal(41, 23, 10);
            break;

        case 'I':
            EscribeCad(1, 23, "Ingrese el nuevo valor para MontoDeInt: ");
            RegPrestamo.MontoDeInt = IngresaReal(41, 23, 10);
            break;

        case 'Q':
            EscribeCad(1, 22, voCadena.Espacios(79));  // Limpiar mensaje de selecci�n
            return;  // Salir de la funci�n

        default:
            EscribeCad(1, 23, "Opci�n no v�lida. Intente de nuevo.");
            break;
        }
    } while (true);
}

int cMantSecPre::InformacionActiva(){
    //determina si el registro esta activo
    return (RegPrestamo.Estado);
}


int cMantSecPre::EsAnulable(){
    int voEsAnulable;
    voEsAnulable = 0;

    if(!RegPrestamo.Estado)
        Mensaje(25, "Prestamo ya esta anulado");
    else
        if(RegPrestamo.NumCuotas > RegPrestamo.NumPagos &&
           RegPrestamo.NumPagos > 0)
            Mensaje(25, "Prestamo tiene cuotas pendientes de pago");
        else
            voEsAnulable = 1;
    return voEsAnulable;
}


void cMantSecPre::AnulaInformacion(){
    //cmabia de valor al campo ESTADO del registro para anularlo
    RegPrestamo.Estado  = 0;
    RegCliente.PrestamoAct  = 0;
    ObjCliente.mRecibeRegistro(RegCliente);
    ObjCliente.ActualizaInformacion();
}


int cMantSecPre::InformacionMostrable(){
    return (RegPrestamo.Estado);
}

char* cMantSecPre::Informacion(){
    cCadena voCadena;

    //devuelve el contenido de la informacion del registro a presentar
    ObjCliente.mObtieneReg(RegPrestamo.LibretaElec, RegCliente);
    char cadenas[12][80], cadena[256];

    strcpy(cadenas[0], reinterpret_cast<const char*>(AlineaDer(3, FormatoNum(RegPrestamo.NumPrestamo, 0))));
    strcpy(cadenas[1], voCadena.ConBlancosIzq(
                                FormatoFecha(RegPrestamo.FechaDePres.dia,
                                             RegPrestamo.FechaDePres.mes,
                                             RegPrestamo.FechaDePres.anio), 11));
    strcpy(cadenas[2], reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.MontoDePres, 2))));
    strcpy(cadenas[3], reinterpret_cast<const char*>(AlineaDer(7, FormatoNum(RegPrestamo.NumCuotas, 0))));
    strcpy(cadenas[4], reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.MontoDeInt, 2))));
    strcpy(cadenas[5], reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.Mensualidad, 2))));
    strcpy(cadenas[6], reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(RegPrestamo.TotalAmort, 2))));
    strcpy(cadenas[7], reinterpret_cast<const char*>(AlineaDer(11, FormatoNum(RegPrestamo.TotalInt, 2))));
    strcpy(cadenas[8], reinterpret_cast<const char*>(AlineaDer(5, FormatoNum(RegPrestamo.NumPagos, 0))));
    strcpy(cadenas[9], voCadena.ConBlancosIzq(RegPrestamo.LibretaElec, 11));

    strcpy(cadena, ObjCliente.mApellidosYNombres());
    strcpy(cadenas[10], voCadena.ConBlancosDer(cadena, 40));

    int longitud = strlen(cadenas[0]);
    strcpy(cadena, cadenas[0]);
    for(int i=1; i<11; i++){
        strcat(cadena, cadenas[i]);
        longitud += strlen(cadenas[i]);
    }
    cadena[longitud] = '\0';
    return cadena;
}


void cMantSecPre::AsignarEncabezado(){
    cCadena voCadena;
    char cadenas[12][80], cadena[256];

    strcpy(cadenas[0], voCadena.ConBlancosDer("PRE",        3));
    strcpy(cadenas[1], voCadena.ConBlancosIzq("FECHA",      11));
    strcpy(cadenas[2], voCadena.ConBlancosIzq("MONTO",      10));
    strcpy(cadenas[3], voCadena.ConBlancosIzq("CUOTAS",     7));
    strcpy(cadenas[4], voCadena.ConBlancosIzq("INTERESES",  10));
    strcpy(cadenas[5], voCadena.ConBlancosIzq("MENSUAL",    10));
    strcpy(cadenas[6], voCadena.ConBlancosIzq("AMORTIZ.",   10));
    strcpy(cadenas[7], voCadena.ConBlancosIzq("INTPAG",     11));
    strcpy(cadenas[8], voCadena.ConBlancosIzq("PAGOS",      5));
    strcpy(cadenas[9], voCadena.ConBlancosIzq("ELECTORAL",  11));
    strcpy(cadenas[10], voCadena.ConBlancosDer("CLIENTE",   40));

    int longitud = strlen(cadenas[0]);
    strcpy(cadena, cadenas[0]);
    for(int i=0; i<11; i++){
        strcat(cadena, cadenas[i]);
        longitud += strlen(cadenas[i]);
    }
    cadena[longitud] = '\0';
    AdicionarEncabezado(cadena);
}


void cMantSecPre::mRecibeRegistro(sRegPrestamo pvRegPrestamo){
    RegPrestamo = pvRegPrestamo;
}


void cMantSecPre::mDevuelveRegistro(sRegPrestamo &prRegPrestamo){
    prRegPrestamo = RegPrestamo;
}


void cMantSecPre::mRecibeNumeroPrest(int pvNumeroPrest){
    NumeroPrest = pvNumeroPrest;
}


int cMantSecPre::mObtieneReg(int pvNumeroPrest,
                               sRegPrestamo &prRegPrestamo){
    int voObtieneReg;

    NumeroPrest = pvNumeroPrest;
    voObtieneReg = 0;
    if(UbicaClave()){
        prRegPrestamo = RegPrestamo;
        voObtieneReg = 1;
    }
    return voObtieneReg;
}


void cMantSecPre::mDevuelveCliente(sRegCliente &prRegCliente){
    ObjCliente.mObtieneReg(prRegCliente.LibretaElec, prRegCliente);
}

