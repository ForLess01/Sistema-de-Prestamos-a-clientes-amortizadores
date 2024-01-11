#include "uProLis6.h" // para la clase cListPagos

void cListPago :: Ejecuta()
{
    Totaliza();
    Listado();
}
//--------------------------------------------------------------------------
int cListPagos :: InformacionMostrable()
{
    mDevuelveRegistro(RegPago);
    return (RegPago.Estado);
}
//--------------------------------------------------------------------------
void cListPagos :: MensajeNoHayInfo()
{
    Mensaje(12,"NO  se ha realizado Pago alguno");
}
//--------------------------------------------------------------------------