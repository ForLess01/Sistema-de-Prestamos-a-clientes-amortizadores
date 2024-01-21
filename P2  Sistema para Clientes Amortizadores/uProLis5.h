#if !defined _uProLis5_h_
#define _uProLis5_h_

#include "uProCli.h"
#include "uProPres.h"
#include "uProPago.h"

class cListPagPre : public cMantSecPag{
protected:
    cMantSecPre ObjPrestamo;
    sRegPrestamo RegPrestamo;
    sRegPago RegPago;
    sRegCliente RegCliente;
public:
    cListPagPre();
    virtual void Ejecuta();
    ~cListPagPre();
protected:
    virtual int InformacionMostrable();
    void FormatoListado();
    virtual int IngresaClave();
    void MuestraDatosPrestammo();
    void Totaliza();
    virtual void AsignarEncabezado();
    virtual char *Informacion();
    virtual void MensajeNoHayInfo();
};

#endif
