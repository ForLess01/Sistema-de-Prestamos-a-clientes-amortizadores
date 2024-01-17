#include "uProLis5.h"

// ----------------------------------------------------------------

cListPagPre :: cListPagPre()
{
    ReiniciaLimites(7,1,23,80,ListadoConFiltro);
    if(!mTodoCorrecto())
    {
        if(!objPrestamo.mTodoCorrecto())
            mRegistraError();
    }
}
// ----------------------------------------------------------------
void cListPagPre :: Ejecuta()
{
    int voIngresaClave;
    do
    {
        FormatoListado();
        voIngresaClave = IngresaClave();
        if(voIngresaClave)
        {
            if(!objPrestamo.mObtieneReg(RegPrestamo.NumPrestamo,RegPrestamo))
                Mensaje(25,"PRESTAMO NO REGISTRADO");
            else
                if(!objPrestamo.InformacionActiva())
                    Mensaje(25,"PRESTAMO ESTA ANULADO");
                else
                {
                    MuestraDatosPrestamo();
                    Totaliza();
                    Listado();
                }
        }
    }while(voIngresaClave);
}
//----------------------------------------------------------------
cListPagPre :: ~cListPagPre()
{
    cCadena voCadena;
    if (mTodoCorrecto())
    {
        EscribeCad(1,25,voCadena.Espacios(79));
    }
}
// ----------------------------------------------------------------
int cListPagPre :: InformacionMostrable()
{
    mDevuelveRegistro(RegPago);
    retrun (RegPago.Estado && (RegPago.NumPrestamo == RegPrestamo.NumPrestamo));
}
// ----------------------------------------------------------------
void cListPagPre :: FormatoListado()
{
    cCadena voCadena;
    BorraArea(1,4,80,23);
    EscribeCad( 1, 25, voCadena.Espacios(79) );
    CentraCad( 25, "Presione solo ENTER en el prestamo para salir");
    EscribeCad( 1,4, "PRESTAMO : ");
    EscribeCad( 1,5, "FECHA : ");
    EscribeCad(40,5, "Pagos : ");
    EscribeCad(55,5, "Mensualidad: ");
    EscribeCad(40,6, "Cuotas: ");
    EscribeCad( 1,6, "DEUDA : ");
    EscribeCad(55,6, "SALDO : ");
}
// ----------------------------------------------------------------
int cListPagPre :: IngresaClave()
{
    RegPrestamo.NumPrestamo = IngresaEnt(14,4,3);
    return (RegPrestamo.NumPrestamo != 0);
}
// ----------------------------------------------------------------
void cListPagPre :: MuestraDatosPrestamo()
{
    cCadena voCadena;

    strcpy(RegCliente.LibretaElec,RegPrestamo.LibretaElec);
    objPrestamo.mDevuelveCliente(RegCliente);
    char apynomb[80];
    strcat(apynomb,RegCliente.Apellidos);
    strcat(apynomb," ");
    strcat(apynomb,RegCliente.Nombres);

    EscribeCad(20,4,voCadena.SinBlancosDer(apynomb));
    EscribeCad(14,5,FormatoFecha(RegPrestamo.FechaDePres.dia,RegPrestamo.FechaDePres.mes,RegPrestamo.FechaDePres.anio));
    EscribeCad(47,5,AlineaDer(3,FormatoNum(RegPrestamo.NumPagos,0)));
    EscribeCad(70,5,AlineaDer(10,FormatoNum(RegPrestamo.Mensualidad,2)));
    EscribeCad(47,6,AlineaDer(3,FormatoNum(RegPrestamo.NumCuotas,0)));

    EscribeCad(14,6,FormatoNum(RegPrestamo.MontoDePres+RegPrestamo/MontoDeInt,2));
    EscribeCad(70,6,AlineaDer(10,FormatoNum(RegPrestamo.MontoDePres+RegPrestamo.MontoDeInt-RegPrestamo.TotalAmort-RegPrestamo.TotalInt,2)));
}
// ----------------------------------------------------------------
void cListPagPre :: Totaliza()
{
    float voTotImpDePago, voTotImpDeInt, voTotImpDeAmort;
    cCadena voCadena;

    //inicializa los totales
    voTotImpDeAmort=0;
    voTotImpDeInt=0;
    voTotImpDePago=0;

    //ir al inicio del archivo de pagos
    IrAlInicio();
    while(!FinDeListado())
    {
        LeerInformacion();
        mDevuelveRegistro(RegPago);
        if(InformacionMostrable())
        {
            voTotImpDePago+=RegPago.ImpDePago;
            voTotImpDeInt+=RegPago.ImpDeInt;
            voTotImpDeAmort+=RegPago.ImpDeAmort;
        }
        IrAlSiguiente();
    }

    if(voTotImpDePago>0)
    {
        EscribeCad(1,25,voCadena.Espacios(79));
        EscribeCad(1,25,"TOTALES --->");
        EscribeCad(19,25,AlineaDer(10,FormatoNum(voTotImpDePago,2)));
        EscribeCad(30,25,AlineaDer(10,FormatoNum(voTotImpDeInt,2)));
        EscribeCad(40,25,AlineaDer(10,FormatoNum(voTotImpDeAmort,2)));
    }
}
// ----------------------------------------------------------------
void cListPagPre :: AsignarEncabezado();
{
    char cadenas [6][20],voEncab[256];
    cCadena voCadena;

    strcpy(cadenas[0],voCadena.ConBlancosDer("PAGO",3));
    strcpy(cadenas[1],voCadena.ConBlancosIzq("PRE",6));
    strcpy(cadenas[2],voCadena.ConBlancosIzq("FECHA",9));
    strcpy(cadenas[3],voCadena.ConBlancosIzq("IMPORTE",10));
    strcpy(cadenas[4],voCadena.ConBlancosIzq("INTERES",10));
    strcpy(cadenas[5],voCadena.ConBlancosIzq("AMORTIZ",10));

    int longitud= strlen(cadenas[0]);
    strcpy(voEncab,cadenas[0]);
    for(int i=1;i<6;i++)
    {
        strcat(voEncab,cadenas[i]);
        longitud+=strlen(cadenas[i]);
    }
    EnCad[longitud]='\0';

    AdicionarEncabezado(voEncab);
}
// ----------------------------------------------------------------
char *cListPagPre::Informacion()
{
    char cadenas [6][20],voInfo[256];
    cCadena voCadena;

    mDevuelveRegistro(RegPago);

    strcpy(cadenas[0],voCadena.ConBlancosIzq(FormatoNum(RegPago.NumPago,0),3));
    strcpy(cadenas[1],voCadena.ConBlancosIzq(FormatoNum(RegPago.NumPrestamo,0),3));
    strcpy(cadenas[2],voCadena.ConBlancosIzq(FormatoFecha(RegPago.FechaDePago.dia,RegPago.FechaDePago.mes,RegPago.FechaDePago.anio),12));
    strcpy(cadenas[3],voCadena.ConBlancosIzq(FormatoNum(RegPago.ImpDePago,2),10));
    strcpy(cadenas[4],voCadena.ConBlancosIzq(FormatoNum(RegPago.ImpDeInt,2),10));
    strcpy(cadenas[5],voCadena.ConBlancosIzq(FormatoNum(RegPago.ImpDeAmort,2),10));

    int longitud= strlen(cadenas[0]);
    strcpy(voInfo,cadenas[0]);
    for(int i=1;i<6;i++)
    {
        strcat(voInfo,cadenas[i]);
        longitud+=strlen(cadenas[i]);
    }
    voInfo[longitud]='\0';
    return voInfo;
}
// ----------------------------------------------------------------
void cListPagPre :: MensajeNoHayInfo()
{
    Mensaje(12,"Cliente NO se ha realizado Pago alguno");
}
// ----------------------------------------------------------------
