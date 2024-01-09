/**********************************************************************
Archivo de desarrollo : uProlis2.cpp
*********************************************************************/
#include "uProlis2.h"
#include "Milib.h"
#include "uCadenas.h"
// ----------------------------------------------------------------
cListPreOto :: cListPreOto()
{
    ReiniciaLimites( 4, 1 ,23,80, ListadoConFiltro );
    BorraArea( 1,4,80,23);
}
// ----------------------------------------------------------------
void cListPreOto :: Ejecuta()
{
    Totaliza();
    Listado();
}
// ----------------------------------------------------------------
void cListPreOto :: Totaliza()
{
float voMontoDePres, voMontoDeInt, voTotalAmort, voTotalInt;
cCadena voCadena;
// inicializa totales
voMontoDePres = O;
voMontoDeInt = O;
voTotalAmort = O;
voTotalInt = O;

// ir al inicio del archivo de pagos
IrAlInicio( );
while ( ! FinDeListado() )
{
LeerInformacion( );
mDevuelveRegistro( RegPrestamo );
// acumula totales
    if ( InformacionMostrable())
    {
        voMontoDePres += RegPrestamo.MontoDePres;
        voMontoDeInt += RegPrestamo.MontoDeInt;
        voTotalAmort += RegPrestamo.TotalAmort;
        voTotalInt += RegPrestamo.TotalInt;
    }
IrAlSiguiente();
}
    if (voMontoDePres > O)
    {
            EscribeCad( 1, 25, voCadena. Espacios(79) );
            EscribeCad( 1,25, "TOTALES ···>");
            EscribeCad( 15, 25,AlineaDer( 10, FormatoNum( voMontoDePres , 2)) );
            EscribeCad( 32, 25,AlineaDer( 10, FormatoNum( voMontoDeInt , 2)) );
            EscribeCad( 53,25,AlineaDer( 10, FormatoNum(voTotalAmort ,2)));
            EscribeCad( 63, 25,AlineaDer( 10, FormatoNum( vo TotalInt , 2)) );
    }
} 
// ----------------------------------------------------------------
cListPreOto :: ~cListPreOto()
{
    cCadena voCadena;
    EscribeCad( 1, 25, voCadena.Espacios( 79) );
} 
// ----------------------------------------------------------------
void clistPreOto :: MensajeNoHayInfo()
{
    Mensaje( 12, "No se ha Otorgado Prestamo alguno");
}
// ----------------------------------------------------------------

