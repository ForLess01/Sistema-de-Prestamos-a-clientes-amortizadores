#include "uProLis2.h"
#include "milib.h"
#include "uCadenas.h"

cListPreOto::cListPreOto(){
    ReiniciaLimites(4, 1, 23, 80, ListadoConFiltro);
    BorraArea(1, 4, 80, 23);
}


void cListPreOto::Ejecuta(){
    Totaliza();
    Listado();
}


void cListPreOto::Totaliza(){
    float voMontoDePres, voMontoDeInt, voTotalAmort, voTotalInt;
    cCadena voCadena;

    voMontoDePres = 0;
    voMontoDeInt = 0;
    voTotalAmort = 0;
    voTotalInt = 0;

    IrAlInicio();
    while(!FinDeListado()){
        LeerInformacion();
        mDevuelveRegistro(RegPrestamo);
        if(InformacionMostrable()){
            voMontoDePres += RegPrestamo.MontoDePres;
            voMontoDeInt += RegPrestamo.MontoDeInt;
            voTotalAmort += RegPrestamo.TotalAmort;
            voTotalInt += RegPrestamo.TotalInt;
        }
        IrAlSiguiente();
    }
    if(voMontoDePres > 0){
        EscribeCad(1, 25, voCadena.Espacios(79));
        EscribeCad(1, 25, "TOTALES --->");
        EscribeCad(15, 25, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(voMontoDePres, 2))));
        EscribeCad(35, 25, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(voMontoDeInt, 2))));
        EscribeCad(53, 25, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(voTotalAmort, 2))));
        EscribeCad(63, 25, reinterpret_cast<const char*>(AlineaDer(10, FormatoNum(voTotalInt, 2))));
    }
}

cListPreOto::~cListPreOto(){
    cCadena voCadena;
    EscribeCad(1, 25, voCadena.Espacios(79));
}

void cListPreOto::MensajeNoHayInfo(){
    Mensaje(12, "No se ha Otorgado Prestamo Alguno");
}
