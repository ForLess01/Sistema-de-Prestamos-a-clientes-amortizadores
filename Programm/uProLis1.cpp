#include "uProLis1.h"
// ----------------------------------------------------------------
clistPreCli :: clistPreCli()
{
    if (mTodoCorrecto( ))
    {
        if (! ObjCliente.mTodoCorrecto())
            mRegistraError( );
        else
            ReiniciaLimites(7, 1, 23, 80, ListadoConFiltro );
    }
} 
// ----------------------------------------------------------------
void cListPreCli :: Ejecuta()
{
int voIngresaClave;
do {
    FormatoListado();
    voIngresaClave = IngresaClave();
    if (voIngresaClave)
    {
        if ( ! ObjCliente.mObtieneReg( RegCliente.LibretaElec, RegCliente))
            Mensaje(23, "CLIENTE NO REGISTRADO");
        else
            if (! ObjCliente.InformacionActiva())
            Mensaje(23, "CLIENTE ESTA ANULADO");
        else
        {
            MuestraDatosCliente( );
           Listado();
        }
    }
}while ( voIngresaClave );
}
// ----------------------------------------------------------------
int cListPreCli :: InformacionMostrable()
{
    mDevuelveRegistro( RegPrestamo );
    return (RegPrestamo.Estado &&
        strcmp( RegPrestamo.LibretaElec, RegCliente.LibretaElec )==0 );
}
// ----------------------------------------------------------------
void cListPreCli :: Formatolistado()
{
    BorraArea( 1,4,80,23);
    EscribeCad( 1,4, "L.ELECTORAL: CLIENTE : ");
    EscribeCad( 1,5, "FECHA ING. : DIRECCION: ");
    EscribeCad( 1,6, "ULT. SALDO : ");
    EscribeCad(30,6, "PRESTAMOS: PRES.ACTUAL: ");
}
// ----------------------------------------------------------------
int cListPreCli :: IngresaClave()
{
    char voTeclaSalida;
    cCadena voCadena;
    strcpy( RegCliente.LibretaElec,voCadena.Espacios(8) );
    strcpy( RegCliente.LibretaElec,lngresaCad(14,4,8) );
    return ( strlen( RegCliente.LibretaElec) > O);
}
// ----------------------------------------------------------------
voidcListPreCli :: MuestraDatosCliente()
{
    char apynomb[80];
    cCadena voCadena;
    strcpy( apynomb,voCadena.SinBlancosDer( RegCliente.Apellidos) );
    strcat( apynomb," ");
    strcat( apynomb,voCadena.SinBlancosDer( RegCliente.Nombres) );
    EscribeCad(41,4,apynomb);
    EscribeCad( 14,5,FomuitoFecha(RegCliente.FechaIng.dia,
        RegCliente.FechaIng.mes,
        RegCliente.FechaIng.anio) );
    EscribeCad( 41,5, RegCliente.Direccion);
    EscribeCad( 14,6, FormatoNum( RegCliente.UltimoSaldo,2) );
    EscribeCad( 41,6, FormatoNum( RegCliente.Prestamos,0));
    if(RegCliente.PrestamoAct)
        EscribeCad(58,6, "SI TIENE");
    else
    EscribeCad( 58,6, "NO TIENE");
}
// ----------------------------------------------------------------
void cListPreCLi :: AsignarEncabezado()
{
    char cadenas[10][80 ], cadena[256];
    cCadena voCadena;
    strcpy( cadenas[0], voCadena.ConBlancosDer( "PRE", 3)); 
    strcpy( cadenas[1], voCadena.ConBlancosIzq( "FECHA", 11));
    strcpy( cadenas[2], voCadena.ConBlancosIzq( "MONTO", 10));
    strcpy( cadenas[3], voCadena.ConBlancosIzq( "CUOTAS", 7));
    strcpy( cadenas[4], voCadena.ConBlancosIzq( "lNTERESES", 10));
    strcpy( cadenas[5], voCadena.ConBlancosIzq("MENSUAL ", /0)); 
    strcpy( cadenas[6], voCadena.ConBlancosIzq("AMORTJZ. ", 10));
    strcpy( cadenas[7], voCadena.ConBlancosIzq( "INTPAG. ", 11));
    strcpy( cadenas[8] , voCadena.ConBlancosIzq( "PAGOS", 5));

    int Longitud;
    strcpy( cadena,cadenas[0]);
    Longitud = strlen( cadenas[0]);
    
    for(int i = /; i < 9; i++)
    {
        strcat(cadena,cadenas[i]);
        Longitud+= strlen(cadenas[i]);
    }

cadena[Longitud] = \0';
AdicionarEncabezado(cadena);
}
// ----------------------------------------------------------------
char *cListPreCli :: lnformacion()
{
    char cadenas[10][80], cadena[256];
    cCadena voCadena;

    strcpy( cadenas[O].AlineaDer( 3,FormatoNum( RegPrestamo.NumPrestamo,0)) );
    strcpy( cadenas[1],AlineaDer( 11,FormatoFecha( RegPrestamo.FechaDePres.dia,
                                                   RegPrestamo.FechaDePres.mes,
                                                   RegPrestamo.FechaDePres.anio)) );
    strcpy( cadenas[2],AlineaDer( 10, FormatoNum( RegPrestamo.MontoDePres,2)) );
    strcpy( cadenas[3],AlineaDer(7, FormatoNum( RegPrestamo.NumCuotas,0)) );
    strcpy( cadenas[4],AlineaDer( 10,FormatoNum( RegPrestamo.MontoDelnt,2 )));
    strcpy(cadenas[5],AlineaDer( 10,FormatoNum(RegPrestamo.Mensualidad,2)));
    strcpy( cadenas[6],AlineaDer( 10,FormatoNum( RegPrestamo.TotalAmort,2)));
    strcpy( cadenas[7],AlineaDer( 10,FormatoNum( RegPrestamo.TotalInt,2)));
    strcpy( cadenas[8],AlineaDer( 6,FormatoNum( RegPrestamo.NumPagos,0 )));
    
    int Longitud;
    strcpy( cadena.cadenas[0]);
    Longitud = strlen(cadenas[0]);

    for (int i = 1; i < 9; i++)
    {
        strcat( cadena,cadenas[i] );
        Longitud += strlen(cadenas[i]);
    }
    cadena[Longitud] = \0';
    return cadena;
}
// ----------------------------------------------------------------
void cListPreCli :: mDevuelveRegCliente(sgStrLibElec pvLibretaElec,
sRegCliente &prRegCliente)
{
    ObjCliente.mObtieneReg(pvLibretaElec, prRegCliente);
} 
// ----------------------------------------------------------------

