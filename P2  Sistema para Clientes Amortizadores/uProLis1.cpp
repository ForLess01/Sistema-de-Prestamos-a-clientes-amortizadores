#include "uProLis1.h"
// -------------------------------------------------------

cListPreCli::cListPreCli(){
    if (mTodoCorrecto()){
        if(! ObjCliente.mTodoCorrecto())
            mRegistraError( );
        else
            ReiniciaLimites(7,1,23,80, ListadoConFiltro);
    }
}

//--------------------------------------------------------

void cListPreCli::Ejecuta()
{
    int voIngresaClave;
    do{
        FormatoListado();
        voIngresaClave = IngresaClave();
        if(voIngresaClave){
            if (!ObjCliente.mObtieneReg(RegCliente.LibretaElec, RegCliente))
                Mensaje(23, "CLIENTE NO REGISTRADO");
            else
                if (!ObjCliente.InformacionActiva())
                    Mensaje( 23, "CLIENTE ESTA ANULADO");
                else{
                    MuestraDatosCliente();
                    Listado();
                }
        }
    }while (voIngresaClave);
}

//---------------------------------------------------------

int cListPreCli::InformacionMostrable(){
    mDevuelveRegistro(RegPrestamo);
    return (RegPrestamo.Estado && strcmp(RegPrestamo.LibretaElec, RegCliente.LibretaElec) == 0);
}

//--------------------------------------------------

void cListPreCli::FormatoListado(){
    BorraArea( 1,4,80,23);
    EscribeCad( 1,4,"L.ELECTORAL:	CLIENTE : ");
    EscribeCad( 1,5, "FECHA ING. :	DIRECCION: ");
    EscribeCad( 1,6, "ULT. SALDO : ");
    EscribeCad(30,6, "PRESTAMOS: PRES.ACTUAL: ");
}

//------------------------------------------------

int cListPreCli::IngresaClave() {
    char voTeclaSalida;
    cCadena voCadena;

    strcpy(RegCliente.LibretaElec,voCadena.Espacios(8));
    strcpy(RegCliente.LibretaElec, reinterpret_cast<const char*>(IngresaCad( 14,4,8)));
    return (strlen(RegCliente.LibretaElec) > 0);
}

//-------------------------------------------

void cListPreCli::MuestraDatosCliente(){
    char apynomb[80];
    cCadena voCadena;

    strcpy(apynomb, voCadena.SinBlancosDer(RegCliente.Apellidos));
    strcat(apynomb," ");
    strcat(apynomb,voCadena.SinBlancosDer(RegCliente.Nombres));
    EscribeCad(41,4,apynomb);
    EscribeCad(14,5,FormatoFecha(RegCliente.FechaIng.dia,
                                RegCliente.FechaIng.mes,
                                RegCliente.FechaIng.anio));
    EscribeCad(41,5,RegCliente.Direccion);
    EscribeCad(14,6, FormatoNum(RegCliente.UltimoSaldo,2));
    EscribeCad(41,6, FormatoNum(RegCliente.Prestamos,0));
    if(RegCliente.PrestamoAct)
        EscribeCad(58,6, "SI TIENE");
    else
        EscribeCad(58,6, "NO TIENE");
}

//----------------------------------------------------

void cListPreCli::AsignarEncabezado(){
    char cadenas[10][80], cadena[256];
    cCadena voCadena;

    strcpy(cadenas[0],voCadena.ConBlancosDer( "PRE",       3));
    strcpy(cadenas[1],voCadena.ConBlancosIzq( "FECHA",    11));
    strcpy(cadenas[2],voCadena.ConBlancosIzq( "MONTO",    10));
    strcpy(cadenas[3],voCadena.ConBlancosIzq( "CUOTAS",    7));
    strcpy(cadenas[4],voCadena.ConBlancosIzq("INTERESES", 10));
    strcpy(cadenas[5],voCadena.ConBlancosIzq( "MENSUAL",  10));
    strcpy(cadenas[6],voCadena.ConBlancosIzq( "AMORTIZ.", 10));
    strcpy(cadenas[7],voCadena.ConBlancosIzq( "INTPAG.",  11));
    strcpy(cadenas[8],voCadena.ConBlancosIzq( "PAGOS",     5));

    int longitud;
    strcpy(cadena,cadenas[0]);
    longitud = strlen(cadenas[0]);
    for(int i=1; i<9; i++){
        strcat(cadena,cadenas[i]);
        longitud += strlen(cadenas[i]);
    }
    cadena[longitud] = '\0';
    AdicionarEncabezado(cadena);
}

//--------------------------------------------

char *cListPreCli::Informacion(){
    char cadenas[10][80], cadena[256];
    cCadena voCadena;

    strcpy(cadenas[0], reinterpret_cast<const char*>(AlineaDer(3,FormatoNum(RegPrestamo.NumPrestamo,0))));
    strcpy(cadenas[1], reinterpret_cast<const char*>(AlineaDer(11,FormatoFecha(RegPrestamo.FechaDePres.dia,
                                                RegPrestamo.FechaDePres.mes,
                                                RegPrestamo.FechaDePres.anio))));
    strcpy(cadenas[2], reinterpret_cast<const char*>(AlineaDer(10,FormatoNum(RegPrestamo.MontoDePres,2))));
    strcpy(cadenas[3], reinterpret_cast<const char*>(AlineaDer(7,FormatoNum(RegPrestamo.NumCuotas,0))));
    strcpy(cadenas[4], reinterpret_cast<const char*>(AlineaDer(10,FormatoNum(RegPrestamo.MontoDeInt,2))));
    strcpy(cadenas[5], reinterpret_cast<const char*>(AlineaDer(10,FormatoNum(RegPrestamo.Mensualidad,2))));
    strcpy(cadenas[6], reinterpret_cast<const char*>(AlineaDer(10,FormatoNum(RegPrestamo. TotalAmort,2))));
    strcpy(cadenas[7], reinterpret_cast<const char*>(AlineaDer(10,FormatoNum(RegPrestamo.TotalInt,2))));
    strcpy(cadenas[8], reinterpret_cast<const char*>(AlineaDer(6,FormatoNum(RegPrestamo.NumPagos,0))));

    int longitud;
    strcpy(cadena,cadenas[0]);
    longitud = strlen(cadenas[0]);
    for (int i=1; i<9; i++){
        strcat(cadena,cadenas[i]);
        longitud += strlen(cadenas[i]);
    }
    cadena[longitud] = '\0';
    return cadena;
}


void cListPreCli::mDevuelveRegCliente(sgStrLibElec pvLibretaElec, sRegCliente &prRegCliente){
    ObjCliente.mObtieneReg(pvLibretaElec, prRegCliente);
}

