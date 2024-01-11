#if !defined _uProLis5_h_
#define _uProLis5_h_

#include "uProCli.h" // para la estructura de cliente
#include "uProPres.h" // para la clase cMantSecPre
#include "uProPago.h" // para la clase cMantSecPag

// definición de la clase
class cListPagPre:public cMantSecPag
{
protected:
    cMantSecPre objPrestamo;
    sRegPrestamo RegPrestamo;
    sRegPago RegPago;
    sRegCliente RegCliente;
public:
    cListPagPre(); //constructor
    virtual void Ejecutar();
    ~cListPagPre(); //destructor
protected:
    virtual int InformacionMostrable();
    void FormatoListado();
    virtual int IngresaClave();
    void MuestraDatosPrestamo();
    void Totaliza();
    virtual void AsignarEncabezado();
    virtual void *Informacion();
    virtual void MensajeNoHayInfo();
}
#endif



