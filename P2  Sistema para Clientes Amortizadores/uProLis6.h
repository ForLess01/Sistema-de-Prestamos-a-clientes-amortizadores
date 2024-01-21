#if !defined _uProLis6_h_
#define _uProLis6_h_

#include "uProLis5.h"
#include "uProPago.h"

class cListPagos:public cListPagPre{
private:
    sRegPago RegPago;

public:
    cListPagos(){ReiniciaLimites(4, 1, 23, 80);}
    virtual void Ejecuta();
    virtual int InformacionMostrable();
    virtual void MensajeNoHayInfo();
};

#endif
