#include "uProLis4.h"
// -----------------------------------
int cListPrePen :: InformacionMostrable(){
    mDevuelveRegistro( RegPrestamo );
    return (RegPrestamo.Estado &&
    RegPrestamo.NumCuotas != RegPrestamo.NumPagos);
}
//-------------------------------------
void clistPrePen :: MensajeNoHayInfo()
{
    Mensaje( 12, "No existen Prestamos Pendientes de Pago");
}