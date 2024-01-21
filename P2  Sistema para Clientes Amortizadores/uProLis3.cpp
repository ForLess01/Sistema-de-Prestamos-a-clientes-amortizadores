#include "uProLis3.h"
#include "uCadenas.h"

int cListPreCan::InformacionMostrable(){
    mDevuelveRegistro(RegPrestamo);
    return(RegPrestamo.Estado && RegPrestamo.NumCuotas == RegPrestamo.NumPagos);
}

void cListPreCan::MensajeNoHayInfo(){
    Mensaje(12, "No existen Prestamos Cancelados");
}
