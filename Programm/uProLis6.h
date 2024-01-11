#if ! defin ed _uProLis6 h_
#define _uProLis6_h_ // definición de la clase
#include "uProLis5.h" // para la clase cListPagPre
#include "uProPago.h"   // para la estructura del registro de pago

class cListPagos : public cListPagPre
{
private:
    sRegPago RegPago;
public:
    cListPagos() { ReiniciaLimites(4,J,23,80); }
    virtual void Ejecuta();
    virtual int InformacionMostrable();
    virtual void MensajeNoHayInfo ();
};
#endif