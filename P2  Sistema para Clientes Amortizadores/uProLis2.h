#if !defined _uProLis2_h_
#define _uProLis2_h_

#include "uProPres.h"

class cListPreOto : public cMantSecPre{
protected:
    sRegPrestamo RegPrestamo;
public:
    cListPreOto();
    ~cListPreOto();
    virtual void Ejecuta();
protected:
    void Totaliza();
    virtual void MensajeNoHayInfo();
};

#endif
